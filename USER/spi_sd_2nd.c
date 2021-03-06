/**
  ******************************************************************************
  * @file    stm32_eval_spi_sd.c
  * @author  MCD Application Team
  * @version V4.5.0
  * @date    07-March-2011  
  * Modefied
  * @date    03-April-2012
  * @author  Armjishu.com Application Team
  * @version V2.1
  * @brief   This file provides a set of functions needed to manage the SPI SD 
  *          Card memory mounted on STM32xx-EVAL board (refer to stm32_eval.h
  *          to know about the boards supporting this memory). 
  *          It implements a high level communication layer for read and write 
  *          from/to this memory. The needed STM32 hardware resources (SPI and 
  *          GPIO) are defined in stm32xx_eval.h file, and the initialization is 
  *          performed in SD_LowLevel_Init() function declared in stm32xx_eval.c 
  *          file.
  *          You can easily tailor this driver to any other development board, 
  *          by just adapting the defines for hardware resources and 
  *          SD_LowLevel_Init() function.
  *
  *          ===================================================================
  *          Note: 
  *           - This driver does support SD High Capacity cards.
  *          ===================================================================
  *
  *          +-------------------------------------------------------+
  *          |                     Pin assignment                    |
  *          +-------------------------+---------------+-------------+
  *          |  STM32 SPI Pins         |     SD        |    Pin      |
  *          +-------------------------+---------------+-------------+
  *          | SD_SPI_CS_PIN           |   ChipSelect  |    1        |
  *          | SD_SPI_MOSI_PIN / MOSI  |   DataIn      |    2        |
  *          |                         |   GND         |    3 (0 V)  |
  *          |                         |   VDD         |    4 (3.3 V)|
  *          | SD_SPI_SCK_PIN / SCLK   |   Clock       |    5        |
  *          |                         |   GND         |    6 (0 V)  |
  *          | SD_SPI_MISO_PIN / MISO  |   DataOut     |    7        |
  *          +-------------------------+---------------+-------------+
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************  
  */

/* Includes ------------------------------------------------------------------*/
#include "spi_sd.h"
#include <stdio.h>


static u8 flag_SDHC = 0;

/** @addtogroup Utilities
  * @{
  */
  
/** @addtogroup STM32_EVAL
  * @{
  */ 

/** @addtogroup Common
  * @{
  */
  
/** @addtogroup STM32_EVAL_SPI_SD
  * @brief      This file includes the SD card driver of STM32-EVAL boards.
  * @{
  */ 

/** @defgroup STM32_EVAL_SPI_SD_Private_Types
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup STM32_EVAL_SPI_SD_Private_Defines
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup STM32_EVAL_SPI_SD_Private_Macros
  * @{
  */
/**
  * @}
  */ 
  

/** @defgroup STM32_EVAL_SPI_SD_Private_Variables
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup STM32_EVAL_SPI_SD_Private_Function_Prototypes
  * @{
  */
/**
  * @}
  */ 


/** @defgroup STM32_EVAL_SPI_SD_Private_Functions
  * @{
  */ 



/**
  * @brief  Initializes the SD/SD communication.
  * @param  None
  * @retval The SD Response: 
  *         - SD_RESPONSE_FAILURE: Sequence failed
  *         - SD_RESPONSE_NO_ERROR: Sequence succeed
  */
SD_Error SD_Init_2nd(void)
{
  uint32_t TimeOut, i = 0;
  SD_Error Status = SD_RESPONSE_NO_ERROR;

  /*!< Initialize SD_SPI */
  SD_LowLevel_Init(); 
  SD_SPI_SetSpeedLow();

  /*------------Put SD in SPI mode--------------*/
  /*!< SD initialized and set to SPI mode properly */
  TimeOut = 0;
  do
  {
    /*!< SD chip select high */
    SD_CS_HIGH_2ND();
  
    /*!< Send dummy byte 0xFF, 10 times with CS high */
    /*!< Rise CS and MOSI for 80 clocks cycles */
    for (i = 0; i <= 9; i++)
    {
      /*!< Send dummy byte 0xFF */
      SD_WriteByte(SD_DUMMY_BYTE);
    }    
    
	Status = SD_GoIdleState_2nd();
    if(TimeOut > 6)
    {
      break;
    }
    TimeOut++;
  }while(Status);

  SD_SPI_SetSpeedHigh();
  
  return (Status);
}

/**
 * @brief  Detect if SD card is correctly plugged in the memory slot.
 * @param  None
 * @retval Return if SD is detected or not
 */
#ifdef CASE_MCR30
uint8_t SD_Detect_2nd(void)
{
  __IO uint8_t status = SD_PRESENT;

  /*!< Check GPIO to detect SD */
  if (GPIO_ReadInputData(SD_DETECT_GPIO_PORT_2ND) & SD_DETECT_PIN_2ND)
  {
    status = SD_NOT_PRESENT;
  }
  return status;
}
#endif

/**
  * @brief  Returns information about specific card.
  * @param  cardinfo: pointer to a SD_CardInfo structure that contains all SD 
  *         card information.
  * @retval The SD Response:
  *         - SD_RESPONSE_FAILURE: Sequence failed
  *         - SD_RESPONSE_NO_ERROR: Sequence succeed
  */
uint32_t CardCapacity_2nd=0;
SD_Error SD_GetCardInfo_2nd(SD_CardInfo *cardinfo)
{
  SD_Error status = SD_RESPONSE_FAILURE;

  status = SD_GetCSDRegister_2nd(&(cardinfo->SD_csd));
  if(status == SD_RESPONSE_FAILURE)
  {
  	status = SD_GetCSDRegister_2nd(&(cardinfo->SD_csd));
    if(status == SD_RESPONSE_FAILURE)
		return status;
  }
  
  status = SD_GetCIDRegister_2nd(&(cardinfo->SD_cid));
  if(status == SD_RESPONSE_FAILURE)
  {
  	status = SD_GetCIDRegister_2nd(&(cardinfo->SD_cid));
	if(status == SD_RESPONSE_FAILURE)
    	return status;
  } 
  
  cardinfo->CardCapacity = (cardinfo->SD_csd.DeviceSize + 1) ;
  cardinfo->CardCapacity *= (1 << (cardinfo->SD_csd.DeviceSizeMul + 2));
  cardinfo->CardBlockSize = 1 << (cardinfo->SD_csd.RdBlockLen);
  cardinfo->CardCapacity *= cardinfo->CardBlockSize;

	//ouhs
	CardCapacity_2nd = cardinfo->CardCapacity;
/*	
	xprintf("\n\r SD CardBlockSize %d CardCapacity %d M", cardinfo->CardBlockSize, cardinfo->CardCapacity / 1024 / 1024);
	xprintf("\n\r SD Product name: %c%c%c%c%c", (cardinfo->SD_cid.ProdName1 & 0xff000000)>>24, 
							(cardinfo->SD_cid.ProdName1 & 0xff0000)>>16, (cardinfo->SD_cid.ProdName1 & 0xff00)>>8,
							(cardinfo->SD_cid.ProdName1 & 0xff),  cardinfo->SD_cid.ProdName2);
	xprintf("\n\r SD ManufactDate: 20%02d.%d \n", (cardinfo->SD_cid.ManufactDate & 0x0ff0)>>4, 
							(cardinfo->SD_cid.ManufactDate & 0x0f));	
*/	
	
  /*!< Returns the reponse */
  return status;
}

/**
  * @brief  Reads a block of data from the SD.
  * @param  pBuffer: pointer to the buffer that receives the data read from the 
  *                  SD.
  * @param  ReadAddr: SD's internal address to read from.
  * @param  BlockSize: the SD card Data block size.
  * @retval The SD Response:
  *         - SD_RESPONSE_FAILURE: Sequence failed
  *         - SD_RESPONSE_NO_ERROR: Sequence succeed
  */
SD_Error SD_ReadBlock_2nd(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t BlockSize)
{
  uint32_t i = 0;
  SD_Error rvalue = SD_RESPONSE_FAILURE;
  SD_Error status = SD_RESPONSE_FAILURE;
	
  /*!< SD chip select low */
  SD_CS_LOW_2ND();
  
if(flag_SDHC == 1)
{
	ReadAddr = ReadAddr/512;
}
  /*!< Send CMD17 (SD_CMD_READ_SINGLE_BLOCK) to read one block */
  SD_SendCmd(SD_CMD_READ_SINGLE_BLOCK, ReadAddr, 0xFF);


//ouhs>>>>>>>>>>>>>>>>>>>>>>
//使用fatfs有时对cmd17命令没有响应，需要重发一次命令。但当作flash操作时没有发现该问题.
	status = SD_GetResponse(SD_RESPONSE_NO_ERROR);
  if (status != SD_RESPONSE_NO_ERROR)
	{
			SD_SendCmd(SD_CMD_READ_SINGLE_BLOCK, ReadAddr, 0xFF);
			status = SD_GetResponse(SD_RESPONSE_NO_ERROR);
	}
//ouhs<<<<<<<<<<<<<<<<<<<<<<  

  /*!< Check if the SD acknowledged the read block command: R1 response (0x00: no errors) */
  //ouhs if (!SD_GetResponse(SD_RESPONSE_NO_ERROR))
	if (status == SD_RESPONSE_NO_ERROR)
  {
    /*!< Now look for the data token to signify the start of the data */
    if (!SD_GetResponse(SD_START_DATA_SINGLE_BLOCK_READ))
    {
#if (SPI_DMA==0)		
      /*!< Read the SD block data : read NumByteToRead data */
      for (i = 0; i < BlockSize; i++)
      {
        /*!< Save the received data */
        *pBuffer = SD_ReadByte();
       
        /*!< Point to the next location where the byte read will be saved */
        pBuffer++;
      }	
#else			
			DMA1_Start_SPI_RX(pBuffer,BlockSize);			
#endif	
			
      /*!< Get CRC bytes (not really needed by us, but required by SD) */
      SD_ReadByte();
      SD_ReadByte();
					
      /*!< Set response value to success */
      rvalue = SD_RESPONSE_NO_ERROR;
    }
  }
  /*!< SD chip select high */
  SD_CS_HIGH_2ND();
  
  /*!< Send dummy byte: 8 Clock pulses of delay */
  SD_WriteByte(SD_DUMMY_BYTE);
  
  /*!< Returns the reponse */
  return rvalue;
}

/**
  * @brief  Reads multiple block of data from the SD.
  * @param  pBuffer: pointer to the buffer that receives the data read from the 
  *                  SD.
  * @param  ReadAddr: SD's internal address to read from.
  * @param  BlockSize: the SD card Data block size.
  * @param  NumberOfBlocks: number of blocks to be read.
  * @retval The SD Response:
  *         - SD_RESPONSE_FAILURE: Sequence failed
  *         - SD_RESPONSE_NO_ERROR: Sequence succeed
  */
SD_Error SD_ReadMultiBlocks_2nd(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t BlockSize, uint32_t NumberOfBlocks)
{
  uint32_t i = 0, Offset = 0;
  SD_Error rvalue = SD_RESPONSE_FAILURE;
  
  /*!< SD chip select low */
  SD_CS_LOW_2ND();
  /*!< Data transfer */
  while (NumberOfBlocks--)
  {
    if(flag_SDHC == 1)
    {
        /*!< Send CMD17 (SD_CMD_READ_SINGLE_BLOCK) to read one block */
        SD_SendCmd (SD_CMD_READ_SINGLE_BLOCK,(ReadAddr + Offset)/512, 0xFF);
    }
    else
    {
        /*!< Send CMD17 (SD_CMD_READ_SINGLE_BLOCK) to read one block */
        SD_SendCmd (SD_CMD_READ_SINGLE_BLOCK, ReadAddr + Offset, 0xFF);
    }
    /*!< Check if the SD acknowledged the read block command: R1 response (0x00: no errors) */
    if (SD_GetResponse(SD_RESPONSE_NO_ERROR))
    {
      return  SD_RESPONSE_FAILURE;
    }
    /*!< Now look for the data token to signify the start of the data */
    if (!SD_GetResponse(SD_START_DATA_SINGLE_BLOCK_READ))
    {
#if (SPI_DMA==0)				
      /*!< Read the SD block data : read NumByteToRead data */
      for (i = 0; i < BlockSize; i++)
      {
        /*!< Read the pointed data */
        *pBuffer = SD_ReadByte();
        /*!< Point to the next location where the byte read will be saved */
        pBuffer++;
      }
#else
			DMA1_Start_SPI_RX(pBuffer,BlockSize);
			pBuffer += 512;			
#endif
      /*!< Set next read address*/
      Offset += 512;
      /*!< get CRC bytes (not really needed by us, but required by SD) */
      SD_ReadByte();
      SD_ReadByte();
      /*!< Set response value to success */
      rvalue = SD_RESPONSE_NO_ERROR;
    }
    else
    {
      /*!< Set response value to failure */
      rvalue = SD_RESPONSE_FAILURE;
    }
  }
  /*!< SD chip select high */
  SD_CS_HIGH_2ND();
  /*!< Send dummy byte: 8 Clock pulses of delay */
  SD_WriteByte(SD_DUMMY_BYTE);
  /*!< Returns the reponse */
  return rvalue;
}

/**
  * @brief  Writes a block on the SD
  * @param  pBuffer: pointer to the buffer containing the data to be written on 
  *                  the SD.
  * @param  WriteAddr: address to write on.
  * @param  BlockSize: the SD card Data block size.
  * @retval The SD Response: 
  *         - SD_RESPONSE_FAILURE: Sequence failed
  *         - SD_RESPONSE_NO_ERROR: Sequence succeed
  */
SD_Error SD_WriteBlock_2nd(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t BlockSize)
{
  uint32_t i = 0;
  SD_Error rvalue = SD_RESPONSE_FAILURE;
  SD_Error status = SD_RESPONSE_FAILURE;

  /*!< SD chip select low */
  SD_CS_LOW_2ND();

  if(flag_SDHC == 1)
  {
  	WriteAddr = WriteAddr/512;
  }
  /*!< Send CMD24 (SD_CMD_WRITE_SINGLE_BLOCK) to write multiple block */
  SD_SendCmd(SD_CMD_WRITE_SINGLE_BLOCK, WriteAddr, 0xFF);
	
//ouhs>>>>>>>>>>>>>>>>>>>>>>
//使用fatfs有时对cmd24命令没有响应，需要重发一次命令。但当作flash操作时没有发现该问题.
	status = SD_GetResponse(SD_RESPONSE_NO_ERROR);
  if (status != SD_RESPONSE_NO_ERROR)
	{		
		SD_SendCmd(SD_CMD_WRITE_SINGLE_BLOCK, WriteAddr, 0xFF);
		status = SD_GetResponse(SD_RESPONSE_NO_ERROR);
	}
//ouhs<<<<<<<<<<<<<<<<<<<<<<  
	
  /*!< Check if the SD acknowledged the write block command: R1 response (0x00: no errors) */
  //if (!SD_GetResponse(SD_RESPONSE_NO_ERROR))
	if (status == SD_RESPONSE_NO_ERROR)
  {
    /*!< Send a dummy byte */
    SD_WriteByte(SD_DUMMY_BYTE);

    /*!< Send the data token to signify the start of the data */
    SD_WriteByte(0xFE);
#if (SPI_DMA==0)
    /*!< Write the block data to SD : write count data by block */
    for (i = 0; i < BlockSize; i++)
    {
      /*!< Send the pointed byte */
      SD_WriteByte(*pBuffer);
      /*!< Point to the next location where the byte read will be saved */
      pBuffer++;
    }
#else
		DMA1_Start_SPI_TX(pBuffer);
		
#endif
		
    /*!< Put CRC bytes (not really needed by us, but required by SD) */
    SD_ReadByte();
    SD_ReadByte();

    /*!< Read data response */
    if (SD_GetDataResponse() == SD_DATA_OK)
    {
      rvalue = SD_RESPONSE_NO_ERROR;
    }
  }
  /*!< SD chip select high */
  SD_CS_HIGH_2ND();
  /*!< Send dummy byte: 8 Clock pulses of delay */
  SD_WriteByte(SD_DUMMY_BYTE);

  /*!< Returns the reponse */
  return rvalue;
}

/**
  * @brief  Writes many blocks on the SD
  * @param  pBuffer: pointer to the buffer containing the data to be written on 
  *                  the SD.
  * @param  WriteAddr: address to write on.
  * @param  BlockSize: the SD card Data block size.
  * @param  NumberOfBlocks: number of blocks to be written.
  * @retval The SD Response: 
  *         - SD_RESPONSE_FAILURE: Sequence failed
  *         - SD_RESPONSE_NO_ERROR: Sequence succeed
  */
SD_Error SD_WriteMultiBlocks_2nd(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t BlockSize, uint32_t NumberOfBlocks)
{
  uint32_t i = 0, Offset = 0;
  SD_Error rvalue = SD_RESPONSE_FAILURE;

  /*!< SD chip select low */
  SD_CS_LOW_2ND();
  /*!< Data transfer */
  while (NumberOfBlocks--)
  {
    if(flag_SDHC == 1)
    {
        /* Send CMD24 (MSD_WRITE_BLOCK) to write blocks */
        SD_SendCmd(SD_CMD_WRITE_SINGLE_BLOCK, (WriteAddr + Offset)/512, 0xFF);
    }
    else
    {
        /*!< Send CMD24 (SD_CMD_WRITE_SINGLE_BLOCK) to write blocks */
        SD_SendCmd(SD_CMD_WRITE_SINGLE_BLOCK, WriteAddr + Offset, 0xFF);
    }
    /*!< Check if the SD acknowledged the write block command: R1 response (0x00: no errors) */
    if (SD_GetResponse(SD_RESPONSE_NO_ERROR))
    {
      return SD_RESPONSE_FAILURE;
    }
    /*!< Send dummy byte */
    SD_WriteByte(SD_DUMMY_BYTE);
    /*!< Send the data token to signify the start of the data */
    SD_WriteByte(SD_START_DATA_SINGLE_BLOCK_WRITE);
    /*!< Write the block data to SD : write count data by block */
#if (SPI_DMA==0)		
    for (i = 0; i < BlockSize; i++)
    {
      /*!< Send the pointed byte */
      SD_WriteByte(*pBuffer);
      /*!< Point to the next location where the byte read will be saved */
      pBuffer++;
    }
#else
		DMA1_Start_SPI_TX(pBuffer);
		pBuffer += 512;
#endif		
    /*!< Set next write address */
    Offset += 512;
    /*!< Put CRC bytes (not really needed by us, but required by SD) */
    SD_ReadByte();
    SD_ReadByte();
    /*!< Read data response */
    if (SD_GetDataResponse() == SD_DATA_OK)
    {
      /*!< Set response value to success */
      rvalue = SD_RESPONSE_NO_ERROR;
    }
    else
    {
      /*!< Set response value to failure */
      rvalue = SD_RESPONSE_FAILURE;
    }
  }
  /*!< SD chip select high */
  SD_CS_HIGH_2ND();
  /*!< Send dummy byte: 8 Clock pulses of delay */
  SD_WriteByte(SD_DUMMY_BYTE);
  /*!< Returns the reponse */
  return rvalue;
}

/**
  * @brief  Read the CSD card register.
  *         Reading the contents of the CSD register in SPI mode is a simple 
  *         read-block transaction.
  * @param  SD_csd: pointer on an SCD register structure
  * @retval The SD Response: 
  *         - SD_RESPONSE_FAILURE: Sequence failed
  *         - SD_RESPONSE_NO_ERROR: Sequence succeed
  */
SD_Error SD_GetCSDRegister_2nd(SD_CSD* SD_csd)
{
  uint32_t i = 0;
  SD_Error rvalue = SD_RESPONSE_FAILURE;
  uint8_t CSD_Tab[16];
//ouhs	uint32_t CardCapacity;
//ouhs  static uint32_t times = 0;

  /*!< SD chip select low */
  SD_CS_LOW_2ND();
  /*!< Send CMD9 (CSD register) or CMD10(CSD register) */
  SD_SendCmd(SD_CMD_SEND_CSD, 0, 0xFF);
  /*!< Wait for response in the R1 format (0x00 is no errors) */
  if (!SD_GetResponse(SD_RESPONSE_NO_ERROR))
  {
    if (!SD_GetResponse(SD_START_DATA_SINGLE_BLOCK_READ))
    {
      for (i = 0; i < 16; i++)
      {
        /*!< Store CSD register value on CSD_Tab */
        CSD_Tab[i] = SD_ReadByte();
/* ouhs       if(0 == times)
        {
          USART_printf("\n\r CSD_Tab[%d] 0x%X", i, CSD_Tab[i]);
        }
*/
      }
    }
    /*!< Get CRC bytes (not really needed by us, but required by SD) */
    SD_WriteByte(SD_DUMMY_BYTE);
    SD_WriteByte(SD_DUMMY_BYTE);
    /*!< Set response value to success */
    rvalue = SD_RESPONSE_NO_ERROR;
  }
  else
  {
     return rvalue;
  }
  /*!< SD chip select high */
  SD_CS_HIGH_2ND();
  /*!< Send dummy byte: 8 Clock pulses of delay */
  SD_WriteByte(SD_DUMMY_BYTE);

  /*!< Byte 0 */
  SD_csd->CSDStruct = (CSD_Tab[0] & 0xC0) >> 6;
  SD_csd->SysSpecVersion = (CSD_Tab[0] & 0x3C) >> 2;
  SD_csd->Reserved1 = CSD_Tab[0] & 0x03;

//ouhs  if(0 == times)
  {
    if(SD_csd->CSDStruct == 1)
    {
      //USART_printf("\n\r SDHC CSD Version 2.0 Acess AS SD High Capacity.");
      flag_SDHC = 1;
    }
	else
	{
      //USART_printf("\n\r SDSC CSD Version 1.0 Acess AS SD Standard Capacity.");	
      flag_SDHC = 0;
	}
  }

  /*!< Byte 1 */
  SD_csd->TAAC = CSD_Tab[1];

  /*!< Byte 2 */
  SD_csd->NSAC = CSD_Tab[2];

  /*!< Byte 3 */
  SD_csd->MaxBusClkFrec = CSD_Tab[3];

  /*!< Byte 4 */
  SD_csd->CardComdClasses = CSD_Tab[4] << 4;

  /*!< Byte 5 */
  SD_csd->CardComdClasses |= (CSD_Tab[5] & 0xF0) >> 4;
  SD_csd->RdBlockLen = CSD_Tab[5] & 0x0F;

  /*!< Byte 6 */
  SD_csd->PartBlockRead = (CSD_Tab[6] & 0x80) >> 7;
  SD_csd->WrBlockMisalign = (CSD_Tab[6] & 0x40) >> 6;
  SD_csd->RdBlockMisalign = (CSD_Tab[6] & 0x20) >> 5;
  SD_csd->DSRImpl = (CSD_Tab[6] & 0x10) >> 4;
  SD_csd->Reserved2 = 0; /*!< Reserved */

  if(flag_SDHC == 0)
  {
    SD_csd->DeviceSize = (CSD_Tab[6] & 0x03) << 10;
  
    /*!< Byte 7 */
    SD_csd->DeviceSize |= (CSD_Tab[7]) << 2;
  
    /*!< Byte 8 */
    SD_csd->DeviceSize |= (CSD_Tab[8] & 0xC0) >> 6;
  }
  else
  {
    SD_csd->DeviceSize = (CSD_Tab[7] & 0x3F) << 16;
    /* Byte 7 */
    SD_csd->DeviceSize += (CSD_Tab[8]) << 8;
    /* Byte 8 */
    SD_csd->DeviceSize += CSD_Tab[9] ;
  }    

  SD_csd->MaxRdCurrentVDDMin = (CSD_Tab[8] & 0x38) >> 3;
  SD_csd->MaxRdCurrentVDDMax = (CSD_Tab[8] & 0x07);

  /*!< Byte 9 */
  SD_csd->MaxWrCurrentVDDMin = (CSD_Tab[9] & 0xE0) >> 5;
  SD_csd->MaxWrCurrentVDDMax = (CSD_Tab[9] & 0x1C) >> 2;
  SD_csd->DeviceSizeMul = (CSD_Tab[9] & 0x03) << 1;
  /*!< Byte 10 */
  SD_csd->DeviceSizeMul |= (CSD_Tab[10] & 0x80) >> 7;
    
  SD_csd->EraseGrSize = (CSD_Tab[10] & 0x40) >> 6;
  SD_csd->EraseGrMul = (CSD_Tab[10] & 0x3F) << 1;

  /*!< Byte 11 */
  SD_csd->EraseGrMul |= (CSD_Tab[11] & 0x80) >> 7;
  SD_csd->WrProtectGrSize = (CSD_Tab[11] & 0x7F);

  /*!< Byte 12 */
  SD_csd->WrProtectGrEnable = (CSD_Tab[12] & 0x80) >> 7;
  SD_csd->ManDeflECC = (CSD_Tab[12] & 0x60) >> 5;
  SD_csd->WrSpeedFact = (CSD_Tab[12] & 0x1C) >> 2;
  SD_csd->MaxWrBlockLen = (CSD_Tab[12] & 0x03) << 2;

  /*!< Byte 13 */
  SD_csd->MaxWrBlockLen |= (CSD_Tab[13] & 0xC0) >> 6;
  SD_csd->WriteBlockPaPartial = (CSD_Tab[13] & 0x20) >> 5;
  SD_csd->Reserved3 = 0;
  SD_csd->ContentProtectAppli = (CSD_Tab[13] & 0x01);

  /*!< Byte 14 */
  SD_csd->FileFormatGrouop = (CSD_Tab[14] & 0x80) >> 7;
  SD_csd->CopyFlag = (CSD_Tab[14] & 0x40) >> 6;
  SD_csd->PermWrProtect = (CSD_Tab[14] & 0x20) >> 5;
  SD_csd->TempWrProtect = (CSD_Tab[14] & 0x10) >> 4;
  SD_csd->FileFormat = (CSD_Tab[14] & 0x0C) >> 2;
  SD_csd->ECC = (CSD_Tab[14] & 0x03);

  /*!< Byte 15 */
  SD_csd->CSD_CRC = (CSD_Tab[15] & 0xFE) >> 1;
  SD_csd->Reserved4 = 1;

//ouhs  if(times < 3)
  {
    if(flag_SDHC ==1)
    {
	  /* SDHC memory capacity = (C_SIZE+1) * 512K byte */
      SD_csd->DeviceSizeMul = 8 ;
    }
/*ouhs
    CardCapacity = (SD_csd->DeviceSize + 1);
    CardCapacity *= (1 << (SD_csd->DeviceSizeMul + 2));
    CardCapacity *= (1<<SD_csd->RdBlockLen);
    USART_printf("\n\r SD CardBlockSize %d CardCapacity %d M.", (1<<SD_csd->RdBlockLen), CardCapacity / 1024 / 1024);

	if(times == 0)
  {
		uint8_t str[20];
		sprintf((char *)&str[0], " SD Card Size %dM. ", CardCapacity / 1024 / 1024);
		//LCD_DisplayStringLine(LCD_LINE_0, str);
	}
	times++;
*/
  }
  /*!< Return the reponse */
  return rvalue;
}

/**
  * @brief  Read the CID card register.
  *         Reading the contents of the CID register in SPI mode is a simple 
  *         read-block transaction.
  * @param  SD_cid: pointer on an CID register structure
  * @retval The SD Response: 
  *         - SD_RESPONSE_FAILURE: Sequence failed
  *         - SD_RESPONSE_NO_ERROR: Sequence succeed
  */
SD_Error SD_GetCIDRegister_2nd(SD_CID* SD_cid)
{
  uint32_t i = 0;
  SD_Error rvalue = SD_RESPONSE_FAILURE;
  uint8_t CID_Tab[16];
  
  /*!< SD chip select low */
  SD_CS_LOW_2ND();
  
  /*!< Send CMD10 (CID register) */
  SD_SendCmd(SD_CMD_SEND_CID, 0, 0xFF);
  
  /*!< Wait for response in the R1 format (0x00 is no errors) */
  if (!SD_GetResponse(SD_RESPONSE_NO_ERROR))
  {
    if (!SD_GetResponse(SD_START_DATA_SINGLE_BLOCK_READ))
    {
      /*!< Store CID register value on CID_Tab */
      for (i = 0; i < 16; i++)
      {
        CID_Tab[i] = SD_ReadByte();
      }
    }
    /*!< Get CRC bytes (not really needed by us, but required by SD) */
    SD_WriteByte(SD_DUMMY_BYTE);
    SD_WriteByte(SD_DUMMY_BYTE);
    /*!< Set response value to success */
    rvalue = SD_RESPONSE_NO_ERROR;
  }
  /*!< SD chip select high */
  SD_CS_HIGH_2ND();
  /*!< Send dummy byte: 8 Clock pulses of delay */
  SD_WriteByte(SD_DUMMY_BYTE);

  /*!< Byte 0 */
  SD_cid->ManufacturerID = CID_Tab[0];

  /*!< Byte 1 */
  SD_cid->OEM_AppliID = CID_Tab[1] << 8;

  /*!< Byte 2 */
  SD_cid->OEM_AppliID |= CID_Tab[2];

  /*!< Byte 3 */
  SD_cid->ProdName1 = CID_Tab[3] << 24;

  /*!< Byte 4 */
  SD_cid->ProdName1 |= CID_Tab[4] << 16;

  /*!< Byte 5 */
  SD_cid->ProdName1 |= CID_Tab[5] << 8;

  /*!< Byte 6 */
  SD_cid->ProdName1 |= CID_Tab[6];

  /*!< Byte 7 */
  SD_cid->ProdName2 = CID_Tab[7];

  /*!< Byte 8 */
  SD_cid->ProdRev = CID_Tab[8];

  /*!< Byte 9 */
  SD_cid->ProdSN = CID_Tab[9] << 24;

  /*!< Byte 10 */
  SD_cid->ProdSN |= CID_Tab[10] << 16;

  /*!< Byte 11 */
  SD_cid->ProdSN |= CID_Tab[11] << 8;

  /*!< Byte 12 */
  SD_cid->ProdSN |= CID_Tab[12];

  /*!< Byte 13 */
  SD_cid->Reserved1 |= (CID_Tab[13] & 0xF0) >> 4;
  SD_cid->ManufactDate = (CID_Tab[13] & 0x0F) << 8;

  /*!< Byte 14 */
  SD_cid->ManufactDate |= CID_Tab[14];

  /*!< Byte 15 */
  SD_cid->CID_CRC = (CID_Tab[15] & 0xFE) >> 1;
  SD_cid->Reserved2 = 1;

  /*!< Return the reponse */
  return rvalue;
}


/**
  * @brief  Returns the SD status.
  * @param  None
  * @retval The SD status.
  */
uint16_t SD_GetStatus_2nd(void)
{
  uint16_t Status = 0;

  /*!< SD chip select low */
  SD_CS_LOW_2ND();

  /*!< Send CMD13 (SD_SEND_STATUS) to get SD status */
  SD_SendCmd(SD_CMD_SEND_STATUS, 0, 0xFF);

  Status = SD_ReadByte();
  Status |= (uint16_t)(SD_ReadByte() << 8);

  /*!< SD chip select high */
  SD_CS_HIGH_2ND();

  /*!< Send dummy byte 0xFF */
  SD_WriteByte(SD_DUMMY_BYTE);

  return Status;
}

/**
  * @brief  Put SD in Idle state.
  * @param  None
  * @retval The SD Response: 
  *         - SD_RESPONSE_FAILURE: Sequence failed
  *         - SD_RESPONSE_NO_ERROR: Sequence succeed
  */
SD_Error SD_GoIdleState_2nd(void)
{
  uint16_t TimeOut;
  uint8_t r1;
  SD_Error Status = SD_RESPONSE_NO_ERROR;
  uint16_t n2,n;
  /*!< SD chip select low */
  SD_CS_LOW_2ND();
  
  /*!< Send CMD0 (SD_CMD_GO_IDLE_STATE) to put SD in SPI mode */
  SD_SendCmd(SD_CMD_GO_IDLE_STATE, 0, 0x95);
  
  /*!< Wait for In Idle State Response (R1 Format) equal to 0x01 */
  if (SD_GetResponse(SD_IN_IDLE_STATE))
  {
    /*!< No Idle State Response: return response failue */
		//USART_printf("\n\r SD_RESPONSE_FAILURE: Send CMD0 (SD_CMD_GO_IDLE_STATE) to put SD in SPI mode");
		//USART_printf("\n\r No SD card detect.");
    return SD_RESPONSE_FAILURE;
  }

  
  SD_SendCmd(8, 0x1AA, 0x87); /*check version*/
  /*!< Check if response is got or a timeout is happen */
  TimeOut = 200;
  while (((r1 = SD_ReadByte()) == 0xFF) && TimeOut)
  {
    TimeOut--;
  }

  if(r1 == 0x05) // not SDHC
  {
    //flag_SDHC = 0;
    //USART_printf("\r\n  this is STD_CAPACITY_SD_CARD!\n");
    
    TimeOut = 0;
    /*----------Activates the card initialization process-----------*/
    do
    {
      /*!< SD chip select high */
      SD_CS_HIGH_2ND();
      
      /*!< Send Dummy byte 0xFF */
      SD_WriteByte(SD_DUMMY_BYTE);
      
      /*!< SD chip select low */
      SD_CS_LOW_2ND();
      
      /*!< Send CMD1 (Activates the card process) until response equal to 0x0 */
      SD_SendCmd(SD_CMD_SEND_OP_COND, 0, 0xFF);
      /*!< Wait for no error Response (R1 Format) equal to 0x00 */
      TimeOut++;
    
      if(TimeOut == 0x00F0)
      {
        break;
      }
  	
  	Status = SD_GetResponse(SD_RESPONSE_NO_ERROR);	
    }
    while (Status);
    
    /*!< SD chip select high */
    SD_CS_HIGH_2ND();
    
    /*!< Send dummy byte 0xFF */
    SD_WriteByte(SD_DUMMY_BYTE);    
  }
  else
  {
    //if(r1 != 1)
    //{
    //    USART_printf("\n\r SD card r1 is %X.\n\r", r1);
    //}
    //USART_printf("\r\n this is SDHC: HIGH_CAPACITY_SD_CARD!\n");
    r1 = 1;
    /* Send Dummy byte 0xFF */
    for(n=0; n<5; n++)
    {
      SD_ReadByte();
    }
  
    /* MSD chip select high */
    SD_CS_HIGH_2ND();
    SD_WriteByte(SD_DUMMY_BYTE);
    /* MSD chip select low */
    SD_CS_LOW_2ND();
    SD_WriteByte(SD_DUMMY_BYTE);
    SD_WriteByte(SD_DUMMY_BYTE);
    n=0xff;
  
    do
    {
      SD_SendCmd(55, 0, 0xFF);
      for(n2=0; n2<0x08;n2++)
      {
       r1= SD_ReadByte();
       if(r1 !=1)n=0;
      }
      SD_SendCmd(41, 0x40000000, 0);
  
      for(n2=0; n2<0xff;n2++)
      {
       r1= SD_ReadByte();
       if(r1 ==0)break;
      }
      n--;
    }while((r1!=0)&&(n>0));
    if(n==0)
    {
      Status =  SD_RESPONSE_FAILURE;
      //USART_printf("\r\n Activates the SDHC card falled!\n");
    }
    else
    {
#if 0	//ouhs20171103	会导致有些SD卡对CMD命令无响应 如ADATA的4G卡
      SD_SendCmd(58, 0, 0);
      for(n=0;n<5;n++)
      {
				r1 = SD_ReadByte();
				//USART_printf("\n\r 58 SD card r1 is %X.\n\r", r1);
      }
#endif			
			flag_SDHC = 1;
      //USART_printf("\r\n Activates the SDHC card sucessed!\n");
      Status =  SD_RESPONSE_NO_ERROR;
     }
  }
  
  
  /*
  if((Status != SD_RESPONSE_NO_ERROR))
  {
    //flag_SDHC = 1;
    USART_printf("\n\r Maybe this is a SDHC(SD High Capacity cards).");
    //break;
  }
  else
  {
    USART_printf("\n\r SD cards inint Done.");
  }  
  */
    
  return Status;//SD_RESPONSE_NO_ERROR;
}



/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
