/*
 * @Author: Gehrychiang
 * @LastEditTime: 2020-03-17 10:14:03
 * @Website: www.yilantingfeng.site
 * @E-mail: gehrychiang@aliyun.com
 */
#include <stdio.h>
#include <wiringPi.h>
#include <ads1115.h>
#define LED 2
int main()
{
    wiringPiSetupGpio();
    pinMode(LED, OUTPUT);
    digitalWrite(LED, 1);
    delay(10000);
    digitalWrite(LED, 0);
    delay(10000);
    digitalWrite(LED, 1);
    pinMode(LED, INPUT);
    return 0;
}