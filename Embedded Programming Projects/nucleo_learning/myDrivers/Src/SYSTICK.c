#include "SYSTICK.h"

Systick_TickFreqTypeDef uwTickFreq = TICK_FREQ_DEFAULT;
__IO uint32_t uwTick;
__IO uint32_t TickLimit;

const uint32_t AHBPrescTable[16UL] = {0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 1UL, 2UL, 3UL, 4UL, 6UL, 7UL, 8UL, 9UL};
const uint32_t APBPrescTable[8UL] =  {0UL, 0UL, 0UL, 0UL, 1UL, 2UL, 3UL, 4UL};

uint32_t SystemCoreClockUpdate()
{
	uint32_t tempValue;
	uint32_t pllVCO;
	uint32_t pllR;
	uint32_t pllSource;
	uint32_t pllM;
	uint32_t hsidiv;

	uint32_t sysClock = SYSTEM_CORE_CLK;

	switch( RCC->CFGR & RCC_CFGR_SW2 )
	{
	case RCC_CFGR_SW2_BIT0:
		sysClock = HSE_VALUE;
		break;

	case (RCC_CFGR_SW2_BIT1 | RCC_CFGR_SW2_BIT0):
		sysClock = LSI_VALUE;
		break;

	case RCC_CFGR_SW2_BIT2:
		sysClock = LSE_VALUE;
		break;

	case RCC_CFGR_SW2_BIT1:

		pllSource = (RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC);
		pllM = ( (RCC->PLLCFGR & RCC_PLLCFGR_PLLM) >> RCC_PLLCFGR_PLLM_POS ) + 1U;

		if( pllSource == 0x03U)
		{
			pllVCO = (HSE_VALUE / pllM);
		}
		else
		{
			pllVCO = (HSI_VALUE / pllM);
		}

		pllVCO = pllVCO * ( (RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_POS );
		pllR = ( ( (RCC->PLLCFGR & RCC_PLLCFGR_PLLR) >> RCC_PLLCFGR_PLLR_POS ) + 1U );

		sysClock = ( pllVCO / pllR );
		break;

	case 0x0U:
	default:
		hsidiv = ( 1U << ( (READ_BIT(RCC->CR, RCC_CR_HSIDIV)) >> RCC_CR_HSIDIV_POS) );
		sysClock = (HSI_VALUE / hsidiv);
		break;
	}

	tempValue = AHBPrescTable[( (RCC->CFGR & RCC_CFGR_HPRE) >> RCC_CFGR_HPRE_Pos)];

	sysClock >>= tempValue;

	return sysClock;
}

void NVIC_SetPriority(IRQNumber_TypeDef_t IRQn, uint32_t priority)
{
	if( ( (int32_t)(IRQn) ) >= 0)
	{
		NVIC->IP[IP_IDX(IRQn)] = ( (uint32_t)(NVIC->IP[IP_IDX(IRQn)] & ~(0xFFU >> BIT_SHIFT(IRQn))) |
		    ( ( (priority << (8U - NVIC_PRIO_BITS)) & (uint32_t)0xFFU) << BIT_SHIFT(IRQn)));
	}
	else
	{
		SCB->SHPR[SHP_IDX(IRQn)] = ((uint32_t)(SCB->SHPR[SHP_IDX(IRQn)] & ~(0xFFUL << BIT_SHIFT(IRQn))) |
			       (((priority << (8U - NVIC_PRIO_BITS)) & (uint32_t)0xFFUL) << BIT_SHIFT(IRQn)));

	}

}

void IncTick()
{
	uwTick += (uint32_t)uwTickFreq;
}

uint32_t GetTick()
{
	return uwTick;
}

void TickReset()
{
	uwTick = 0;
}

uint32_t SysTickConfig(uint32_t ticks)
{
	if( (ticks - 1U) > SYSTICK_RVR_RELOAD)
	{
		return (1U);
	}

	SYSTICK->RVR = (uint32_t)(ticks - 1U);
	//NVIC_SetPriority(IRQ_SysTick, (1U << NVIC_PRIO_BITS) -1U);
	SYSTICK->CVR = 0U;
	SYSTICK->CSR = SYSTICK_CSR_CLKSOURCE |
				   SYSTICK_CSR_TICKINT	 |
				   SYSTICK_CSR_ENABLE;

	return (0U);
}

uint32_t GetTickLimit()
{
	return TickLimit;
}

void Delay(uint32_t ticks)
{
	if(ticks < 100) {ticks = 100;}

	TickLimit = ticks;

}

