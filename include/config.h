#ifndef F9019A2B_C53E_4EBF_A9AD_2D0A98E85C02
#define F9019A2B_C53E_4EBF_A9AD_2D0A98E85C02
// 3 Pins -> BBCar
// Rot -> Grau              RX
// Grün -> Schwarz          GND
// Schwarz -> Blau          TX
#define     BBCAR_TX        GPIO_NUM_12
#define     BBCAR_RX        GPIO_NUM_13



typedef struct{
   uint16_t start;
   int16_t  steer;
   int16_t  speed;
   uint16_t checksum;
} SerialCommand;
/*
Brauche:
  - Controlmode         (lesen / schreiben)
  - * siehe Multimode --- I_MOT_MAX           (lesen / schreiben)
  - * siehe Multimode --- N_MOT_MAX           (lesen / schreiben)
  - Tempomat            (lesen / schreiben)
  - Standstill          (lesen / schreiben)
  - Electric brake      (lesen / schreiben)
  - Multimode-Features  (lesen / schreiben)
      #define MULTI_MODE_DRIVE_M1_MAX   175
      #define MULTI_MODE_DRIVE_M1_RATE  250
      #define MULTI_MODE_M1_I_MOT_MAX   4
      #define MULTI_MODE_M1_N_MOT_MAX   30

      #define MULTI_MODE_DRIVE_M3_MAX   1000
      #define MULTI_MODE_DRIVE_M3_RATE  450
      #define MULTI_MODE_M3_I_MOT_MAX   I_MOT_MAX
      #define MULTI_MODE_M3_N_MOT_MAX   N_MOT_MAX

Future:
    - Field Weakening
*/


// cmdLed   neue Nutzung
// Bit 0:       Tempomat an, aus
// Bit 1:       Standstill

typedef struct{
   uint16_t start;
   int16_t  cmd1;
   int16_t  cmd2;
   int16_t  speedR_meas;
   int16_t  speedL_meas;
   int16_t  batVoltage;
   int16_t  boardTemp;
   uint16_t cmdLed;
   uint16_t checksum;
} SerialFeedback;

#endif /* F9019A2B_C53E_4EBF_A9AD_2D0A98E85C02 */
