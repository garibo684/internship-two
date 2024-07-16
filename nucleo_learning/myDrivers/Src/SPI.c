#include "SPI.h"


static void SPI_CloseIsr_TX(SPI_HandleTypeDef_t *SPI_Handle)
{
	SPI_Handle->Instance->CR2 &= ~(0x1U << SPI_CR2_TXEIE);
	SPI_Handle->TxDataSize = 0;
	SPI_Handle->pTxDataAddr = NULL;
	SPI_Handle->BusStateTx = SPI_BUS_FREE;

}

static void SPI_TransmitHelper_16Bits(SPI_HandleTypeDef_t *SPI_Handle)
{
	SPI_Handle->Instance->DR = *( (uint16_t *)(SPI_Handle->pTxDataAddr) );
	SPI_Handle->pTxDataAddr += sizeof(uint16_t);
	SPI_Handle->TxDataSize -= 2;

}

static void SPI_TransmitHelper_8Bits(SPI_HandleTypeDef_t *SPI_Handle)
{
	SPI_Handle->Instance->DR = *( (uint8_t *)(SPI_Handle->pTxDataAddr) );
	SPI_Handle->pTxDataAddr += sizeof(uint8_t);
	SPI_Handle->TxDataSize --;

	if( SPI_Handle->TxDataSize == 0)
	{
		SPI_CloseISR_TX(SPI_Handle);
	}

}


/*
 * @brief SPI_Init, Configures the PI peripheral
 *
 * @param SPI_Handle = User config structure
 *
 * @retval void
 *
 */

void SPI_Init(SPI_HandleTypeDef_t * SPI_Handle)
{
	uint32_t tempValue = 0;

	tempValue = SPI_Handle->Instance->CR1;

	tempValue |= ( SPI_Handle->Init.BaudRate | SPI_Handle->Init.CPHA | SPI_Handle->Init.CPOL |	SPI_Handle->Init.Mode | \
				   SPI_Handle->Init.FrameFormat | SPI_Handle->Init.BusConfig | SPI_Handle->Init.SSM_CMD );

	SPI_Handle->Instance->CR1 = tempValue;

}


/*
 * @brief SPI_PeripCmd, Enable or Disable SPI peripheral
 *
 *
 * @param SPI_Handle = User config structure
 *
 * @param stateOfSPI = ENABLE or DISABLE
 *
 *
 * @retval void
 *
 */

void SPI_PeripCmd(SPI_HandleTypeDef_t *SPI_Handle, FunctionalState_t stateOfSPI)
{
	if( stateOfSPI == ENABLE )
	{
		SPI_Handle->Instance->CR1 |= ( 0x1U << SPI_CR1_SPE);
	}
	else
	{
		SPI_Handle->Instance->CR1 &= ~( 0x1U << SPI_CR1_SPE);
	}

}


/*
 * @brief SPI_TransmitData, Transmits data to the slave
 *
 *
 * @param SPI_Handle = User config structure
 *
 * @param pData = Address of data to send
 *
 * @param sizeOfData = Length of the data in bytes
 *
 *
 * @retval void
 *
 */

void SPI_TransmitData(SPI_HandleTypeDef_t *SPI_Handle, uint8_t *pData, uint16_t sizeOfData)
{
	if(SPI_Handle->Init.CRCL == SPI_CRCL_16BIT)
	{
		while( sizeOfData > 0)
		{
			if( SPI_GetFlagStatus(SPI_Handle, SPI_TXE_FLAG ) )
			{
				SPI_Handle->Instance->DR = *( (uint16_t *)pData );
				pData += sizeof(uint16_t);
				sizeOfData -= 2;
			}
		}
	}
	else
	{
		while( sizeOfData > 0)
		{
			if( (SPI_Handle->Instance->SR >> 1U) &  0x1U)
			{
				SPI_Handle->Instance->DR = *pData;
				pData += sizeof(uint8_t);
				sizeOfData--;
			}
		}
	}

	while( (SPI_Handle->Instance->SR >> 7U) & 0x1U ); // Wait for Busy Flag

}


void SPI_RecieveData(SPI_HandleTypeDef_t *SPI_Handle, uint8_t *pBuffer, uint16_t sizeOfData)
{
	if( SPI_Handle->Init.CRCL == SPI_CRCL_16BIT )
	{
		while( sizeOfData > 0 )
		{
			if( SPI_GetFlagStatus(SPI_Handle, SPI_RXNE_FLAG) )
			{
				*( (uint16_t *)pBuffer ) = (uint16_t)SPI_Handle->Instance->DR;
				pBuffer += sizeof(uint16_t);
				sizeOfData -= 2;
			}
		}
	}
	else
	{
		while( sizeOfData > 0 )
		{
			if( SPI_GetFlagStatus(SPI_Handle, SPI_RXNE_FLAG) )
			{
				*pBuffer =*( (__IO uint8_t *)&SPI_Handle->Instance->DR );
				pBuffer += sizeof(uint8_t);
				sizeOfData --;
			}
		}
	}

}

void SPI_TransmitData_IT(SPI_HandleTypeDef_t *SPI_Handle, uint8_t *pData, uint16_t sizeOfData)
{

	SPI_BusStatus_t busState = SPI_Handle->BusStateTx;

	if( busState != SPI_BUS_BUSY_TX)
	{
		SPI_Handle->pTxDataAddr = pData;
		SPI_Handle->TxDataSize = sizeOfData;
		SPI_Handle->BusStateTx = SPI_BUS_BUSY_TX;

		if( SPI_Handle->Instance->CR1 & (0x1U << SPI_CR1_CRCL) )
		{
			SPI_Handle->TxISRFunction = SPI_TransmitHelper_16Bits;
		}
		else
		{
			SPI_Handle->TxISRFunction = SPI_TransmitHelper_8Bits;
		}

		SPI_Handle->Instance->CR2 |= (0x1U << SPI_CR2_TXEIE);
	}
}

void SPI_InterruptHandler(SPI_HandleTypeDef_t *SPI_Handle)
{
	uint8_t interuptSource = 0;
	uint8_t interruptFlag = 0;

	interuptSource = SPI_Handle->Instance->CR2 & (0x1U << SPI_CR2_TXEIE);
	interruptFlag = SPI_Handle->Instance->SR & (0x1U << SPI_SR_TXE);

	if( (interuptSource != 0) && (interruptFlag != 0) )
	{
		SPI_Handle->TxISRFunction(SPI_Handle);
	}

}

/*
 * @brief SPI_GetFlagStatus, Returns flag of SR register
 *
 * @param SPI_Handle = User config structure
 *
 * @param SPI_Flag = Flag name of SR register
 *
 *
 * @retval SPI_FlagStatus_t
 *
 */

SPI_FlagStatus_t SPI_GetFlagStatus(SPI_HandleTypeDef_t * SPI_Handle, uint16_t SPI_Flag)
{
	return (SPI_Handle->Instance->SR & SPI_Flag) ? SPI_FLAG_SET : SPI_FLAG_RESET;
}
