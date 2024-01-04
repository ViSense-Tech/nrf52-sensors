char txPacket[30];

float txNumber;

void setup() {
  Serial2.begin(115200); //set baud rate of uart2
  txNumber = 0;
}
void loop() {
  sprintf(txPacket, "MESSAGE-NUMBER %0.2f \r\n", txNumber);
  Serial2.printf("AT+SEND=101, %d, %s", strlen(txPacket), txPacket);
  txNumber++;
  delay(2000);
 
}

  