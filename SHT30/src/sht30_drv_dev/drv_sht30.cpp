/**
 * @file drv_sht30.cpp
 * @author ちみ/Chimi（https://github.com/Chimipupu）
 * @brief SHT30 ドライバ
 * @version 0.1
 * @date 2024-10-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "drv_sht30.hpp"

void drv_sht30_init(void)
{
#ifdef BOARD_RP2040
    WIRE_I2C.setSCL(I2C_SCL);
    WIRE_I2C.setSDA(I2C_SDA);
#endif

#ifdef BOARD_ESP32_S3
    // WIRE_I2C.begin(I2C_SCL, I2C_SDA, I2C_FREQ_100KHZ);
    WIRE_I2C.begin();
#else
    WIRE_I2C.begin();
#endif
}

bool drv_sht30_data_read(float &ctemp, float &ftemp, float &humidity)
{
    bool res = false;

    WIRE_I2C.beginTransmission(SH30_I2C_ADDR);
    WIRE_I2C.write(0x2C); // コマンド MSB
    WIRE_I2C.write(0x06); // コマンド LSB
    while(WIRE_I2C.endTransmission() != 0)
    {
        WIRE_I2C.beginTransmission(SH30_I2C_ADDR);
        WIRE_I2C.write(0x2C); // コマンド MSB
        WIRE_I2C.write(0x06); // コマンド LSB
        Serial.print(".");
        delay(500); // センサーがデータを準備するのを待つ
    }

    // delay(1000); // センサーがデータを準備するのを待つ

    WIRE_I2C.requestFrom(SH30_I2C_ADDR, 6); // 6バイト（温度2バイト+CRC、湿度2バイト+CRC）

    uint8_t i2c_data_num = WIRE_I2C.available();

    if (WIRE_I2C.available() == 6)
    {
        uint16_t tempData = (WIRE_I2C.read() << 8) | WIRE_I2C.read(); // 温度データ
        WIRE_I2C.read();                                          // CRCを無視

        uint16_t humData = (WIRE_I2C.read() << 8) | WIRE_I2C.read(); // 湿度データ
        WIRE_I2C.read();                                         // CRCを無視

        // データシートの14ページの計算式のまま計算
        // ※データシート(https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/docs/datasheet/unit/SHT3x_Datasheet_digital.pdf);
        // 摂氏温度 (-45°C to 130°C)
        ctemp = -45.0 + 175.0 * (float)tempData / 65535.0;
        // 華氏温度
        ftemp = -49.0 + 315.0 * (float)tempData / 65535.0;
        // 湿度を計算 (0% to 100%)
        humidity = 100.0 * (float)humData / 65535.0;

        res = true;
    }

    return res;
}