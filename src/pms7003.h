/**
file:     pms7003.h
author:   megumifox

MIT License

Copyright (c) 2020 megumifox <i@megumifox.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

**/

#ifndef _PMS7003_H_
#define _PMS7003_H_

#include <stdint.h>
#include <string.h>
#include "app_uart.h"
#include "ble_nus.h"

#define PMS7003_DATA_SIZE 32
#define PMS7003_BLE_MSG_SIZE 10

typedef struct{
  uint8_t magic_1;          // Magic Header 1 0x42 (fixed)
  uint8_t magic_2;          // Magic Header 2 0x4d (fixed)
  uint16_t frame_length;    // Frame length = 2x13 + 2 (data + parity) (28)

  uint16_t pm_1_0;          // PM1.0 concentration (CF = 1, standard particles) Unit ug/m^3
  uint16_t pm_2_5;          // PM2.5 concentration (CF = 1, standard particulates) Unit ug/m^3
  uint16_t pm_10_0;         // PM10 concentration (CF = 1, standard particulate matter) Unit ug/m^3
  
  uint16_t pm_1_0_atmos;    // PM1.0 concentration (in the atmosphere) Unit ug/m^3
  uint16_t pm_2_5_atmos;    // PM2.5 concentration (in the atmosphere) Unit ug/m^3
  uint16_t pm_10_0_atmos;   // PM10 concentration (in the atmosphere) Unit ug/m^3

  uint16_t raw_gt_0_3;      // Particles in 0.1 liter of air > 0.3um 
  uint16_t raw_gt_0_5;      // Particles in 0.1 liter of air > 0.5um 
  uint16_t raw_gt_1_0;      // Particles in 0.1 liter of air > 1.0um 
  uint16_t raw_gt_2_5;      // Particles in 0.1 liter of air > 2.5um 
  uint16_t raw_gt_5_0;      // Particles in 0.1 liter of air > 5.0um 
  uint16_t raw_gt_10_0;     // Particles in 0.1 liter of air > 10um 
  
  uint8_t version_number;   // Version number
  uint8_t error_code;       // Error code

  uint16_t checksum;        // Sum of each byte from  magic_1 to error_code
} pms7003_t;

typedef union {
    pms7003_t data;
    uint8_t data_buf[PMS7003_DATA_SIZE];
} pms7003_data_t;

typedef struct{
    uint8_t magic_header;   // Magic Header 0x77 (fixed)
    uint8_t msg_type;       // Message Type
    uint16_t block[3];      // Payload
    uint16_t checksum;      // Checksum
} pms7003_ble_msg_struct_t;

typedef union {
    pms7003_ble_msg_struct_t msg;
    uint8_t msg_array[PMS7003_BLE_MSG_SIZE];
} pms7003_ble_msg_block_t;

pms7003_ble_msg_block_t pms7003_ble_msg_gen(uint8_t type,uint16_t block[3]);

void pms7003_uart_event_handle(app_uart_evt_t * p_event);

bool pms7003_data_is_valid(pms7003_data_t data_array);

void pms7003_data_copy(pms7003_data_t data_array);

void pms7003_data_invalid();

void pms7003_data_handle(pms7003_data_t data_array);

void pms7003_data_report();



#endif /*_PMS7003_H_*/
