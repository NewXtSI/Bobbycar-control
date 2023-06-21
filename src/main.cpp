#include <Arduino.h>

#include "../include/config.h"

void ui_task(void *param);
void communication_task(void *param);
void i2c_task(void *param);

void setup() {
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    xTaskCreatePinnedToCore(ui_task, "ui_task", 1024 * 14, NULL, 2, nullptr, 1);
    xTaskCreate(i2c_task, "i2c_task", 1024 * 6, NULL, 1, nullptr);
    xTaskCreate(communication_task, "communication_task", 1024 * 6, NULL, 4, nullptr);

}
void loop() {
    delay(10);
}

