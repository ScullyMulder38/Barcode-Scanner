import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import text_sensor
from . import AXP2101Component

CONF_CHARGE_STATUS = "charge_status"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.use_id(AXP2101Component),
    cv.Optional(CONF_CHARGE_STATUS): text_sensor.text_sensor_schema(),
})

async def to_code(config):
    parent = await cg.get_variable(config[cv.GenerateID()])
    if CONF_CHARGE_STATUS in config:
        sens = await text_sensor.new_text_sensor(config[CONF_CHARGE_STATUS])
        cg.add(parent.set_charge_status_sensor(sens))
