/* 
 * File:   message_handler.h
 * Author: USER
 *
 * Created on November 2, 2026, 3:36 PM
 */

#ifndef MESSAGE_HANDLER_H
#define	MESSAGE_HANDLER_H
#include <stdint.h>

#define LED_OFF 0
#define LED_ON 1

#define RIGHT_IND_ON() (PORTB = PORTB | 0xC0)
#define RIGHT_IND_OFF() (PORTB = PORTB & ~0xC0)
#define LEFT_IND_ON() (PORTB = PORTB | 0x03)
#define LEFT_IND_OFF() (PORTB = PORTB & ~0x03)

extern volatile unsigned char led_state, status;

typedef enum {
    e_ind_off,
    e_ind_left,
    e_ind_right
} IndicatorStatus;

void process_canbus_data();
void blink_indicator_led(void);
void handle_speed_data(uint8_t *data, uint8_t len);
void handle_gear_data(uint8_t *data, uint8_t len);
void handle_rpm_data(uint8_t *data, uint8_t len);
void handle_engine_temp_data(uint8_t *data, uint8_t len);
void handle_indicator_data(uint8_t *data, uint8_t len);
static void display_indicator(unsigned char indicator);


#endif	/* MESSAGE_HANDLER_H */

