#include "stm32G031K8.h"

static void GPIO_LedConfig();

static void ButtonInputConfig();

static void GPIO_ButtonInterruptConfig();

static void SPI_TestConfig();

static void SPI_GPIO_Config();

static void EXTI_TestConfig();

uint32_t SysTickConfig(uint32_t ticks);

SPI_HandleTypeDef_t SPI_Handle;

void SysTick_Handler(void)
{
	IncTick();

  /* Toggle Led for every x interrupt */

	if( GetTick() >= GetTickLimit() )
	{
		GPIO_TogglePin(GPIOC, GPIO_PIN_6);
		TickReset();
	}

}

void EXTI2_3_IRQHandler()
{
	//char msgToSend[] = "Hello World\n";

	if( EXTI->RPR1 & 0x4 )
	{
		EXTI->RPR1 |= (0x1U << 2U);

		GPIO_TogglePin(GPIOC, GPIO_PIN_6);

		//SPI_TransmitData(&SPI_Handle, (uint8_t *)msgToSend, strlen(msgToSend) );

	}
}

void SPI1_IRQHandler()
{

	SPI_InterruptHandler(&SPI_Handle);

}



int main(void)
{
	GPIO_LedConfig();

/* Generate Interupt for each 1 ms*/
	SysTickConfig( (SYSTEM_CORE_CLK/ 1000) );

	Delay(1000);


//	ButtonInputConfig();

//	GPIO_ButtonInterruptConfig();


//	SPI_GPIO_Config();
//
//	SPI_TestConfig();




	while(1)
	{

	}

}


static void EXTI_TestConfig()
{
	GPIO_InitTypeDef_t GPIO_TestStruct = { 0 };

	RCC_GPIOF_CLK_ENABLE();

	GPIO_TestStruct.pinNumber = GPIO_PIN_10;
	GPIO_TestStruct.Mode = GPIO_MODE_OUTPUT;
	GPIO_TestStruct.Otype = GPIO_OTYPE_PP;
	GPIO_TestStruct.Speed = GPIO_SPEED_LOW;

	GPIO_Init(GPIOF, &GPIO_TestStruct);

	EXTI_InitTypeDef_t EXTI_TestStruct = { 0 };

	EXTI_LineConfig_t(EXTI_PORTSOURCE_GPIOF, EXTI_LINESOURCE_10);

	EXTI_TestStruct.EXTI_LineCmd = ENABLE;
	EXTI_TestStruct.EXTI_LineNumber = EXTI_LINESOURCE_10;
	EXTI_TestStruct.EXTI_Mode = EXTI_MODE_INTERRUPT;
	EXTI_TestStruct.TriggerSelection = EXTI_TRIGGER_RF1;

	EXTI_Init(&EXTI_TestStruct);

	NVIC_EnableInterrupt(IRQ_EXTI4_15);

}

static void GPIO_LedConfig()
{
	GPIO_InitTypeDef_t GPIO_LedStruct = { 0 };

	RCC_GPIOC_CLK_ENABLE();  // Clock is active

	GPIO_LedStruct.pinNumber = GPIO_PIN_6;
	GPIO_LedStruct.Mode = GPIO_MODE_OUTPUT;
	GPIO_LedStruct.Otype = GPIO_OTYPE_PP;
	GPIO_LedStruct.Speed = GPIO_SPEED_VERYL;
	GPIO_LedStruct.PuPd = GPIO_PUPD_NOPULL;

	GPIO_Init(GPIOC, &GPIO_LedStruct);  // Config

}

static void ButtonInputConfig()
{
	GPIO_InitTypeDef_t GPIO_InitStruct = { 0 };

	RCC_GPIOF_CLK_ENABLE();  // Clock is active

	GPIO_InitStruct.pinNumber = GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.PuPd = GPIO_PUPD_UP;

	GPIO_Init(GPIOF, &GPIO_InitStruct);  // Config

}

static void GPIO_ButtonInterruptConfig()
{
	EXTI_InitTypeDef_t EXTI_InitStruct = { 0 };

	EXTI_LineConfig_t(EXTI_PORTSOURCE_GPIOF, EXTI_LINESOURCE_2);

	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_LineNumber = EXTI_LINESOURCE_2;
	EXTI_InitStruct.EXTI_Mode = EXTI_MODE_INTERRUPT;
	EXTI_InitStruct.TriggerSelection = EXTI_TRIGGER_RISING1;

	EXTI_Init(&EXTI_InitStruct);

	NVIC_EnableInterrupt(IRQ_EXTI2_3);

}

static void SPI_TestConfig()
{
	SPI_HandleTypeDef_t SPI_Handle = { 0 };

	RCC_SPI1_CLK_ENABLE();

	SPI_Handle.Instance = SPI1;
	SPI_Handle.Init.BaudRate = SPI_BAUDRATE_DIV8;
	SPI_Handle.Init.BusConfig = SPI_BUS_FULLDUPLEX;
	SPI_Handle.Init.CPHA = SPI_CPHA_FIRST;
	SPI_Handle.Init.CPOL = SPI_CPOL_LOW;
	SPI_Handle.Init.CRCL = SPI_CRCL_8BIT;
	SPI_Handle.Init.FrameFormat = SPI_FRAMEFORMAT_MSB;
	SPI_Handle.Init.Mode = SPI_MODE_MASTER;
	SPI_Handle.Init.SSM_CMD = SPI_SSM_ENABLE;

	SPI_Init( &SPI_Handle );

	SPI_PeripCmd(&SPI_Handle, ENABLE);

}

static void SPI_GPIO_Config()
{
	GPIO_InitTypeDef_t GPIO_InitStruct =  { 0 };

	RCC_GPIOA_CLK_ENABLE();

	GPIO_InitStruct.pinNumber = GPIO_PIN_5 | GPIO_PIN_7; // PA5 = SCK, PA7 = MOSI
	GPIO_InitStruct.Mode = GPIO_MODE_AF;
	GPIO_InitStruct.Otype = GPIO_OTYPE_PP;
	GPIO_InitStruct.PuPd = GPIO_PUPD_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF0;

	GPIO_Init(GPIOA, &GPIO_InitStruct);

}
