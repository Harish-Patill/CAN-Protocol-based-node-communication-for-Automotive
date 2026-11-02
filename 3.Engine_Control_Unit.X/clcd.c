#include "ecu3_header.h"

void clcd_write(unsigned char byte, unsigned char control_bit){
	CLCD_RS = control_bit;
	TRISD = 0x00;                 /* PIC drives the data bus */
	CLCD_PORT = byte;
    
    unsigned char busy;

	/* Enable pulse (ideally >= 230 ns) */
	CLCD_EN = HI;
	CLCD_EN = LO;

	TRISD = 0xFF;                 /* release the whole bus so LCD can answer */
	CLCD_RW = HI;
	CLCD_RS = INSTRUCTION_COMMAND;

//	do
//	{
//		CLCD_EN = HI;
//		CLCD_EN = LO;
//	} while (CLCD_BUSY);
    
    do {
        CLCD_EN = HI;
        __delay_us(1);
        busy = CLCD_BUSY;
        CLCD_EN = LO;
    } while (busy);

	CLCD_RW = LO;
	TRISD = 0x00;
}

void init_clcd(){
    
    __delay_ms(20);

	/* Set PortD as output port for CLCD data */
	TRISD = 0x00;
	/* Set PortC as output port for CLCD control */
	TRISC = TRISC & 0xF8;

	CLCD_RW = LO;

	CURSOR_HOME;
	TWO_LINE_5x8_MATRIX_8_BIT;
	DISP_ON_AND_CURSOR_OFF;
	CLEAR_DISP_SCREEN;
}

void clcd_print(const unsigned char *data, unsigned char addr){
	clcd_write(addr, INSTRUCTION_COMMAND);
	while (*data != '\0'){
		clcd_write(*data++, DATA_COMMAND);
	}
}

void clcd_putch(const unsigned char data, unsigned char addr){
	clcd_write(addr, INSTRUCTION_COMMAND);
	clcd_write(data, DATA_COMMAND);
}