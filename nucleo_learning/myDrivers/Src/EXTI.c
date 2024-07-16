#include "EXTI.h"


/*
 * @brief EXTI_LineConfig, Configures the port and pin for EXTI
 *
 *
 * @param PortSource = Port Value A-F @def_group PORT_Values
 *
 * @param EXTI_LineSource = Pin Nubers & Line Numbers @def_group EXTI_Line_Values
 *
 *
 * @retval void
 *
 */

void EXTI_LineConfig_t( uint8_t PortSource, uint8_t EXTI_LineSource)
{
	uint32_t tempValue;

	tempValue = EXTI->EXTICR[EXTI_LineSource >> 2U];
	tempValue &= ~(0x1FU << ( (EXTI_LineSource & 0x3U) * 8) );
	tempValue = (PortSource << ( (EXTI_LineSource & 0x3U) * 8) );
	EXTI->EXTICR[EXTI_LineSource >> 2U] = tempValue;

}


/*
 * @brief EXTI_Init for valid GPIO port and Line number
 *
 * @param EXTI_InitStruct = User Config structure
 *
 * @retval void
 *
 */

void EXTI_Init(EXTI_InitTypeDef_t *EXTI_InitStruct)
{
	uint32_t tempValue = 0;

	tempValue = (uint32_t)EXTI_BASE_ADDR;

	EXTI->IMR1 &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber);
	EXTI->EMR1 &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber);

	if( EXTI_InitStruct->EXTI_LineCmd != DISABLE )
	{
		tempValue += EXTI_InitStruct->EXTI_Mode;

		*( (__IO uint32_t *)tempValue ) |= ( 0x1U << EXTI_InitStruct->EXTI_LineNumber );

		tempValue = (uint32_t)EXTI_BASE_ADDR;

		EXTI->RTSR1 &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber);
		EXTI->FTSR1 &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber);

		if ( EXTI_InitStruct->TriggerSelection == EXTI_TRIGGER_RF1 )
		{
			EXTI->RTSR1 |= (0x1U << EXTI_InitStruct->EXTI_LineNumber);
			EXTI->FTSR1 |= (0x1U << EXTI_InitStruct->EXTI_LineNumber);
		}
		else
		{
			tempValue += EXTI_InitStruct->TriggerSelection;
			* ( (__IO uint32_t *)tempValue ) |= ( 0x1U << EXTI_InitStruct->EXTI_LineNumber );

		}
	}
	else
	{
		tempValue = ( uint32_t )EXTI_BASE_ADDR;

		tempValue += EXTI_InitStruct->EXTI_Mode;

		*( (__IO uint32_t *)tempValue ) &= ( 0x1U << EXTI_InitStruct->EXTI_LineNumber );
	}
}


/*
 * @brief NVIC_EnableInterrupt
 *
 * @param IRQNumber = IRQ Number of Line
 *
 * @retval void
 *
 */

void NVIC_EnableInterrupt(IRQNumber_TypeDef_t IRQNumber)
{
	uint32_t tempValue = 0;

	tempValue = *NVIC_ISER;
	tempValue &= ~(0x1 << (IRQNumber & 0x1FU) );
	tempValue |= (0x1 << (IRQNumber & 0x1FU) );
	 *NVIC_ISER = tempValue;

}

