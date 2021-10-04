
/*
 * PIC18F4550 I2C Source File
 * http://www.electronicwings.com
 */ 



#include "I2C_Master_File.h"
#include <pic18f4550.h>

/*********************************************************************
 * Function:        char I2C_Read(char flag)
 *
 *
 * Input:           flag: bandera utilizada para seguir leyendo o para salir
 *
 * Output:          buffer: dato recuperado
 *
 *
 * Overview:        Lee la informacion del reloj y la retorna para cada variable
 *                  que lo requiere
 *
 * Note:            None
 ********************************************************************/

char I2C_Read(char flag)                 /*read data from location and 
                                         *send ack or nack depending upon parameter*/
{
        char buffer;
        RCEN = 1;                         /*enable receive*/
        while(!SSPSTATbits.BF);         /*wait for buffer full flag 
                                         *which is set when complete byte received*/
        buffer = SSPBUF;                  /*copy SSPBUF to buffer*/
       /*send acknowledgment or negative acknowledgment */        
        if(flag==0)
            I2C_Ack();
        else
            I2C_Nack();
        I2C_Ready();
        return(buffer);
}

/*********************************************************************
 * Function:        void I2C_Init(void)
 *
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Inicializa los puertos y configura el reloj
 *
 * Note:            None
 ********************************************************************/

void I2C_Init(void)
{
    TRISB0=1;							/*set up I2C lines by setting as input*/
	TRISB1=1;
	SSPSTAT=80;                         /*slew rate disabled, other bits are cleared*/
    SSPCON1=0x28;						/*enable SSP port for I2C Master mode,
                                         *clock = FOSC / (4 * (SSPADD+1))*/ 
	SSPCON2=0;
    SSPADD=BITRATE;                    /*clock 100 kHz*/  
    SSPIE=1;                            /*enable SSPIF interrupt*/
    SSPIF=0;
}

/*********************************************************************
 * Function:        void I2C_Ready(void)
 *
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Se encarga de comprobar la operacion si se completa o no
 *
 * Note:            None
 ********************************************************************/

void I2C_Ready(void)
{
    while(!SSPIF);                  /* Wait for operation complete */
    SSPIF=0;                        /*clear SSPIF interrupt flag*/
}

/*********************************************************************
 * Function:        void I2C_Start_Wait(char slave_write_address)
 *
 * Input:           slave_write_address: Direccion de escritura del esclavo
 *
 * Output:          None
 *
 * Overview:        Se encarga de escribir la informacion en el esclavo
 *
 * Note:            None
 ********************************************************************/

void I2C_Start_Wait(char slave_write_address)
{
  while(1)
  {   
    SSPCON2bits.SEN=1;              /*send start pulse*/
    while(SSPCON2bits.SEN);         /*wait for completion of start pulse*/
    SSPIF=0;
	if(!SSPSTATbits.S)              /*wait till start bit is detected*/    
        continue;
    I2C_Write(slave_write_address); /*write slave device address with write to communicate*/
    if(ACKSTAT)
    {
        I2C_Stop();
        continue;
    }    
    break;        
  }
}

/*********************************************************************
 * Function:        char I2C_Start(char slave_write_address)
 *
 * Input:           slave_write_address: Direccion de escritura del esclavo
 *
 * Output:          I2C_Write(slave_write_address): Retorna la direccion de erscritura
 *                  del esclavo para comunicarse
 *
 * Overview:        Se encarga iniciar la comunicacion con el esclavo
 *                  para poder escribir en el
 *
 * Note:            None
 ********************************************************************/

char I2C_Start(char slave_write_address)
{   
    SSPCON2bits.SEN=1;              /*send start pulse*/
    while(SSPCON2bits.SEN);         /*wait for completion of start */
	SSPIF=0;
    if(!SSPSTATbits.S)              /*wait till start bit is detected*/
    return 0;                       /*start failed*/    
    return (I2C_Write(slave_write_address));     /*write slave device address with write to communicate*/
     
}

/*********************************************************************
 * Function:        char I2C_Repeated_Start(char slave_read_address)
 *
 * Input:           slave_read_address: Direccion de lectura del esclavo
 *
 * Output:          Numero: Bandera para determinar si se continua
 *                  leyendo o no
 *
 * Overview:        Se encarga de determinar si se debe seguir leyendo
 *                  la informacion o no
 *
 * Note:            None
 ********************************************************************/

char I2C_Repeated_Start(char slave_read_address)
{
    RSEN = 1;                         /*send repeated start pulse*/
    while(RSEN);                    /*wait for completion of repeated start pulse*/
    SSPIF = 0;
	if(!SSPSTATbits.S)             /*wait till start bit is detected*/
    return 0;                       /*start failed*/    
    I2C_Write(slave_read_address);      /*write slave device address with read to communicate*/
    if (ACKSTAT)
     return 1;
    else
     return 2;
}

/*********************************************************************
 * Function:        char I2C_Stop(void)
 *
 * Input:           None
 *
 * Output:          Numero: Si se falla en deterner la comunicacion
 *
 * Overview:        Se encarga de deterner la comunicacion con el esclavo
 *                  ya sea en modo lectura o escritura
 *
 * Note:            None
 ********************************************************************/

char I2C_Stop(void)
{
    PEN = 1;                          /*stop communication*/
    while(PEN);                     /*wait for end of stop pulse*/
    if(!SSPSTATbits.P);             /*wait till stop bit is detected*/
    return 0;                       /*stop failed*/        
}

/*********************************************************************
 * Function:        char I2C_Write(unsigned char data)
 *
 * Input:          data: El dato a escribir en el SSPBUF
 *
 * Output:          Numero: Bandera para determinar si la escritura
 *                  fue correcta o no
 *
 * Overview:        Se encarga de escrinir la informacion en el registro 
 *                  SSPBUF
 *
 * Note:            None
 ********************************************************************/

char I2C_Write(unsigned char data)
{
      SSPBUF = data;                  /*write data to SSPBUF*/
      I2C_Ready();
      if (ACKSTAT)                  /*check for acknowledge bit*/
        return 1;
      else
        return 2;
}

/*********************************************************************
 * Function:        void I2C_Ack(void)
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Se encarga de reconocer los datos que se enviaran
 *
 * Note:            None
 ********************************************************************/

void I2C_Ack(void)
{
    ACKDT=0;					/*acknowledge data 1:NACK,0:ACK */
	ACKEN=1;					/*enable ACK to send*/	          
    while(ACKEN);
}

/*********************************************************************
 * Function:        void I2C_NAck(void)
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Se encarga de reconocer los datos que se enviaran y determinar
 *                  que no se quieren enviar mas datos
 *
 * Note:            None
 ********************************************************************/

void I2C_Nack(void)
{
    ACKDT=1;					/*acknowledge data 1:NACK,0:ACK*/
	ACKEN=1;					/*enable ACK to send*/	          
    while(ACKEN);
}
