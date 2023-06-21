#include <Arduino.h>
#include "../include/config.h"

#define START_FRAME         0xABCD

// Global variables
uint8_t idx = 0;                        // Index for new data pointer
uint16_t bufStartFrame;                 // Buffer Start Frame
byte *p;                                // Pointer declaration for the new received data
byte incomingByte;
byte incomingBytePrev;


SerialCommand Command;

SerialFeedback Feedback;
SerialFeedback NewFeedback;

SemaphoreHandle_t               feedbackSemaphore = NULL;
bool lockFeedback() {
    if (feedbackSemaphore == NULL)
        feedbackSemaphore = xSemaphoreCreateMutex();
    if (xSemaphoreTake(feedbackSemaphore, (TickType_t)10000) == pdTRUE) {
        return true;
    } else {
        Serial.printf("%s could not get semaphore!\n", __PRETTY_FUNCTION__);
        return false;
    }

    return true;
}

void unlockFeedback() {
    xSemaphoreGive(feedbackSemaphore);
}
void parseChar(byte uiChar) {
    incomingByte = uiChar;
//    Serial.printf(" 0x%02X", uiChar);
    bufStartFrame	= ((uint16_t)(incomingByte) << 8) | incomingBytePrev;       // Construct the start frame
    // Copy received data
    if (bufStartFrame == START_FRAME) {	                    // Initialize if new data is detected
        p       = (byte *)&NewFeedback;
        *p++    = incomingBytePrev;
        *p++    = incomingByte;
        idx     = 2;	
    } else if (idx >= 2 && idx < sizeof(SerialFeedback)) {  // Save the new received data
        *p++    = incomingByte; 
        idx++;
    }	
    
    // Check if we reached the end of the package
    if (idx == sizeof(SerialFeedback)) {
        uint16_t checksum;
        checksum = (uint16_t)(NewFeedback.start ^ NewFeedback.cmd1 ^ NewFeedback.cmd2 ^ NewFeedback.speedR_meas ^ NewFeedback.speedL_meas
                            ^ NewFeedback.batVoltage ^ NewFeedback.boardTemp ^ NewFeedback.cmdLed);

        // Check validity of the new data
        if (NewFeedback.start == START_FRAME && checksum == NewFeedback.checksum) {
            float speedCombined;
            // Copy the new data
            if (lockFeedback()) {
                memcpy(&Feedback, &NewFeedback, sizeof(SerialFeedback));
                unlockFeedback();
            }

            // Print data to built-in Serial
            Serial.print("1: ");   Serial.print(Feedback.cmd1);
            Serial.print(" 2: ");  Serial.print(Feedback.cmd2);
            Serial.print(" 3: ");  Serial.print(Feedback.speedR_meas);
            Serial.print(" 4: ");  Serial.print(Feedback.speedL_meas);
            Serial.print(" 5: ");  Serial.print(Feedback.batVoltage);
            Serial.print(" 6: ");  Serial.print(Feedback.boardTemp);
            Serial.print(" 7: ");  Serial.print(Feedback.cmdLed);
            speedCombined = (float)(abs(Feedback.speedR_meas)+ abs(Feedback.speedL_meas)) / 2.0;
            speedCombined *= 0.55;      // m/min
            speedCombined *= 60.0;      // m/h
            speedCombined /= 1000.0;    // km/h
            Serial.printf(" 8: %5.2f\n",speedCombined);
            // 55cm ein Reifen im Umfang
        } else {
          Serial.println("Non-valid data skipped");
        }
        idx = 0;    // Reset the index (it prevents to enter in this if condition in the next cycle)
    }

    // Update previous states
    incomingBytePrev = incomingByte;

}

unsigned long iTimeSend = 0;

// ########################## SEND ##########################
void Send(int16_t uSteer, int16_t uSpeed)
{
  // Create command
  Command.start    = (uint16_t)START_FRAME;
  Command.steer    = (int16_t)uSteer;
  Command.speed    = (int16_t)uSpeed;
  Command.checksum = (uint16_t)(Command.start ^ Command.steer ^ Command.speed);

  // Write to Serial
  Serial1.write((uint8_t *) &Command, sizeof(Command)); 
}

#define TIME_SEND           100         // [ms] Sending time interval


void communication_task(void *param) {
    int iSpeed = 0;
    Serial1.begin(115200, SERIAL_8N1, BBCAR_RX, BBCAR_TX);
    unsigned int uiStart = millis();
    vTaskDelay(100);
    while (1) {
        unsigned long timeNow = millis();
        // Send commands
        if (iTimeSend <= timeNow) {
            iTimeSend = timeNow + TIME_SEND;
            if ((millis()-uiStart) > 30000)
                Send(0, 0);
            else
                Send(0, 50);
        }
        if (Serial1.available()) {
            parseChar(Serial1.read());
        }
        vTaskDelay(1);
    }
    vTaskDelete(NULL);
}