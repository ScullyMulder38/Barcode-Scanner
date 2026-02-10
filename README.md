# Barcode-Scanner
Barcode scanner mit GM60 Scanner,Buzzer and Waveshare ESP32-S3 3.5inch Capacitive Touch Display, 320x480 IPS
# Barcode-Scanner mit Waveshare ESP32-S3 3.5" & GM60

Dieses Projekt nutzt das **Waveshare ESP32-S3 3.5-Zoll kapazitive Touch-Display** (320x480) als Basis für einen smarten Barcode-Scanner. Die Daten werden über ein **GM60 Barcode-Modul** eingelesen, auf dem IPS-Display angezeigt und an Home Assistant weitergeleitet.

## Hardware
* **Display:** Waveshare ESP32-S3 3.5" Touch LCD (320x480 Pixel).
* **Scanner:** GM60 Barcode Reader Modul.
* **Controller:** ESP32-S3 (16MB Flash, 8MB PSRAM).
* **Buzzer: DC 3 V Aktive Summer Alarm, Elektromagnetische Beeper, Aktive Piezo Summer Alarm, Industrie Sounder 9x6mm/9x5,5mm

### Verkabelung (Beispiel)
| GM60 Pin | ESP32 Pin (Waveshare) | Beschreibung |
| :--- | :--- | :--- |
| VCC | 5V | Stromversorgung |
| GND | GND | Masse |
| TX | GPIO 18 | Daten vom Scanner |
| RX | GPIO 17 | Befehle zum Scanner |

---

## Features
* **Induction Mode:** Der Scanner aktiviert sich automatisch bei Bewegung.
* **Home Assistant Anbindung:** Vollständige Integration via ESPHome.
* **Status-Feedback:** Anzeige des zuletzt gescannten Barcodes auf dem Display.
* **Reparatur-Buttons:** Integrierte Buttons in Home Assistant zum Resetten und Rekonfigurieren des Scanners (fixiert Probleme mit der grünen LED oder dem Lese-Modus).

---

## Installation & Struktur

### 1. Repository-Struktur
Stelle sicher, dass dein GitHub-Ordner wie folgt aufgebaut ist:
- `Barcode-Scanner.yaml` (Hauptdatei)
- `README.md` (Diese Anleitung)
- `secrets.yaml.example` (Beispiel für WLAN-Daten)
- `/components` (Spezifische Treiber für das Waveshare Board)
- `/fonts` (Schriftarten für das Display)

### 2. Einrichtung
1. Erstelle eine `secrets.yaml` basierend auf der `secrets.yaml.example`.
2. Lade den Code via ESPHome auf dein Board hoch.

---

## GM60 Befehle (Troubleshooting)
Sollte der Scanner nicht wie gewünscht reagieren (z.B. kein Licht oder kein Scan), sendet der "Reset"-Button im Projekt folgende Sequenzen:
* **Reset auf Werkseinstellung:** `7E 00 09 01 00 00 00 DE C8`
* **Aktivierung Induction Mode:** `7E 00 08 01 00 00 03 AB CD`
