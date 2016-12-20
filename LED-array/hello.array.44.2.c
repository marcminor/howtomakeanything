//
//
// hello.array.44.2.c
//
// Charlieplex LED array hello-world
// two-layer version
//
// Neil Gershenfeld
// 11/11/11
//
// (c) Massachusetts Institute of Technology 2011
// This work may be reproduced, modified, distributed,
// performed, and displayed for any purpose. Copyright is
// retained and must be preserved. The work is provided
// as is; no warranty is provided, and users accept all 
// liability.
//

#include <avr/io.h>
#include <util/delay.h>

#define output(directions,pin) (directions |= pin) // set port direction for output
#define input(directions,pin) (directions &= (~pin)) // set port direction for input 
#define set(port,pin) (port |= pin) // set port pin
#define clear(port,pin) (port &= (~pin)) // clear port pin
#define pin_test(pins,pin) (pins & pin) // test for port pin
#define bit_test(byte,bit) (byte & (1 << bit)) // test for bit set
#define bit_delay_time 100 // bit delay for 9600 with overhead
#define bit_delay() _delay_us(bit_delay_time) // RS232 bit delay
#define half_bit_delay() _delay_us(bit_delay_time/2) // RS232 half bit delay

#define led_delay() _delay_ms(1) // LED delay
#define led_port PORTA
#define led_direction DDRA

#define serial_port PORTA
#define serial_direction DDRA
#define serial_pins PINA
#define serial_pin_in (1 << PA6)
#define serial_pin_out (1 << PA5)

#define A (1 << PA0) // row 1
#define B (1 << PA1) // row 2
#define C (1 << PA2) // row 3
#define D (1 << PA3) // row 4
#define E (1 << PA4) // row 5


void get_char(volatile unsigned char *pins, unsigned char pin, char *rxbyte) {
   //
   // read character into rxbyte on pins pin
   //    assumes line driver (inverts bits)
   //
   *rxbyte = 0;
   while (pin_test(*pins,pin))
      //
      // wait for start bit
      //
      ;
   //
   // delay to middle of first data bit
   //
   half_bit_delay();
   bit_delay();
   //
   // unrolled loop to read data bits
   //
   if pin_test(*pins,pin)
      *rxbyte |= (1 << 0);
   else
      *rxbyte |= (0 << 0);
   bit_delay();
   if pin_test(*pins,pin)
      *rxbyte |= (1 << 1);
   else
      *rxbyte |= (0 << 1);
   bit_delay();
   if pin_test(*pins,pin)
      *rxbyte |= (1 << 2);
   else
      *rxbyte |= (0 << 2);
   bit_delay();
   if pin_test(*pins,pin)
      *rxbyte |= (1 << 3);
   else
      *rxbyte |= (0 << 3);
   bit_delay();
   if pin_test(*pins,pin)
      *rxbyte |= (1 << 4);
   else
      *rxbyte |= (0 << 4);
   bit_delay();
   if pin_test(*pins,pin)
      *rxbyte |= (1 << 5);
   else
      *rxbyte |= (0 << 5);
   bit_delay();
   if pin_test(*pins,pin)
      *rxbyte |= (1 << 6);
   else
      *rxbyte |= (0 << 6);
   bit_delay();
   if pin_test(*pins,pin)
      *rxbyte |= (1 << 7);
   else
      *rxbyte |= (0 << 7);
   //
   // wait for stop bit
   //
   bit_delay();
   half_bit_delay();
   }


void flash(uint8_t from, uint8_t, uint8_t delay) {
   //
   // source from, sink to, flash
   //
   static uint8_t i;
   set(led_port,from);
   clear(led_port,to);
   output(led_direction,from);
   output(led_direction,to);
   for (i = 0; i < delay; ++i)
       led_delay();
   input(led_direction,from);
   input(led_direction,to);
   }

void led_cycle(uint8_t number, uint8_t delay) {
   //
   // cycle through LEDs
   //
   uint8_t i;
   for (i = 0; i < number; ++i) {
      flash(B,A,delay);
      flash(C,A,delay);
      flash(D,A,delay);
      flash(E,A,delay);
      flash(A,B,delay);
      flash(C,B,delay);
      flash(D,B,delay);
      flash(E,B,delay);
      flash(A,C,delay);
      flash(B,C,delay);
      flash(D,C,delay);
      flash(E,C,delay);
      flash(A,D,delay);
      flash(B,D,delay);
      flash(C,D,delay);
      flash(E,D,delay);
      flash(A,E,delay);
      flash(B,E,delay);
      flash(C,E,delay);
      flash(D,E,delay);
      }
   }


void display(uint8_t count, uint8_t delay) {

	if (count == 0) {
		flash(C,A,delay);
		flash(D,A,delay);
		flash(E,A,delay);
		flash(E,B,delay);
		flash(C,B,delay);
		flash(B,C,delay);
		flash(E,C,delay);
		flash(B,D,delay);
		flash(E,D,delay);
		flash(B,E,delay);
		flash(C,E,delay);
		flash(D,E,delay);
	}
	if (count == 1) {
		flash(C,A,delay);
		flash(D,A,delay);
		flash(D,B,delay);
		flash(D,C,delay);
		flash(C,D,delay);
		flash(C,E,delay);
		flash(D,E,delay);
		flash(B,E,delay);
	}
	if (count == 2) {
		flash(C,A,delay);
		flash(D,A,delay);
		flash(E,A,delay);
		flash(E,B,delay);
		flash(B,C,delay);
		flash(D,C,delay);
		flash(E,C,delay);
		flash(B,D,delay);
		flash(B,E,delay);
		flash(C,E,delay);
		flash(D,E,delay);
	}
	if (count == 3) {
		flash(C,A,delay);
		flash(D,A,delay);
		flash(E,A,delay);
		flash(E,B,delay);
		flash(D,C,delay);
		flash(E,C,delay);
		flash(E,D,delay);
		flash(B,E,delay);
		flash(C,E,delay);
		flash(D,E,delay);
	}
	if (count == 4) {
		flash(C,A,delay);
		flash(E,A,delay);
		flash(C,B,delay);
		flash(E,B,delay);
		flash(B,C,delay);
		flash(D,C,delay);
		flash(E,C,delay);
		flash(E,D,delay);
		flash(D,E,delay);
	}
	if (count == 5) {
		flash(C,A,delay);
		flash(D,A,delay);
		flash(E,A,delay);
		flash(C,B,delay);
		flash(B,C,delay);
		flash(D,C,delay);
		flash(E,C,delay);
		flash(E,D,delay);
		flash(B,E,delay);
		flash(C,E,delay);
		flash(D,E,delay);
	}
	if (count == 6) {
		flash(C,A,delay);
		flash(D,A,delay);
		flash(E,A,delay);
		flash(C,B,delay);
		flash(B,C,delay);
		flash(D,C,delay);
		flash(E,C,delay);
		flash(B,D,delay);
		flash(E,D,delay);
		flash(B,E,delay);
		flash(C,E,delay);
		flash(D,E,delay);
	}
	if (count == 7) {
		flash(C,A,delay);
		flash(D,A,delay);
		flash(E,A,delay);
		flash(E,B,delay);
		flash(E,C,delay);
		flash(E,D,delay);
		flash(D,E,delay);
	}
	if (count == 8) {
		flash(C,A,delay);
		flash(D,A,delay);
		flash(E,A,delay);
		flash(E,B,delay);
		flash(C,B,delay);
		flash(B,C,delay);
		flash(D,C,delay);
		flash(E,C,delay);
		flash(B,D,delay);
		flash(E,D,delay);
		flash(B,E,delay);
		flash(C,E,delay);
		flash(D,E,delay);
	}
	if (count == 9) {
		flash(C,A,delay);
		flash(D,A,delay);
		flash(E,A,delay);
		flash(E,B,delay);
		flash(C,B,delay);
		flash(B,C,delay);
		flash(D,C,delay);
		flash(E,C,delay);
		flash(E,D,delay);
		flash(D,E,delay);
	}
}
// void counter(uint8_t count, uint8_t number, uint8_t delay) {
// 	uint8_t i;

// 	for (i = 0; i < number; ++i) {
// 		if (count == 0) {
// 			flash(C,A,delay);
// 			flash(D,A,delay);
// 			flash(E,A,delay);
// 			flash(E,B,delay);
// 			flash(C,B,delay);
// 			flash(B,C,delay);
// 			flash(E,C,delay);
// 			flash(B,D,delay);
// 			flash(E,D,delay);
// 			flash(B,E,delay);
// 			flash(C,E,delay);
// 			flash(D,E,delay);
// 		}
// 		if (count == 1) {
// 			flash(C,A,delay);
// 			flash(D,A,delay);
// 			flash(D,B,delay);
// 			flash(D,C,delay);
// 			flash(C,D,delay);
// 			flash(C,E,delay);
// 			flash(D,E,delay);
// 			flash(B,E,delay);
// 		}
// 		if (count == 2) {
// 			flash(C,A,delay);
// 			flash(D,A,delay);
// 			flash(E,A,delay);
// 			flash(E,B,delay);
// 			flash(B,C,delay);
// 			flash(D,C,delay);
// 			flash(E,C,delay);
// 			flash(B,D,delay);
// 			flash(B,E,delay);
// 			flash(C,E,delay);
// 			flash(D,E,delay);
// 		}
// 		if (count == 3) {
// 			flash(C,A,delay);
// 			flash(D,A,delay);
// 			flash(E,A,delay);
// 			flash(E,B,delay);
// 			flash(D,C,delay);
// 			flash(E,C,delay);
// 			flash(E,D,delay);
// 			flash(B,E,delay);
// 			flash(C,E,delay);
// 			flash(D,E,delay);
// 		}
// 		if (count == 4) {
// 			flash(C,A,delay);
// 			flash(E,A,delay);
// 			flash(C,B,delay);
// 			flash(E,B,delay);
// 			flash(B,C,delay);
// 			flash(D,C,delay);
// 			flash(E,C,delay);
// 			flash(E,D,delay);
// 			flash(D,E,delay);
// 		}
// 		if (count == 5) {
// 			flash(C,A,delay);
// 			flash(D,A,delay);
// 			flash(E,A,delay);
// 			flash(C,B,delay);
// 			flash(B,C,delay);
// 			flash(D,C,delay);
// 			flash(E,C,delay);
// 			flash(E,D,delay);
// 			flash(B,E,delay);
// 			flash(C,E,delay);
// 			flash(D,E,delay);
// 		}
// 		if (count == 6) {
// 			flash(C,A,delay);
// 			flash(D,A,delay);
// 			flash(E,A,delay);
// 			flash(C,B,delay);
// 			flash(B,C,delay);
// 			flash(D,C,delay);
// 			flash(E,C,delay);
// 			flash(B,D,delay);
// 			flash(E,D,delay);
// 			flash(B,E,delay);
// 			flash(C,E,delay);
// 			flash(D,E,delay);
// 		}
// 		if (count == 7) {
// 			flash(C,A,delay);
// 			flash(D,A,delay);
// 			flash(E,A,delay);
// 			flash(E,B,delay);
// 			flash(E,C,delay);
// 			flash(E,D,delay);
// 			flash(D,E,delay);
// 		}
// 		if (count == 8) {
// 			flash(C,A,delay);
// 			flash(D,A,delay);
// 			flash(E,A,delay);
// 			flash(E,B,delay);
// 			flash(C,B,delay);
// 			flash(B,C,delay);
// 			flash(D,C,delay);
// 			flash(E,C,delay);
// 			flash(B,D,delay);
// 			flash(E,D,delay);
// 			flash(B,E,delay);
// 			flash(C,E,delay);
// 			flash(D,E,delay);
// 		}
// 		if (count == 9) {
// 			flash(C,A,delay);
// 			flash(D,A,delay);
// 			flash(E,A,delay);
// 			flash(E,B,delay);
// 			flash(C,B,delay);
// 			flash(B,C,delay);
// 			flash(D,C,delay);
// 			flash(E,C,delay);
// 			flash(E,D,delay);
// 			flash(D,E,delay);
// 		}
// 	}
// }

int main(void) {
   //
   static char chr;
   //
   // set clock divider to /1
   //
   CLKPR = (1 << CLKPCE);
   CLKPR = (0 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0);
   //
   // initialize input pins
   //
   set(serial_port, serial_pin_in);
   input(serial_direction, serial_pin_in);
   //
   // main loop
   //
   while (1) {
       
      get_char(&serial_pins, serial_pin_in, &chr);

      //default state (no one on bar)
      while (chr == 200) {
      	led_cycle(3,20);
      }
      //session output
      while (chr < 200) {
      	display(chr, 1);
      }
    }
   }
