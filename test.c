/*
 * @Author: Gehrychiang
 * @LastEditTime: 2020-03-17 11:39:02
 * @Website: www.yilantingfeng.site
 * @E-mail: gehrychiang@aliyun.com
 */
//this is a test
#include <stdio.h>
#include <wiringPi.h>
#include <ads1115.h>
#define LED 1
int main()
{
    wiringPiSetupGpio();
    pinMode(LED, OUTPUT);
    digitalWrite(LED, 1);
    printf("111\n");
    delay(1000);
    digitalWrite(LED, 0);
    delay(1000);
    digitalWrite(LED, 1);
    printf("222\n");
    delay(1000);
    digitalWrite(LED, 0);
    pinMode(LED, INPUT);
    return 0;
}