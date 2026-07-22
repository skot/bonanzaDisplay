#include "i2c_control.h"

#include <stddef.h>

#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "hardware/sync.h"
#include "pico/i2c_slave.h"

#include "pin_config.h"

#define CONTROL_I2C i2c0
#define REGISTER_FILE_SIZE 128u
#define PROTOCOL_VERSION 1u

static volatile uint8_t register_file[REGISTER_FILE_SIZE];
static volatile uint8_t transaction_file[REGISTER_FILE_SIZE];
static volatile bool update_pending;
static uint8_t register_address;
static uint8_t transaction_start;
static bool pointer_received;
static bool transaction_has_data;

static bool register_is_writable(uint8_t address) {
    return address >= BONANZA_REG_DEVICE_FAMILY &&
           address < REGISTER_FILE_SIZE;
}

static void clear_string_if_at_start(uint8_t address) {
    uint8_t length = 0;

    switch (address) {
        case BONANZA_REG_DEVICE_FAMILY: length = BONANZA_DEVICE_FAMILY_SIZE; break;
        case BONANZA_REG_DEVICE_MODEL:  length = BONANZA_DEVICE_MODEL_SIZE; break;
        case BONANZA_REG_DEVICE_NAME:   length = BONANZA_DEVICE_NAME_SIZE; break;
        case BONANZA_REG_IP_ADDRESS:    length = BONANZA_IP_ADDRESS_SIZE; break;
        case BONANZA_REG_BEST_SHARE:    length = BONANZA_BEST_SHARE_SIZE; break;
        default: return;
    }

    for (uint8_t i = 0; i < length; ++i) {
        transaction_file[address + i] = 0;
    }
}

static void __not_in_flash_func(i2c_slave_handler)(i2c_inst_t *i2c,
                                                    i2c_slave_event_t event) {
    switch (event) {
        case I2C_SLAVE_RECEIVE:
            while (i2c_get_read_available(i2c)) {
                const uint8_t value = i2c_read_byte_raw(i2c);
                if (!pointer_received) {
                    register_address = value & (REGISTER_FILE_SIZE - 1u);
                    transaction_start = register_address;
                    pointer_received = true;
                    transaction_has_data = false;
                } else {
                    if (!transaction_has_data) {
                        for (size_t i = 0; i < REGISTER_FILE_SIZE; ++i) {
                            transaction_file[i] = register_file[i];
                        }
                        clear_string_if_at_start(transaction_start);
                    }
                    if (register_is_writable(register_address)) {
                        transaction_file[register_address] = value;
                    }
                    register_address = (register_address + 1u) &
                                       (REGISTER_FILE_SIZE - 1u);
                    transaction_has_data = true;
                }
            }
            break;

        case I2C_SLAVE_REQUEST:
            i2c_write_byte_raw(i2c, register_file[register_address]);
            register_address = (register_address + 1u) &
                               (REGISTER_FILE_SIZE - 1u);
            break;

        case I2C_SLAVE_FINISH:
            if (transaction_has_data) {
                for (size_t i = 0; i < REGISTER_FILE_SIZE; ++i) {
                    register_file[i] = transaction_file[i];
                }
                update_pending = true;
            }
            pointer_received = false;
            transaction_has_data = false;
            break;
    }
}

static void set_default_string(uint8_t address, size_t field_size,
                               const char *value) {
    size_t i = 0;
    for (; i + 1 < field_size && value[i] != '\0'; ++i) {
        register_file[address + i] = (uint8_t)value[i];
    }
    for (; i < field_size; ++i) {
        register_file[address + i] = 0;
    }
}

static void set_default_u32(uint8_t address, uint32_t value) {
    register_file[address] = (uint8_t)value;
    register_file[address + 1] = (uint8_t)(value >> 8);
    register_file[address + 2] = (uint8_t)(value >> 16);
    register_file[address + 3] = (uint8_t)(value >> 24);
}

void bonanza_i2c_control_init(void) {
    for (size_t i = 0; i < REGISTER_FILE_SIZE; ++i) {
        register_file[i] = 0;
    }

    register_file[BONANZA_REG_PROTOCOL_VERSION] = PROTOCOL_VERSION;
    register_file[BONANZA_REG_I2C_ADDRESS] = BONANZA_I2C_ADDRESS;
    register_file[BONANZA_REG_REGISTER_BYTES] = REGISTER_FILE_SIZE;

    set_default_string(BONANZA_REG_DEVICE_FAMILY, BONANZA_DEVICE_FAMILY_SIZE,
                       "BONANZA");
    set_default_string(BONANZA_REG_DEVICE_MODEL, BONANZA_DEVICE_MODEL_SIZE,
                       "1002");
    set_default_string(BONANZA_REG_DEVICE_NAME, BONANZA_DEVICE_NAME_SIZE,
                       "battleaxe");
    set_default_string(BONANZA_REG_IP_ADDRESS, BONANZA_IP_ADDRESS_SIZE,
                       "192.168.1.234");
    set_default_string(BONANZA_REG_BEST_SHARE, BONANZA_BEST_SHARE_SIZE,
                       "123T");
    set_default_u32(BONANZA_REG_HASHRATE_GHS, 1200);
    set_default_u32(BONANZA_REG_TEMPERATURE_C, 58);
    set_default_u32(BONANZA_REG_POWER_W, 17);
    set_default_u32(BONANZA_REG_FREQUENCY_MHZ, 621);
    set_default_u32(BONANZA_REG_FAN_PERCENT, 66);

    update_pending = false;
    pointer_received = false;
    transaction_has_data = false;
    register_address = 0;

    i2c_init(CONTROL_I2C, 100 * 1000);
    gpio_set_function(PIN_CONTROL_SDA, GPIO_FUNC_I2C);
    gpio_set_function(PIN_CONTROL_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(PIN_CONTROL_SDA);
    gpio_pull_up(PIN_CONTROL_SCL);
    i2c_slave_init(CONTROL_I2C, BONANZA_I2C_ADDRESS, i2c_slave_handler);
}

static void copy_string(char *destination, size_t destination_size,
                        uint8_t address, size_t field_size) {
    size_t i = 0;
    for (; i + 1 < destination_size && i < field_size; ++i) {
        const char value = (char)register_file[address + i];
        destination[i] = value;
        if (value == '\0') {
            return;
        }
    }
    destination[i] = '\0';
}

static uint32_t read_u32(uint8_t address) {
    return (uint32_t)register_file[address] |
           ((uint32_t)register_file[address + 1] << 8) |
           ((uint32_t)register_file[address + 2] << 16) |
           ((uint32_t)register_file[address + 3] << 24);
}

bool bonanza_i2c_control_take_update(bonanza_metrics_t *metrics) {
    if (metrics == NULL || !update_pending) {
        return false;
    }

    const uint32_t irq_state = save_and_disable_interrupts();
    if (!update_pending) {
        restore_interrupts(irq_state);
        return false;
    }

    copy_string(metrics->device_family, sizeof(metrics->device_family),
                BONANZA_REG_DEVICE_FAMILY, BONANZA_DEVICE_FAMILY_SIZE);
    copy_string(metrics->device_model, sizeof(metrics->device_model),
                BONANZA_REG_DEVICE_MODEL, BONANZA_DEVICE_MODEL_SIZE);
    copy_string(metrics->device_name, sizeof(metrics->device_name),
                BONANZA_REG_DEVICE_NAME, BONANZA_DEVICE_NAME_SIZE);
    copy_string(metrics->ip_address, sizeof(metrics->ip_address),
                BONANZA_REG_IP_ADDRESS, BONANZA_IP_ADDRESS_SIZE);
    copy_string(metrics->best_share, sizeof(metrics->best_share),
                BONANZA_REG_BEST_SHARE, BONANZA_BEST_SHARE_SIZE);
    metrics->hashrate_ghs = read_u32(BONANZA_REG_HASHRATE_GHS);
    metrics->temperature_c = read_u32(BONANZA_REG_TEMPERATURE_C);
    metrics->power_w = read_u32(BONANZA_REG_POWER_W);
    metrics->frequency_mhz = read_u32(BONANZA_REG_FREQUENCY_MHZ);
    metrics->fan_percent = read_u32(BONANZA_REG_FAN_PERCENT);
    update_pending = false;
    restore_interrupts(irq_state);
    return true;
}
