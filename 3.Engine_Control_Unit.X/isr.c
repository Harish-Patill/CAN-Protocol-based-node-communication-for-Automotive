#include "ecu3_header.h"

extern unsigned long int timer_count;

void __interrupt() isr(void) {
    if(TMR0IF) {
        TMR0 = TMR0 + 9;
        if(timer_count++ == 20000) timer_count = 0;
        TMR0IF = 0;
    }
}