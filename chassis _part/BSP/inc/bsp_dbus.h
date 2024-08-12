#ifndef __BSP_DBUS_H
#define __BSP_DBUS_H
#include "main.h"

typedef struct
{
   struct
   {   
     int16_t ch[5];
     uint8_t s1;
     uint8_t s2;
   }rc;
   int32_t Lost_contact;
}rc_data_t;

typedef struct 
{
 uint8_t *start;
 uint8_t *start_head;
 uint8_t *end;
 uint8_t *end_head;
}LCB;

typedef struct
{
 uint32_t Rxcount;
 uint32_t Txcount;
 uint32_t TxFlag;	
 LCB      Rxlocation[10];
 LCB      Txlocation[10];
 LCB     *RxInPtr;
 LCB     *RxOutPtr;
 LCB     *RxEndPtr;
 LCB     *TxInPtr;
 LCB     *TxOutPtr;	
 LCB     *TxEndPtr; 
}UCB;

#define RX_BufSIZE 2048
#define TX_BufSIZE 2048	
#define RX_MAX 256

extern UCB dmarx;

void USART_DBUSData(uint8_t *pdata,uint32_t data_len);
void USART_PtrInit(void);
void DMA_RX_Init(void);
void dr16_data_input(void);
void rx_data_cpy(void);
void Rcdata_Decode(rc_data_t  *RC,uint8_t *pData);
void Lost_contact_CHSetZero(rc_data_t  *RC);
rc_data_t *get_rc_struct(void);
#endif /*__BSP_DBUS_H*/