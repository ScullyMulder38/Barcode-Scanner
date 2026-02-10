#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace axp2101 {

class AXP2101Component : public PollingComponent, public i2c::I2CDevice {
 public:
  void setup() override;
  void update() override;
  void dump_config() override;

  void set_battery_voltage_sensor(sensor::Sensor *s) { battery_voltage_sensor_ = s; }
  void set_battery_level_sensor(sensor::Sensor *s) { battery_level_sensor_ = s; }
  void set_charge_status_sensor(text_sensor::TextSensor *s) { charge_status_sensor_ = s; }

 protected:
  sensor::Sensor *battery_voltage_sensor_{nullptr};
  sensor::Sensor *battery_level_sensor_{nullptr};
  text_sensor::TextSensor *charge_status_sensor_{nullptr};
};

}  // namespace axp2101
}  // namespace esphome
