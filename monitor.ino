
enum cmds { CMD_NONE, CMD_ST, CMD_RB, CMD_IP, CMD_SB, CMD_GW, CMD_AP, CMD_PD, CMD_SD, CMD_SS, CMD_PW, CMD_PA, CMD_MS, CMD_MP, CMD_MU, CMD_MW, CMD_MD, 
            CMD_R1, CMD_R2, CMD_R3, CMD_R4, CMD_R5, CMD_R6, CMD_R7, CMD_R8,
            CMD_N1, CMD_N2, CMD_N3, CMD_N4, CMD_N5, CMD_N6, CMD_N7, CMD_N8
          };

void serialMonitor(void)
{
IPAddress IP, IPZ;
char *p;
uint port;

  if(getMLine()) {
    int cmd = getCommand();
    switch(cmd) {
      case CMD_NONE:
        Serial.println("Unknown command:");
        Serial.println(buffer);
        break;
      case CMD_ST:
        Serial.println();
        Serial.println("Status:");
        Serial.print("Firmware Version: ");
        Serial.println(ver);
        Serial.print("IP: ");
        IP = nvm.getUInt("IPAddress", 0);
        Serial.print(IP.toString());
        IPZ.fromString("0.0.0.0");
        if( IP==IPZ ) {
          Serial.print(" (");
          Serial.print(WiFi.localIP());
          Serial.print(")");
        }
        Serial.println();
        Serial.print("Subnet: ");
        IP = nvm.getUInt("SubNet", 0);
        Serial.println(IP.toString());
        Serial.print("Gateway: ");
        IP = nvm.getUInt("GateWay", 0);
        Serial.println(IP.toString());
        Serial.print("Primary DNS: ");
        IP = nvm.getUInt("primaryDNS", 0);
        Serial.println(IP.toString());
        Serial.print("Secondary DNS: ");
        IP = nvm.getUInt("secondaryDNS", 0);
        Serial.println(IP.toString());
        Serial.print("SSID: ");
        Serial.println(ssid);
        Serial.print("WifiPassword: ");
        Serial.println(password2);
        Serial.print("AsciiPassword: ");
        Serial.println(AsciiPassword);
        Serial.print("ASCII TCP Port: ");
        Serial.println(AsciiPort);
        Serial.print("RSSI: ");
        Serial.print(WiFi.RSSI());
        Serial.println();
        Serial.print("MQTT Server: ");
        Serial.println(MqttServer);
        Serial.print("MQTT Port: ");
        Serial.println(MqttPort);
        Serial.print("MQTT ID: ");
        Serial.println(MqttID);
        Serial.print("MQTT User: ");
        Serial.println(MqttUser);
        Serial.print("MQTT Password: ");
        Serial.println(mqttpasswd2);
        Serial.print("Relay1 Topic: ");
        Serial.println(R1Topic);
        Serial.print("Relay2 Topic: ");
        Serial.println(R2Topic);
        Serial.print("Relay3 Topic: ");
        Serial.println(R3Topic);
        Serial.print("Relay4 Topic: ");
        Serial.println(R4Topic);
        Serial.print("Relay5 Topic: ");
        Serial.println(R5Topic);
        Serial.print("Relay6 Topic: ");
        Serial.println(R6Topic);
        Serial.print("Relay7 Topic: ");
        Serial.println(R7Topic);
        Serial.print("Relay8 Topic: ");
        Serial.println(R8Topic);
        Serial.print("Input1 Topic: ");
        Serial.println(N1Topic);
        Serial.print("Input2 Topic: ");
        Serial.println(N2Topic);
        Serial.print("Input3 Topic: ");
        Serial.println(N3Topic);
        Serial.print("Input4 Topic: ");
        Serial.println(N4Topic);
        Serial.print("Input5 Topic: ");
        Serial.println(N5Topic);
        Serial.print("Input6 Topic: ");
        Serial.println(N6Topic);
        Serial.print("Input7 Topic: ");
        Serial.println(N7Topic);
        Serial.print("Input8 Topic: ");
        Serial.println(N8Topic);
        break;
      case CMD_RB:
        Serial.println("Re-Booting.. .");
        delay(500);
        esp_restart();
        break;       
      case CMD_IP:
        p = getStrPtr(&buffer[3]);
        if(p) {
          IP = getIP(p);
          nvm.putUInt("IPAddress", IP);
          Serial.print(" OK. Saved IP Address: "); 
          Serial.println(IP.toString());
        }
        break;
      case CMD_SB:
        p = getStrPtr(&buffer[3]);
        if(p) {
          IP = getIP(p);
          nvm.putUInt("SubNet", IP);
          Serial.print("OK. Saved Subnet Mask: "); 
          Serial.println(IP.toString());
        }
        break;
      case CMD_GW:
        p = getStrPtr(&buffer[3]);
        if(p) {
          IP = getIP(p);
          nvm.putUInt("GateWay", IP);
          Serial.print("OK. Saved Gateway Address: "); 
          Serial.println(IP.toString());
        }
        break;
      case CMD_PD:
        p = getStrPtr(&buffer[3]);
        if(p) {
          IP = getIP(p);
          nvm.putUInt("primaryDNS", IP);
          Serial.print("OK. Saved Primary DNS: "); 
          Serial.println(IP.toString());
        }
        break;
      case CMD_SD:
        p = getStrPtr(&buffer[3]);
        if(p) {
          IP = getIP(p);
          nvm.putUInt("secondaryDNS", IP);
          Serial.print("OK. Saved Secondary DNS: "); 
          Serial.println(IP.toString());
        }
        break;
      case CMD_SS:
        p = getStrPtr(&buffer[3]);
        if(p) {
          nvm.putString("ssid", p);
          nvm.getString("ssid", ssid, sizeof(ssid)-1);
          Serial.print("OK. Saved SSID: "); 
          Serial.println(ssid);  
          WiFi.disconnect();  
        }
        else Serial.println("SSID string not found");    
        break;
      case CMD_PW:
        p = getStrPtr(&buffer[3]);
        if(p) {
          nvm.putString("WifiPassword", p);
          nvm.getString("WifiPassword", WifiPassword, sizeof(WifiPassword)-1);
          strcpy(password2, WifiPassword);
          Serial.print("OK. Saved WifiPassword: "); 
          Serial.println(password2);   
          WiFi.disconnect(); 
        }
        else Serial.println("WifiPassword string not found");    
        break;
      case CMD_AP:
        p = getStrPtr(&buffer[3]);
        if(p) {
          nvm.putString("AsciiPassword", p);
          nvm.getString("AsciiPassword", AsciiPassword, sizeof(AsciiPassword)-1);
          Serial.print("OK. Saved AsciiPassword: "); 
          Serial.println(AsciiPassword);    
          WiFi.disconnect();
        }
        else Serial.println("AsciiPassword string not found");    
        break;
      case CMD_PA:
        AsciiPort = getNumber(&buffer[3]);
        nvm.putUInt("AsciiPort", AsciiPort);
        Serial.print("OK. Saved ASCII port number: "); 
        Serial.println(AsciiPort);  
        tcpServer.close();
        tcpServer = WiFiServer(AsciiPort);
        tcpServer.begin();  
        break;
      case CMD_MS:
        p = getStrPtr(&buffer[3]);
        if(p) {
          nvm.putString("MqttServer", p);
          nvm.getString("MqttServer", MqttServer, BUFSIZE-1);
          Serial.print("OK. Saved MQTT Server: "); 
          Serial.println(MqttServer);    
        }
        else Serial.println("MQTT Server string not found");    
        break;
      case CMD_MD:
        p = getStrPtr(&buffer[3]);
        if(p) {
          nvm.putString("MqttID", p);
          nvm.getString("MqttID", MqttID, BUFSIZE-1);
          Serial.print("OK. Saved MQTT ID: "); 
          Serial.println(MqttID);    
        }
        else Serial.println("MQTT ID string not found");    
        break;
      case CMD_MP:
        MqttPort = getNumber(&buffer[3]);
        nvm.putUInt("MqttPort", MqttPort);
        Serial.print("OK. Saved MQTT port number: "); 
        Serial.println(MqttPort);  
        break;
      case CMD_MU:
        p = getStrPtr(&buffer[3]);
        if(p) {
          nvm.putString("MqttUser", p);
          nvm.getString("MqttUser", MqttUser, BUFSIZE-1);
          Serial.print("OK. Saved MQTT User: "); 
          Serial.println(MqttUser);    
        }
        else Serial.println("MQTT User string not found");    
        break;
        case CMD_MW:
        p = getStrPtr(&buffer[3]);
        if(p) {
          nvm.putString("MqttPasswd", p);
          nvm.getString("MqttPasswd", MqttPasswd, BUFSIZE-1);
          strcpy(mqttpasswd2, MqttPasswd);
          Serial.print("OK. Saved MQTT Password: "); 
          Serial.println(MqttPasswd);    
        }
        else Serial.println("MQTT Password string not found");    
        break;
      case CMD_R1:
        p = getStrPtr(&buffer[3]);
        if(p) {
          nvm.putString("R1Topic", p);
          nvm.getString("R1Topic", R1Topic, BUFSIZE-1);
          Serial.print("OK. Saved Relay 1 Topic: "); 
          Serial.println(R1Topic);    
        }
        else Serial.println("Relay 1 MQTT topic string not found");    
        break;
      case CMD_R2:
        p = getStrPtr(&buffer[3]);
        if(p) {
          nvm.putString("R2Topic", p);
          nvm.getString("R2Topic", R2Topic, BUFSIZE-1);
          Serial.print("OK. Saved Relay 2 Topic: "); 
          Serial.println(R2Topic);    
        }
        else Serial.println("Relay 2 MQTT topic string not found");    
        break;
      case CMD_R3:
        p = getStrPtr(&buffer[3]);
        if(p) {
          nvm.putString("R3Topic", p);
          nvm.getString("R3Topic", R3Topic, BUFSIZE-1);
          Serial.print("OK. Saved Relay 3 Topic: "); 
          Serial.println(R3Topic);    
        }
        else Serial.println("Relay 3 MQTT topic string not found");    
        break;
      case CMD_R4:
        p = getStrPtr(&buffer[3]);
        if(p) {
          nvm.putString("R4Topic", p);
          nvm.getString("R4Topic", R4Topic, BUFSIZE-1);
          Serial.print("OK. Saved Relay 4 Topic: "); 
          Serial.println(R4Topic);    
        }
        else Serial.println("Relay 4 MQTT topic string not found");    
        break;
      case CMD_R5:
        p = getStrPtr(&buffer[3]);
        if(p) {
          nvm.putString("R5Topic", p);
          nvm.getString("R5Topic", R5Topic, BUFSIZE-1);
          Serial.print("OK. Saved Relay 5 Topic: "); 
          Serial.println(R5Topic);    
        }
        else Serial.println("Relay 5 MQTT topic string not found");    
        break;
      case CMD_R6:
        p = getStrPtr(&buffer[3]);
        if(p) {
          nvm.putString("R6Topic", p);
          nvm.getString("R6Topic", R6Topic, BUFSIZE-1);
          Serial.print("OK. Saved Relay 6 Topic: "); 
          Serial.println(R6Topic);    
        }
        else Serial.println("Relay 6 MQTT topic string not found");    
        break;
      case CMD_R7:
        p = getStrPtr(&buffer[3]);
        if(p) {
          nvm.putString("R7Topic", p);
          nvm.getString("R7Topic", R7Topic, BUFSIZE-1);
          Serial.print("OK. Saved Relay 7 Topic: "); 
          Serial.println(R7Topic);    
        }
        else Serial.println("Relay 7 MQTT topic string not found");    
        break;
      case CMD_R8:
        p = getStrPtr(&buffer[3]);
        if(p) {
          nvm.putString("R8Topic", p);
          nvm.getString("R8Topic", R8Topic, BUFSIZE-1);
          Serial.print("OK. Saved Relay 8 Topic: "); 
          Serial.println(R8Topic);    
        }
        else Serial.println("Relay 8 MQTT topic string not found");    
        break;
      case CMD_N1:
        p = getStrPtr(&buffer[3]);
        if(p) {
          nvm.putString("N1Topic", p);
          nvm.getString("N1Topic", N1Topic, BUFSIZE-1);
          Serial.print("OK. Saved Input 1 Topic: "); 
          Serial.println(N1Topic);    
        }
        else Serial.println("Input 1 MQTT topic string not found");    
        break;
      case CMD_N2:
        p = getStrPtr(&buffer[3]);
        if(p) {
          nvm.putString("N2Topic", p);
          nvm.getString("N2Topic", N2Topic, BUFSIZE-1);
          Serial.print("OK. Saved Input 2 Topic: "); 
          Serial.println(N2Topic);    
        }
        else Serial.println("Input 2 MQTT topic string not found");    
        break;
      case CMD_N3:
        p = getStrPtr(&buffer[3]);
        if(p) {
          nvm.putString("N3Topic", p);
          nvm.getString("N3Topic", N3Topic, BUFSIZE-1);
          Serial.print("OK. Saved Input 3 Topic: "); 
          Serial.println(N3Topic);    
        }
        else Serial.println("Input 3 MQTT topic string not found");    
        break;
      case CMD_N4:
        p = getStrPtr(&buffer[3]);
        if(p) {
          nvm.putString("N4Topic", p);
          nvm.getString("N4Topic", N4Topic, BUFSIZE-1);
          Serial.print("OK. Saved Input 4 Topic: "); 
          Serial.println(N4Topic);    
        }
        else Serial.println("Input 4 MQTT topic string not found");    
        break;
      case CMD_N5:
        p = getStrPtr(&buffer[3]);
        if(p) {
          nvm.putString("N5Topic", p);
          nvm.getString("N5Topic", N5Topic, BUFSIZE-1);
          Serial.print("OK. Saved Input 5 Topic: "); 
          Serial.println(N5Topic);    
        }
        else Serial.println("Input 5 MQTT topic string not found");    
        break;
      case CMD_N6:
        p = getStrPtr(&buffer[3]);
        if(p) {
          nvm.putString("N6Topic", p);
          nvm.getString("N6Topic", N6Topic, BUFSIZE-1);
          Serial.print("OK. Saved Input 6 Topic: "); 
          Serial.println(N6Topic);    
        }
        else Serial.println("Input 6 MQTT topic string not found");    
        break;
      case CMD_N7:
        p = getStrPtr(&buffer[3]);
        if(p) {
          nvm.putString("N7Topic", p);
          nvm.getString("N7Topic", N7Topic, BUFSIZE-1);
          Serial.print("OK. Saved Input 7 Topic: "); 
          Serial.println(N7Topic);    
        }
        else Serial.println("Input 7 MQTT topic string not found");    
        break;
      case CMD_N8:
        p = getStrPtr(&buffer[3]);
        if(p) {
          nvm.putString("N8Topic", p);
          nvm.getString("N8Topic", N8Topic, BUFSIZE-1);
          Serial.print("OK. Saved Input 8 Topic: "); 
          Serial.println(N8Topic);    
        }
        else Serial.println("Input 8 MQTT topic string not found");    
        break;
    }
  }
}


int getIP(char* p)
{
char *p1;
IPAddress IP;

   p = skipWhite(p);
   p1 = p;
   while( (*p >= '0' && *p <= '9') || (*p == '.') ) ++p;
   *p = 0;
   IP.fromString(p1);
   return IP;
}

int getNumber(char *p)
{
  p = skipWhite(p);
  return atoi(p);
}

char* skipWhite(char *p)
{
  while(isspace(*p)) ++p;  
  return p;
}

char * getStrPtr(char *p)
{
char *p1, *p2;

  p = skipWhite(p);
  if(*p!='"') return 0;
  p1 = ++p; 
  p2 = p1;
  while( *p )  {
    if(*p == '\\') {
      if(p[1]=='\\' || p[1]=='"') {
        *p2++ = p[1];
        p += 2; 
      }
      else ++p;     // ignore single escape char
    }
    else {
      if(*p=='"') {
        *p2 = 0;
        return p1;
      }
      *p2++ = *p++;
    }
  }
  return 0;
}

bool getMLine(void)
{
static int idx = 0;
char c;

  if(Serial.available()) {
    c = Serial.read();
    Serial.write(c);
    if( (c == '\n') || (c == '\r') )
    {
      if(idx == 0) return false;    // ignore empty lines
    }
    buffer[idx++] = c;
    if(idx == sizeof(buffer)-1) {
      idx = 0;                    // we overflowed the buffer, just start over.
      return false;
    }
    if( (c == '\n') || (c == '\r') )
    {
      buffer[idx] = '\0';
      idx = 0;
      return true;
    }
  }
  return false;
}

int getCommand()
{
  if(toupper(buffer[0]) == 'S') {
    if(toupper(buffer[1]) == 'T') return CMD_ST; 
    if(toupper(buffer[1]) == 'B') return CMD_SB; 
    if(toupper(buffer[1]) == 'D') return CMD_SD; 
    if(toupper(buffer[1]) == 'S') return CMD_SS; 
  }
  else if(toupper(buffer[0]) == 'I') {
    if(toupper(buffer[1]) == 'P') return CMD_IP; 
  }
  else if(toupper(buffer[0]) == 'G') {
    if(toupper(buffer[1]) == 'W') return CMD_GW; 
  }
  else if(toupper(buffer[0]) == 'A') {
    if(toupper(buffer[1]) == 'P') return CMD_AP; 
  }
  else if(toupper(buffer[0]) == 'P') {
    if(toupper(buffer[1]) == 'D') return CMD_PD; 
    if(toupper(buffer[1]) == 'W') return CMD_PW; 
    if(toupper(buffer[1]) == 'A') return CMD_PA; 
  }  
  else if(toupper(buffer[0]) == 'M') {
    if(toupper(buffer[1]) == 'P') return CMD_MP; // MQTT Port
    if(toupper(buffer[1]) == 'S') return CMD_MS; // MQTT Server
    if(toupper(buffer[1]) == 'D') return CMD_MD; // MQTT ID
    if(toupper(buffer[1]) == 'U') return CMD_MU; // MQTT User
    if(toupper(buffer[1]) == 'W') return CMD_MW; // MQTT Password
  }
  else if(toupper(buffer[0]) == 'R') {
    if(toupper(buffer[1]) == 'B') return CMD_RB; // ReBoot
    if(toupper(buffer[1]) == '1') return CMD_R1; // MQTT Relay Topics
    if(toupper(buffer[1]) == '2') return CMD_R2; 
    if(toupper(buffer[1]) == '3') return CMD_R3; 
    if(toupper(buffer[1]) == '4') return CMD_R4; 
    if(toupper(buffer[1]) == '5') return CMD_R5; 
    if(toupper(buffer[1]) == '6') return CMD_R6; 
    if(toupper(buffer[1]) == '7') return CMD_R7; 
    if(toupper(buffer[1]) == '8') return CMD_R8; 
  }
  else if(toupper(buffer[0]) == 'N') {
    if(toupper(buffer[1]) == '1') return CMD_N1; // MQTT Input Topics
    if(toupper(buffer[1]) == '2') return CMD_N2; 
    if(toupper(buffer[1]) == '3') return CMD_N3; 
    if(toupper(buffer[1]) == '4') return CMD_N4; 
    if(toupper(buffer[1]) == '5') return CMD_N5; 
    if(toupper(buffer[1]) == '6') return CMD_N6; 
    if(toupper(buffer[1]) == '7') return CMD_N7; 
    if(toupper(buffer[1]) == '8') return CMD_N8;     
  }
  return CMD_NONE;
}
