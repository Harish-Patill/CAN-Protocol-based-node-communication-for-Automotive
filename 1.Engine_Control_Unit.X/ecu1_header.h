/* 
 * File:   ecu1_header.h
 * Author: Harish
 * Created on November 2, 2026, 11:18 PM
 * 
 * Description: This reads speed (from potentiometer with help of ADC) and gear position (from matrix keypad), and transmits over CAN
 * 
 * Operating:
 *      Switch1 = gear incementation
 *      Switch2 = gear decremenation
 *      Switch3 = reverse gear
 *      Switch4 = neutral 
 */

#ifndef ECU1_HEADER_H
#define	ECU1_HEADER_H

#include <xc.h>
#include <stdint.h>

#include "adc.h"
#include "can.h"
#include "digital_keypad.h"
#include "ecu1_sensor.h"
#include "msg_id.h"
#include "uart.h"

#endif	/* ECU1_HEADER_H */

