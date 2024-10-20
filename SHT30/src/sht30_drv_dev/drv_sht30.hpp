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

// I2C
#define I2C_FREQ_100KHZ 100000
#define I2C_FREQ_400KHZ 400000

// ESP32
// #define I2C_SCL 33
// #define I2C_SDA 32

// ESP32 S3
// #define I2C_SCL 1
// #define I2C_SDA 2

// Maker Pi RP2040
#define I2C_SCL 17
#define I2C_SDA 16

#define SH30_I2C_ADDR 0x44
// #define SH30_I2C_ADDR 0x45
#define SLAVE_FOUNED  0x00

// #define SOFT_WIRE
#ifdef SOFT_WIRE
#include <SoftWire.h>
SoftWire softWire=SoftWire(I2C_SDA, I2C_SCL);
#define WIRE_I2C   softWire
#else
#include <Wire.h>
#define WIRE_I2C   Wire
#endif /* SOFT_WIRE */

bool drv_sht30_data_read(float &ctemp, float &ftemp, float &humidity);

#endif /* DRV_SHT30_HPP */