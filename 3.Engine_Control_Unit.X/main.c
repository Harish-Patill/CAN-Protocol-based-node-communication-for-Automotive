#include "ecu3_header.h"


static void init_leds() {
    TRISB = 0x08; // Set RB2 as output, RB3 as input, remaining as output
    PORTB = 0x00;
}

static void init_config(void) {
    init_clcd();
    init_can();
    init_leds();
    init_timer0();

    PEIE = 1;
    GIE = 1;
}

unsigned long int timer_count = 0;

void main(void) {
    init_config();

    while (1) {
        process_canbus_data();
    }

    return;
}
