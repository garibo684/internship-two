#ifndef INC_INTERFACE_H_
#define INC_INTERFACE_H_

#include "audio_player.h"

typedef enum
{
	Default  = 48,
	Option_1 = 49,
	Option_2 = 50,
	Option_3 = 51,
	Option_4 = 52,
	Option_5 = 53,
	Option_6 = 54,
	Option_7 = 55,
	Option_8 = 56,


}OptionsType_t;

typedef enum
{
	Default_1kHz  = 48,
	Freq_100Hz = 49,
	Freq_500Hz = 50,
	Freq_1000Hz = 51,
	Freq_1500Hz = 52,
	Freq_2000Hz = 53,
	Freq_5000Hz = 54,
	Freq_7500Hz = 55,
	Freq_10kHz = 56,

}FreqOptions;

typedef enum
{
	STATE_ON  = 1,
	STATE_OFF = 0,

}StateType_t;

typedef enum
{

	ASCII_Char_Enter = 13,
	ASCII_Char_Space = 32,
	ASCII_Char_0 = 48,
	ASCII_Char_1 = 49,
	ASCII_Char_2 = 50,
	ASCII_Char_3 = 51,
	ASCII_Char_4 = 52,
	ASCII_Char_5 = 53,
	ASCII_Char_6 = 54,
	ASCII_Char_7 = 55,
	ASCII_Char_8 = 56,
	ASCII_Char_9 = 57,

}ASCII_ChartoDecimalNumbers;


void PlayerInterface(UART_HandleTypeDef *huart, I2S_HandleTypeDef hi2s);
void InterfaceInit(UART_HandleTypeDef *huart, I2S_HandleTypeDef hi2s, I2C_HandleTypeDef hi2c);


#endif /* INC_INTERFACE_H_ */
