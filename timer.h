#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned long int milis = 0;

void timer0Init(void){
   TCCR0A = (1<<WGM01);
   TCCR0B = ((1<<CS01)|(1<<CS00));
   OCR0A = 249;
   TIMSK0 = (1<<OCIE0A);
   sei();
}
ISR(TIMER0_COMPA_vect){
   milis++;
}