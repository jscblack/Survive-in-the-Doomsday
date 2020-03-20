/*
 * @Author: Gehrychiang
 * @LastEditTime: 2020-03-20 21:51:33
 * @Website: www.yilantingfeng.site
 * @E-mail: gehrychiang@aliyun.com
 */
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ads1115.h>
int main()
{

    // Settup:
    wiringPiSetup();
    // Listen on 0x48,which is the address of the module
    ads1115Setup(70, 0x48);
    while (1)
    {
        // Read channel 0:
        int ch0 = analogRead(70 + 0);
        printf("%d", ch0);
    }
}