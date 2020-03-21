/*
 * @Author: Gehrychiang
 * @LastEditTime: 2020-03-21 18:08:02
 * @Website: www.yilantingfeng.site
 * @E-mail: gehrychiang@aliyun.com
 */
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ads1115.h>

float dust_measure(int ledpin, int measurepin)
{
    float voMeasured = 0;
    float calcVoltage = 0;

    digitalWrite(ledpin, LOW);
    delayMicroseconds(280);

    voMeasured = analogRead(70 + measurepin);
    delayMicroseconds(40);
    digitalWrite(ledpin, HIGH);
    delayMicroseconds(40);
    calcVoltage = voMeasured * (5.0 / 1024.0);
    return 0.17 * calcVoltage - 0.1;
}
int main()
{
    // Settup:
    wiringPiSetup();
    // Listen on 0x48,which is the address of the module
    ads1115Setup(70, 0x48);
    int ledpin = 4;
    int measurepin = 0;
    float sum = 0;
    int trys = 10;
    pinMode(ledpin, OUTPUT);
    while (trys--)
    {
        digitalWrite(ledpin, HIGH);
        printf("%f\n", dust_measure(ledpin, measurepin));
        delay(1000);
    }
    return 0;
}
