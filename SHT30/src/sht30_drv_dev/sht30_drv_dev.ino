#include "drv_sht30.hpp"

void setup()
{
    Serial.begin(115200);

#ifndef SOFT_WIRE
    WIRE_I2C.setSDA(I2C_SDA);
    WIRE_I2C.setSCL(I2C_SCL);
#endif
    WIRE_I2C.begin();
}

void loop()
{
    float ctemp, ftemp, humidity;

    drv_sht30_data_read(ctemp, ftemp, humidity);
    Serial.printf("[SHT30センサーデータ（温度、湿度）]\n");
    Serial.printf("- 温度(摂氏) : %.3f C\n", ctemp);
    Serial.printf("- 温度(華氏) : %.3f F\n", ftemp);
    Serial.printf("- 湿度 : %.3f %%(RH)\n", humidity);

    delay(1000);
}