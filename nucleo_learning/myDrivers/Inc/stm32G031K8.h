
#ifndef INC_STM32G031K8_H_
#define INC_STM32G031K8_H_

#include <stdint.h>
#include <string.h>
#include <stddef.h>


#define __IO volatile

/*
 * SysTick Freq Definitions
 *
 */
#define SYSTEM_CORE_CLK 		( (uint32_t)(16000000U) )

typedef enum
{
  TICK_FREQ_100KHZ       = 100U,
  TICK_FREQ_10KHZ        = 10U,
  TICK_FREQ_1KHZ         = 1U,
  TICK_FREQ_DEFAULT      = TICK_FREQ_1KHZ
} Systick_TickFreqTypeDef;

/*
 * Microprocessor Definitions
 *
 */

#define SCS_BASE_ADDR            (0xE000E000UL)

#define SYSTICK_BASE_ADDR			(SCS_BASE_ADDR + 0x0010U)
#define NVIC_BASE_ADDR				(SCS_BASE_ADDR + 0x0100U)
#define SCB_BASE_ADDR				(SCS_BASE_ADDR + 0x0D00U)

#define NVIC_ISER					( (uint32_t *)(NVIC_BASE_ADDR) )
#define NVIC_ISER_POS				( (uint32_t *)(NVIC_BASE_ADDR + 0x40U) )

#define NVIC_PRIO_BITS          	(2U)

#define BIT_SHIFT(IRQn)         (  ((((uint32_t)(int32_t)(IRQn))         )      &  0x03UL) * 8UL)
#define SHP_IDX(IRQn)           ( (((((uint32_t)(int32_t)(IRQn)) & 0x0FUL)-8UL) >>    2UL)      )
#define IP_IDX(IRQn)            (   (((uint32_t)(int32_t)(IRQn))                >>    2UL)      )


/*
 *  IRQ Numbers of MCU
 *
 */

typedef enum
{
	IRQ_SysTick  = -1,

	IRQ_EXTI0_1  = 5,
	IRQ_EXTI2_3  = 6,
	IRQ_EXTI4_15 = 7,

}IRQNumber_TypeDef_t;


#define SET_BIT(REG, BIT)			( (REG) |= (BIT) )
#define CLEAR_BIT(REG, BIT)			( (REG) &= ~(BIT))
#define READ_BIT(REG, BIT)			( (REG) &  (BIT) )
#define UNUSED(x)					(void)x


typedef enum
{
	DISABLE = 0x0U,
	ENABLE = ~DISABLE

}FunctionalState_t;

typedef enum
{

	OK = 0x00U,
	ERROR = 0x01U,
	BUSY = 0x02U,
	TIMEOUT = 0x03U

}StatusTypeDef_t;

/*
 *  Memory Base Address
 *
 */

#define FLASH_BASE_ADDR 		(0x08000000UL) /* Flash Base Address (up to 64 KB) 	*/
#define SRAM_BASE_ADDR			(0x20000000UL) /* SRAM Base Address 8 KB 			*/

/*
 * Peripheral Base Addresses
 *
 */

#define PERIPH_BASE_ADDR			(0x40000000UL) 						/* Base Address for All Peripherals 	*/

#define APB_BASE_ADDR			PERIPH_BASE_ADDR 					/* APB Bus Domain Base Address 		*/
#define AHB_BASE_ADDR 			(PERIPH_BASE_ADDR + 0x00020000UL)	/* AHB Bus Domain Base Address 		*/
#define IOPORT_BASE_ADDR		(PERIPH_BASE_ADDR + 0x10000000UL)	/* IOPORT Domain Base Address		*/

/*
 *  APB Peripherals Base Addresses
 *
 */

#define TIM1_BASE_ADDR			(APB_BASE_ADDR + 0x00012C00UL)	/* Timer 1 Base Address	*/
#define TIM2_BASE_ADDR			APB_BASE_ADDR 					/* Timer 2 Base Address */
#define TIM3_BASE_ADDR			(APB_BASE_ADDR + 0x00000400UL)	/* Timer 3 Base Address */
#define TIM4_BASE_ADDR			(APB_BASE_ADDR + 0x00000800UL)	/* Timer 4 Base Address */

#define SPI1_BASE_ADDR			(APB_BASE_ADDR + 0x00013000UL)	/* SPI 1 Base Address	*/
#define SPI2_BASE_ADDR			(APB_BASE_ADDR + 0x00003800UL)	/* SPI 2 Base Address 	*/
#define SPI3_BASE_ADDR			(APB_BASE_ADDR + 0x00003C00UL)  /* SPI 3 Base Address 	*/

#define USART1_BASE_ADDR		(APB_BASE_ADDR + 0x00013800UL)	/* USART 1 Base Address	*/
#define USART2_BASE_ADDR		(APB_BASE_ADDR + 0x00004400UL)	/* USART 2 Base Address */
#define USART3_BASE_ADDR		(APB_BASE_ADDR + 0x00004800UL)	/* USART 3 Base Address */
#define USART4_BASE_ADDR		(APB_BASE_ADDR + 0x00004C00UL)	/* USART 4 Base Address */
#define USART5_BASE_ADDR		(APB_BASE_ADDR + 0x00005000UL)	/* USART 5 Base Address	*/
#define USART6_BASE_ADDR		(APB_BASE_ADDR + 0x00013C00UL)	/* USART 6 Base Address	*/

#define I2C1_BASE_ADDR			(APB_BASE_ADDR + 0x00005400UL)	/* I2C 1 Base Address	*/
#define I2C2_BASE_ADDR			(APB_BASE_ADDR + 0x00005800UL)	/* I2C 2 Base Address 	*/
#define I2C3_BASE_ADDR			(APB_BASE_ADDR + 0x00008800UL) 	/* I2C 3 Base Address	*/

#define SYSCFG_BASE_ADDR		(APB_BASE_ADDR + 0x00010000UL)	/* SYSCFG Base Address	*/

/*
 *  AHB Peripherals Base Addresses
 *
 */

#define EXTI_BASE_ADDR			(AHB_BASE_ADDR + 0x00001800UL)	/* EXTI Base Address	*/

#define RCC_BASE_ADDR			(AHB_BASE_ADDR + 0x00001000UL)  /* RCC Base Address 	*/

/*
 *  IOPORT Peripherals Base Addresses
 *
 */

#define GPIOA_BASE_ADDR			IOPORT_BASE_ADDR					/* GPIO A Base Address	*/
#define GPIOB_BASE_ADDR			(IOPORT_BASE_ADDR + 0x00000400UL)	/* GPIO B Base Address  */
#define GPIOC_BASE_ADDR			(IOPORT_BASE_ADDR + 0x00000800UL)	/* GPIO C Base Address  */
#define GPIOD_BASE_ADDR			(IOPORT_BASE_ADDR + 0x00000C00UL)	/* GPIO D Base Address 	*/
#define GPIOE_BASE_ADDR			(IOPORT_BASE_ADDR + 0x00001000UL)	/* GPIO E Base Address	*/
#define GPIOF_BASE_ADDR			(IOPORT_BASE_ADDR + 0x00001400UL)	/* GPIO F Base Address	*/

/*
 * Microprocessor Structure Definitions
 *
 */

typedef struct
{
	__IO uint32_t CPUID;
	__IO uint32_t ICSR;
	__IO uint32_t VTOR;
	__IO uint32_t AIRCR;
	__IO uint32_t SCR;
	__IO uint32_t CCR;
	__IO uint32_t SHPR[2];

}SCB_TypeDef_t;

typedef struct
{
  __IO	uint32_t ISER;               /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
        uint32_t RESERVED0[31];
  __IO  uint32_t ICER;               /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
        uint32_t RESERVED1[31];
  __IO  uint32_t ISPR;               /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
        uint32_t RESERVED2[31];
  __IO  uint32_t ICPR;               /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
        uint32_t RESERVED3[31];
        uint32_t RESERVED4[64];
  __IO  uint32_t IP[8];                 /*!< Offset: 0x300 (R/W)  Interrupt Priority Register */
}NVIC_TypeDef_t;


/*
 *  Peripheral Structure Definitions
 *
 */

typedef struct
{
	__IO uint32_t MODER;		/*!< GPIO port mode register 							Address Offset = 0x0000 		*/
	__IO uint32_t OTYPER;		/*!< GPIO port output type register 					Address Offset = 0x0004 		*/
	__IO uint32_t OSPEEDR;		/*!< GPIO port output speed register 					Address Offset = 0x0008 		*/
	__IO uint32_t PUPDR;		/*!< GPIO port pull-up/pull-down register 				Address Offset = 0x000C 		*/
	__IO uint32_t IDR;			/*!< GPIO port input data register 						Address Offset = 0x0010 		*/
	__IO uint32_t ODR;			/*!< GPIO port output data register 					Address Offset = 0x0014 		*/
	__IO uint32_t BSRR;			/*!< GPIO port bit set/reset register 					Address Offset = 0x0018 		*/
	__IO uint32_t LCKR;			/*!< GPIO port configuration lock register 				Address Offset = 0x001C 		*/
	__IO uint32_t AFR[2];		/*!< GPIO alternate function low and high registers 	Address Offset = 0x0020-0x0024 	*/
	__IO uint32_t BRR;			/*!< GPIO port bit reset register 						Address Offset = 0x0028 		*/

}GPIO_TypeDef_t;

typedef struct
{
	__IO uint32_t CR;			/*!< RCC Clock control register										Address Offset = 0x0000 	*/
	__IO uint32_t ICSCR;		/*!< RCC Internal clock source calibration register 				Address Offset = 0x0004 	*/
	__IO uint32_t CFGR;			/*!< RCC Clock configuration register 								Address Offset = 0x0008 	*/
	__IO uint32_t PLLCFGR;		/*!< RCC PLL configuration register 								Address Offset = 0x000C 	*/
	__IO uint32_t RESERVED0;	/*!< RCC Reserved													Address Offset = 0x0010 	*/
	__IO uint32_t CRRCR;		/*!< RCC clock recovery RC register 								Address Offset = 0x0014 	*/
	__IO uint32_t CIER;			/*!< RCC Clock interrupt enable register 							Address Offset = 0x0018 	*/
	__IO uint32_t CIFR;			/*!< RCC Clock interrupt flag register 								Address Offset = 0x001C 	*/
	__IO uint32_t CICR;			/*!< RCC Clock interrupt clear register 							Address Offset = 0x0020 	*/
	__IO uint32_t IOPRSTR;		/*!< RCC I/O port reset register									Address Offset = 0x0024 	*/
	__IO uint32_t AHBRSTR;		/*!< RCC AHB peripheral reset register 								Address Offset = 0x0028 	*/
	__IO uint32_t APBRSTR1;		/*!< RCC APB peripheral reset register 1 							Address Offset = 0x002C 	*/
	__IO uint32_t APBRSTR2;		/*!< RCC APB peripheral reset register 2 							Address Offset = 0x0030 	*/
	__IO uint32_t IOPENR;		/*!< RCC I/O port clock enable register 							Address Offset = 0x0034 	*/
	__IO uint32_t AHBENR;		/*!< RCC AHB peripheral clock enable register						Address Offset = 0x0038 	*/
	__IO uint32_t APBENR1;		/*!< RCC APB peripheral clock enable register 1 					Address Offset = 0x003C 	*/
	__IO uint32_t APBENR2;		/*!< RCC APB peripheral clock enable register 2 					Address Offset = 0x0040 	*/
	__IO uint32_t IOPSMENR;		/*!< RCC I/O port in Sleep mode clock enable register 				Address Offset = 0x0044 	*/
	__IO uint32_t AHBSMENR;		/*!< RCC AHB peripheral clock enable in Sleep/Stop mode register 	Address Offset = 0x0048 	*/
	__IO uint32_t APBSMENR1;	/*!< RCC APB peripheral clock enable in Sleep/Stop mode register 1 	Address Offset = 0x004C 	*/
	__IO uint32_t APBSMENR2;	/*!< RCC APB peripheral clock enable in Sleep/Stop mode register 2 	Address Offset = 0x0050 	*/
	__IO uint32_t CCIPR;		/*!< RCC Peripherals independent clock configuration register 		Address Offset = 0x0054 	*/
	__IO uint32_t CCIPR2;		/*!< RCC Peripherals independent clock configuration register 2 	Address Offset = 0x0058 	*/
	__IO uint32_t BDCR;			/*!< RCC RTC domain control register 								Address Offset = 0x005C 	*/
	__IO uint32_t CSR;			/*!< RCC Control/status register 									Address Offset = 0x0060 	*/

}RCC_Typedef_t;

typedef struct
{
	__IO uint32_t CFGR1;		/*	SYSCFG configuration register 1 				Address Offset = 0x00	*/
	__IO uint32_t RESERVED0;	/*	SYSCFG Reserved									Address Offset = 0x04	*/
	__IO uint32_t CFGR2;		/*	SYSCFG configuration register 1 				Address Offset = 0x18	*/
	__IO uint32_t RESERVED1;	/*	SYSCFG Reserved									Address Offset = 0x1D	*/
	__IO uint32_t ITLINE[32];	/* 	SYSCFG interrupt line 0 - 32 status registers 	Address Offset = 0x80   */

}SYSCFG_TypeDef_t;

typedef struct
{
	__IO uint32_t RTSR1;		/* EXTI rising trigger selection register 1 		Address Offset = 0x000	*/
	__IO uint32_t FTSR1;		/* EXTI falling trigger selection register 1 		Address Offset = 0x004	*/
	__IO uint32_t SWIER1;		/* EXTI software interrupt event register 1 		Address Offset = 0x008	*/
	__IO uint32_t RPR1;			/* EXTI rising edge pending register 1 				Address Offset = 0x00C	*/
	__IO uint32_t FPR1;			/* EXTI falling edge pending register 1 			Address Offset = 0x010	*/
	__IO uint32_t RESERVED0[5];	/* EXTI Reserved									Address Offset = 0x014	*/
	__IO uint32_t RTSR2;		/* EXTI rising trigger selection register 2 		Address Offset = 0x028	*/
	__IO uint32_t FTSR2;		/* EXTI falling trigger selection register 2 		Address Offset = 0x02C	*/
	__IO uint32_t SWIER2;		/* EXTI software interrupt event register 2 		Address Offset = 0x030	*/
	__IO uint32_t RPR2;			/* EXTI rising edge pending register 2 				Address Offset = 0x034	*/
	__IO uint32_t FPR2;			/* EXTI falling edge pending register 2 			Address Offset = 0x038	*/
	__IO uint32_t RESERVED1[9];	/* EXTI Reserved									Address Offset = 0x03C	*/
	__IO uint32_t EXTICR[4];	/* EXTI external interrupt selection registers  	Address Offset = 0x060	*/
	__IO uint32_t RESERVED2[4];	/* EXTI Reserved									Address Offset = 0x070	*/
	__IO uint32_t IMR1;			/* EXTI CPU wakeup with interrupt mask register 1  	Address Offset = 0x080	*/
	__IO uint32_t EMR1;			/* EXTI CPU wakeup with event mask register 1		Address Offset = 0x084	*/
	__IO uint32_t RESERVED3[2];	/* EXTI Reserved									Address Offset = 0x088	*/
	__IO uint32_t IMR2;			/* EXTI CPU wakeup with interrupt mask register 2  	Address Offset = 0x090	*/
	__IO uint32_t EMR2;			/* EXTI CPU wakeup with event mask register 1		Address Offset = 0x094	*/

}EXTI_TypeDef_t;

typedef struct
{
	__IO uint32_t CR1;		/* SPI control register 1 			Address Offset = 0x00	*/
	__IO uint32_t CR2;		/* SPI control register 2 			Address Offset = 0x04	*/
	__IO uint32_t SR;		/* SPI status  register	 			Address Offset = 0x08	*/
	__IO uint32_t DR;		/* SPI data    register	 			Address Offset = 0x0C	*/
	__IO uint32_t CRCPR;	/* SPI CRC polynominal register  	Address Offset = 0x10	*/
	__IO uint32_t RXCRCR;	/* SPI Rx CRC register  			Address Offset = 0x14	*/
	__IO uint32_t TXCRCR;	/* SPI Tx CRC register  			Address Offset = 0x18	*/
	__IO uint32_t I2SCFGR;	/* SPIx_I2S configuration register 	Address Offset = 0x1C	*/
	__IO uint32_t I2SPR;	/* SPIx_I2S prescaler register  	Address Offset = 0x20	*/

}SPI_TypeDef_t;

typedef struct
{
	__IO uint32_t CSR;                   	/*!< SysTick Control and Status Register 	Address Offset: 0x000 */
	__IO uint32_t RVR;                   	/*!< SysTick Reload Value Register 			Address Offset: 0x004 */
	__IO uint32_t CVR;                    	/*!< SysTick Current Value Register 		Address Offset: 0x008 */
	__IO uint32_t CALIB;                  	/*!< SysTick Calibration Register 			Address Offset: 0x00C */

}SysTick_TypeDef_t;


#define GPIOA					( (GPIO_TypeDef_t *)(GPIOA_BASE_ADDR) 	)
#define GPIOB					( (GPIO_TypeDef_t *)(GPIOB_BASE_ADDR) 	)
#define GPIOC					( (GPIO_TypeDef_t *)(GPIOC_BASE_ADDR) 	)
#define GPIOD					( (GPIO_TypeDef_t *)(GPIOD_BASE_ADDR) 	)
#define GPIOE					( (GPIO_TypeDef_t *)(GPIOE_BASE_ADDR) 	)
#define GPIOF					( (GPIO_TypeDef_t *)(GPIOF_BASE_ADDR) 	)

#define RCC 					( (RCC_Typedef_t *)(RCC_BASE_ADDR) 		)

#define SYSCFG					( (SYSCFG_TypeDef_t *)(SYSCFG_BASE_ADDR))

#define EXTI					( (EXTI_TypeDef_t *)(EXTI_BASE_ADDR)	)

#define SPI1					( (SPI_TypeDef_t *)(SPI1_BASE_ADDR) )
#define SPI2					( (SPI_TypeDef_t *)(SPI2_BASE_ADDR) )
#define SPI3					( (SPI_TypeDef_t *)(SPI3_BASE_ADDR) )

#define SYSTICK					( (SysTick_TypeDef_t *)(SYSTICK_BASE_ADDR) )

#define NVIC						( (NVIC_TypeDef_t *)(NVIC_ISER) )
#define SCB							( (SCB_TypeDef_t *)(SCB_BASE_ADDR) )

/*
 *  Bit Definitions
 *
 */

/*	Bit definition for PWR_CR1 register	*/

#define PWR_CR1_LPMS_POS		(0U)
#define PWR_CR1_LPMS_MSK		(0x7U << PWR_CR1_LPMS_POS)
#define PWR_CR1_LPMS			PWR_CR1_LPMS_MSK
#define PWR_CR1_LPMS_BIT0		(0x1U << PWR_CR1_LPMS_POS)
#define PWR_CR1_LPMS_BIT1		(0x2U << PWR_CR1_LPMS_POS)
#define PWR_CR1_LPMS_BIT2		(0x4U << PWR_CR1_LPMS_POS)

#define PWR_CR1_FPD_STOP_POS	(3U)
#define PWR_CR1_FPD_STOP_MSK	(0x1U << PWR_CR1_FPD_STOP_POS)
#define PWR_CR1_FPD_STOP		PWR_CR1_FPD_STOP_MSK

#define PWR_CR1_FPD_LPRUN_POS	(4U)
#define PWR_CR1_FPD_LPRUN_MSK	(0x1U << PWR_CR1_FPD_LPRUN_POS)
#define PWR_CR1_FPD_LPRUN		PWR_CR1_FPD_LPRUN_MSK

#define PWR_CR1_FPD_LPSLP_POS	(5U)
#define PWR_CR1_FPD_LPSLP_MSK	(0x1U << PWR_CR1_FPD_LPSLP_POS)
#define PWR_CR1_FPD_LPSLP		PWR_CR1_FPD_LPSLP_MSK

#define PWR_CR1_DBP_POS			(8U)
#define PWR_CR1_DBP_MSK			(0x1U << PWR_CR1_DBP_POS)
#define PWR_CR1_DBP				PWR_CR1_DBP_MSK

#define PWR_CR1_VOS_POS			(9U)
#define PWR_CR1_VOS_MSK			(0x3U << PWR_CR1_VOS_POS)
#define PWR_CR1_VOS				PWR_CR1_VOS_MSK
#define PWR_CR1_VOS_BIT0		(0x1U << PWR_CR1_VOS_POS)
#define PWR_CR1_VOS_BIT1		(0x2U << PWR_CR1_VOS_POS)

#define PWR_CR1_LPR_POS			(14U)
#define PWR_CR1_LPR_MSK			(0x1U << PWR_CR1_LPR_POS)
#define PWR_CR1_LPR				PWR_CR1_LPR_MSK

/*	Bit definition for RCC_IOPENR register*/

#define RCC_IOPENR_GPIOAEN_POS	(0U)							// RCC IOPENR register GPIOAEN Bit Position
#define RCC_IOPENR_GPIOAEN_MSK	(0x1 << RCC_IOPENR_GPIOAEN_POS) // RCC IOPENR register GPIOAEN Bit Mask
#define RCC_IOPENR_GPIOAEN		RCC_IOPENR_GPIOAEN_MSK			// RCC IOPENR register GPIOAEN Macro

#define RCC_IOPENR_GPIOBEN_POS	(1U)							// RCC IOPENR register GPIOBEN Bit Position
#define RCC_IOPENR_GPIOBEN_MSK	(0x1 << RCC_IOPENR_GPIOBEN_POS) // RCC IOPENR register GPIOBEN Bit Mask
#define RCC_IOPENR_GPIOBEN		RCC_IOPENR_GPIOBEN_MSK			// RCC IOPENR register GPIOBEN Macro

#define RCC_IOPENR_GPIOCEN_POS	(2U)							// RCC IOPENR register GPIOCEN Bit Position
#define RCC_IOPENR_GPIOCEN_MSK	(0x1 << RCC_IOPENR_GPIOCEN_POS) // RCC IOPENR register GPIOCEN Bit Mask
#define RCC_IOPENR_GPIOCEN 		RCC_IOPENR_GPIOCEN_MSK			// RCC IOPENR register GPIOCEN Macro

#define RCC_IOPENR_GPIODEN_POS	(3U)							// RCC IOPENR register GPIODEN Bit Position
#define RCC_IOPENR_GPIODEN_MSK 	(0x1 << RCC_IOPENR_GPIODEN_POS) // RCC IOPENR register GPIODEN Bit Mask
#define RCC_IOPENR_GPIODEN		RCC_IOPENR_GPIODEN_MSK			// RCC IOPENR register GPIODEN Macro

#define RCC_IOPENR_GPIOEEN_POS 	(4U)							// RCC IOPENR register GPIOEEN Bit Position
#define RCC_IOPENR_GPIOEEN_MSK	(0x1 << RCC_IOPENR_GPIOEEN_POS)	// RCC IOPENR register GPIOEEN Bit Mask
#define RCC_IOPENR_GPIOEEN		RCC_IOPENR_GPIOEEN_MSK			// RCC IOPENR register GPIOEEN Macro

#define RCC_IOPENR_GPIOFEN_POS	(5U)							// RCC IOPENR register GPIOFEN Bit Position
#define RCC_IOPENR_GPIOFEN_MSK	(0x1 << RCC_IOPENR_GPIOFEN_POS) // RCC IOPENR register GPIOFEN Bit Mask
#define RCC_IOPENR_GPIOFEN		RCC_IOPENR_GPIOFEN_MSK			// RCC IOPENR register GPIOFEN Macro

#define RCC_APBENR2_SYSCFGEN_POS	(0U)								// RCC APBENR2 register SYSCFGEN Bit Position
#define RCC_APBENR2_SYSCFGEN_MSK	(0x1 << RCC_APBENR2_SYSCFGEN_POS)	// RCC APBENR2 register SYSCFGEN Bit Mask
#define RCC_APBENR2_SYSCFGEN		RCC_APBENR2_SYSCFGEN_MSK			// RCC APBENR2 register SYSCFGEN Macro

#define RCC_APBENR2_SPI1EN_POS		(12U)								// RCC APBENR2 register SPI1 Bit Position
#define RCC_APBENR2_SPI1EN_MSK		(0x1 << RCC_APBENR2_SPI1EN_POS)		// RCC APBENR2 register SPI1 Bit Mask
#define RCC_APBENR2_SPI1EN			RCC_APBENR2_SPI1EN_MSK				// RCC APBENR2 register SPI1 Macro

#define RCC_APBENR1_SPI2EN_POS		(14U)								// RCC APBENR1 register SPI2 Bit Position
#define RCC_APBENR1_SPI2EN_MSK		(0x1 << RCC_APBENR1_SPI2EN_POS)		// RCC APBENR1 register SPI2 Bit Mask
#define RCC_APBENR1_SPI2EN			RCC_APBENR1_SPI2EN_MSK				// RCC APBENR1 register SPI2 Macro

#define RCC_APBENR1_SPI3EN_POS		(15U)								// RCC APBENR1 register SPI3 Bit Position
#define RCC_APBENR1_SPI3EN_MSK		(0x1 << RCC_APBENR1_SPI3EN_POS)		// RCC APBENR1 register SPI3 Bit Mask
#define RCC_APBENR1_SPI3EN			RCC_APBENR1_SPI3EN_MSK				// RCC APBENR1 register SPI3 Macro

#define SPI_CR1_SPE					(6U)								// SPI CR1 Regişter SPE Bit Macro
#define SPI_CR1_CRCL				(11U)

#define SPI_CR2_TXEIE				(7U)

#define SPI_SR_RXNE					(0U)
#define SPI_SR_TXE					(1U)								// SPI SR Regişter TxE Bit Macro
#define SPI_SR_BUSY					(7U)


#define SYSTICK_MAX_DELAY			(0xFFFFFFFFU)

/*	Bit definitions for RCC_CFGR Register*/

#define RCC_CFGR_SW1_POS			(0U)
#define	RCC_CFGR_SW1_MSK			(0x7U << RCC_CFGR_SW1_POS)
#define RCC_CFGR_SW1				RCC_CFGR_SW1_MSK
#define RCC_CFGR_SW1_BIT0				(0x1U << RCC_CFGR_SW1_POS)
#define RCC_CFGR_SW1_BIT1				(0x2U << RCC_CFGR_SW1_POS)
#define RCC_CFGR_SW1_BIT2				(0x4U << RCC_CFGR_SW1_POS)

#define RCC_CFGR_SW2_POS			(3U)
#define RCC_CFGR_SW2_MSK			(0x7 << RCC_CFGR_SW2_POS)
#define RCC_CFGR_SW2				RCC_CFGR_SW2_MSK
#define RCC_CFGR_SW2_BIT0				(0x1 << RCC_CFGR_SW2_POS)
#define RCC_CFGR_SW2_BIT1				(0x2 << RCC_CFGR_SW2_POS)
#define RCC_CFGR_SW2_BIT2				(0x4 << RCC_CFGR_SW2_POS)

#define RCC_CFGR_SW2_HSISYS			(0x000U)
#define RCC_CFGR_SW2_HSE			(0x008U)
#define RCC_CFGR_SW2_PLLRCLK		(0x010U)
#define RCC_CFGR_SW2_LSI			(0x018U)
#define RCC_CFGR_SW2_HLSE			(0x100U)

#define RCC_CFGR_HPRE_Pos              (8U)
#define RCC_CFGR_HPRE_Msk              (0xFUL << RCC_CFGR_HPRE_Pos)
#define RCC_CFGR_HPRE                  RCC_CFGR_HPRE_Msk
#define RCC_CFGR_HPRE_0                (0x1UL << RCC_CFGR_HPRE_Pos)
#define RCC_CFGR_HPRE_1                (0x2UL << RCC_CFGR_HPRE_Pos)
#define RCC_CFGR_HPRE_2                (0x4UL << RCC_CFGR_HPRE_Pos)
#define RCC_CFGR_HPRE_3                (0x8UL << RCC_CFGR_HPRE_Pos)


/* Bit definition for RCC_PLLCFGR register*/

#define RCC_PLLCFGR_PLLSRC_POS			(0U)
#define RCC_PLLCFGR_PLLSRC_MSK			(0X3U << RCC_PLLCFGR_PLLSRC_POS)
#define RCC_PLLCFGR_PLLSRC				RCC_PLLCFGR_PLLSRC_MSK
#define RCC_PLLCFGR_PLLSRC_BIT0			(0x1 << RCC_PLLCFGR_PLLSRC_POS)
#define RCC_PLLCFGR_PLLSRC_BIT1			(0x2 << RCC_PLLCFGR_PLLSRC_POS)

#define RCC_PLLCFGR_PLLSRC_NONE         (0x0U)
#define RCC_PLLCFGR_PLLSRC_HSI_POS      (1U)
#define RCC_PLLCFGR_PLLSRC_HSI_MSK      (0x1U << RCC_PLLCFGR_PLLSRC_HSI_POS)
#define RCC_PLLCFGR_PLLSRC_HSI          RCC_PLLCFGR_PLLSRC_HSI_MSK
#define RCC_PLLCFGR_PLLSRC_HSE_POS      (0U)
#define RCC_PLLCFGR_PLLSRC_HSE_MSK      (0x3U << RCC_PLLCFGR_PLLSRC_HSE_POS)
#define RCC_PLLCFGR_PLLSRC_HSE          RCC_PLLCFGR_PLLSRC_HSE_MSK

#define RCC_PLLCFGR_PLLM_POS			(4U)
#define RCC_PLLCFGR_PLLM_MSK			(0x7U << RCC_PLLCFGR_PLLM_POS)
#define RCC_PLLCFGR_PLLM				RCC_PLLCFGR_PLLM_MSK
#define RCC_PLLCFGR_PLLM_BIT0			(0x1U << RCC_PLLCFGR_PLLM_POS)
#define RCC_PLLCFGR_PLLM_BIT1			(0x2U << RCC_PLLCFGR_PLLM_POS)
#define RCC_PLLCFGR_PLLM_BIT2			(0x4U << RCC_PLLCFGR_PLLM_POS)

#define RCC_PLLCFGR_PLLN_POS			(8U)
#define RCC_PLLCFGR_PLLN_MSK			(0x7FU << RCC_PLLCFGR_PLLN_POS)
#define RCC_PLLCFGR_PLLN				RCC_PLLCFGR_PLLN_MSK
#define RCC_PLLCFGR_PLLN_Bit0			(0x01U << RCC_PLLCFGR_PLLN_POS)
#define RCC_PLLCFGR_PLLN_Bit1			(0x02U << RCC_PLLCFGR_PLLN_POS)
#define RCC_PLLCFGR_PLLN_Bit2			(0x04U << RCC_PLLCFGR_PLLN_POS)
#define RCC_PLLCFGR_PLLN_Bit3	 		(0x08U << RCC_PLLCFGR_PLLN_POS)
#define RCC_PLLCFGR_PLLN_Bit4			(0x10U << RCC_PLLCFGR_PLLN_POS)
#define RCC_PLLCFGR_PLLN_Bit5			(0x20U << RCC_PLLCFGR_PLLN_POS)
#define RCC_PLLCFGR_PLLN_Bit6			(0x40U << RCC_PLLCFGR_PLLN_POS)

#define RCC_PLLCFGR_PLLPEN_POS			(16U)
#define RCC_PLLCFGR_PLLPEN_MSK			(0x1U << RCC_PLLCFGR_PLLPEN_POS)
#define RCC_PLLCFGR_PLLPEN				RCC_PLLCFGR_PLLPEN_MSK

#define RCC_PLLCFGR_PLLP_POS			(17U)
#define RCC_PLLCFGR_PLLP_MSK			(0x1FU << RCC_PLLCFGR_PLLP_POS)
#define RCC_PLLCFGR_PLLP				RCC_PLLCFGR_PLLP_MSK
#define RCC_PLLCFGR_PLLP_BIT0			(0x01U << RCC_PLLCFGR_PLLP_POS)
#define RCC_PLLCFGR_PLLP_BIT1			(0x02U << RCC_PLLCFGR_PLLP_POS)
#define RCC_PLLCFGR_PLLP_BIT2			(0x04U << RCC_PLLCFGR_PLLP_POS)
#define RCC_PLLCFGR_PLLP_BIT3			(0x08U << RCC_PLLCFGR_PLLP_POS)
#define RCC_PLLCFGR_PLLP_BIT4			(0x10U << RCC_PLLCFGR_PLLP_POS)

#define RCC_PLLCFGR_PLLQEN_POS			(24U)
#define RCC_PLLCFGR_PLLQEN_MSK			(0x1U << RCC_PLLCFGR_PLLQEN_POS)
#define RCC_PLLCFGR_PLLQEN				RCC_PLLCFGR_PLLQEN_MSK

#define RCC_PLLCFGR_PLLQ_POS			(25U)
#define RCC_PLLCFGR_PLLQ_MSK			(0x7U << RCC_PLLCFGR_PLLQ_POS)
#define RCC_PLLCFGR_PLLQ				RCC_PLLCFGR_PLLQ_MSK
#define RCC_PLLCFGR_PLLQ_BIT0			(0x1U << RCC_PLLCFGR_PLLQ_POS)
#define RCC_PLLCFGR_PLLQ_BIT1			(0x2U << RCC_PLLCFGR_PLLQ_POS)
#define RCC_PLLCFGR_PLLQ_BIT2			(0x4U << RCC_PLLCFGR_PLLQ_POS)

#define RCC_PLLCFGR_PLLREN_POS			(28U)
#define RCC_PLLCFGR_PLLREN_MSK			(0x1U << RCC_PLLCFGR_PLLREN_POS)
#define RCC_PLLCFGR_PLLREN				RCC_PLLCFGR_PLLREN_MSK

#define RCC_PLLCFGR_PLLR_POS			(29U)
#define RCC_PLLCFGR_PLLR_MSK			(0x7U << RCC_PLLCFGR_PLLR_POS)
#define RCC_PLLCFGR_PLLR				RCC_PLLCFGR_PLLR_MSK
#define RCC_PLLCFGR_PLLR_BIT0			(0x1U << RCC_PLLCFGR_PLLR_POS)
#define RCC_PLLCFGR_PLLR_BIT1			(0x2U << RCC_PLLCFGR_PLLR_POS)
#define RCC_PLLCFGR_PLLR_BIT2			(0x4U << RCC_PLLCFGR_PLLR_POS)

/*	Bit definition for RCC_CR register	*/

#define RCC_CR_HSION_POS				(8U)
#define RCC_CR_HSION_MSK				(0x1U << RCC_CR_HSION_POS)
#define RCC_CR_HSION					RCC_CR_HSION_MSK

#define RCC_CR_HSIDIV_POS				(11U)
#define RCC_CR_HSIDIV_MSK				(0x7U << RCC_CR_HSIDIV_POS)
#define RCC_CR_HSIDIV					RCC_CR_HSIDIV_MSK
#define RCC_CR_HSIDIV_BIT0				(0x1U << RCC_CR_HSIDIV_POS)
#define RCC_CR_HSIDIV_BIT1				(0x2U << RCC_CR_HSIDIV_POS)
#define RCC_CR_HSIDIV_BIT2				(0x4U << RCC_CR_HSIDIV_POS)

/* SysTick Control - Status Register Definitions */

#define SYSTICK_CSR_ENABLE_POS		(0U)									// SysTick CSR register ENABLE Bit Position
#define SYSTICK_CSR_ENABLE_MSK		(0x1 << SYSTICK_CSR_ENABLE_POS)			// SysTick CSR register ENABLE Bit Mask
#define SYSTICK_CSR_ENABLE			SYSTICK_CSR_ENABLE_MSK					// SysTick CSR register ENABLE Bit Macro

#define SYSTICK_CSR_TICKINT_POS		(1U)									// SysTick CSR register TICKINT Bit Position
#define SYSTICK_CSR_TICKINT_MSK		(0x1 << SYSTICK_CSR_TICKINT_POS)		// SysTick CSR register TICKINT Bit Mask
#define SYSTICK_CSR_TICKINT			SYSTICK_CSR_TICKINT_MSK					// SysTick CSR register TICKINT Bit Macro

#define SYSTICK_CSR_CLKSOURCE_POS	(2U)									// SysTick CSR register CLKSOURCE Bit Position
#define SYSTICK_CSR_CLKSOURCE_MSK	(0x1 << SYSTICK_CSR_CLKSOURCE_POS)		// SysTick CSR register CLKSOURCE Bit Mask
#define SYSTICK_CSR_CLKSOURCE		SYSTICK_CSR_CLKSOURCE_MSK				// SysTick CSR register CLKSOURCE Bit Macro


#define SYSTICK_CSR_COUNTFLAG_POS	(16U)									// SysTick CSR register COUNTFLAG Bit Position
#define SYSTICK_CSR_COUNTFLAG_MSK	(0x1 << SYSTICK_CSR_COUNTFLAG_POS)		// SysTick CSR register COUNTFLAG Bit Mask
#define SYSTICK_CSR_COUNTFLAG		SYSTICK_CSR_COUNTFLAG_MSK				// SysTick CSR register COUNTFLAG Bit Macro

/* SysTick Reload Register Definitions */

#define SYSTICK_RVR_RELOAD_POS		(0U)									// SysTick RVR register RELOAD Bit Position
#define SYSTICK_RVR_RELOAD_MSK		(0xFFFFFF << SYSTICK_RVR_RELOAD_POS)	// SysTick RVR register RELOAD Bit Mask
#define SYSTICK_RVR_RELOAD			SYSTICK_RVR_RELOAD_MSK					// SysTick RVR register RELOAD Bit Macro

/* SysTick Current Register Definitions */

#define SYSTICK_CVR_CURRENT_POS		(0U)									// SysTick CVR register CURRENT Bit Position
#define SYSTICK_CVR_CURRENT_MSK		(0xFFFFFF << SYSTICK_CVR_CURRENT_POS)	// SysTick CVR register CURRENT Bit Mask
#define SYSTICK_CVR_CURRENT			SYSTICK_CVR_CURRENT_MSK					// SysTick CVR register CURRENT Bit Macro

/* SysTick Calibration Register Definitions */

#define SYSTICK_CALIB_TENMS_POS		(0U)									// SysTick CALIB register TENMS Bit Position
#define SYSTICK_CALIB_TENMS_MSK		(0xFFFFFF << SYSTICK_CALIB_TENMS_POS)	// SysTick CALIB register TENMS Bit Mask
#define SYSTICK_CALIB_TENMS			SYSTICK_CALIB_TENMS_MSK					// SysTick CALIB register TENMS Bit Macro

#define SYSTICK_CALIB_SKEW_POS		(30U)									// SysTick CALIB register SKEW Bit Position
#define SYSTICK_CALIB_SKEW_MSK		(0x1 << SYSTICK_CALIB_SKEW_POS)			// SysTick CALIB register SKEW Bit Mask
#define SYSTICK_CALIB_SKEW			SYSTICK_CALIB_SKEW_MSK					// SysTick CALIB register SKEW Bit Macro

#define SYSTICK_CALIB_NOREF_POS		(31U)									// SysTick CALIB register NOREF Bit Position
#define SYSTICK_CALIB_NOREF_MSK		(0x1 << SYSTICK_CALIB_NOREF_POS)		// SysTick CALIB register NOREF Bit Mask
#define SYSTICK_CALIB_NOREF			SYSTICK_CALIB_NOREF_MSK					// SysTick CALIB register NOREF Bit Macro

/*
 * Flag Definitions
 *
 */

#define SPI_BUSY_FLAG				(0x1U << SPI_SR_BUSY)
#define SPI_TXE_FLAG				(0x1U << SPI_SR_TXE)
#define SPI_RXNE_FLAG				(0x1U << SPI_SR_RXNE)

#include "RCC.h"
#include "GPIO.h"
#include "EXTI.h"
#include "SPI.h"
#include "SYSTICK.h"

#endif /* INC_STM32G031K8_H_ */
