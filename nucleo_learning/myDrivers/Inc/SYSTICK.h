#ifndef INC_SYSTICK_H_
#define INC_SYSTICK_H_

#include "stm32G031K8.h"

#define HSE_VALUE    			(8000000U)
#define LSI_VALUE  				(32000U)
#define LSE_VALUE    			(32768U)
#define HSI_VALUE    			(16000000U)


//void Delay(uint32_t delayValue);

void IncTick();

uint32_t GetTick();

void TickReset();

uint32_t SystemCoreClockUpdate();

void NVIC_SetPriority(IRQNumber_TypeDef_t IRQn, uint32_t priority);

void SystemClock_Config();

uint32_t SysTickConfig(uint32_t ticks);

uint32_t SysTickConfig(uint32_t ticks);

void SetTickLimit(uint32_t ticks);

uint32_t GetTickLimit();

void Delay(uint32_t ticks);

#endif /* INC_SYSTICK_H_ */
