#define TIMEOUT 5000 // mS

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
  delay(3000);
  Serial.begin(38400);
  SendCommand("AT", "OK");
  SendCommand("AT+NAME=Batuino-BT", "OK");
  //SendCommand("AT+ROLE=1", "OK");  //master mode
  SendCommand("AT+ROLE=0", "OK");  //slave mode
  SendCommand("AT+UART=9600,0,0", "OK");  //Baud rate 9600, stop bit 1, parity bit 0
  SendCommand("AT+PSWD=1234", "OK");  //Passkey 1234
  digitalWrite(13, HIGH);
}

void loop() {
  
}

boolean SendCommand(String cmd, String ack){
  Serial.println(cmd); // Send "AT+" command to module
  if (!echoFind(ack, TIMEOUT)) // timed out waiting for ack string
    return true; // ack blank
    else return false; //  ack found
}
 
boolean echoFind(String keyword, int timeout){
 byte current_char = 0;
 byte keyword_length = keyword.length();
 long deadline = millis() + timeout;
 while(millis() < deadline){
  if (Serial.available()){
    char ch = Serial.read();
    if (ch == keyword[current_char])
      if (++current_char == keyword_length){
       return true;
    }
   }
  }
 return false; // Timed out
}
