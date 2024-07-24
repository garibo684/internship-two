#ifndef INC_RCC_H_
#define INC_RCC_H_

#include "stm32G031K8.h"


#define RCC_GPIOA_CLK_ENABLE()			do{ uint32_t tempValue = 0;									\
											SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOAEN); 				\
											tempValue = READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOAEN); 	\
											UNUSED(tempValue); 										\
										  }while(0)

#define RCC_GPIOB_CLK_ENABLE()			do{	uint32_t tempValue = 0;									\
											SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOBEN);				\
											tempValue = READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOBEN);	\
											UNUSED(tempValue);										\
											}while(0)

#define RCC_GPIOC_CLK_ENABLE()			do{	uint32_t tempValue = 0;									\
											SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOCEN);				\
											tempValue = READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOCEN);	\
											UNUSED(tempValue);										\
										  }while(0)

#define RCC_GPIOD_CLK_ENABLE()			do{ uint32_t tempValue = 0;									\
											SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIODEN);				\
											tempValue = READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIODEN);	\
											UNUSED(tempValue);										\
										  }while(0)

#define RCC_GPIOE_CLK_ENABLE()			do{ uint32_t tempValue = 0;									\
											SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOEEN);				\
											tempValue = READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOEEN);	\
											UNUSED(tempValue);										\
										  }while(0)

#define RCC_GPIOF_CLK_ENABLE()			do{ uint32_t tempValue = 0;									\
											SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOFEN);				\
											tempValue = READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOFEN);	\
											UNUSED(tempValue);										\
										  }while(0)

#define RCC_SYSCFG_CLK_ENABLE()			do{ uint32_t tempValue = 0;										\
											SET_BIT(RCC->APBENR2, RCC_APBENR2_SYSCFGEN);				\
											tempValue = READ_BIT(RCC->APBENR2, RCC_APBENR2_SYSCFGEN);	\
											UNUSED(tempValue);											\
										}while(0)

#define RCC_SPI1_CLK_ENABLE()			do{	uint32_t tempValue;										\
											SET_BIT(RCC->APBENR2, RCC_APBENR2_SPI1EN);				\
											tempValue = READ_BIT(RCC->APBENR2, RCC_APBENR2_SPI1EN);	\
											UNUSED(tempValue);										\
										}while(0)

#define RCC_SPI2_CLK_ENABLE()			do{	uint32_t tempValue;										\
											SET_BIT(RCC->APBENR1, RCC_APBENR1_SPI2EN);				\
											tempValue = READ_BIT(RCC->APBENR1, RCC_APBENR1_SPI2EN);	\
											UNUSED(tempValue);										\
										}while(0)

#define RCC_SPI3_CLK_ENABLE()			do{	uint32_t tempValue;										\
											SET_BIT(RCC->APBENR1, RCC_APBENR1_SPI3EN);				\
											tempValue = READ_BIT(RCC->APBENR1, RCC_APBENR1_SPI3EN);	\
											UNUSED(tempValue);										\
										}while(0)


#define RCC_GPIOA_CLK_DISABLE()			CLEAR_BIT(RCC->IOPENR, RCC_IOPENR_GPIOAEN)
#define RCC_GPIOB_CLK_DISABLE()			CLEAR_BIT(RCC->IOPENR, RCC_IOPENR_GPIOBEN)
#define RCC_GPIOC_CLK_DISABLE()			CLEAR_BIT(RCC->IOPENR, RCC_IOPENR_GPIOCEN)
#define RCC_GPIOD_CLK_DISABLE()			CLEAR_BIT(RCC->IOPENR, RCC_IOPENR_GPIODEN)
#define RCC_GPIOE_CLK_DISABLE()			CLEAR_BIT(RCC->IOPENR, RCC_IOPENR_GPIOEEN)
#define RCC_GPIOF_CLK_DISABLE()			CLEAR_BIT(RCC->IOPENR, RCC_IOPENR_GPIOFEN)

#define RCC_SPI1_CLK_DISABLE()			CLEAR_BIT(RCC->APBENR2, RCC_APBENR2_SPI1EN)
#define RCC_SPI2_CLK_DISABLE()			CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_SPI2EN)
#define RCC_SPI3_CLK_DISABLE()			CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_SPI3EN)


#define RCC_OSCTYPE_NONE				(0x0U)
#define RCC_OSCTYPE_HSE					(0x1U)
#define RCC_OSCTYPE_HSI					(0x2U)
#define RCC_OSCTYPE_LSE					(0x4U)
#define RCC_OSCTYPE_LSI					(0x8U)

#define RCC_HSI_DIV1					(0x0U)
#define RCC_HSI_DIV2					RCC_CR_HSIDIV_BIT0
#define RCC_HSI_DIV4					RCC_CR_HSIDIV_BIT1
#define RCC_HSI_DIV8					(RCC_CR_HSIDIV_BIT1 | RCC_CR_HSIDIV_BIT0)
#define RCC_HSI_DIV16					RCC_CR_HSIDIV_BIT2
#define RCC_HSI_DIV32					(RCC_CR_HSIDIV_BIT2 | RCC_CR_HSIDIV_BIT0)
#define RCC_HSI_DIV64					(RCC_CR_HSIDIV_BIT2 | RCC_CR_HSIDIV_BIT1)
#define RCC_HSI_DIV128					(RCC_CR_HSIDIV_BIT2 | RCC_CR_HSIDIV_BIT1 | RCC_CR_HSIDIV_BIT0)

#define RCC_HSI_OFF						(0x0U)
#define RCC_HSI_ON						RCC_CR_HSION

#define RCC_HSICALIB_DEFAULT			(64U)

#define RCC_PLL_NONE					(0x0U)
#define RCC_PLL_OFF						(0x1U)
#define RCC_PLL_ON						(0x2U)



typedef struct
{
	uint32_t PLLState;
	uint32_t PLLSource;
	uint32_t PLLM;
	uint32_t PLLN;
	uint32_t PLLP;
	uint32_t PLLQ;
	uint32_t PLLR;

}RCC_PLLInitTypeDef_t;

typedef struct
{
	uint32_t OscillatorType;
	uint32_t HSEState;
	uint32_t LSEState;
	uint32_t HSIState;
	uint32_t HSIDiv;
	uint32_t HSICalibrationValue;
	uint32_t LSIState;
	RCC_PLLInitTypeDef_t PLL;


}RCC_OscInitTypeDef_t;

typedef struct
{
	uint32_t ClockType;
	uint32_t SYSCLKSource;
	uint32_t AHBCLKDivider;
	uint32_t APB1CLKDivider;

}RCC_CLKInitTypeDef_t;


#endif /* INC_RCC_H_ */
