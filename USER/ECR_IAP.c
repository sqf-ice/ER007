/***************************************************************************************

*****************************************************************************************/
#include "king.h"				/* Kingtron library and I/O routines */
#include "exthead.h"
#include "exth.h"

#include "stm32f2xx_flash.h"

//#include "lcd_160x.h"

//__IO FLASH_Status status = FLASH_COMPLETE;
//#define __DEBUG__

typedef  void (*pFunction)(void);

#define SIZE_IAP    2048

#define APPLICATION_ADDRESS	 FLASH_BASE


#define SECTOR_MASK               ((uint32_t)0xFFFFFF07)

//////////////////////////////////////////////////////
#if (DD_LCD_1601 || DD_ZIP)

#define LCD_BL	GPIO_Pin_2

#define IAP_LED_SendData(i, dat) do{\
                        if (dat & 1)\
                            GPIOB->BSRRL = LCD_BL;\
                        else\
                            GPIOB->BSRRH = LCD_BL;\
                    }while(0)

#else

#define	LED_DATA_High()		GPIOF->BSRRL = GPIO_Pin_10
#define	LED_DATA_Low()		GPIOF->BSRRH = GPIO_Pin_10
#define	LED_CLK_High()	 	GPIOG->BSRRL =  GPIO_Pin_14
#define	LED_CLK_Low()	 	GPIOG->BSRRH =  GPIO_Pin_14
#define	LED_LATCH_High()	GPIOF->BSRRL =  GPIO_Pin_9
#define	LED_LATCH_Low()		GPIOF->BSRRH =  GPIO_Pin_9


#define IAP_LED_SendBit(databit) do{\
                        	if (databit & 0x01)\
                        		LED_DATA_High();\
                        	else\
                        		LED_DATA_Low();\
                        	LED_CLK_High();LED_CLK_High();LED_CLK_High();LED_CLK_High();\
                        	LED_CLK_Low();LED_CLK_Low();LED_CLK_Low();LED_CLK_Low();\
                        }while(0)


#define IAP_LED_SendData(i, dat) do{\
                    	LED_LATCH_Low();\
                    	for (i=0; i<DISP_WIDTH; i++)\
                    	{\
                    		IAP_LED_SendBit(1>>i);\
                    	}\
                    	for (i=0; i<8; i++)\
                    	{\
                   			IAP_LED_SendBit(dat>>i);\
                    	}\
                    	LED_LATCH_High();\
                    }while(0)
#endif
///////////////////////////////////////////////////////

/**
  * @brief  Read single data from the UART0 peripheral.
  * @retval uint8_t Data
  */
#define IAP_Get(Data)    do {\
                            if ((UART0->SR & USART_FLAG_RXNE) != (uint16_t)RESET)\
                            {\
                                Data = (uint8_t)UART0->DR;\
                                break;\
                            }\
                        } while (1)
/////////////////////////////////////////////////

/**
  * @brief  Transmits single data through the UART0 peripheral.
  * @retval None
  */
#define IAP_Send(Data) do {\
                        UART0->DR = (Data & (uint16_t)0x00FF);\
                        while ((UART0->SR & USART_FLAG_TC) == (uint16_t)RESET){}\
                      } while (0)


#ifdef __DEBUG__

#define IAP_FLASH_Lock()   {}//DispStrXY("LOCK",0,0)

#define IAP_FLASH_Unlock() {}

#define IAP_FLASH_GetStatus(flashstatus) do {\
                    }while (0)

#define IAP_FLASH_WaitForLastOperation(status) do{ \
                        } while(0)

#define IAP_FLASH_EraseAllSectors(status) do  {\
                        } while (0)

/**
  * @brief  Programs a half word (16-bit) at a specified address.
  * @note   This function must be used when the device voltage range is from 2.1V to 3.6V.
  * @param  Address: specifies the address to be programmed.
  *         This parameter can be any address in Program memory zone or in OTP zone.
  * @param  Data: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERROR_PROGRAM,
  *                       FLASH_ERROR_WRP, FLASH_ERROR_OPERATION or FLASH_COMPLETE.
  */
#define IAP_FLASH_ProgramHalfWord(Address, Data, status) do  {\
                                } while (0)


#else
#define IAP_FLASH_Lock()   FLASH->CR |= FLASH_CR_LOCK

#define IAP_FLASH_Unlock() do{\
                        if((FLASH->CR & FLASH_CR_LOCK) != RESET)\
                        {\
                            FLASH->KEYR = FLASH_KEY1;\
                            FLASH->KEYR = FLASH_KEY2;\
                        }\
                      }while(0)

#define IAP_FLASH_GetStatus(flashstatus) do {\
                      if((FLASH->SR & FLASH_FLAG_BSY) == FLASH_FLAG_BSY) \
                          flashstatus = FLASH_BUSY;\
                      else if((FLASH->SR & FLASH_FLAG_WRPERR) != (uint32_t)0x00)\
                          flashstatus = FLASH_ERROR_WRP;\
                      else if((FLASH->SR & (uint32_t)0xEF) != (uint32_t)0x00)\
                            flashstatus = FLASH_ERROR_PROGRAM; \
                      else if((FLASH->SR & FLASH_FLAG_OPERR) != (uint32_t)0x00)\
                           flashstatus = FLASH_ERROR_OPERATION;\
                      else\
                           flashstatus = FLASH_COMPLETE;\
                    }while (0)

#define IAP_FLASH_WaitForLastOperation(status) do{ \
                            IAP_FLASH_GetStatus(status);\
                        } while(status == FLASH_BUSY)

#define IAP_FLASH_EraseAllSectors(status) do  {\
                             FLASH->CR &= CR_PSIZE_MASK;\
                             FLASH->CR |= FLASH_PSIZE_WORD;\
                             FLASH->CR |= FLASH_CR_MER;\
                             FLASH->CR |= FLASH_CR_STRT;\
                             IAP_FLASH_WaitForLastOperation(status);\
                             FLASH->CR &= (~FLASH_CR_MER);\
                        } while (0)

/**
  * @brief  Programs a half word (16-bit) at a specified address.
  * @note   This function must be used when the device voltage range is from 2.1V to 3.6V.
  * @param  Address: specifies the address to be programmed.
  *         This parameter can be any address in Program memory zone or in OTP zone.
  * @param  Data: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERROR_PROGRAM,
  *                       FLASH_ERROR_WRP, FLASH_ERROR_OPERATION or FLASH_COMPLETE.
  */
#define IAP_FLASH_ProgramHalfWord(Address, Data, status) do  {\
                                    IAP_FLASH_WaitForLastOperation(status);\
                                    FLASH->CR &= CR_PSIZE_MASK;\
                                    FLASH->CR |= FLASH_PSIZE_HALF_WORD;\
                                    FLASH->CR |= FLASH_CR_PG;\
                                    *(__IO uint16_t*)Address = Data;\
                                    IAP_FLASH_WaitForLastOperation(status);\
                                    FLASH->CR &= (~FLASH_CR_PG);\
                                } while (0)

#endif
// communicat with Host computer throw Rs232 port
// 0 1 2 3 4 5 6
//:02000002F0000C
// |||  ||||  |\/______Check value
// |||  |||\__/________Datas (2 bytes)
// |||  |\/____________Flag, 00h=Data;01h=End of a segment;02h=New segment address;04h=扩展线性地址记录
// ||\__/______________Offset address in Segment
// \/__________________Length of Datas (02h=2 bytes
// 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0
// :10000000434C454152000000000000000000000089
// :100010004E554D31000000000000000000000000BF
// :04101000B3A32E0058
// :00000001FF		;End of the file

//void ((*GotoBoot)()) = (void((*)()))(*((ULONG *)(APPLICATION_ADDRESS+4)));//获得boot入口
//pFunction GotoBoot;
//#include <absacc.h> //用于__at(0x08080000)
//void  UpdateBIOS() __attribute__((section("LR_IROM2")));
void  UpdateBIOS()
{
    FLASH_Status Flash_Status;

    BYTE length, bcc;
    BYTE sBuf;
    WORD sCheckSum,sLines,i,j;

    ULONG SegAddr,sAddr;

	WORD OffAddr;

    sCheckSum=sLines=0;
	SegAddr = 0xffff;

	while (TRUE)
	{
        //收取一条数据包>>>>>>>>>>>>>>>>>>
	    do {
		    IAP_Get(sBuf);
		}while (sBuf != SOH);

		IAP_Send(ACK);

	    IAP_Get(sBuf);
	    length = sBuf;

#if (PCBUFMAX<256)
	    if (!length || length >= PCBUFMAX-2)
	    {
			sBuf = NAK;				 // sent NAK
			IAP_Send(NAK);
	        continue;
	    }
#endif
	    bcc = length;
	    i = 0;
	    for (i=0;i < length+1;i++)
	    {
            IAP_Get(sBuf);
		    PCBuffer[i]=sBuf;
	        bcc += sBuf;
	    }
	    if (bcc)// the verify error
	    {
			IAP_Send(NAK);
	        continue;
	    }
	    if (length == 3 && PCBuffer[0]=='U')
	    {
	    	if (PCBuffer[1]=='C' && PCBuffer[2]=='A')
				while (1){}//下载异常终止
	    }

        //将一行HEX数据转换为BIN数据>>>>>>>>
		j = 0;
		sCheckSum += PCBuffer[0];
		for (i=1;i<length;i++)// skip the first ':'
		{
			sCheckSum+=PCBuffer[i];
			if (PCBuffer[i]>'9')
				sBuf =  PCBuffer[i]-'A'+10;
			else
				sBuf =  PCBuffer[i]-'0';
			if (i & 1)
				bcc = sBuf;
			else
				PCBuffer[j++]= (bcc<<4) | sBuf;
		}
        PCBuffer[j]=0xff;
		bcc = 0;
		for (i=0;i<j;i++)
			bcc += PCBuffer[i];// check the data recived
		if (bcc)// data error when tranxmited
	    {
			IAP_Send(NAK);
	        continue;
	    }
        IAP_Send(ACK);
		sLines++;

        if ((sLines & 0x3f)==0)
        {
			j = (sLines>>6);
            IAP_LED_SendData(i,j);
//            DisplayDecXY(sLines,0,2,6);
        }

        if (PCBuffer[3] == 0x00)//为数据
        {
            OffAddr = PCBuffer[1];
            OffAddr = (OffAddr<<8)+PCBuffer[2];

            SegAddr &= 0xffff0000L;
            SegAddr += OffAddr;

            length = PCBuffer[0];

            sAddr = SegAddr;
            for (i=0;i<length;i+=2)
            {//将数据写入FLASH
                OffAddr = PCBuffer[i+5];
                OffAddr = (OffAddr<<8)+PCBuffer[i+4];
                if (SegAddr>=FLASH_BASE && SegAddr<(FLASH_BASE+0x80000L))//ccr2016-05-25
                    IAP_FLASH_ProgramHalfWord(SegAddr,OffAddr,Flash_Status);
                SegAddr+=2;
            }
            for (i=0;i<length;i+=2)
            {//校验写入FLASH的数据
                OffAddr = PCBuffer[i+5];
                OffAddr = (OffAddr<<8)+PCBuffer[i+4];

                if (*(__IO uint16_t*)sAddr != OffAddr)
                {
                    IAP_Send(CAN);
                    IAP_FLASH_Lock();
                    while (1);
                }
                sAddr+=2;
            }
        }
        else if (PCBuffer[3] == 0x01)//HEX数据结束
        {
            IAP_Send((sCheckSum & 0xff));//发送校验和
            IAP_Send((sCheckSum>>8));
            IAP_FLASH_Lock();
            for (SegAddr=0;SegAddr<0x800000L;SegAddr++)
            {//delay moments for IAP_Send
                __NOP();
            }
#if (1)          //Reset system
            //__set_FAULTMASK(1);
            NVIC_SystemReset();
                                                  /* wait until reset */
#else
            GotoBoot = (pFunction)(*(__IO uint32_t*) (APPLICATION_ADDRESS + 4));
            __set_MSP(*(__IO uint32_t*) APPLICATION_ADDRESS);/* Initialize user application's Stack Pointer */
            __enable_irq();    //打开所有中断
            __enable_fault_irq();
            GotoBoot();/* Jump to Boot */
            while (1);// break;//程序数据下载完毕,复位
#endif
        }
		else if (PCBuffer[3] == 0x02 || PCBuffer[3] == 0x04)// new address for data or at the end of HEX file
		{
            sAddr = PCBuffer[4];
            sAddr = (sAddr<<8)+PCBuffer[5];
            sAddr <<= 16;

            if (sAddr<FLASH_BASE || sAddr>=(FLASH_BASE+0x80000L))
            {//超出Flash空间范围,禁止更新
                IAP_Send(CAN);
                IAP_FLASH_Lock();
                while (1);
            }
            else if (SegAddr == 0xffff)// save the data to flash
			{// 擦除flash
                IAP_FLASH_Unlock();
                IAP_FLASH_EraseAllSectors(Flash_Status);
			}

            SegAddr = sAddr;
		}
	}
}
/*
void EnterBootLoader()
{
	void((*BootLoaderEntry)()) = (void((*)()))(*((ULONG *)0x1FFFF004));
	SCB->VTOR = 0X1FFFF000;
	__set_MSP(*(__IO uint32_t*) ((ULONG *)0x1FFFF000));
	(*BootLoaderEntry)();
}*/
