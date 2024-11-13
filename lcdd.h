#ifndef _LCD_
#define _LCD_ 

void LCD_Command(unsigned char cmnd);
void LCD_Char (unsigned char char_data);
void LCD_Init (void);
void LCD_String (char *str);
void LCD_String_xy (char row, char pos, char *str);
void LCD_Clear();

#endif /_LCD_/
