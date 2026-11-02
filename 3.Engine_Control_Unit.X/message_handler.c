#include "ecu3_header.h"

volatile unsigned char led_state = LED_OFF, status = e_ind_off;

void handle_speed_data(uint8_t *data, uint8_t len){
    unsigned char buf[4];
    uint8_t speed;

    if(len == 0) return;

    speed = data[0];                       /* raw number, 0..100 */
    buf[0] = (speed / 100) + '0';
    buf[1] = ((speed / 10) % 10) + '0';
    buf[2] = (speed % 10) + '0';
    buf[3] = '\0';

    clcd_print(buf, LINE2(0));
}

void handle_gear_data(uint8_t *data, uint8_t len){
    unsigned char buf[2];

    if(len == 0) return;

    buf[0] = data[0];                      /* ASCII 'N', 'R', '1'..'5' */
    buf[1] = '\0';

    clcd_print(buf, LINE2(10));
}

void handle_rpm_data(uint8_t *data, uint8_t len) 
{
    //Implement the rpm function
}

void handle_engine_temp_data(uint8_t *data, uint8_t len) 
{
    //Implement the temperature function
}

void handle_indicator_data(uint8_t *data, uint8_t len) 
{
    //Implement the indicator function
}

void process_canbus_data(void){
    uint16_t msg_id;
    uint8_t  data[8];
    uint8_t  len;

    can_receive(&msg_id, data, &len);

    if(len == 0) return;                   /* nothing new, do nothing */

    switch(msg_id){
        case SPEED_MSG_ID:
            handle_speed_data(data, len);
            break;

        case GEAR_MSG_ID:
            handle_gear_data(data, len);
            break;

        case RPM_MSG_ID:
            handle_rpm_data(data, len);
            break;

        case ENG_TEMP_MSG_ID:
            handle_engine_temp_data(data, len);
            break;

        case INDICATOR_MSG_ID:
            handle_indicator_data(data, len);
            break;
    }
}