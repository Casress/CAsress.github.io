#include "mbed.h"
#include "ultrasonic.h"
#include "XNucleo53L0A1.h"
#include <cstdio>
DigitalOut motor3(p20);
DigitalOut motor(p21);
DigitalOut motor2(p22);
DigitalOut shdn(p26);
#define VL53L0_I2C_SDA   p28
#define VL53L0_I2C_SCL   p27
static XNucleo53L0A1 *board=NULL;
void dist(int distance)
{
    if (distance <= 250) {
        motor3 = 1;
    } else {
        motor3 = 0;
    }
    //put code here to execute when the distance has changed
    printf("Distance %d mm\r\n", distance);
}

void distance(int dist) {
    if (dist <= 250) {
        motor = 1;
    } else {
        motor = 0;
    }
    printf("Distance2 %d mm\r\n", dist);
}
ultrasonic mu(p6, p7, .1, 1, &dist);    //Set the trigger pin to D8 and the echo pin to D9
ultrasonic mu2(p12, p13,.1, 1,&distance);                                       //have updates every .1 seconds and a timeout after 1
                                        //second, and call dist when the distance changes

int main()
{
    int status;
    uint32_t distance;
    DevI2C *device_i2c = new DevI2C(VL53L0_I2C_SDA, VL53L0_I2C_SCL);
    board = XNucleo53L0A1::instance(device_i2c, A2, D8, D2);
    shdn = 0; //must reset sensor for an mbed reset to work
    wait(0.1);
    shdn = 1;
    wait(0.1);
    status = board->init_board();
    while (status) {
        printf("Failed to init board! \r\n");
        status = board->init_board();
    }
    mu.startUpdates();//start measuring the distance
    mu2.startUpdates();
    
    while(1)
    {
        //Do something else here
        mu.checkDistance();     //call checkDistance() as much as possible, as this is where
        mu2.checkDistance();                 //the class checks if dist needs to be called.
        status = board->sensor_centre->get_distance(&distance);
        if (status == VL53L0X_ERROR_NONE) {
            printf("Left sensor D=%ld mm\r\n", distance);
            printf("%d\n",status);
        }
        if (status == -6) {
            motor2 = 0;
        } else if (distance <= 250) {
            motor2 = 1;
            printf("Left sensor D=%ld mm\r\n", distance);
            printf("%d\n",status);
        } else {
            motor2 = 0;
        }
    }
}
