/*
 * @Author: Gehrychiang
 * @LastEditTime: 2020-03-19 20:36:58
 * @Website: www.yilantingfeng.site
 * @E-mail: gehrychiang@aliyun.com
 */
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define MAX_TIME 100
#define DHT11PIN 1                  //读取数据引脚
#define ATTEMPTS 7                  //retry 5 times when no response
int dht22_val[5] = {0, 0, 0, 0, 0}; //according to the docu 8 bit per group

int dht11_read_val()
{
    uint8_t las = HIGH; //last state
    uint8_t counter = 0;
    uint8_t j = 0, i;
    for (i = 0; i < 5; i++)
        dht22_val[i] = 0;
    //host send start signal
    pinMode(DHT11PIN, OUTPUT);   //set pin to output
    digitalWrite(DHT11PIN, LOW); //set to low at least 1ms
    delay(1);
    digitalWrite(DHT11PIN, HIGH); //set to high 20-40us
    delayMicroseconds(30);

    //start recieve dht response
    pinMode(DHT11PIN, INPUT); //set pin to input
    for (i = 0; i < MAX_TIME; i++)
    {
        counter = 0;
        while (digitalRead(DHT11PIN) == las)
        { //read pin state to see if dht responsed. if dht always high for 255 + 1 times, break this while circle
            counter++;
            delayMicroseconds(1);
            if (counter == 255)
                break;
        }
        las = digitalRead(DHT11PIN); //read current state and store as last state.
        if (counter == 255)          //if dht always high for 255 + 1 times, break this for circle
            break;
        // top 3 transistions are ignored, maybe aim to wait for dht finish response signal
        if ((i >= 4) && (i % 2 == 0))
        {
            dht22_val[j / 8] <<= 1;    //write 1 bit to 0 by moving left (auto add 0)
            if (counter > 30)          //long mean 1(while short is shorter than 28)
                dht22_val[j / 8] |= 1; //write 1 bit to 1
            j++;
        }
    }
    printf("i readed successfully\n");
    // verify checksum and print the verified data
    if ((j >= 40) && (dht22_val[4] == ((dht22_val[0] + dht22_val[1] + dht22_val[2] + dht22_val[3]) & 0xFF)))
    {
        float f, h;
        h = dht22_val[0] * 256 + dht22_val[1];
        h /= 10;
        f = (dht22_val[2] & 0x7F) * 256 + dht22_val[3];
        f /= 10.0;
        if (dht22_val[2] & 0x80)
            f *= -1;
        printf("Temp =  %.1f *C, Hum = %.1f %% \n", f, h);
        return 1;
    }
    else
    {
        printf("i failed the check\n");
        return 0;
    }
}

int main(void)
{
    int attempts = ATTEMPTS;
    if (wiringPiSetup() == -1)
        exit(1);
    while (attempts--)
    {
        int res = dht11_read_val(); //get result including printing out
        if (res)
        {
            break;
        }
        delay(2500); //the sensor cannot work consistently
    }
    if (attempts <= 0)
    {
        printf("fail\n");
    }
    return 0;
}
