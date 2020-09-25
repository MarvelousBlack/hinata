/**
file:     pms7003.c
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

#include "pms7003.h"

extern ble_nus_t      m_nus;    /**< Structure to identify the Nordic UART Service. */

extern pms7003_data_t pms7003_data;   /**< Structure to save PMS7003 data. */       

// Function for handling app_uart events. Data from pms7003
void pms7003_uart_event_handle(app_uart_evt_t * p_event){
    static uint8_t index = 0;
    static pms7003_data_t data_array;
    static const uint8_t PMS7003_MAGIC_HEADER[] = {0x42,0x4d,0x00,0x1c};

    switch (p_event->evt_type){
        case APP_UART_DATA_READY:
            UNUSED_VARIABLE(app_uart_get(&data_array.data_buf[index]));
            
            if (index > 3){
                index++;
                if (index >= PMS7003_DATA_SIZE){
                    pms7003_data_handle(data_array);
                    index = 0;
                }
                break;
            } else {
                if (data_array.data_buf[index] == PMS7003_MAGIC_HEADER[index]){
                    index++;
                } else {
                    index = 0;
                }
                break;
            }

        case APP_UART_COMMUNICATION_ERROR:
            APP_ERROR_HANDLER(p_event->data.error_communication);
            break;

        case APP_UART_FIFO_ERROR:
            APP_ERROR_HANDLER(p_event->data.error_code);
            break;

        default:
            break;
    }
}

bool pms7003_data_is_valid(pms7003_data_t data_array){
    uint16_t check_code = 0;

    for(int i=0; i<(PMS7003_DATA_SIZE-2); i++){
        check_code += data_array.data_buf[i];
    }
    // nrf51 use little endian but pms7003 use big endian, so we have to swap bytes.
    // https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
    check_code = __builtin_bswap16(check_code);
    //for other compiler
    //check_code = ((check_code & 0xff) << 8) | ((check_code & 0xff00) >> 8);      
    return (check_code == data_array.data.checksum);
}

void pms7003_data_handle(pms7003_data_t data_array){
    if (pms7003_data_is_valid(data_array)){
        pms7003_data_copy(data_array);
        pms7003_data_report();
    } else {
        pms7003_data_invalid();
    }
}

void pms7003_data_copy(pms7003_data_t data_array){
    for(int i=0; i<PMS7003_DATA_SIZE; i++){
        pms7003_data.data_buf[i] = data_array.data_buf[i];
    }
}

void pms7003_data_invalid(){
    pms7003_ble_msg_block_t ble_msg;
    uint32_t err_code;

    uint16_t block[] = {0x00,0x00,0x00};
    ble_msg = pms7003_ble_msg_gen(0xEE,block);
    err_code = ble_nus_string_send(&m_nus,(uint8_t *)&ble_msg.msg_array, PMS7003_BLE_MSG_SIZE);
    if (err_code != NRF_ERROR_INVALID_STATE){
        APP_ERROR_CHECK(err_code);
    }
}

pms7003_ble_msg_block_t pms7003_ble_msg_gen(uint8_t type,uint16_t block[3]){
    pms7003_ble_msg_block_t ble_msg;
    int i = 0;

    ble_msg.msg.magic_header = 0x77;
    ble_msg.msg.msg_type = type;
    ble_msg.msg.checksum = 0x00;

    for (i = 0;i < 3;i++){
        ble_msg.msg.block[i] = block[i];
    }
    for (i =0 ;i < PMS7003_BLE_MSG_SIZE -2;i++){
        ble_msg.msg.checksum += ble_msg.msg_array[i];
    }
    ble_msg.msg.checksum = __builtin_bswap16(ble_msg.msg.checksum);
    //for other compiler
    //ble_msg.msg.checksum = ((ble_msg.msg.checksum & 0xff) << 8) | ((ble_msg.msg.checksum & 0xff00) >> 8);      

    return ble_msg;
}

void pms7003_data_report(){
    uint32_t       err_code;
    uint16_t block[] = {pms7003_data.data.pm_1_0,pms7003_data.data.pm_2_5,pms7003_data.data.pm_10_0};
    pms7003_ble_msg_block_t ble_msg;
    
    ble_msg = pms7003_ble_msg_gen(0x77,block);

    err_code = ble_nus_string_send(&m_nus,(uint8_t *)&ble_msg.msg_array, PMS7003_BLE_MSG_SIZE);
    if (err_code != NRF_ERROR_INVALID_STATE){
        APP_ERROR_CHECK(err_code);
    }
}


    

