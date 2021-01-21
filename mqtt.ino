
#include <WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.


WiFiClient espClient;
PubSubClient MQTTclient(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
int MQTTconnectionTimer = 1;
int MQTTPortInUse = 0;

void setupMQTT() {
  if(MqttPort==0) return;                     // do not try to connect if port is zero
  MQTTclient.setServer(MqttServer, MqttPort);
  MQTTclient.setCallback(callback);
  MQTTconnectionTimer = millis()-5000;
  MQTTPortInUse = MqttPort;
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if(strcmp(topic, R1Topic)==0) {
    if ((char)payload[0] == '1') digitalWrite(Rly1, HIGH);    // Switch on the Relay if an 1 was received as first character
    else digitalWrite(Rly1, LOW); 
  }
  if(strcmp(topic, R2Topic)==0) {
    if ((char)payload[0] == '1') digitalWrite(Rly2, HIGH);
    else digitalWrite(Rly2, LOW); 
  }
  if(strcmp(topic, R3Topic)==0) {
    if ((char)payload[0] == '1') digitalWrite(Rly3, HIGH);
    else digitalWrite(Rly3, LOW); 
  }
  if(strcmp(topic, R4Topic)==0) {
    if ((char)payload[0] == '1') digitalWrite(Rly4, HIGH);
    else digitalWrite(Rly4, LOW); 
  }
  if(strcmp(topic, R5Topic)==0) {
    if ((char)payload[0] == '1') digitalWrite(Rly5, HIGH);
    else digitalWrite(Rly5, LOW); 
  }
  if(strcmp(topic, R6Topic)==0) {
    if ((char)payload[0] == '1') digitalWrite(Rly6, HIGH);
    else digitalWrite(Rly6, LOW); 
  }
  if(strcmp(topic, R7Topic)==0) {
    if ((char)payload[0] == '1') digitalWrite(Rly7, HIGH);
    else digitalWrite(Rly7, LOW); 
  }
  if(strcmp(topic, R8Topic)==0) {
    if ((char)payload[0] == '1') digitalWrite(Rly8, HIGH);
    else digitalWrite(Rly8, LOW); 
  }
}

void reconnect() {
    if(WiFi.status() != WL_CONNECTED) return; //WIFI disconnected so don't attempt reconnect
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (MQTTclient.connect(MqttID,MqttUser,MqttPasswd)) {
      Serial.println("connected");
      
// subscribe
      MQTTclient.subscribe(R1Topic);
      MQTTclient.loop();
      MQTTclient.subscribe(R2Topic);
      MQTTclient.loop();
      MQTTclient.subscribe(R3Topic);
      MQTTclient.loop();
      MQTTclient.subscribe(R4Topic);
      MQTTclient.loop();
      MQTTclient.subscribe(R5Topic);
      MQTTclient.loop();
      MQTTclient.subscribe(R6Topic);
      MQTTclient.loop();
      MQTTclient.subscribe(R7Topic);
      MQTTclient.loop();
      MQTTclient.subscribe(R8Topic);
      MQTTclient.loop();
    } else {
      Serial.print("failed, rc=");
      Serial.print(MQTTclient.state());
      Serial.println(" try again in 10 seconds");
    }
}



void modeMQTT() {
char Inp;
char Msg[] = "0";
static int x=0;


if(MQTTPortInUse != MqttPort){
  setupMQTT();
  return;
}

if (MQTTclient.connected()) {
    switch(x) {
      case 0:
        Inp = digitalRead(Inp1);                          // read the input
        if(Inp != Inputs[0]) {                            // if its changed ..
          Inputs[0] = Inp;                                // store new state
          msg[0] = Inp+0x30;    // convert to ASCII       // generate MQTT message
          MQTTclient.publish(N1Topic, msg, true);             // and publish it
        }
        break;      
      case 1:
        Inp = digitalRead(Inp2);
        if(Inp != Inputs[1]) {
          Inputs[1] = Inp;
          msg[0] = Inp+0x30;    // convert to ASCII
          MQTTclient.publish(N2Topic, msg, true);
        }
        break;      
      case 2:
        Inp = digitalRead(Inp3);
        if(Inp != Inputs[2]) {
          Inputs[2] = Inp;
          msg[0] = Inp+0x30;    // convert to ASCII
          MQTTclient.publish(N3Topic, msg, true);
        }
        break;      
      case 3:
        Inp = digitalRead(Inp4);
        if(Inp != Inputs[3]) {
          Inputs[3] = Inp;
          msg[0] = Inp+0x30;    // convert to ASCII
          MQTTclient.publish(N4Topic, msg, true);
        }
        break;      
      case 4:
        Inp = digitalRead(Inp5);
        if(Inp != Inputs[4]) {
          Inputs[4] = Inp;
          msg[0] = Inp+0x30;    // convert to ASCII
          MQTTclient.publish(N5Topic, msg, true);
        }
        break;      
      case 5:
        Inp = digitalRead(Inp6);
        if(Inp != Inputs[5]) {
          Inputs[5] = Inp;
          msg[0] = Inp+0x30;    // convert to ASCII
          MQTTclient.publish(N6Topic, msg, true);
        }
        break;      
      case 6:
        Inp = digitalRead(Inp7);
        if(Inp != Inputs[6]) {
          Inputs[6] = Inp;
          msg[0] = Inp+0x30;    // convert to ASCII
          MQTTclient.publish(N7Topic, msg, true);
        }
        break;      
      default:
        Inp = digitalRead(Inp8);
        if(Inp != Inputs[7]) {
          Inputs[7] = Inp;
          msg[0] = Inp+0x30;    // convert to ASCII
          MQTTclient.publish(N8Topic, msg, true);
        }
        break;      
    }
    if(++x > 7) x=0;      // bump to next input to process
    MQTTclient.loop();
  }
  else {
    if(MqttPort==0) return;                     // do not try to connect if port is zero  
    if(millis()-MQTTconnectionTimer<10000) return;
    reconnect();
    MQTTconnectionTimer = millis();
  }
}
