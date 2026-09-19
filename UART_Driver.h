#ifndef USART_CONFIG_H
#define USART_CONFIG_H
#include <avr/io.h>
#define F_CPU 16000000UL
#include <stdint.h>

#define USART_DATA_FRAME_5BITS 0U
#define USART_DATA_FRAME_6BITS 1U
#define USART_DATA_FRAME_7BITS 2U
#define USART_DATA_FRAME_8BITS 3U
#define USART_DATA_FRAME_9BITS 7U

#define USART_NO_PARITY         0U
#define USART_EVEN_PARITY       2U
#define USART_ODD_PARITY        3U

#define USART_ONE_STOP_BIT      0U
#define USART_TWO_STOP_BITS     1U
/**
 * mode options:
 *         -Synchronous -> SYNC
 *         -Asynchronous-> ASYNC
 */

/**
 * define data frame size  options:
 *                             -DATA_FRAME_5BITS
 *                             -DATA_FRAME_6BITS
 *                             -DATA_FRAME_7BITS
 *                             -DATA_FRAME_8BITS
 *                             -DATA_FRAME_9BITS
 */

/**
 * define number of stop bits :
 *                      -STOP_1BIT
 *                      -STOP_2BITS
 */






/**
 * define the the parity mode
 *                          -EVEN
 *                          -ODD
 *                          -NO_PARITY
 */


/**
 * define the baud rate standard options:
 *                                     -2400
 *                                     -4800
 *                                     -9600
 *                                     -14400
 *                                     -19200
 *
 */

void    USART_voidInit(uint32_t Copy_u32BaudRate, uint8_t Copy_u8DataBits, uint8_t Copy_u8Parity, uint8_t Copy_u8StopBits);
void    USART_voidSendChar(uint8_t Copy_u8Data);
uint8_t USART_u8ReceiveChar(void);
void    USART_voidSendString(const uint8_t *Copy_pu8String);
void USART_voidReceiveString(uint8_t *Copy_pu8Buffer, uint16_t Copy_u16BufferSize) ;
#endif
