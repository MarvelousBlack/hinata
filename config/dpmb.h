#ifndef DPMB_H
#define DPMB_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nrf_gpio.h"

// LEDs definitions for DPMB
#define LEDS_NUMBER    4

#define LED_GREEN      9
#define LED_RED        10
#define LED_POW        21
#define LED_BLE        22

#define LED_START      LED_BLE
#define LED_1          LED_BLE
#define LED_2          LED_POW
#define LED_3          LED_GREEN
#define LED_4          LED_RED
#define LED_STOP       LED_RED

#define LEDS_ACTIVE_STATE 1

#define LEDS_LIST { LED_1, LED_2, LED_3, LED_4 }

#define LEDS_INV_MASK  LEDS_MASK

#define BSP_LED_0      LED_1
#define BSP_LED_1      LED_2
#define BSP_LED_2      LED_3
#define BSP_LED_3      LED_4

#define BUTTONS_NUMBER 1

#define BUTTON_START   30
#define BUTTON_1       30
#define BUTTON_STOP    30
#define BUTTON_PULL    NRF_GPIO_PIN_PULLUP

#define BUTTONS_ACTIVE_STATE 0

#define BUTTONS_LIST { BUTTON_1 }

#define BSP_BUTTON_0   BUTTON_1

#define PMS_TX        5
#define PMS_RX        4

#define RX_PIN_NUMBER  PMS_RX
#define TX_PIN_NUMBER  PMS_TX
#define CTS_PIN_NUMBER 0
#define RTS_PIN_NUMBER 0
#define HWFC           false

#define PIN_BAT_POWER 29
#define PIN_WAKE_BTN  30

#define RTC_SDA       23
#define RTC_SCL       24

#define BAT_VO        3
#define BAT_CH        11
#define BAT_STANDBY   12

// Low frequency clock source to be used by the SoftDevice
#ifdef S210
#define NRF_CLOCK_LFCLKSRC      NRF_CLOCK_LFCLKSRC_XTAL_20_PPM
#else
#define NRF_CLOCK_LFCLKSRC      {.source        = NRF_CLOCK_LF_SRC_RC,            \
                                 .rc_ctiv       = 16,                                \
                                 .rc_temp_ctiv  = 1,                                \
                                 .xtal_accuracy = NRF_CLOCK_LF_XTAL_ACCURACY_20_PPM}
#endif

#ifdef __cplusplus
}
#endif

#endif // DPMB_H
