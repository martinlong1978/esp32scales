#include <Arduino.h>
#include <SPI.h>
#include <U8g2lib.h>
#include "menu.h"

U8G2_SH1107_64X128_F_HW_I2C u8g2(U8G2_R1);
MenuManager menu(&u8g2);

//[full framebuffer, size = 1024 bytes]

void setup()
{
    u8g2.begin();
    Serial.begin(115200);

}

void loop()
{
    menu.display_loop();  
}