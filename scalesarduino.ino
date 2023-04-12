#include <Arduino.h>
#include <SPI.h>
#include <U8g2lib.h>
#include "menu.h"
#include <ADS1232.h>
#include "queues.h"
#include "esp_sleep.h"

ADS1232 scale(7, 11, 10);
// ADS1232 scale(9, 13, 12);
U8G2_SH1107_64X128_F_HW_I2C u8g2(U8G2_R1);
MenuManager menu(&u8g2);
QueueHandle_t weightStream;

hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR onTimer()
{
    portENTER_CRITICAL_ISR(&timerMux);
    if (menu.pressed)
    {
        menu.isLongPress = true;
        menu.pressed = false;
    }
    timerAlarmDisable(timer);
    portEXIT_CRITICAL_ISR(&timerMux);
}

void ButtonISR(uint8_t button)
{
    bool pressed = digitalRead(button) == LOW;
    portENTER_CRITICAL_ISR(&timerMux);
    if (menu.lastbutton == 0 && pressed)
    {
        menu.lastbutton = button;
        menu.isLongPress = false;
        menu.pressed = true;
        timerRestart(timer);
        timerAlarmWrite(timer, 1000000, false);
        timerAlarmEnable(timer);
    }
    else if (digitalRead(button) == HIGH)
    {
        if (!menu.isLongPress)
        {
            menu.pressed = false;
            menu.isLongPress = false;
        }
        timerAlarmDisable(timer);
    }
    portEXIT_CRITICAL_ISR(&timerMux);
}

void IRAM_ATTR ISR_A()
{
    ButtonISR(BTN_A);
}

void IRAM_ATTR ISR_B()
{
    ButtonISR(BTN_B);
}

void IRAM_ATTR ISR_C()
{
    ButtonISR(BTN_C);
}

void sensor_loop(void *parameters)
{
    menu.weightManager.load();
    for (;;)
    {
        long value = scale.raw_read(10);
        if (value == 8388607)
        {
            ESP.restart();
        }
        else
        {
            xQueueSend(weightStream, &value, 1000 / portTICK_PERIOD_MS);
            Serial.printf("Weight %d\n", value);
        }
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
    gpio_deep_sleep_hold_dis();
    gpio_hold_dis(GPIO_NUM_5);

    pinMode(5, OUTPUT);
    digitalWrite(5, HIGH);

    timer = timerBegin(0, 80, true);

    // delay(3000);

    u8g2.begin();
    // u8g2.initDisplay();
    Serial.begin(115200);

    scale.power_up();

    attachInterrupt(BTN_A, ISR_A, CHANGE);
    attachInterrupt(BTN_B, ISR_B, CHANGE);
    attachInterrupt(BTN_C, ISR_C, CHANGE);

    timerAttachInterrupt(timer, &onTimer, true);
    timerAlarmWrite(timer, 1000000, false);

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