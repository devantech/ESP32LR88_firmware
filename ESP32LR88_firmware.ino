
/******************************************************************************
 * V1.6
 * Added MQTT Username and Password
 * See MU and MW commands
 ******************************************************************************/

#include <Preferences.h>
#include <WiFi.h>

const char ver[] = {"1.6"};
const char moduleID = 41;       // ESP32LR20 = 39, LR42=40, LR88=41

Preferences nvm;
WiFiServer server(80);
WiFiServer tcpServer(0);

IPAddress local_IP(192, 168, 0, 121);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8); //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional

#define Rly1  33
#define Rly2  25
#define Rly3  26
#define Rly4  27
#define Rly5  14
#define Rly6  12
#define Rly7  13
#define Rly8  2

#define Inp1  4
#define Inp2  16
#define Inp3  17
#define Inp4  5
#define Inp5  18
#define Inp6  19
#define Inp7  21
#define Inp8  22

#define Led 23
#define BUFSIZE 51

char buffer[BUFSIZE];
char ssid[BUFSIZE];
char WifiPassword[BUFSIZE];
char password2[BUFSIZE];
uint AsciiPort;
char MqttServer[BUFSIZE];
char MqttID[BUFSIZE];
uint MqttPort;
char MqttUser[BUFSIZE];
char MqttPasswd[BUFSIZE];
char mqttpasswd2[BUFSIZE];
char R1Topic[BUFSIZE];    // Relay topics
char R2Topic[BUFSIZE];
char R3Topic[BUFSIZE];
char R4Topic[BUFSIZE];
char R5Topic[BUFSIZE];
char R6Topic[BUFSIZE];
char R7Topic[BUFSIZE];
char R8Topic[BUFSIZE];
char N1Topic[BUFSIZE];    // Input topics
char N2Topic[BUFSIZE];
char N3Topic[BUFSIZE];
char N4Topic[BUFSIZE];
char N5Topic[BUFSIZE];
char N6Topic[BUFSIZE];
char N7Topic[BUFSIZE];
char N8Topic[BUFSIZE];
char AsciiPassword[BUFSIZE];

char Inputs[8] = {2,2,2,2,2,2,2,2};
 
void setup()
{
    pinMode(Rly1, OUTPUT);      // set the pin modes
    pinMode(Rly2, OUTPUT);
    pinMode(Rly3, OUTPUT);
    pinMode(Rly4, OUTPUT);
    pinMode(Rly5, OUTPUT);
    pinMode(Rly6, OUTPUT);
    pinMode(Rly7, OUTPUT);
    pinMode(Rly8, OUTPUT);
    pinMode(Led, OUTPUT);
    digitalWrite(Rly1, LOW);
    digitalWrite(Rly2, LOW);
    digitalWrite(Rly3, LOW);
    digitalWrite(Rly4, LOW);
    digitalWrite(Rly5, LOW);
    digitalWrite(Rly6, LOW);
    digitalWrite(Rly7, LOW);
    digitalWrite(Rly8, LOW);
    digitalWrite(Led, HIGH);
    pinMode(Inp1, INPUT);
    pinMode(Inp2, INPUT);
    pinMode(Inp3, INPUT);
    pinMode(Inp4, INPUT);
    pinMode(Inp5, INPUT);
    pinMode(Inp6, INPUT);
    pinMode(Inp7, INPUT);
    pinMode(Inp8, INPUT);
    
    Serial.begin(115200);
    delay(10);
    
    wifi_connect();
}


void loop(){
  modeHttp();
  modeAscii();
  modeMQTT();
  serialMonitor();
  if(WiFi.status() != WL_CONNECTED) wifi_connect(); 
}

void wifi_connect(void)
{
    unsigned int x;
    
    digitalWrite(Led, HIGH);
    Serial.println("");
    nvm.begin("devantech", false);    // Note: Namespace name is limited to 15 chars
    local_IP = nvm.getUInt("IPAddress", 0);
    gateway = nvm.getUInt("GateWay", 0);
    subnet = nvm.getUInt("SubNet", 0);
    primaryDNS = nvm.getUInt("primaryDNS", 0);
    secondaryDNS = nvm.getUInt("secondaryDNS", 0);
    nvm.getString("ssid", ssid, sizeof(ssid)-1);
    nvm.getString("WifiPassword", WifiPassword, sizeof(WifiPassword)-1);
    strcpy(password2, "********");
    AsciiPort = nvm.getUInt("AsciiPort", 17123);
    nvm.getString("MqttServer", MqttServer, BUFSIZE-1);
    nvm.getString("MqttID", MqttID, BUFSIZE-1);
    nvm.getString("MqttUser", MqttUser, BUFSIZE-1);
    nvm.getString("MqttPasswd", MqttPasswd, BUFSIZE-1);
    strcpy(mqttpasswd2, "********");
    MqttPort = nvm.getUInt("MqttPort", 0);            // 0 means do not connect, normally should be 1883
    nvm.getString("R1Topic", R1Topic, BUFSIZE-1);    
    nvm.getString("R2Topic", R2Topic, BUFSIZE-1);    
    nvm.getString("R3Topic", R3Topic, BUFSIZE-1);    
    nvm.getString("R4Topic", R4Topic, BUFSIZE-1);    
    nvm.getString("R5Topic", R5Topic, BUFSIZE-1);    
    nvm.getString("R6Topic", R6Topic, BUFSIZE-1);    
    nvm.getString("R7Topic", R7Topic, BUFSIZE-1);    
    nvm.getString("R8Topic", R8Topic, BUFSIZE-1);    
    nvm.getString("N1Topic", N1Topic, BUFSIZE-1);    
    nvm.getString("N2Topic", N2Topic, BUFSIZE-1);    
    nvm.getString("N3Topic", N3Topic, BUFSIZE-1);    
    nvm.getString("N4Topic", N4Topic, BUFSIZE-1);    
    nvm.getString("N5Topic", N5Topic, BUFSIZE-1);    
    nvm.getString("N6Topic", N6Topic, BUFSIZE-1);    
    nvm.getString("N7Topic", N7Topic, BUFSIZE-1);    
    nvm.getString("N8Topic", N8Topic, BUFSIZE-1);   
    nvm.getString("AsciiPassword", AsciiPassword, BUFSIZE-1);      

    // We start by connecting to a WiFi network
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.println("...");

    if(local_IP != 0) {
      if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
        Serial.println("STA Failed to configure");
      }
    }
    WiFi.mode(WIFI_STA);

    while(WiFi.status() != WL_CONNECTED){
      WiFi.disconnect();
      delay(100);     
      WiFi.begin(ssid, WifiPassword);
      for(x = 0; x < 300; x++){
        delay(10);
        serialMonitor();
      }
    }
    digitalWrite(Led, LOW);
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    server.begin();
    tcpServer.close();
    tcpServer = WiFiServer(AsciiPort);
    tcpServer.begin();
    setupMQTT();   
}
