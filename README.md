# ESP32 ile UDP Tabanlı NMEA (GPS) Veri Ayrıştırıcı ve Gösterge Sistemi

Bu proje, marin ve yat elektroniği sektöründe sıkça kullanılan **NMEA-0183** protokolünü temel alarak, iki adet ESP32 mikrodenetleyicisinin yerel Wi-Fi ağı üzerinden UDP protokolüyle kablosuz haberleşmesini ve gelen ham GPS verilerini gerçek zamanlı olarak ayrıştırıp görselleştirmesini sağlamak amacıyla geliştirilmiştir.

Staj ve endüstriyel portfolyo hedefiyle geliştirilen bu çalışma; gömülü sistemler, kablosuz ağ protokolleri ve düşük seviyeli veri işleme (string parsing) yetkinliklerini bir arada sunmaktadır.



## Teknik Özellikler & Teknolojiler
* **Mikrodenetleyici:** 2x ESP32 (Geliştirme Kartı)
* **Haberleşme Protokolü:** UDP (User Datagram Protocol) üzerinden kablosuz veri iletimi (Wi-Fi)
* **Denizcilik Protokolü:** NMEA-0183 ($GPRMC Cümlesi)
* **Görselleştirme:** 16x2 I2C LCD Ekran (3.3V Besleme)
* **Programlama Dili & Geliştirme Ortamı:** C++ / Arduino IDE
* **Veri Ayrıştırma Teknolojisi:** C-Style Pointer & `strtok()` fonksiyonu ile sıfır gecikmeli veri parçalama



## Sistem Mimarisi & Çalışma Mantığı

Sistem, denizcilik telemetri altyapılarına benzer şekilde **Verici (Transmitter)** ve **Alıcı (Receiver)** olmak üzere iki ana düğümden (node) oluşmaktadır:

### 1. Verici Düğüm (ESP32 Transmitter)
* Yerel bir Wi-Fi ağı (Access Point) oluşturur veya mevcut ağa bağlanır.
* İçerisinde simüle edilmiş ham **$GPRMC** (Recommended Minimum Navigation Information) cümleleri barındırır.
* Belirlenen periyotlarla (her 2 saniyede bir) bu NMEA paketlerini UDP üzerinden yayınlar (Broadcast/Unicast).

### 2. Alıcı Düğüm (ESP32 Receiver)
* Verici ile aynı Wi-Fi ağına bağlanarak UDP portunu dinlemeye başlar.
* Gelen UDP paketini tampon belleğe (buffer) alır.
* Gelen ham NMEA cümlesini (`$GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*6A`) analiz eder.
* **`strtok()`** yardımıyla metni virgüllerden parçalayarak **Hız (Knots)** ve **Rota (Degrees)** bilgilerini milisaniyeler içinde çeker.
* Ayrıştırılan temiz verileri I2C LCD ekran üzerinde düzenli bir arayüzle kaptanın paneline yazdırır.



## Proje Demo & Çalışma Testleri
Sistem, fiziksel donanım üzerinde uçtan uca test edilmiş ve stabil bir şekilde çalıştırılmıştır.

* **Veri İletimi:** Verici ESP32, yerel ağ üzerinden her 2 saniyede bir simüle edilmiş `$GPRMC` NMEA cümlesini UDP paketi olarak başarıyla yayınlamaktadır.
* **Veri Ayrıştırma:** Alıcı ESP32, gelen ham paketleri havada yakalayıp `strtok()` fonksiyonu ile gerçek zamanlı olarak parçalamaktadır.
* **Ekran Çıktısı:** Ayrıştırılan hız (Knots) ve rota (Degrees) bilgileri, ESP32'nin 3.3V pini üzerinden beslenen I2C LCD ekrana anlık ve kesintisiz olarak yazdırılmaktadır.

### Çalışma Videosu (GIF)
![Proje Demo](proje_demo.gif)



## Proje Klasör Yapısı
* `/esp_transmitter.ino` -> Verici ESP32 düğümünün kaynak kodları.
* `/esp_receiver.ino` -> Alıcı ESP32 ve LCD ekran yönetiminin kaynak kodları.
* `/sistem_mimarisi.png` -> Sistem haberleşme ve veri akış diyagramı.
* `/donanim_semasi.png` -> Alıcı tarafındaki ESP32 - I2C LCD devre bağlantı şeması.
* `/proje_demo.gif` -> Sistemin canlı çalışma simülasyonu / videosu.
* `/serial_monitor_output.png` -> Seri Port çıktısı /Telemetri.
* `/fiziksel_tasarim.jpg` -> Fiziksel devre bağlantılarının görseli.
* `/LICENSE` -> MIT Lisansı.



## Geliştirici
* **Çağla Karaman** - Bilgisayar Mühendisliği Öğrencisi, Bilecik Şeyh Edebali Üniversitesi

---

## Lisans
Bu proje **MIT Lisansı** altında lisanslanmıştır. Detaylar için [LICENSE](./LICENSE) dosyasını inceleyebilirsiniz.
