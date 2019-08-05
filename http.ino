
enum { NONE=0, INDEX, XML };

 void modeHttp(void)
 {
  WiFiClient client = server.available();   // listen for incoming clients
 int pos, page = 0;
 
  if (client) {                             // if you get a client,
 //   Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
//        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character
          
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {

            if(page==INDEX) {
              // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
              // and a content-type so the client knows what's coming, then a blank line:
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.println();
              // the content of the HTTP response follows the header:
  
              client.println("<!DOCTYPE HTML><html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>ESP32LR88</title></head><body>");
              client.println("<p style='text-align:center'><b>ESP32LR88</b> <br></p>");
              client.println("<style>button{width:44%;height:35px;margin:5px;}</style>");
              
              client.println("<button id='Rly1'; onclick='setRly(1)'; >Relay 1</button>");
              client.println("<button id='Rly2'; onclick='setRly(2)'; >Relay 2</button>");
              client.println("<button id='Rly3'; onclick='setRly(3)'; >Relay 3</button>");
              client.println("<button id='Rly4'; onclick='setRly(4)'; >Relay 4</button>");
              client.println("<button id='Rly5'; onclick='setRly(5)'; >Relay 5</button>");
              client.println("<button id='Rly6'; onclick='setRly(6)'; >Relay 6</button>");
              client.println("<button id='Rly7'; onclick='setRly(7)'; >Relay 7</button>");
              client.println("<button id='Rly8'; onclick='setRly(8)'; >Relay 8</button>");

              client.println("<br><br><div> Inputs 1<input type='radio' value='' id='Inp1'>");
              client.println("<input type='radio' id='Inp2'>");
              client.println("<input type='radio' id='Inp3'>");
              client.println("<input type='radio' id='Inp4'>");
              client.println("<input type='radio' id='Inp5'>");
              client.println("<input type='radio' id='Inp6'>");
              client.println("<input type='radio' id='Inp7'>");
              client.println("<input type='radio' id='Inp8'>8 </div>");
              
              client.println("<script>");
              client.println("var xhttp = new XMLHttpRequest();");
              client.println("var xmlDoc;");
              client.println("var Rly=0;");
              client.println("var Working=50;");
              client.println("setInterval(toggleRly, 10);");              
              client.println("xhttp.onreadystatechange = function() {");
              client.println("    if (this.readyState == 4 && this.status == 200) {");
              client.println("        myFunction(this);");
              client.println("    }");
              client.println("};");

              client.println("function setRly(num) {");
              client.println("    Rly = num");
              client.println("};");
              
              client.println("function getValue(tag) {");
              client.println("    var x = xmlDoc.getElementsByTagName(tag)[0];");
              client.println("    var y = x.childNodes[0].nodeValue;");
              client.println("    return y;");
              client.println("};");
              client.println("function toggleRly() {");
              client.println("  var file = '';");
              client.println("  if(Working>0) { --Working; return; }");
              client.println("  switch(Rly) {");
              client.println("    case 0: file = \"status.xml\"; break;");
              client.println("    case 1: file = \"?Rly1=2\"; break;");
              client.println("    case 2: file = \"?Rly2=2\"; break;");
              client.println("    case 3: file = \"?Rly3=2\"; break;");
              client.println("    case 4: file = \"?Rly4=2\"; break;");
              client.println("    case 5: file = \"?Rly5=2\"; break;");
              client.println("    case 6: file = \"?Rly6=2\"; break;");
              client.println("    case 7: file = \"?Rly7=2\"; break;");
              client.println("    case 8: file = \"?Rly8=2\"; break;");
              client.println("  };");
              client.println("  Rly = 0; Working = 500;");
              client.println("  xhttp.open(\"GET\", file, true);");
              client.println("  xhttp.send();");
              client.println("}");
              client.println("function myFunction(xml) {");
              client.println("  xmlDoc = xml.responseXML;");
              client.println("  document.getElementById('Rly1').style.backgroundColor = (getValue('RLY1')=='on') ? 'rgba(255,0,0,0.2)' : 'rgba(0,0,255,0.2)';");
              client.println("  document.getElementById('Rly2').style.backgroundColor = (getValue('RLY2')=='on') ? 'rgba(255,0,0,0.2)' : 'rgba(0,0,255,0.2)';");
              client.println("  document.getElementById('Rly3').style.backgroundColor = (getValue('RLY3')=='on') ? 'rgba(255,0,0,0.2)' : 'rgba(0,0,255,0.2)';");
              client.println("  document.getElementById('Rly4').style.backgroundColor = (getValue('RLY4')=='on') ? 'rgba(255,0,0,0.2)' : 'rgba(0,0,255,0.2)';");
              client.println("  document.getElementById('Rly5').style.backgroundColor = (getValue('RLY5')=='on') ? 'rgba(255,0,0,0.2)' : 'rgba(0,0,255,0.2)';");
              client.println("  document.getElementById('Rly6').style.backgroundColor = (getValue('RLY6')=='on') ? 'rgba(255,0,0,0.2)' : 'rgba(0,0,255,0.2)';");
              client.println("  document.getElementById('Rly7').style.backgroundColor = (getValue('RLY7')=='on') ? 'rgba(255,0,0,0.2)' : 'rgba(0,0,255,0.2)';");
              client.println("  document.getElementById('Rly8').style.backgroundColor = (getValue('RLY8')=='on') ? 'rgba(255,0,0,0.2)' : 'rgba(0,0,255,0.2)';");
              client.println("  if(getValue('INP1')=='1') document.getElementById('Inp1').checked = true; else document.getElementById('Inp1').checked = false;");
              client.println("  if(getValue('INP2')=='1') document.getElementById('Inp2').checked = true; else document.getElementById('Inp2').checked = false;");
              client.println("  if(getValue('INP3')=='1') document.getElementById('Inp3').checked = true; else document.getElementById('Inp3').checked = false;");
              client.println("  if(getValue('INP4')=='1') document.getElementById('Inp4').checked = true; else document.getElementById('Inp4').checked = false;");
              client.println("  if(getValue('INP5')=='1') document.getElementById('Inp5').checked = true; else document.getElementById('Inp5').checked = false;");
              client.println("  if(getValue('INP6')=='1') document.getElementById('Inp6').checked = true; else document.getElementById('Inp6').checked = false;");
              client.println("  if(getValue('INP7')=='1') document.getElementById('Inp7').checked = true; else document.getElementById('Inp7').checked = false;");
              client.println("  if(getValue('INP8')=='1') document.getElementById('Inp8').checked = true; else document.getElementById('Inp8').checked = false;");
              client.println("  Working=0;");
              client.println("}");

              client.println("</script>");
              client.println("");
  
              client.print("</body>");
              
              // The HTTP response ends with another blank line:
              client.println();             
            }
            else if(page==XML) {
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:application/xml");
              client.println();
              client.println("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
              client.println("<ESP32LR88DATA>");
              client.println("<RELAYS>");
              if(digitalRead(Rly1)) client.println("<RLY1>on</RLY1>"); else client.println("<RLY1>off</RLY1>");
              if(digitalRead(Rly2)) client.println("<RLY2>on</RLY2>"); else client.println("<RLY2>off</RLY2>");
              if(digitalRead(Rly3)) client.println("<RLY3>on</RLY3>"); else client.println("<RLY3>off</RLY3>");
              if(digitalRead(Rly4)) client.println("<RLY4>on</RLY4>"); else client.println("<RLY4>off</RLY4>");
              if(digitalRead(Rly5)) client.println("<RLY5>on</RLY5>"); else client.println("<RLY5>off</RLY5>");
              if(digitalRead(Rly6)) client.println("<RLY6>on</RLY6>"); else client.println("<RLY6>off</RLY6>");
              if(digitalRead(Rly7)) client.println("<RLY7>on</RLY7>"); else client.println("<RLY7>off</RLY7>");
              if(digitalRead(Rly8)) client.println("<RLY8>on</RLY8>"); else client.println("<RLY8>off</RLY8>");
              client.println("</RELAYS>");
              client.println("<INPUTS>");
              if(digitalRead(Inp1)) client.println("<INP1>1</INP1>"); else client.println("<INP1>0</INP1>");
              if(digitalRead(Inp2)) client.println("<INP2>1</INP2>"); else client.println("<INP2>0</INP2>");
              if(digitalRead(Inp3)) client.println("<INP3>1</INP3>"); else client.println("<INP3>0</INP3>");
              if(digitalRead(Inp4)) client.println("<INP4>1</INP4>"); else client.println("<INP4>0</INP4>");
              if(digitalRead(Inp5)) client.println("<INP5>1</INP5>"); else client.println("<INP5>0</INP5>");
              if(digitalRead(Inp6)) client.println("<INP6>1</INP6>"); else client.println("<INP6>0</INP6>");
              if(digitalRead(Inp7)) client.println("<INP7>1</INP7>"); else client.println("<INP7>0</INP7>");
              if(digitalRead(Inp8)) client.println("<INP8>1</INP8>"); else client.println("<INP8>0</INP8>");
              client.println("</INPUTS>");
              client.println("</ESP32LR88DATA>");
              client.println();                  
            }
            else {
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.println();
              client.println();              
            }
            // break out of the while loop:
            break;
          } else {    // check for a GET command
            if(currentLine.startsWith("GET / ")) page=INDEX;
            else if(currentLine.startsWith("GET /INDEX.HTM")) page=INDEX;
            else if(currentLine.startsWith("GET /STATUS.XML")) page=XML;
            else if(currentLine.startsWith("GET /?RLY")) page=XML;
            currentLine = "";
          }
          
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          c = toupper(c);
          currentLine += c;      // add it to the end of the currentLine
        }

        if(currentLine.length()==12) {
          pos = currentLine.indexOf('?');
          if( (currentLine.substring(pos, pos+4) == "?RLY") && (pos>0) ) {
            int rly = currentLine.charAt(pos+4)-0x30;
            int action = currentLine.charAt(pos+6)-0x30;
            switch(rly) {
              case 1:
                switch(action) {
                  case 0: digitalWrite(Rly1, 0); break;
                  case 1: digitalWrite(Rly1, 1); break;
                  case 2: digitalWrite(Rly1, !digitalRead(Rly1)); break;
                }
                break;
              case 2:
                switch(action) {
                  case 0: digitalWrite(Rly2, 0); break;
                  case 1: digitalWrite(Rly2, 1); break;
                  case 2: digitalWrite(Rly2, !digitalRead(Rly2)); break;
                }
                break;
              case 3:
                switch(action) {
                  case 0: digitalWrite(Rly3, 0); break;
                  case 1: digitalWrite(Rly3, 1); break;
                  case 2: digitalWrite(Rly3, !digitalRead(Rly3)); break;
                }
                break;
              case 4:
                switch(action) {
                  case 0: digitalWrite(Rly4, 0); break;
                  case 1: digitalWrite(Rly4, 1); break;
                  case 2: digitalWrite(Rly4, !digitalRead(Rly4)); break;
                }
                break;
              case 5:
                switch(action) {
                  case 0: digitalWrite(Rly5, 0); break;
                  case 1: digitalWrite(Rly5, 1); break;
                  case 2: digitalWrite(Rly5, !digitalRead(Rly5)); break;
                }
                break;
              case 6:
                switch(action) {
                  case 0: digitalWrite(Rly6, 0); break;
                  case 1: digitalWrite(Rly6, 1); break;
                  case 2: digitalWrite(Rly6, !digitalRead(Rly6)); break;
                }
                break;
              case 7:
                switch(action) {
                  case 0: digitalWrite(Rly7, 0); break;
                  case 1: digitalWrite(Rly7, 1); break;
                  case 2: digitalWrite(Rly7, !digitalRead(Rly7)); break;
                }
                break;
              case 8:
                switch(action) {
                  case 0: digitalWrite(Rly8, 0); break;
                  case 1: digitalWrite(Rly8, 1); break;
                  case 2: digitalWrite(Rly8, !digitalRead(Rly8)); break;
                }
                break;                
            }
          }  
        }
      }
    }
    // close the connection:
    client.stop();
//Serial.println("Client Disconnected.");
  }
 }
