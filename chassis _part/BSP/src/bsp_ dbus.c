#include "bsp_dbus.h"
#include <string.h> 
#include "usart.h"

uint8_t  DR16_DATA[18]; 

rc_data_t rc;
UCB dmarx;

uint8_t rxbuffer[RX_BufSIZE];
uint8_t dbus_buffer[TX_BufSIZE];
//对应18字节
#define  DBUS_data_len   18
#define  CH_DATA_OFFSET  1024

#define Dead_Band(x,val) (x < val && x > -val) ? 0 : x 

rc_data_t *get_rc_struct(void)
{
	return &rc; 
}


/// @brief 遥控器数据解码 
/// @param rc 通道数据结构体
/// @param pdata dbus原始数据
void Rcdata_Decode(rc_data_t  *RC,uint8_t *pData)
{
    RC->rc.ch[0] = ((int16_t)pData[0] | ((int16_t)pData[1] << 8)) & 0x07FF;
    RC->rc.ch[1] = (((int16_t)pData[1] >> 3) | ((int16_t)pData[2] << 5)) & 0x07FF;
    RC->rc.ch[2] = (((int16_t)pData[2] >> 6) | ((int16_t)pData[3] << 2) | ((int16_t)pData[4] << 10)) & 0x07FF;
    RC->rc.ch[3] = (((int16_t)pData[4] >> 1) | ((int16_t)pData[5] << 7)) & 0x07FF;
    RC->rc.ch[4] = ((int16_t)pData[16]) | ((int16_t)pData[17] << 8);
    RC->rc.s1 = ((pData[5] >> 4) & 0x000C) >> 2;
    RC->rc.s2 = ((pData[5] >> 4) & 0x0003);
    //遥控数据抵消
    RC->rc.ch[0] -= CH_DATA_OFFSET;
    RC->rc.ch[1] -= CH_DATA_OFFSET;
    RC->rc.ch[2] -= CH_DATA_OFFSET;
    RC->rc.ch[3] -= CH_DATA_OFFSET;
    RC->rc.ch[4] -= CH_DATA_OFFSET;
    //死区设置，防止误操作,导致摇杆乱摆
    for (int i = 0;i <= 4;i++)
    {
        RC->rc.ch[i] = Dead_Band(RC->rc.ch[i],50); 
    }
    //失联时间重置
    RC->Lost_contact = 0;
}

/// @brief 失联时间过长，重置通道值
/// @param  
void Lost_contact_CHSetZero(rc_data_t  *RC)
{
    RC->rc.ch[0] = 0;
    RC->rc.ch[1] = 0;
    RC->rc.ch[2] = 0;
    RC->rc.ch[3] = 0;
    RC->rc.ch[4] = 0;
}

/// @brief 缓冲区重置
/// @param  
void USART_PtrInit(void)
{
	// 对指针进行赋倿
	dmarx.RxInPtr = &dmarx.Rxlocation[0];
	dmarx.RxOutPtr = &dmarx.Rxlocation[0];
	dmarx.RxEndPtr = &dmarx.Rxlocation[9];
	dmarx.Rxcount = 0;
	dmarx.RxInPtr->start = rxbuffer;

	dmarx.TxInPtr = &dmarx.Txlocation[0];
	dmarx.TxOutPtr = &dmarx.Txlocation[0];
	dmarx.TxEndPtr = &dmarx.Txlocation[9];
	dmarx.Txcount = 0;
	dmarx.TxInPtr->start = dbus_buffer;
    
	
	DMA_RX_Init();
}



// 使能中断
void DMA_RX_Init(void)
{
	__HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE);
	HAL_UART_Receive_DMA(&huart3, dmarx.RxInPtr->start, RX_MAX);
}

/// @brief 中断回调
/// @param huart 
void HAL_UART_AbortReceiveCpltCallback(UART_HandleTypeDef *huart)
{
	// static int count = 0;
	if (huart->Instance == USART3)
	{
		// 接收到数据的朿后一位的位置
		dmarx.RxInPtr->end = &rxbuffer[dmarx.Rxcount - 1];
		
		// 将结构体数组的位置自增
	    dmarx.RxInPtr++;
		
		// 如果存储的数据达到了location数组的最后一位，则将inptr归位，重新存傿
		if (dmarx.RxInPtr == dmarx.RxEndPtr)
		{
			dmarx.RxInPtr = dmarx.Rxlocation;
		}
		// 如果RX_BUFFER能接收的数据量剩余量小于256，则将RXbuffer归位，重罿
		// 防止数据断层，导致读数错误
		if ((RX_BufSIZE - dmarx.Rxcount) < RX_MAX)
		{
			dmarx.Rxcount = 0;
			dmarx.RxInPtr->start = rxbuffer;
		}
		else 
		{
			// 从数据的下一位开时
			dmarx.RxInPtr->start = &rxbuffer[dmarx.Rxcount];
		}
		// 重启接收
		HAL_UART_Receive_DMA(&huart3, dmarx.RxInPtr->start, RX_MAX);
        rx_data_cpy();
		dr16_data_input();
	}
}
/// @brief 
/// @param pdata 
/// @param data_len 
void USART_DBUSData(uint8_t *pdata, uint32_t data_len)
{
	if ((TX_BufSIZE - dmarx.Txcount) >= data_len)
	{
		dmarx.TxInPtr->start = &dbus_buffer[dmarx.Txcount];
	}
	else
	{
		dmarx.Txcount = 0;
		dmarx.TxInPtr->start = dbus_buffer;
	}
	memcpy(dmarx.TxInPtr->start, pdata, data_len);
	dmarx.Txcount += data_len;
	//问题
	dmarx.TxInPtr->end = &dbus_buffer[dmarx.Txcount - 1];
	dmarx.TxInPtr++;
	if (dmarx.TxInPtr == dmarx.TxEndPtr)
	{
		dmarx.TxInPtr = &dmarx.Txlocation[0];
	}
}


/// @brief 传递
/// @param  
void rx_data_cpy(void)
{
	if (dmarx.RxOutPtr != dmarx.RxInPtr)
	{
		USART_DBUSData(dmarx.RxOutPtr->start, (dmarx.RxOutPtr->end - dmarx.RxOutPtr->start + 1));
		dmarx.RxOutPtr++;
		if (dmarx.RxOutPtr == dmarx.RxEndPtr)
		{
			dmarx.RxOutPtr = &dmarx.Rxlocation[0];
		}
	}
}
/// @brief 解算数据
/// @param  
void dr16_data_input(void)
{
	if ((dmarx.TxOutPtr != dmarx.TxInPtr))
	{
		// 判断数据是否合法＿18byte＿
		if ((dmarx.TxOutPtr->end - dmarx.TxOutPtr->start + 1) == DBUS_data_len)
		{
		     Rcdata_Decode(&rc,dmarx.TxOutPtr->start);

		}
		dmarx.TxOutPtr++;
		if (dmarx.TxOutPtr == dmarx.TxEndPtr)
		{
			dmarx.TxOutPtr = &dmarx.Txlocation[0];
		}
	}
}
