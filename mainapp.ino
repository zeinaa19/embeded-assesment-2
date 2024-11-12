#include <util/delay.h> //including the deley library to allow for delays in the code to create time intervales for the leds and buttons
#include "adc.h" // including the analog  to digtal converter file 
#include "lcdd.h" // including the display file 
#include <stdlib.h> // including this library to be used for conversions 

int main (void) { // this is the begining of the main code
    buttoninit(); // inisialisation for buttons 
    Adc_Init();  // insilisation for adc
    LCD_Init(); // inisilisation for lcd
    float temperature;  // defiines float variable temperature 
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
