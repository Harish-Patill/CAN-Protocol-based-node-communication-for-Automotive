#include "ecu2_header.h"

#define DEBUG_UART 1    // set to 0 for the final build

static void init_config(void){
    init_adc();
    init_can();
    init_digital_keypad();
#if DEBUG_UART
    init_uart();
#endif

    /* RB0, RB1, RB6, RB7 are indicator LED outputs */
    TRISB = TRISB & ~0xC3;
    PORTB = PORTB & ~0xC3;
}

void main(void){
    uint16_t rpm, temp;
    IndicatorStatus ind;
    uint8_t buf[2];
    uint8_t ind_byte;

    init_config();

    while(1){
        rpm  = get_rpm();
        temp = get_engine_temp();
        ind  = process_indicator();

#if DEBUG_UART
        puts("rpm : ");
        putch((rpm/1000)+'0');
        putch(((rpm/100)%10)+'0');
        putch(((rpm/10)%10)+'0');
        putch((rpm%10)+'0');
        puts("   |   ");
        puts("ind : ");
        putch((uint8_t)ind + '0');
        puts("   |   ");
        puts("temp : ");
        putch((temp/100)+'0');
        putch(((temp/10)%10)+'0');
        putch((temp%10)+'0');
        puts(" C\n\r");
#endif

        buf[0] = (uint8_t)(rpm >> 8);
        buf[1] = (uint8_t)(rpm & 0xFF);
        can_transmit(RPM_MSG_ID, buf, 2);

        buf[0] = (uint8_t)(temp >> 8);
        buf[1] = (uint8_t)(temp & 0xFF);
        can_transmit(ENG_TEMP_MSG_ID, buf, 2);

        ind_byte = (uint8_t)ind;
        can_transmit(INDICATOR_MSG_ID, &ind_byte, 1);
    }
}