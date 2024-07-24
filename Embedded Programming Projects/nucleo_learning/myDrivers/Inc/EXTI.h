#ifndef INC_EXTI_H_
#define INC_EXTI_H_

#include "stm32G031K8.h"


/*
 * @def_group PORT_Value
 *
 */

#define EXTI_PORTSOURCE_GPIOA					( (uint8_t)(0x00U) )
#define EXTI_PORTSOURCE_GPIOB					( (uint8_t)(0x01U) )
#define EXTI_PORTSOURCE_GPIOC					( (uint8_t)(0x02U) )
#define EXTI_PORTSOURCE_GPIOD					( (uint8_t)(0x03U) )
#define EXTI_PORTSOURCE_GPIOF					( (uint8_t)(0x05U) )


/*
 * @def_group EXTI_Line_Value
 *
 */

#define EXTI_LINESOURCE_0						( (uint8_t)(0x0U)    )
#define EXTI_LINESOURCE_1						( (uint8_t)(0x1U)    )
#define EXTI_LINESOURCE_2						( (uint8_t)(0x2U)    )
#define EXTI_LINESOURCE_3						( (uint8_t)(0x3U)    )
#define EXTI_LINESOURCE_4						( (uint8_t)(0x4U)    )
#define EXTI_LINESOURCE_5						( (uint8_t)(0x5U)    )
#define EXTI_LINESOURCE_6						( (uint8_t)(0x6U)    )
#define EXTI_LINESOURCE_7						( (uint8_t)(0x7U)    )
#define EXTI_LINESOURCE_8						( (uint8_t)(0x8U)    )
#define EXTI_LINESOURCE_9						( (uint8_t)(0x9U)    )
#define EXTI_LINESOURCE_10						( (uint8_t)(0xAU)    )
#define EXTI_LINESOURCE_11						( (uint8_t)(0xBU)    )
#define EXTI_LINESOURCE_12						( (uint8_t)(0xCU)    )
#define EXTI_LINESOURCE_13						( (uint8_t)(0xDU)    )
#define EXTI_LINESOURCE_14						( (uint8_t)(0xEU)    )
#define EXTI_LINESOURCE_15						( (uint8_t)(0xFU) 	 )


/*
 * @def_group EXTI_Modes
 *
 */

#define EXTI_MODE_INTERRUPT		(0x080U)
#define EXTI_MODE_EVENT			(0x084U)

/*
 * @def_group EXTI_Trigger_Modes
 *
 */

#define EXTI_TRIGGER_RISING1	(0x000U)
#define EXTI_TRIGGER_FALLING1	(0x004U)
#define EXTI_TRIGGER_RF1		(0x008U)


typedef struct
{

	uint8_t EXTI_LineNumber;
	uint8_t TriggerSelection;
	uint8_t EXTI_Mode;
	FunctionalState_t EXTI_LineCmd;

}EXTI_InitTypeDef_t;

void EXTI_Init(EXTI_InitTypeDef_t *EXTI_InitStruct);
void EXTI_LineConfig_t(uint8_t PortSource, uint8_t LineSource);
void NVIC_EnableInterrupt(IRQNumber_TypeDef_t IRQNumber);

#endif /* INC_EXTI_H_ */
