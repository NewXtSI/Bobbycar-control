#include <Arduino.h>

#include "../include/config.h"

void ui_task(void *param);

void setup() {
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    xTaskCreatePinnedToCore(ui_task, "ui_task", 1024 * 14, NULL, 2, nullptr, 1);

}
void loop() {
    delay(10);
}

