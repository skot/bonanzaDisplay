#ifndef I2C_CONTROL_H
#define I2C_CONTROL_H

#include <stdbool.h>
#include <stdint.h>

// 7-bit I2C slave address.
#define BONANZA_I2C_ADDRESS 0x3c

// Byte-addressed register map. Text fields are NUL-terminated and zero-padded;
// numeric fields are unsigned 32-bit little-endian values.
enum {
    BONANZA_REG_PROTOCOL_VERSION = 0x00,
    BONANZA_REG_I2C_ADDRESS      = 0x01,
    BONANZA_REG_REGISTER_BYTES   = 0x02,

    BONANZA_REG_DEVICE_FAMILY    = 0x10, // 16 bytes
    BONANZA_REG_DEVICE_MODEL     = 0x20, // 8 bytes
    BONANZA_REG_DEVICE_NAME      = 0x28, // 16 bytes
    BONANZA_REG_IP_ADDRESS       = 0x38, // 16 bytes
    BONANZA_REG_BEST_SHARE       = 0x48, // 16 bytes

    BONANZA_REG_HASHRATE_GHS     = 0x60,
    BONANZA_REG_TEMPERATURE_C    = 0x64,
    BONANZA_REG_POWER_W          = 0x68,
    BONANZA_REG_FREQUENCY_MHZ    = 0x6c,
    BONANZA_REG_FAN_PERCENT      = 0x70,
};

#define BONANZA_DEVICE_FAMILY_SIZE 16
#define BONANZA_DEVICE_MODEL_SIZE   8
#define BONANZA_DEVICE_NAME_SIZE   16
#define BONANZA_IP_ADDRESS_SIZE    16
#define BONANZA_BEST_SHARE_SIZE    16

typedef struct {
    char device_family[BONANZA_DEVICE_FAMILY_SIZE];
    char device_model[BONANZA_DEVICE_MODEL_SIZE];
    char device_name[BONANZA_DEVICE_NAME_SIZE];
    char ip_address[BONANZA_IP_ADDRESS_SIZE];
    char best_share[BONANZA_BEST_SHARE_SIZE];
    uint32_t hashrate_ghs;
    uint32_t temperature_c;
    uint32_t power_w;
    uint32_t frequency_mhz;
    uint32_t fan_percent;
} bonanza_metrics_t;

void bonanza_i2c_control_init(void);

// Copies one coherent snapshot after an I2C write transaction. This function
// is called from the main loop so the IRQ handler never calls LVGL.
bool bonanza_i2c_control_take_update(bonanza_metrics_t *metrics);

#endif // I2C_CONTROL_H
