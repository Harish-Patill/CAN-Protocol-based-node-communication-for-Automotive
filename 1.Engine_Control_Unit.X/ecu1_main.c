#include "ecu1_header.h"

#define DEBUG_UART 1    // set to 0 for the final build

void init_config(void){
    init_adc();
    init_can();
    init_digital_keypad();
#if DEBUG_UART
    init_uart();        // will be used if debug is set
#endif
}

void main(void){
    uint8_t speed;
    unsigned char gear;

    init_config();      // initializer

    while(1){
        speed = get_speed();        // gets speed
        gear  = get_gear_pos();     // gets gear position

#if DEBUG_UART                      // used to debug and check output in the tera term, done using uart protocol
        puts("speed : ");
        putch((speed/100)+'0');
        putch(((speed/10)%10)+'0');
        putch((speed%10)+'0');
        puts("    |    ");
        puts("gear : ");
        putch(gear);
        puts("\n\r");
#endif
        
        // data transmission through can
        can_transmit(SPEED_MSG_ID, &speed, 1);
        can_transmit(GEAR_MSG_ID, &gear, 1);
    }
}