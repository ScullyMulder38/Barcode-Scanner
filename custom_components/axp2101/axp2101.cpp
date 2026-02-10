#include "axp2101.h"
#include "esphome/core/log.h"

namespace esphome {
namespace axp2101 {

static const char *const TAG = "axp2101.sensor";

void AXP2101Component::setup() {
    ESP_LOGCONFIG(TAG, "Initializing AXP2101 Hub...");
    // Register 0x18: Bit 0=Fuel Gauge Enable, Bit 1=Charger Enable
    this->write_byte(0x18, 0x03); 
    // Register 0x69: Lade-LED Steuerung
    this->write_byte(0x69, 0x02); 
}

void AXP2101Component::update() {
    uint8_t data[2];

    // 1. Spannung (Register 0x34-0x35)
    if (this->read_bytes(0x34, data, 2)) {
        uint16_t vbat_raw = (data[0] << 8) | data[1];
        float voltage = vbat_raw / 1000.0f;
        if (this->battery_voltage_sensor_ != nullptr)
            this->battery_voltage_sensor_->publish_state(voltage);
    }

    // 2. Ladestatus & VBUS (Register 0x01)
    uint8_t status;
    if (this->read_byte(0x01, &status)) {
        std::string charge_msg = "Akkubetrieb";
        bool vbus_present = (status >> 7) & 0x01; // Bit 7: USB Power
        uint8_t charge_bits = (status >> 5) & 0x03; // Bit 5-6: Phase

        if (vbus_present) {
            switch (charge_bits) {
                case 0: charge_msg = "Netz (Standby)"; break;
                case 1: charge_msg = "Lädt..."; break;
                case 2: charge_msg = "Voll geladen"; break;
                case 3: charge_msg = "Ladefehler"; break;
            }
        }
        if (this->charge_status_sensor_ != nullptr)
            this->charge_status_sensor_->publish_state(charge_msg);
    }

    // 3. Prozent (Register 0xA4)
    uint8_t percentage;
    if (this->read_byte(0xA4, &percentage)) {
        if (this->battery_level_sensor_ != nullptr && percentage <= 100)
            this->battery_level_sensor_->publish_state(percentage);
    }
}

void AXP2101Component::dump_config() {
    ESP_LOGCONFIG(TAG, "AXP2101 Hub Configured");
}

}  // namespace axp2101
}  // namespace esphome
