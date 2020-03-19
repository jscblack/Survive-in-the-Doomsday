/*
 * @Author: Gehrychiang
 * @LastEditTime: 2020-03-19 20:22:37
 * @Website: www.yilantingfeng.site
 * @E-mail: gehrychiang@aliyun.com
 */
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define MAX_TIME 100
#define DHT11PIN 7 //读取数据引脚
#define ATTEMPTS 5 //retry 5 times when no response
int dht11_val[5] = {0, 0, 0, 0, 0};

int dht11_read_val()
{
    uint8_t lststate = LOW; //last state
    uint8_t counter = 0;
    uint8_t j = 0, i;
    for (i = 0; i < 5; i++)
        dht11_val[i] = 0;
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
        while (digitalRead(DHT11PIN) == lststate)
        { //read pin state to see if dht responsed. if dht always high for 255 + 1 times, break this while circle
            counter++;
            delayMicroseconds(1);
            if (counter == 255)
                break;
        }
        lststate = digitalRead(DHT11PIN); //read current state and store as last state.
        if (counter == 255)               //if dht always high for 255 + 1 times, break this for circle
            break;
        // top 3 transistions are ignored, maybe aim to wait for dht finish response signal
        if (i < 2)
        {
            printf("%d\n", counter);
        }
        if ((i >= 2) && (i % 2 == 0))
        {
            dht11_val[j / 8] <<= 1;    //write 1 bit to 0 by moving left (auto add 0)
            if (counter > 30)          //long mean 1
                dht11_val[j / 8] |= 1; //write 1 bit to 1
            j++;
        }
    }
    printf("i readed successfully\n");
    // verify checksum and print the verified data
    if ((j >= 40) && (dht11_val[4] == ((dht11_val[0] + dht11_val[1] + dht11_val[2] + dht11_val[3]) & 0xFF)))
    {
        float f, h;
        h = dht11_val[0] * 256 + dht11_val[1];
        h /= 10;
        f = (dht11_val[2] & 0x7F) * 256 + dht11_val[3];
        f /= 10.0;
        if (dht11_val[2] & 0x80)
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
    while (attempts)
    {                                   //you have 5 times to retry
        int success = dht11_read_val(); //get result including printing out
        if (success)
        { //if get result, quit program; if not, retry 5 times then quit
            break;
        }
        attempts--;
        delay(2500);
    }
    if (attempts <= 0)
    {
        printf("fail\n");
    }
    return 0;
}
