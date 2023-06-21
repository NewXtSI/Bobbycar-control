#include <Arduino.h>

void i2c_task(void *param) {
    vTaskDelete(NULL);
}
