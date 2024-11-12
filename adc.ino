#if !defined(_AVR_ATmega328P_)
#include <avr/iom328p.h>
#endif
#include "Adc_pot.h"

void Adc_Init(void)
{
   
    ADMUX = (1<<REFS0);
 
    
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

unsigned short Adc_ReadChannel(unsigned char ch)
{

  
  ch &= 0b00000111; 
  ADMUX = (ADMUX & 0xF8)|ch; 
 
  
  ADCSRA |= (1<<ADSC);
 
  
  while(ADCSRA & (1<<ADSC));
 
  return (ADC);

}
