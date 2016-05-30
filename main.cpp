// This code is designed to work with the NXP FRDM-K64F board 
// Mbed Platform
// c. Kevin Maganga 2016
#include "mbed.h"
#include "BMP180.h"
Serial usb(USBTX,USBRX);
DigitalOut gpo(D0);
DigitalOut led(LED_BLUE);
I2C i2c(I2C_SDA, I2C_SCL);
BMP180 bmp180(I2C_SDA,I2C_SCL);

int main()
{
    usb.baud(9600);
    while(1) {
        if (bmp180.init() != 0) {
            usb.printf("Error communicating with BMP180\r\n");
        } else {
            usb.printf("Initialized BMP180\r\n");
            break;
        }
        wait(1);
    }
 
    while(1) {
        bmp180.startTemperature();
        wait_ms(5);     // Wait for conversion to complete
        float temp;
        if(bmp180.getTemperature(&temp) != 0) {
            usb.printf("Error getting temperature\r\n");
            continue;
        }
 
        bmp180.startPressure(BMP180::ULTRA_LOW_POWER);
        wait_ms(10);    // Wait for conversion to complete
        int pressure;
        if(bmp180.getPressure(&pressure) != 0) {
            usb.printf("Error getting pressure\r\n");
            continue;
        }
 
        usb.printf("Pressure = %d Pa Temperature = %f C\r\n", pressure, temp);
        wait(1);
        gpo = !gpo; // toggle pin
        led = !led; // toggle led
        wait(0.2f);
    }
    
}
