#include "Energia.h"

#line 1 "C:/Users/Liam/ti/TxRxCreateNetwork/CreateNetwork/CreateNetwork.ino"
















#ifndef __CC3200R1M1RGC__
#include <SPI.h>
#endif
#include <WiFi.h>
#include <WiFiUDP.h>


void setup();
void loop();
void printWifiStatus();

#line 24
WiFiUDP Udp;

char wifi_name[] = "LiamTest";
char wifi_password[] = "Test12345";

IPAddress gateway;
unsigned int localPort = 8000;      


char packetBuffer[255]; 
char ReplyBuffer[] = "Ready for Transmission -------------------------------------------------------------------------------------------------";       


void setup() {
    Serial.begin(115200);

    
    
    Serial.println("Creating network...");
    WiFi.beginNetwork(wifi_name, wifi_password);
    Udp.begin(localPort);
    while (WiFi.localIP() == INADDR_NONE) {
        delay(300);
    }
    Serial.println("Done\n");

    printWifiStatus();


    Serial.println("\nWaiting for a packet to be transmitted from a client...\n");

}

int i = 0;
void loop() {

    int packetSize = Udp.parsePacket();

    
    if (i == 0) {
        for (i = 0; i < 1; i++) {
            Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
            Serial.println(ReplyBuffer);
            Udp.write(ReplyBuffer);
            Udp.endPacket();
        }
    }

    if (i != 0) {
        if (packetSize) {



            Serial.print("Client: ");
            IPAddress remoteIp = Udp.remoteIP();
            Serial.print(remoteIp);
            Serial.print(", Port: ");
            Serial.println(Udp.remotePort());

            
            int len = Udp.read(packetBuffer, 255);

            if (len > 0) packetBuffer[len] = 0;
            Serial.print("Contents: ");
            Serial.println(packetBuffer);
        }
    }
}

void printWifiStatus() {
    
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);
}



