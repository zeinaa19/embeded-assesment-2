#include <util/delay.h> //including the delay library to allow for delays in the code to create time intervals for the LEDs and buttons
#include "adc.h" // including the analog  to digital converter file 
#include "lcdd.h" // including the display file 
#include <stdlib.h> // including this library to be used for conversions 

int main (void) { // this is the beginning of the main code
    buttoninit(); // initialization for buttons 
    Adc_Init();  // initialization for adc
    LCD_Init(); // initialization for LCD
    float temperature;  // defines float variable temperature 
    unsigned short adcsensor;  // defines adc sensor (short because it only requires 16-bit values & unsigned because it only holds +ve values)
    unsigned short upper=0;  // define upper as a variable
    unsigned short lower=0; // define lower as a variable
    unsigned char buffer[6]; //define the buffer as an unsigned character that holds only +ve values to store 6 elements

    while (1) {  // using while(1) as an infinite loop
        _delay_ms(200);  // setting delay as 200 to ensure data runs smoothly

        adcsensor=Adc_ReadChannel(1); //reads the analog value from the sensor from channel A1
        temperature =adcsensor*(5.0/1024.0)*100;  // this formula is used to calculate the temperature from the sensor as its output is mv

        dtostrf(temperature,5,1,buffer); // this converts a float number to a string

        if (((PINB>>PB4)&1)==0) { // this if condition is used to check if the button is pressed or not
            lower+=5; // if the button is pressed the lower limit increases by 5
            _delay_ms(200); 
        } 
        if (((PINB>>PB5)&1)==0) {
            upper+=5; // if the button is pressed the upper limit increases by 5
            _delay_ms(200);
        } 
        

        if (temperature>=lower && temperature<upper) { // this checks if the temperature sensor value is inside the range or not
            PORTD |= (1 <<PD2);  // the LED turns on if its inside the range
            PORTD &= ~(1<<PD0);      
            LCD_Command(0x8D); //This command is used to move the cursor to a specific character (character 14)
            LCD_String("oK"); // displays "ok" if the value is in the range
        } 
        else { 
            PORTD |= (1<<PD0); // turns off the LED if its outside the range
            PORTD &= ~(1 <<PD2);
            LCD_Command(0x8D);
            LCD_String("Nok");
        }


        LCD_Clear(); //This command is used to clear the LCD
        LCD_String("Temp:"); // displays the word "temp"
        LCD_String(buffer); // displays the value stored in the buffer
        LCD_String("C"); // displays degree celsius 
        LCD_Command(0xC0); //This command is used to shift to the second row of the LCD
        LCD_String("L:"); //This command displays "l" which refers to the lower limit
        itoa(lower,buffer,10); // this function converts the value in the variable lower to a string base 10 and stores it in the buffer
        LCD_String(buffer); 
        LCD_String("U:"); // displays the letter "u" which refers to the upper limit
        itoa(upper,buffer,10); 
        LCD_String(buffer);



    }

    return 0;
}

void buttoninit(){ 
    DDRB=DDRB & ~(1<<PB4); // define pb4 as an input  
    PORTB=PORTB | (1<<PB4); // enables the internal pullup resistor in pb4
    DDRB=DDRB & ~(1<<PB5);  // define pb5 as an input  
    PORTB=PORTB | (1<<PB5); // enables the internal pullup resistor in pb5
}
