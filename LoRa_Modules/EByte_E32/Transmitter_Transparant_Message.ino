/*
 * EBYTE LoRa E32
 * send a transparent message, you must check that the transmitter and receiver have the same
 * CHANNEL ADDL and ADDH
 *
 *
 * https://mischianti.org
 *
 * E32        ----- esp32
 * M0         ----- 19 (or GND)
 * M1         ----- 21 (or GND)
 * RX         ----- TX2 (PullUP)
 * TX         ----- RX2 (PullUP)
 * AUX        ----- 15  (PullUP)
 * VCC        ----- 3.3v/5v
 * GND        ----- GND
 *
 */
#include "Arduino.h"
#include "LoRa_E32.h"
// ---------- esp8266 pins --------------
// LoRa_E32 e32ttl(RX, TX, AUX, M0, M1);  // Arduino RX <-- e22 TX, Arduino TX --> e22 RX
// LoRa_E32 e32ttl(D3, D4, D5, D7, D6); // Arduino RX <-- e22 TX, Arduino TX --> e22 RX AUX M0 M1
// LoRa_E32 e32ttl(D2, D3); // Config without connect AUX and M0 M1

// SoftwareSerial mySerial(D2, D3); // Arduino RX <-- e22 TX, Arduino TX --> e22 RX
// LoRa_E32 e32ttl(&mySerial, D5, D7, D6); // AUX M0 M1
//  -------------------------------------
//  ---------- Arduino pins --------------
// LoRa_E32 e32ttl(4, 5, 3, 7, 6); // Arduino RX <-- e22 TX, Arduino TX --> e22 RX AUX M0 M1
// LoRa_E32 e32ttl(4, 5); // Config without connect AUX and M0 M1
// #include <SoftwareSerial.h>
// SoftwareSerial mySerial(4, 5); // Arduino RX <-- e22 TX, Arduino TX --> e22 RX
// LoRa_E32 e32ttl(&mySerial, 3, 7, 6); // AUX M0 M1
//  -------------------------------------
//  ------------- Arduino MKR WiFi 1010 -------------
//  LoRa_E32 e220ttl(&Serial1, 1, 2, 3); //  RX AUX M0 M1
//  -------------------------------------------------
//  ---------- esp32 pins --------------
// #include <HardwareSerial.h>
// HardwareSerial Serial2(13, 12);
LoRa_E32 e32ttl(&Serial2, 15, 21, 19); //  RX AUX M0 M1
// LoRa_E32 e32ttl(&Serial2, 22, 4, 18, 21, 19, UART_BPS_RATE_9600); //  esp32 RX <-- e22 TX, esp32 TX --> e22 RX AUX M0 M1
//  -------------------------------------
void setup()
{
    Serial.begin(9600);
    delay(5000);
    // Startup all pins and UART
    e32ttl.begin();
    Serial.println("Hi, I'm going to send message!");
    // Send message
    ResponseStatus rs = e32ttl.sendMessage("Hello, world?");
    // Check If there is some problem of succesfully send
    Serial.println(rs.getResponseDescription());
    Serial.println("setup end");
}
void loop()
{
    // If something available
    if (e32ttl.available() > 1)
    {
        // read the String message
        ResponseContainer rc = e32ttl.receiveMessage();
        // Is something goes wrong print error
        if (rc.status.code != 1)
        {
            Serial.println(rc.status.getResponseDescription());
        }
        else
        {
            // Print the data received
            Serial.println(rc.status.getResponseDescription());
            Serial.println(rc.data);
        }
    }
    if (Serial.available())
    {
        String input = Serial.readString();
        e32ttl.sendMessage(input);
    }
}