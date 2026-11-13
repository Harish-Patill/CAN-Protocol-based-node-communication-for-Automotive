/*
 * File:   ecu2_sensor.c
 * Author: USER
 *
 * Created on October 29, 2026, 10:26 PM
 */


#include "ecu2_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"

uint16_t get_rpm(){
    //Implement the rpm function
    int adc = read_adc(RPM_ADC_CHANNEL);
    uint16_t rpm = ((uint32_t)adc*2000)/1023;
    
    return rpm;
}

uint16_t get_engine_temp(){
    //Implement the engine temperature function
    int adc = read_adc(ENG_TEMP_ADC_CHANNEL);
    uint16_t temperature = ((uint32_t)adc * 500)/1023;
    
    return temperature;
}

IndicatorStatus process_indicator(){
    //Implement the indicator function
    static unsigned char indicator = e_ind_off;
    
    char key = read_digital_keypad(STATE_CHANGE);
    
    if(key == SWITCH1){
        LEFT_IND_ON();
        RIGHT_IND_OFF();
        indicator = e_ind_left;
    }

    else if(key == SWITCH2){
        LEFT_IND_OFF();
        RIGHT_IND_ON();
        indicator = e_ind_right;
    }
    else if(key==SWITCH3){
        LEFT_IND_ON();
        RIGHT_IND_ON();
        indicator = 3;
    }
    else if(key==SWITCH4){
        LEFT_IND_OFF();
        RIGHT_IND_OFF();
        indicator = e_ind_off;
    }
    
    return indicator;
}