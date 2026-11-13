#include "ecu1_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"

uint16_t get_speed(){
    int adc = read_adc(CHANNEL4); // Implement the speed function
    uint16_t speed = ((uint32_t)adc * 100)/1023;
    
    return speed;
} 

unsigned char get_gear_pos(){
    static unsigned char gear = 'N';

    char key=read_digital_keypad(STATE_CHANGE);

    if(key == SWITCH1){
        if(gear=='N'){
            gear='1';
        }
        else if(gear >= '1' && gear < '5'){
            gear++;
        }
     }
    else if(key == SWITCH2){
        if(gear=='1'){
             gear='N';
        }
        else if(gear > '1' && gear <= '5'){
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
