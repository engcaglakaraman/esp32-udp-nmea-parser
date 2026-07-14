#include <WiFi.h>
#include <WiFiUdp.h>

// Kablosuz Ağ Bilgileri 
const char* ssid = "ESP32_NMEA_Net";
const char* password = "password123";

// UDP Ayarları
WiFiUDP udp;
const char* receiverIP = "192.168.4.255"; // Broadcast adresi 
const int udpPort = 12345;

// Simüle edilmiş $GPRMC NMEA cümlesi (Hız: 22.4 knot, Rota: 84.4 derece)
const char* nmeaSentence = "$GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*6A";

void setup() {
  Serial.begin(115200);
  
  // ESP32'yi Access Point yapıyoruz.
  WiFi.softAP(ssid, password);
  Serial.println("Wi-Fi Agi Baslatildi.");
  Serial.print("IP Adresi: ");
  Serial.println(WiFi.softAPIP());
  
  udp.begin(udpPort);
}

void loop() {
  udp.beginPacket(receiverIP, udpPort);
  udp.print(nmeaSentence);
  udp.endPacket();
  
  Serial.print("Gonderilen NMEA Verisi: ");
  Serial.println(nmeaSentence);
  
  delay(2000); 
}
