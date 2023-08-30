/************************************************************************************************
Company:
Microside Technology Inc.
File Name:
Bluetooth HM-10.c
Product Revision  :  1
Device            :  X-TRAINER
Driver Version    :  1.0
************************************************************************************************/

/*
---------------------------------------------------------------------------
Esta práctica consiste en realizar el envio de datos por medio de un módulo
Bluetooth, usando el protocolo de comunicación serial UART, para enviar un
comando simple para prender y apagar un LED incluido en la tarjeta X-TRAINER,
y un segundo comando para preguntar el estado de un botón.
---------------------------------------------------------------------------
*/

#include <16F887.h>                      // Incluye el microcontrolador con el que se va a trabajar
#use delay( clock = 20Mhz, crystal )     // Tipo de oscilador y frecuencia dependiendo del microcontrolador

//-------------------------------------------------------------------------------
#USE RS232( stream = SERIE, BAUD = 9600, PARITY = N, XMIT = PIN_C6, RCV = PIN_C7, BITS = 8 )

#define LED pin_A1
#define Boton pin_A2

void main( void ) {

   while ( !kbhit() ) {                  // Pregunta si hay algun dato recibido
      
      while ( 1 ) {
         char Caracter = getc();         // Guarda el caracter

         if ( Caracter == '0' ) {
            output_low( LED );           // Apaga el LED
            fprintf( SERIE, "LED APAGADO\r\n" );
         } else if ( Caracter == '1' ) {
            output_HIGH( LED );          // Enciende el LED
            fprintf( SERIE, "LED ENCENDIDO\r\n" );
         } else if ( Caracter == '?' ) {

            if ( 1 == input( Boton ) ) { // Pregunta el estado del botón
               Printf( "0" );            // Envía un 0 si el botón no está presionado
            } else {
               Printf( "1" );            // Envía un 1 si el botón está presionado
            }
         }
      }
   }
}