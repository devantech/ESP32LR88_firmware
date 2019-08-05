
enum Acmds { A_NONE, A_ST, A_SR, A_GR, A_GI, A_AL };
enum A_SM { SM_WAITING, SM_READING };

WiFiClient Aclient;

void modeAscii(void)
{
static char ALine[300];
static int idx = 0, SM_State=SM_WAITING;
int cmd = 0, rly, state;

  switch(SM_State) {
    case SM_WAITING:
      Aclient = tcpServer.available();   // listen for incoming clients
      if (Aclient) {
        SM_State = SM_READING;              // if you get a client
        Serial.println("New Ascii Client.");           // print a message out the serial port
      }
      break;
      
    case SM_READING:
      if(Aclient.connected()) {
        if (Aclient.available()) {             // if there's bytes to read from the client,
          char c = Aclient.read();             // read a byte, then
          ALine[idx++] = toupper(c);
          if (c == '\n') {                    // if the byte is a newline character
            ALine[idx] = 0;
  
            if(ALine[0] == 'S') {
              if(ALine[1] == 'T') cmd = A_ST;       // Status command
              else if(ALine[1] == 'R') cmd = A_SR;  // Set Relay command
            }
            else if(ALine[0] == 'G') {
              if(ALine[1] == 'R') cmd = A_GR;       // Get Relay command
              else if(ALine[1] == 'I') cmd = A_GI;  // Get Input command
            }
            else if(ALine[0] == 'A') {
              if(ALine[1] == 'L') cmd = A_AL;       // Get Relay command
            }
            idx = 2;                                // first char after the command
            switch(cmd) {
              case A_SR:
                idx = 2;
                while(isspace(ALine[idx])) ++idx;     // skip white space
                rly = ALine[idx++];
                while(isspace(ALine[idx])) ++idx;     // skip white space
                state = ALine[idx];
                if(setRelay(rly, state)) Aclient.println("ok");
                else Aclient.println("fail");
                idx = 0;
                break;
              case A_GR:
                idx = 2;
                while(isspace(ALine[idx])) ++idx;     // skip white space
                rly = ALine[idx++];
                switch(getRelay(rly)) {
                  case 0: Aclient.println("0"); break;
                  case 1: Aclient.println("1"); break;
                  default: Aclient.println("fail"); break;
                }
                idx = 0;
                break;
              case A_GI:
                idx = 2;
                while(isspace(ALine[idx])) ++idx;     // skip white space
                rly = ALine[idx++];
                switch(getInput(rly)) {
                  case 0: Aclient.println("0"); break;
                  case 1: Aclient.println("1"); break;
                  default: Aclient.println("fail"); break;
                }
                idx = 0;
                break;            
              case A_AL:
                idx = 2;
                while(isspace(ALine[idx])) ++idx;     // skip white space
                for(rly=0x31; rly<0x39; rly++) {
                  state = ALine[idx++];
                  if(state=='0' || state=='1') setRelay(rly, state);
                  else if(state != 'x' && state != 'X') break;
                }
                for(idx=0x31; idx<0x39; idx++) {
                  state = getInput(idx);
                  Aclient.write(state+0x30);
                }
                Aclient.println();              
                idx = 0;
                break;
              default:
                idx = 0;
                break;
            }
            cmd = 0;                            // don't leave old command in buffer.
        } // if newline
      }   // if client.available
    }     // if client.connected
    else {
      Aclient.stop();                              // close the connection:
      Serial.println("Client Disconnected.");   
      SM_State = SM_WAITING;
      return;    
    }
  }     // switch
}       // function


bool setRelay(char rly, char state) 
{
  if(state=='0') state = 0;
  else if(state=='1') state = 1;
  else return false;
  
  switch(rly) {
    case '1': digitalWrite(Rly1, state); return true;
    case '2': digitalWrite(Rly2, state); return true;
    case '3': digitalWrite(Rly3, state); return true;
    case '4': digitalWrite(Rly4, state); return true;
    case '5': digitalWrite(Rly5, state); return true;
    case '6': digitalWrite(Rly6, state); return true;
    case '7': digitalWrite(Rly7, state); return true;
    case '8': digitalWrite(Rly8, state); return true;
  }
  return false;
}

char getRelay(char rly)
{
  switch(rly) {
    case '1': return digitalRead(Rly1);
    case '2': return digitalRead(Rly2);
    case '3': return digitalRead(Rly3);
    case '4': return digitalRead(Rly4);
    case '5': return digitalRead(Rly5);
    case '6': return digitalRead(Rly6);
    case '7': return digitalRead(Rly7);
    case '8': return digitalRead(Rly8);
  }
  return '?';
}

char getInput(char inp)
{
  switch(inp) {
    case '1': return digitalRead(Inp1);
    case '2': return digitalRead(Inp2);
    case '3': return digitalRead(Inp3);
    case '4': return digitalRead(Inp4);
    case '5': return digitalRead(Inp5);
    case '6': return digitalRead(Inp6);
    case '7': return digitalRead(Inp7);
    case '8': return digitalRead(Inp8);
  }
  return '?';
}



