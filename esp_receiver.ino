#include <WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Kablosuz Ağ Bilgileri (Vericiye bağlanacağız)
const char* ssid = "ESP32_NMEA_Net";
const char* password = "password123";

// UDP Ayarları
WiFiUDP udp;
const int udpPort = 12345;
char packetBuffer[255];

// LCD Ekran Tanımlaması (0x27 veya 0x3F I2C adresi, 16 sütun, 2 satır)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  
  // LCD Ekranı Başlatma
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Sistem Aciliyor...");
  
  // Wi-Fi Ağına Bağlanma
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nAga Baglanildi!");
  lcd.clear();
  lcd.print("WiFi Baglandi");
  delay(1000);
  
  udp.begin(udpPort);
}

void loop() {
  int packetSize = udp.parsePacket();
  if (packetSize) {
    // Gelen UDP paketini oku
    int len = udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0; // String sonu karakteri ekle
    }
    
    Serial.print("Alinan Ham Veri: ");
    Serial.println(packetBuffer);
    
    // NMEA ($GPRMC) Verisini Ayrıştırma (Parsing)
    // Örnek: $GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*6A
    char* token;
    int index = 0;
    char* speedKnots = "";
    char* courseDegrees = "";
    
    // strtok ile virgüllere göre parçala
    token = strtok(packetBuffer, ",");
    while (token != NULL) {
      if (index == 7) { // 7. indeks Hız (Speed) bilgisidir
        speedKnots = token;
      }
      if (index == 8) { // 8. indeks Rota (Course) bilgisidir
        courseDegrees = token;
      }
      token = strtok(NULL, ",");
      index++;
    }
    
    // LCD Ekrana Yazdırma
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Hiz : " + String(speedKnots) + " Knots");
    lcd.setCursor(0, 1);
    lcd.print("Rota: " + String(courseDegrees) + " Deg");
    
    Serial.println("--- Ayristirilan Veriler ---");
    Serial.print("Hiz (Knots): "); Serial.println(speedKnots);
    Serial.print("Rota (Derece): "); Serial.println(courseDegrees);
  }
}
