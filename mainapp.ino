#include <util/delay.h> //including the dely library to allow for delays in the code to create time intervales for the LEDs and buttons
#include "adc.h" //including the analog to digial converter file
#include "Lcd.h" //including the display file
#include <stdlib.h> // including this ibrary to be used for later conversions 

int main (void) { // this is the bedining of the main code
    buttoninit(); // initialization for the buttons
    Adc_Init(); // initialization for the adc
    LCD_Init(); // initialization for the the LCD
    float temperature;  // defines float variable temperature
    unsigned short adcsensor;  //defines adc sensor (short because it only requires 16-bit values and unsigned because it only holds positive values)
    unsigned short upper=0;  // define upper as a variablee
    unsigned short lower=0;  // defines lower as a variable
    unsigned char buffer[6]; //define th buffer as an unsigned charecter that holds only positive values to store 6 elements 
    while (1) {  // using while(1) as an infinite continuous loop 
        _delay_ms(200);  // setting a delay too to ensure data runs smoothly 

        adcsensor=Adc_ReadChannel(1); //reads the analog value from the sensor from channel A1
        temperature=adcsensor*(5.0/1024.0)*100;  //this formula is used to calculate the temperature from the sensor as its output is in millivolts 

        dtostrf(temperature,5,1,buffer); // this converts a float number to a string 

        if (((PINB >> PB4)&1)==0) { // this if contition is used to check if the button to check if the button is pressed or not
            lower += 5; // if the button is pressed the lower limit increases by 5 
            _delay_ms(200); // adding a delay of 200 milliseconds to ensure the code runs smoothly
        } 
        if (((PINB >> PB5)&1)==0) { //this if contition is used to check if the button to check if the button is pressed or not
            upper += 5; // if the button is pressed the upper limit increases by 5
            _delay_ms(200); // adding a dely of 200 milliseconds to ensure that the code runs smoothly
        } 
        
        LCD_Clear(); //this comand is to clear the LCD

        
        LCD_Command(0x80); 
        LCD_String("Temp:"); // displays the word "temp"
        LCD_String(buffer); // displays value stores in the buffer
        LCD_String("C"); // displays degree celsius 

        LCD_Command(0xC0); // this command is sued to shift the second row of the lcd
        LCD_String("L:");
        itoa(lower,buffer,10); 
        LCD_String(buffer); 
        LCD_String("U:"); 
        itoa(upper,buffer,10); 
        LCD_String(buffer);

       
        if (temperature>=lower&&temperature<upper) { //this checks if the tempereture sensor value is inside the range or not
            PORTD |= (1<<PD2);  // the led turns on if its inside the range
            PORTD &= ~(1<<PD0); 
            LCD_Command(0x8E);    
            LCD_String("OK");     //displays "ok" if the value is in the range
        } 
        else { 
            PORTD |= (1<<PD0);  //turns off the led if its outside the range 
            PORTD &= ~(1<<PD2); 
            LCD_Command(0x8D);    
            LCD_String("Nok");    //displays "nok" if the value is out of range
        }
    }

    return 0;
}

void buttoninit() { 
    DDRB = DDRB & ~(1<<PB4);  
    PORTB = PORTB | (1<<PB4); 
    DDRB = DDRB & ~(1<<PB5);  
    PORTB = PORTB | (1<<PB5); 
}
