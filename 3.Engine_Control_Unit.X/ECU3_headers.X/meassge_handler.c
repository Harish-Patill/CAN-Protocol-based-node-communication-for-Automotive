
#include <xc.h>
#include <string.h>
#include "message_handler.h"
#include "msg_id.h"
#include "can.h"
#include "clcd.h"


volatile unsigned char led_state = LED_OFF, status = e_ind_off;

volatile unsigned char indicator_status = e_ind_off;
volatile unsigned char blink_flag = 0;
void handle_speed_data(uint8_t *data, uint8_t len){
    static uint16_t prev_speed = 0;
    static uint8_t first_time = 1;

    if(len == 2){
        uint16_t speed;

        speed = data[0] | ((uint16_t)data[1] << 8);

        // Print only when speed changes
        if(first_time || speed != prev_speed){
            char str[6] = "S:000";

            str[2] = (speed / 100) + '0';
            str[3] = ((speed / 10) % 10) + '0';
            str[4] = (speed % 10) + '0';

            clcd_print((const unsigned char *)str, LINE1(0));

            prev_speed = speed;
            first_time = 0;
        }
    }
}

void handle_gear_data(uint8_t *data, uint8_t len){
    static unsigned char prev_gear = 0;
    static uint8_t first_time = 1;

    if(len == 1){
        unsigned char gear = data[0];

        if(first_time || gear != prev_gear){
            char str[4] = "G:0";

            str[2] = gear;

            clcd_print((const unsigned char *)str, LINE1(6));

            prev_gear = gear;
            first_time = 0;
        }
    }
}

void handle_rpm_data(uint8_t *data, uint8_t len){
    static uint16_t prev_rpm = 0;
    static uint8_t first_time = 1;

    if(len == 2){
        uint16_t rpm;

        rpm = data[0] | ((uint16_t)data[1] << 8);

        if(first_time || rpm != prev_rpm){
            char str[7] = "R:0000";

            str[2] = (rpm / 1000) + '0';
            str[3] = ((rpm / 100) % 10) + '0';
            str[4] = ((rpm / 10) % 10) + '0';
            str[5] = (rpm % 10) + '0';

            clcd_print((const unsigned char *)str, LINE1(9));

            prev_rpm = rpm;
            first_time = 0;
        }
    }
}

void handle_engine_temp_data(uint8_t *data, uint8_t len){
    static uint16_t prev_temp = 0;
    static uint8_t first_time = 1;

    if(len == 2){
        uint16_t temperature;

        temperature = data[0] | ((uint16_t)data[1] << 8);

        if(first_time || temperature != prev_temp){
            char str[6] = "T:000";

            str[2] = (temperature / 100) + '0';
            str[3] = ((temperature / 10) % 10) + '0';
            str[4] = (temperature % 10) + '0';

            clcd_print((const unsigned char *)str, LINE2(0));

            prev_temp = temperature;
            first_time = 0;
        }
    }
}

void blink_indicator_led(void){
    static unsigned int count = 0;

    count++;

    if(count >= 250){
        count = 0;
        blink_flag = !blink_flag;

        if(indicator_status == e_ind_left){
            if(blink_flag){
                LEFT_IND_ON();
                RIGHT_IND_OFF();
            }
            else{
                LEFT_IND_OFF();
                RIGHT_IND_OFF();
            }
        }
        else if(indicator_status == e_ind_right){
            if(blink_flag){
                RIGHT_IND_ON();
                LEFT_IND_OFF();
            }
            else{
                LEFT_IND_OFF();
                RIGHT_IND_OFF();
            }
        }
        else if(indicator_status == 3){
            if(blink_flag){
                LEFT_IND_ON();
                RIGHT_IND_ON();
            }
            else{
                LEFT_IND_OFF();
                RIGHT_IND_OFF();
            }
        }
        else{
            LEFT_IND_OFF();
            RIGHT_IND_OFF();
        }
    }
}


void handle_indicator_data(uint8_t *data, uint8_t len){
    static unsigned char prev_indicator = 0xFF;

    if(len == 1){
        unsigned char indicator = data[0];

        if(indicator != prev_indicator){
            indicator_status = indicator;
            blink_flag = 0;

            LEFT_IND_OFF();
            RIGHT_IND_OFF();

            display_indicator(indicator);   /* show state on CLCD */

            prev_indicator = indicator;
        }

        if(indicator == e_ind_off){
            LEFT_IND_OFF();
            RIGHT_IND_OFF();
        }
    }
}

void process_canbus_data() {   
   
    uint16_t msg_id;
    uint8_t data[8];
    uint8_t len;
    
    can_receive(&msg_id,data,&len);
    
    if(len == 0)
        return;
    
    switch(msg_id){
        case SPEED_MSG_ID :
            handle_speed_data(data,len);
            break;
            
        case GEAR_MSG_ID :
            handle_gear_data(data,len);
            break;
        
        case RPM_MSG_ID :
            handle_rpm_data(data, len);
            break;
        
        case ENG_TEMP_MSG_ID:
            handle_engine_temp_data(data, len);
            break;
        
        case INDICATOR_MSG_ID :
            handle_indicator_data(data, len);
            break;       
                    
    }
}


static void display_indicator(unsigned char indicator){
    /* Trailing spaces clear any leftover characters */
    if(indicator == e_ind_left)
        clcd_print((const unsigned char *)"I: L  ", LINE2(6));
    else if(indicator == e_ind_right)
        clcd_print((const unsigned char *)"I: R  ", LINE2(6));
    else if(indicator == 3)
        clcd_print((const unsigned char *)"I: B  ", LINE2(6));
    else
        clcd_print((const unsigned char *)"I: O  ", LINE2(6));
}