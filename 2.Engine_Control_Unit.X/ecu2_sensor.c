#include "ecu2_header.h"

uint16_t get_rpm(void){
    uint16_t adc = read_adc(RPM_ADC_CHANNEL);
    return (uint16_t)(((uint32_t)adc * 2000) / 1023);
}

uint16_t get_engine_temp(void){
    uint16_t adc = read_adc(ENG_TEMP_ADC_CHANNEL);
    return (uint16_t)(((uint32_t)adc * 500) / 1023);
}

static void update_leds(IndicatorStatus s){
    LEFT_IND_OFF();
    RIGHT_IND_OFF();

    if(s == e_ind_left || s == e_ind_hazard){
        LEFT_IND_ON();
    }
    if(s == e_ind_right || s == e_ind_hazard){
        RIGHT_IND_ON();
    }
}

IndicatorStatus process_indicator(void){
    static IndicatorStatus indicator = e_ind_off;
    unsigned char key = read_digital_keypad(STATE_CHANGE);

    if(key == SWITCH1){                 /* left: press again to cancel */
        indicator = (indicator == e_ind_left) ? e_ind_off : e_ind_left;
    }
    else if(key == SWITCH2){            /* right: press again to cancel */
        indicator = (indicator == e_ind_right) ? e_ind_off : e_ind_right;
    }
    else if(key == SWITCH3){            /* hazard: press again to cancel */
        indicator = (indicator == e_ind_hazard) ? e_ind_off : e_ind_hazard;
    }
    else if(key == SWITCH4){            /* all off */
        indicator = e_ind_off;
    }

    update_leds(indicator);
    return indicator;
}