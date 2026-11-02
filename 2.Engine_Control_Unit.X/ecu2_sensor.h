#ifndef ECU2_SENSOR_H
#define ECU2_SENSOR_H

#define RPM_ADC_CHANNEL      0x04
#define ENG_TEMP_ADC_CHANNEL 0x06

#define RIGHT_IND_ON()   (PORTB = PORTB | 0xC0)
#define RIGHT_IND_OFF()  (PORTB = PORTB & ~0xC0)
#define LEFT_IND_ON()    (PORTB = PORTB | 0x03)
#define LEFT_IND_OFF()   (PORTB = PORTB & ~0x03)

typedef enum {
    e_ind_off,      /* 0 */
    e_ind_left,     /* 1 */
    e_ind_right,    /* 2 */
    e_ind_hazard    /* 3 */
} IndicatorStatus;

uint16_t get_rpm(void);
uint16_t get_engine_temp(void);
IndicatorStatus process_indicator(void);

#endif