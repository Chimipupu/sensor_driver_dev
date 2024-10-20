/**
 * @file drv_sht30.hpp
 * @author ちみ/Chimi（https://github.com/Chimipupu）
 * @brief SHT30 ドライバ
 * @version 0.1
 * @date 2024-10-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef DRV_SHT30_HPP
#define DRV_SHT30_HPP

#include <stdint.h>
#include <string.h>
#include <math.h>
#include <Arduino.h>

#define SH30_I2C_ADDR 0x44
// #define SH30_I2C_ADDR 0x45
#ifndef SH30_I2C_ADDR
#error "Please, define SH30_I2C_ADDR!"
#endif

// #define BOARD_ESP32
#define BOARD_ESP32_S3
// #define BOARD_RP2040

// I2C
#define I2C_FREQ_100KHZ 100000
#define I2C_FREQ_400KHZ 400000

// ESP32
#ifdef BOARD_ESP32
#define I2C_SCL 33
#define I2C_SDA 32
#endif /* BOARD_ESP32 */

// ESP32 S3
#ifdef BOARD_ESP32_S3
#define I2C_SCL 39
#define I2C_SDA 38
#endif /* BOARD_ESP32_S3 */

// Maker Pi RP2040
#ifdef BOARD_RP2040
#define I2C_SCL 17
#define I2C_SDA 16
#endif /* BOARD_RP2040 */

#include <Wire.h>
#define HARD_WIRE
#define WIRE_I2C   Wire

bool drv_sht30_data_read(float &ctemp, float &ftemp, float &humidity);
void drv_sht30_init(void);

#endif /* DRV_SHT30_HPP */