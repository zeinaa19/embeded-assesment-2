#include <util/delay.h>
#include "adc.h"
#include "lcdd.h"
#include <stdlib.h>

int main (void) {
    buttoninit();
    Adc_Init(); 
    Uart_Init();
    LCD_Init();
    float temperature;
    unsigned short adcsensor;
    unsigned short upper=0;  
    unsigned short lower=0;
    unsigned char buffer[6];

    while (1) {
        _delay_ms(200);  

        adcsensor=Adc_ReadChannel(1);
        temperature =adcsensor*(5.0/1024.0)*100;

        dtostrf(temperature,5,1,buffer);

        if (((PINB>>PB4)&1)==0) {
            lower+=5;
            _delay_ms(200); 
        } 
        if (((PINB>>PB5)&1)==0) {
            upper-=1;
            _delay_ms(200);
        } 

        if (temperature>=lower && temperature<upper) {
            PORTD=PORTD|(1 <<PD2);  
        } 
        else {
            PORTD=PORTD & ~(1<<PD2); 
        }


        LCD_Clear();
        LCD_String("Temp:");
        LCD_String(buffer);
        LCD_String("C");
        LCD_Command(0xC0); 
        LCD_String("L:");
        itoa(lower,buffer,10);
        LCD_String(buffer);
        LCD_String("U:");
        itoa(upper,buffer,10);
        LCD_String(buffer);



    }

    return 0;
}

void buttoninit(){
    DDRB=DDRB & ~(1<<PB4);  
    PORTB=PORTB | (1<<PB4);
    DDRB=DDRB & ~(1<<PB5);  
    PORTB=PORTB | (1s<<PB5);
}
