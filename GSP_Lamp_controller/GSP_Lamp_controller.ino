#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

byte mac[] = {0xAE, 0xAC, 0xBE, 0xEF, 0xFE, 0xEB};
EthernetUDP udp;

// destination IP
byte gspIp[] = {169,254,76,3};
// own IP in network
byte myIp[] = {169,254,76,4};
// UDP port
int gspPort = 12346;
int lastValue = -1;

void setup() {
	Serial.begin(9600);
        Serial.println("try to initialize Ethernet");
        Ethernet.begin(mac, myIp);
	if(0 != 0) {
		Serial.println("Failed to configure Ethernet using DHCP");
	} else {
		Serial.println("start udp session");
		udp.begin(4221);
		delay(1000);
	}
        Serial.println(Ethernet.localIP());
}

void loop() {	
	int value = analogRead(A0);
        value = map(value, 0, 1023, 0, 5);
        value = map(value, 0, 5, 0, 255);
    
        if(value != lastValue) {
		lastValue = value;		
		String test = "508:";
		test += value;
		char msg[30];
		test.toCharArray(msg, 30);
		Serial.println(msg);
		writeToGSP(msg);
	}
}

void writeToGSP(char* msg) {
	udp.beginPacket(gspIp, gspPort);
	udp.write(msg);
	udp.endPacket();
        Serial.print("sent: ");
        Serial.print(msg);
        Serial.println(" as udp package");
}
