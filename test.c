/*
 * @Author: Gehrychiang
 * @LastEditTime: 2020-03-17 20:13:07
 * @Website: www.yilantingfeng.site
 * @E-mail: gehrychiang@aliyun.com
 */
#include <stdio.h>
#include <wiringPi.h>
#define LED 1
int main()
{
    wiringPiSetup();
    pinMode(LED, OUTPUT);
    for (int i = 1; i <= 10; i++)
    {
        digitalWrite(LED, 1);
        delay(1000);
        digitalWrite(LED, 0);
        delay(1000);
        printf("%d\n", i);
    }
    pinMode(LED, INPUT);
    return 0;
}
