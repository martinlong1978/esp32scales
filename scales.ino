#include <Arduino.h>
#include <SPI.h>
#include <U8g2lib.h>
#include "menu.h"
#include <ADS1232.h>
#include "queues.h"

ADS1232 scale(7, 11, 10);
//ADS1232 scale(9, 13, 12);
U8G2_SH1107_64X128_F_HW_I2C u8g2(U8G2_R1);
MenuManager menu(&u8g2);
QueueHandle_t weightStream;

void IRAM_ATTR ISR_A()
{
    if (menu.lastbutton == 0 && digitalRead(BTN_A) == LOW)
        menu.lastbutton = BTN_A;
    else if (digitalRead(BTN_A) == HIGH)
        menu.lastbutton = 0;
}

void IRAM_ATTR ISR_B()
{
    if (menu.lastbutton == 0 && digitalRead(BTN_B) == LOW)
        menu.lastbutton = BTN_B;
    else if (digitalRead(BTN_B) == HIGH)
        menu.lastbutton = 0;
}

void IRAM_ATTR ISR_C()
{
    if (menu.lastbutton == 0 && digitalRead(BTN_C) == LOW)
        menu.lastbutton = BTN_C;
    else if (digitalRead(BTN_C) == HIGH)
        menu.lastbutton = 0;
}

void IRAM_ATTR REL()
{
    menu.lastbutton = 0;
}

void sensor_loop(void *parameters)
{
    menu.weightManager.load();
    for (;;)
    {
        long value = scale.raw_read(100);
        xQueueSend(weightStream, &value, 1000 / portTICK_PERIOD_MS);
        Serial.printf("Weight %d\n", value);
    }
}

void ui_loop(void *parameters)
{
    for (;;)
    {
        menu.display_loop();
    }
}

void setup()
{
    u8g2.begin();
    Serial.begin(115200);

    delay(3000);
   
    scale.power_up();

    attachInterrupt(BTN_A, ISR_A, CHANGE);
    attachInterrupt(BTN_B, ISR_B, CHANGE);
    attachInterrupt(BTN_C, ISR_C, CHANGE);

    weightStream = xQueueCreate(10, sizeof(long));

    xTaskCreate(
        ui_loop,
        "UI",
        4000,
        NULL,
        1,
        NULL);

    xTaskCreate(
        sensor_loop,
        "Sensor",
        4000,
        NULL,
        1,
        NULL);
}

void loop()
{
    delay(1000);
}