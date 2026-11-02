#include "ecu1_header.h"

uint8_t get_speed(void){
    uint16_t adc = read_adc(CHANNEL4);
    return (uint8_t)(((uint32_t)adc * 100) / 1023);
}

unsigned char get_gear_pos(){
    // Implement the gear function
    static unsigned char gear='N';

    char key=read_digital_keypad(STATE_CHANGE);

    if (key == SWITCH1){
        if (gear == 'N'){
            gear = '1';
        }
        else if (gear >= '1' && gear < '5'){
            gear++;
        }
    }
    else if (key == SWITCH2){
        if (gear == '1'){
            gear = 'N';
        }
        else if (gear > '1' && gear <= '5'){
            gear--;
        }
    }

    if(key == SWITCH3){
        gear = 'R';
    }
    if(key == SWITCH4){
        gear = 'N';
    }

    return gear;
}