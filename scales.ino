#include <Arduino.h>
#include <SPI.h>
#include <U8g2lib.h>
#include "menu.h"

U8G2_SH1107_64X128_F_HW_I2C u8g2(U8G2_R1);
MenuManager menu(&u8g2);

//[full framebuffer, size = 1024 bytes]

void IRAM_ATTR ISR_A()
{
    if (menu.lastbutton == 0 && digitalRead(BTN_A) == LOW)
        menu.lastbutton = BTN_A;
    else if(digitalRead(BTN_A) == HIGH)
        menu.lastbutton = 0;
}

void IRAM_ATTR ISR_B()
{
    if (menu.lastbutton == 0 && digitalRead(BTN_B) == LOW)
        menu.lastbutton = BTN_B;
    else if(digitalRead(BTN_B) == HIGH)
        menu.lastbutton = 0;
}

void IRAM_ATTR ISR_C()
{
    if (menu.lastbutton == 0 && digitalRead(BTN_C) == LOW)
        menu.lastbutton = BTN_C;
    else if(digitalRead(BTN_C) == HIGH)
        menu.lastbutton = 0;
}

void IRAM_ATTR REL()
{
    menu.lastbutton = 0;
}

void setup()
{
    u8g2.begin();
    Serial.begin(115200);

    attachInterrupt(BTN_A, ISR_A, CHANGE);
    attachInterrupt(BTN_B, ISR_B, CHANGE);
    attachInterrupt(BTN_C, ISR_C, CHANGE);

}

void loop()
{
    menu.display_loop();
}