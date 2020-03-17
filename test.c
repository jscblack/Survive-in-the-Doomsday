/*
 * @Author: Gehrychiang
 * @LastEditTime: 2020-03-17 14:32:36
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
    pinMode(LED, INPUT);
    for (int i = 0; i < 10; i++)
    {
        printf("%d\n",digitalRead(LED));
        delay(2000);
    }
    return 0;
}