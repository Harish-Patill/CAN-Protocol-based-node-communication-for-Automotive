#include <stdint.h>
//#include <stdlib.h>

#include "adc.h"
#include "can.h"
#include "ecu1_sensor.h"
#include "msg_id.h"
#include "uart.h"

void main(){
    //Call the functions
    init_adc();
    init_uart();
    init_digital_keypad();
    init_can();
    
    //RXB0CONbits.RXM0=1;
    //RXB0CONbits.RXM1=1;

    while(1){
        uint16_t speed = get_speed();

        puts("speed: ");
        
        putch((speed / 100) + '0');
        putch(((speed / 10) % 10) + '0');
        putch((speed % 10) + '0');
        
        puts("   |   ");

        unsigned char gear = get_gear_pos();

        puts("Gear : ");
        putch(gear);
        puts("\n\r");
        
        // Transmit speed
        uint8_t speed_data[2];

        speed_data[0] = speed & 0xFF;
        speed_data[1] = (speed >> 8) & 0xFF;

        can_transmit(SPEED_MSG_ID, speed_data, 2);

        // Transmit gear
        uint8_t gear_data[1];

        gear_data[0] = gear;

        can_transmit(GEAR_MSG_ID, gear_data, 1);

    }
}
