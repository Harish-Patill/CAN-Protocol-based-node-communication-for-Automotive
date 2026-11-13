/*
 * File:   ecu2_main.c
 * Author: USER
 *
 * Created on October 29, 2026, 10:26 PM
 */


#include "ecu2_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"

void init_config()
{
    TRISB=0X00;
    PORTB=0X00;
    init_adc();
    init_uart();
    init_digital_keypad();
    init_can();
    
}
void main(){
    
    init_config();
    
        
    while(1){
        uint16_t rpm = get_rpm();
        
            uint8_t rpm_data[2];

            rpm_data[0] = rpm & 0xFF;
            rpm_data[1] = (rpm >> 8) & 0xFF;
        
            can_transmit(RPM_MSG_ID, rpm_data, 2);
            
            puts("rpm : ");
            putch((rpm/1000)+'0');
            putch(((rpm/100)%10)+'0');
            putch(((rpm/10)%10)+'0');
            putch((rpm%10)+'0');

            puts("   |   ");
        
        IndicatorStatus indicator = process_indicator();
        
            uint8_t indicator_data[1];

            indicator_data[0] = indicator;

            can_transmit(INDICATOR_MSG_ID, indicator_data, 1);
            
            puts("indicator : ");
            if(indicator == e_ind_left){
                puts("LEFT");
            }
            else if(indicator == e_ind_right){
                puts("RIGHT");
            }
            else if(indicator == e_ind_off){
                puts("PARKING");
            }
            else{
                puts("OFF");
            }

            puts("   |   ");
        
        
        unsigned int temperature = get_engine_temp();
            
            uint8_t temp_data[2];

            temp_data[0] = temperature & 0xFF;
            temp_data[1] = (temperature >> 8) & 0xFF;

            can_transmit(ENG_TEMP_MSG_ID, temp_data, 2);
            
            puts("temperature : ");
            putch((temperature / 100) + '0');
            putch(((temperature / 10) % 10) + '0');
            putch((temperature % 10) + '0');
            
            puts(" C");
            puts("\n\r");
            
            
    }
}

