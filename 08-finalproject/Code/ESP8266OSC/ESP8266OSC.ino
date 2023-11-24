#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif
#include <WiFiUdp.h>
#include <OSCMessage.h>

char ssid[] = "Fablab O";          // your network SSID (name)
char pass[] = "fablabshanghai";                    // your network password
int sensorValue = 0;

WiFiUDP Udp; 

const IPAddress outIp(100,79,24,144);        // remote IP of your computer
const unsigned int outPort = 20716;          // remote port to receive OSC
const unsigned int localPort = 8888;        // local port to listen for OSC packets (actually not used for sending)

void setup() {
    Serial.begin(115200); 

    // Connect to WiFi network
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");

    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    Serial.println("Starting UDP");
    Udp.begin(localPort);
    Serial.print("Local port: ");
#ifdef ESP32
    Serial.println(localPort);
#else
    Serial.println(Udp.localPort());
#endif

    while (!Serial) {
    ; // wait for serial port to connect.
    }

}

void loop() {
    if (Serial.available() > 0) {
      String data = Serial.readStringUntil('\n');
      OSCMessage msg("");
      msg.add(data.c_str());
      Udp.beginPacket(outIp, outPort);
      msg.send(Udp);
      Udp.endPacket();
      msg.empty();
      // 在这里处理从Arduino接收到的数据
    }
}
