import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import (
    DEVICE_CLASS_BATTERY, 
    UNIT_PERCENT, 
    ICON_BATTERY, 
    UNIT_VOLT, 
    DEVICE_CLASS_VOLTAGE
)
from . import AXP2101Component

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.use_id(AXP2101Component),
    cv.Optional("battery_level"): sensor.sensor_schema(
        unit_of_measurement=UNIT_PERCENT,
        device_class=DEVICE_CLASS_BATTERY,
        icon=ICON_BATTERY,
        accuracy_decimals=0,
    ),
    cv.Optional("battery_voltage"): sensor.sensor_schema(
        unit_of_measurement=UNIT_VOLT,
        device_class=DEVICE_CLASS_VOLTAGE,
        accuracy_decimals=2,
    ),
})

async def to_code(config):
    parent = await cg.get_variable(config[cv.GenerateID()])

    if "battery_level" in config:
        sens = await sensor.new_sensor(config["battery_level"])
        cg.add(parent.set_battery_level_sensor(sens))
    if "battery_voltage" in config:
        sens = await sensor.new_sensor(config["battery_voltage"])
        cg.add(parent.set_battery_voltage_sensor(sens))
