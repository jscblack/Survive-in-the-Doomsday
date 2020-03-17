/*
 * @Author: Gehrychiang
 * @LastEditTime: 2020-03-17 14:55:12
 * @Website: www.yilantingfeng.site
 * @E-mail: gehrychiang@aliyun.com
 */
#include <stdio.h>
#include <wiringPi.h>
int main()
{
    wiringPiSetup();
    pinMode(0, INPUT);
    for (int i = 0; i < 10; i++)
    {
        printf("%d\n", digitalRead(0));
        delay(2000);
    }
    return 0;
}