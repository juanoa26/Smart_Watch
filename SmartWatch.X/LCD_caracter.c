/*
 * PIC18F4550 I2C Source File
 * http://www.electronicwings.com
 */ 

#include "Funciones.h"
#include "LCD_caracter.h"

/****************************Functions********************************/

/*********************************************************************
 * Function:        void LCD_Init(void)
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Inicializa la configuracion de la pantalla LCD
 *
 * Note:            None
 ********************************************************************/

void LCD_Init(void)
{
    LCD_Port = 0;       /*PORT as Output Port*/
    LCD_MSdelay(15);        /*15ms,16x2 LCD Power on delay*/
    LCD_Command(0x02);  /*send for initialization of LCD 
                          for nibble (4-bit) mode */
    LCD_Command(0x28);  /*use 2 line and 
                          initialize 5*8 matrix in (4-bit mode)*/
	LCD_Command(0x01);  /*clear display screen*/
    LCD_Command(0x0c);  /*display on cursor off*/
	LCD_Command(0x06);  /*increment cursor (shift cursor to right)*/	   
}

/*********************************************************************
 * Function:        void LCD_Command(unsigned char cmd )
 *
 * Input:           unsigned char cmd: Resibe la fila en donde se imprimira la informacion
 *
 * Output:          None
 *
 * Overview:        Con la direccion recibida determina en donde se mostrara la informacion
 *
 * Note:            None
 ********************************************************************/

void LCD_Command(unsigned char cmd )
{
	ldata = (ldata & 0x0f) |(0xF0 & cmd);  /*Send higher nibble of command first to PORT*/ 
	RS = 0;  /*Command Register is selected i.e.RS=0*/ 
	EN = 1;  /*High-to-low pulse on Enable pin to latch data*/ 
	NOP();
	EN = 0;
	LCD_MSdelay(1);
    ldata = (ldata & 0x0f) | (cmd<<4);  /*Send lower nibble of command to PORT */
	EN = 1;
	NOP();
	EN = 0;
	LCD_MSdelay(3);
}

/*********************************************************************
 * Function:        void LCD_Char(unsigned char dat)
 *
 * Input:           unsigned char dat: Resibe los datos que se enviaran al LCD
 *
 * Output:          None
 *
 * Overview:        Trasmite la informacion recibida al LCD
 *
 * Note:            None
 ********************************************************************/

void LCD_Char(unsigned char dat)
{
	ldata = (ldata & 0x0f) | (0xF0 & dat);  /*Send higher nibble of data first to PORT*/
	RS = 1;  /*Data Register is selected*/
	EN = 1;  /*High-to-low pulse on Enable pin to latch data*/
	NOP();
	EN = 0;
	LCD_MSdelay(1);
    ldata = (ldata & 0x0f) | (dat<<4);  /*Send lower nibble of data to PORT*/
	EN = 1;  /*High-to-low pulse on Enable pin to latch data*/
	NOP();
	EN = 0;
	LCD_MSdelay(3);
}
/*********************************************************************
 * Function:        void LCD_String(const char *msg)
 *
 * Input:           const char *msg: Lleva la informacion
 *
 * Output:          None
 *
 * Overview:        Muestra la informacion en el LCD
 *
 * Note:            None
 ********************************************************************/

void LCD_String(const char *msg)
{
	while((*msg)!=0)
	{		
	  LCD_Char(*msg);
	  msg++;	
    }
}

/*********************************************************************
 * Function:        void LCD_String_xy(char row,char pos,const char *msg)
 *
 * Input:           char row: Determina la Fila
 *                  char pos: Determina la posicion
 *                  const char *msg: Lleva la informacion a imprimir
 *
 * Output:          None
 *
 * Overview:        Muestra la informacion en el LCD
 *
 * Note:            None
 ********************************************************************/

void LCD_String_xy(char row,char pos,const char *msg)
{
    char location=0;
    if(row<=1)
    {
        location=(0x80) | ((pos) & 0x0f);  /*Print message on 1st row and desired location*/
        LCD_Command(location);
    }
    else
    {
        location=(0xC0) | ((pos) & 0x0f);  /*Print message on 2nd row and desired location*/
        LCD_Command(location);    
    }  
    

    LCD_String(msg);

}

/*********************************************************************
 * Function:       void LCD_Clear(void)
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Limpia la pantalla LCD
 *
 * Note:            None
 ********************************************************************/

void LCD_Clear(void)
{
   	LCD_Command(0x01);  /*clear display screen*/
    LCD_MSdelay(3);
}

/*********************************************************************
 * Function:       void  LCD_Custom_Char ( unsigned  char  loc, unsigned  char  *msg) 
 *
 * Input:           unsigned  char  loc: Determina la posicion
 *                  unsigned  char  *msg: Lleva la informacion
 *
 * Output:          None
 *
 * Overview:        Determina el tama�o de ventana en donde se mostrara la informacion
 *
 * Note:            None
 ********************************************************************/

void  LCD_Custom_Char ( unsigned  char  loc, unsigned  char  *msg) 
{ 
    unsigned  char  i; 
    if (loc< 8 ) 
    { 
     LCD_Command ( 0x40 +(loc* 8 ));      /*  Command 0x40 and onwards forces the device to point CGRAM address  */ 
       for (i= 0 ;i< 8 ;i++)              /*  Write 8 byte for generation of 1 character  */ 
           LCD_Char (msg[i]); 
        
    }    
}

/*********************************************************************
 * Function:       void LCD_MSdelay(unsigned int val)
 *
 * Input:           unsigned int val: Determina el tiempo del retardo
 *
 * Output:          None
 *
 * Overview:        Se encarga del tiempo que se mostrara la infprmacion 
 *                  en el LCD
 *
 * Note:            None
 ********************************************************************/

void LCD_MSdelay(unsigned int val)
{
 unsigned int i,j;
 for(i=0;i<val;i++)
     for(j=0;j<165;j++);  /*This count Provide delay of 1 ms for 8MHz Frequency */
 }