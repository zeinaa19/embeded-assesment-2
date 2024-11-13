#include <avr/io.h>	// includes the avr library file 		  
#include <util/delay.h>	  // includes the delay library
#include "lcdd.h" // includes lcd header 
#if !defined(_AVR_ATmega328P_)
#include <avr/iom328p.h>
#endif

#define LCD_Dir  DDRD	 //defines the data port direction 	 
#define LCD_Port PORTD		// defines the lcd data port 

#define RS_EN_Dir  DDRB	//this defines the RS and the En data port direction 
#define RS_EN_Port PORTB  // this defines the RS and and En port 
#define RS PB0		// defines register select pin 	   
#define EN PB1 	 	// defines the enable signal pin

void LCD_Command( unsigned char cmnd )
{
	LCD_Port = (LCD_Port & 0x0F) | (cmnd & 0xF0); //sends the upper nibble 
	RS_EN_Port &= ~ (1<<RS);	// Rs = 0, command reg	
	RS_EN_Port |= (1<<EN);		// enables puls 
	_delay_us(1);
	RS_EN_Port &= ~ (1<<EN);

	_delay_us(200);

	LCD_Port = (LCD_Port & 0x0F) | (cmnd << 4);  //sends lower nibble 
	RS_EN_Port |= (1<<EN);
	_delay_us(1);
	RS_EN_Port &= ~ (1<<EN);
	_delay_ms(2);
}


void LCD_Char( unsigned char data )
{
	LCD_Port = (LCD_Port & 0x0F) | (data & 0xF0); //sending upper nibble 
	RS_EN_Port |= (1<<RS);		//Rs = 1 data 
	RS_EN_Port|= (1<<EN);
	_delay_us(1);
	RS_EN_Port &= ~ (1<<EN);

	_delay_us(200);

	LCD_Port = (LCD_Port & 0x0F) | (data << 4); 
	RS_EN_Port |= (1<<EN);
	_delay_us(1);
	RS_EN_Port &= ~ (1<<EN);
	_delay_ms(2);
}

void LCD_Init (void)			
{
	LCD_Dir = 0xFF;			    
  	RS_EN_Dir |= (1 << EN) | (1 << RS);

	_delay_ms(20);			    
	
	LCD_Command(0x02);		  
	LCD_Command(0x28);      
	LCD_Command(0x0c);      
	LCD_Command(0x06);      
	LCD_Command(0x01);      
	_delay_ms(2);
}

void LCD_String (char str)		
{
	int i;
	for(i=0;str[i]!=0;i++)		
	{
		LCD_Char (str[i]);
	}
}

void LCD_String_xy (char row, char pos, char str)	
{
	if (row == 0 && pos<16)
	  LCD_Command((pos & 0x0F)|0x80);	                  
	else if (row == 1 && pos<16)
	  LCD_Command((pos & 0x0F)|0xC0);	                  
    
	LCD_String(str);	                              	
}

void LCD_Clear()
{
	LCD_Command (0x01);	
	_delay_ms(2);
	LCD_Command (0x80);		
}
