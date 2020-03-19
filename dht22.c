/*
 * @Author: Gehrychiang
 * @LastEditTime: 2020-03-19 22:41:38
 * @Website: www.yilantingfeng.site
 * @E-mail: gehrychiang@aliyun.com
 */
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
int dht22_val[5] = {0, 0, 0, 0, 0}; //according to the docu 8 bit per group

int dht22_read_val()
{
    int dht22 = 1;
    int max_time = 100;
    uint8_t las = LOW; //last state
    uint8_t cnt = 0;
    uint8_t j = 0, i;
    memset(dht22_val, 0, 40);

    //host send start signal
    pinMode(dht22, OUTPUT);   //set pin to output
    digitalWrite(dht22, LOW); //set to low at least 1ms
    delay(1);
    digitalWrite(dht22, HIGH); //set to high 20-30us
    delayMicroseconds(25);

    //start recieve dht response
    pinMode(dht22, INPUT); //set pin to input
    for (i = 0; i < max_time; i++)
    {
        cnt = 0; //for recording the lenth of HIGH and LOW
        while (digitalRead(dht22) == las)
        { //read pin state to see if dht responsed. if dht always high for 255 + 1 times, break this while circle
            cnt++;
            delayMicroseconds(1);
            if (cnt == 255)
                break;
        }
        las = digitalRead(dht22); //read current state and store as last state.
        if (cnt == 255)           //if dht always high for 255 + 1 times, break this for circle
            break;
        // top 3 transistions are ignored, maybe aim to wait for dht finish response signal
        if ((i >= 3) && (i % 2 == 1))
        {
            dht22_val[j / 8] <<= 1;    //write 1 bit to 0 by moving left (auto add 0)
            if (cnt > 30)              //long mean 1(while short is shorter than 28)
                dht22_val[j / 8] |= 1; //write 1 bit to 1
            j++;
        }
    }
    //printf("i readed successfully\n");
    // verify checksum and print the verified data
    if ((j == 40) && (dht22_val[4] == ((dht22_val[0] + dht22_val[1] + dht22_val[2] + dht22_val[3]) & 0xFF)))
    {
        float f, h;
        h = dht22_val[0] * 256 + dht22_val[1];
        h /= 10.0;
        f = (dht22_val[2] & 0x7F) * 256 + dht22_val[3];
        f /= 10.0;
        if (dht22_val[2] & 0x80) //whether below zero
            f *= -1;
        printf("Temp =  %.1f *C, Hum = %.1f %% \n", f, h);
        return 1;
    }
    else
    {
        //printf("i failed the check\n");
        return 0;
    }
}

int main()
{
    if (wiringPiSetup() == -1)
    {
        exit(1); //fail to initialize, please to check the root
    }

    for (int i = 0; i < 5;)
    {
        int res = dht22_read_val();
        if (res)
        {
            i++;
        }
        delay(2500); //accord to the doc,not recommend to read with an interval less than 2s
    }
    return 0;
}
