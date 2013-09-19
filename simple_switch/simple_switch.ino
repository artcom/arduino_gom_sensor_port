#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

byte mac[] = {0x90, 0xA2, 0xDA, 0x0E, 0x0D, 0xCE};
EthernetUDP udp;

// destination IP
byte gspIp[] = {172,40,2,22};
// own IP in network
byte myIp[] = {
  172,40,13,31}; // 172,40,13,30

byte myDns[] = {8,8,8,8}; 
byte myGateway[] = {172,40,1,1}; 
byte myNetmask[] = {255,255,0,0}; 

// UDP port
unsigned int gspPort = 44470;

const int inputPin = 8;  
int pVal = HIGH;

void setup() {
    Serial.begin(9600);
    Serial.println("try to initialize Ethernet");
    Ethernet.begin(mac, myIp, myDns, myGateway, myNetmask);
    if(0 != 0) {
        Serial.println("Failed to configure Ethernet using DHCP");
    } 
    else {
        Serial.println("start udp session");
        udp.begin(4221);
        delay(1000);
    }

    Serial.println(Ethernet.localIP());

    pinMode(inputPin, INPUT);
    digitalWrite(inputPin,HIGH); 

}

void loop() {	
    int val = digitalRead(inputPin);  // read input value
    String test;

    if(val != pVal){
        if (val == HIGH){                  
            test = "lightswitch:on";
        }
        else{
            test = "lightswitch:off";	
        }
        char msg[30];
        test.toCharArray(msg, 30);
        writeToGSP(msg);
    }

    pVal = val; 
}

void writeToGSP(char* msg) {
    udp.beginPacket(gspIp, gspPort);
    udp.write(msg);
    udp.endPacket();
    Serial.print("sent: ");
    Serial.print(msg);
    Serial.println(" as udp package");
}




