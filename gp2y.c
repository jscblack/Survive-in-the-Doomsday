/*
 * @Author: Gehrychiang
 * @LastEditTime: 2020-03-20 22:52:50
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

    voMeasured = analogRead(measurepin);
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
    pinMode(ledpin, OUTPUT);
    digitalWrite(ledpin, HIGH);
    printf("%f", dust_measure(ledpin, measurepin));
    return 0;
}