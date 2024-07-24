#include "interface.h"

PlayerState audio_flag = PLAYER_OFF;
StateType_t first_flag = STATE_ON;
uint8_t rx_buffer = Default;
uint8_t var = 0;
uint8_t test_count = 49;
float freq_out = 1000.0;



void PlayerInterface(UART_HandleTypeDef *huart, I2S_HandleTypeDef hi2s)
{


	uint8_t askFreq[] = "\n Choose the frequency value.\n\n\r 1- 100 Hz \n\r 2- 500Hz \n\r 3- 1 kHz \n\r 4- 1.5 kHz \n\r 5- 2 kHz \n\r 6- 5kHz \n\r 7- 7.5 kHz \n\r 8- 10 kHz\n\n\r";
	uint8_t repeat[] = "\n\n\n\r Actions \n\n\r 1- Play/Pause the sound \n\r 2- Change Frequency \n\r ";

		if( !first_flag )
		{
			HAL_UART_Receive(huart, &rx_buffer, sizeof(rx_buffer), HAL_MAX_DELAY);
			HAL_Delay(100);
		}

		switch(rx_buffer){

		case Option_1:

			// Pause-Play Audio
			AudioToggle();

			if( audio_flag )
			{
				uint8_t turn_off[] = "\n\n\r Audio Paused \n\n\r";
				HAL_UART_Transmit(huart, turn_off, sizeof(turn_off), 500);
				audio_flag = PLAYER_OFF;
			}
			else
			{
				uint8_t turn_on[] = "\n\n\r Audio Playing \n\n\r";
				HAL_UART_Transmit(huart, turn_on, sizeof(turn_on), 500);
				audio_flag = PLAYER_ON;
			}

			var = 0;
			rx_buffer = Default;

			break;

		case Option_2:

			HAL_UART_Transmit(huart, askFreq, sizeof(askFreq), 500);

			HAL_UART_Receive(huart, &var, sizeof(var), HAL_MAX_DELAY);
			HAL_Delay(100);

			// Set and Play new frequency
			switch(var)
			{
				case Freq_100Hz:
					freq_out = 100.0;
					AudioPlay(hi2s, freq_out);
					break;

				case Freq_500Hz:
					freq_out = 500.0;
					AudioPlay(hi2s, freq_out);
					break;

				case Freq_1000Hz:
					freq_out = 1000.0;
					AudioPlay(hi2s, freq_out);
					break;

				case Freq_1500Hz:
					freq_out = 1500.0;
					AudioPlay(hi2s, freq_out);
					break;

				case Freq_2000Hz:
					freq_out = 2000.0;
					AudioPlay(hi2s, freq_out);
					break;

				case Freq_5000Hz:
					freq_out = 5000.0;
					AudioPlay(hi2s, freq_out);
					break;

				case Freq_7500Hz:
					freq_out = 7500.0;
					AudioPlay(hi2s, freq_out);
					break;

				case Freq_10kHz:
					freq_out = 10000.0;
					AudioPlay(hi2s, freq_out);
					break;

				default:
					uint8_t error[] = "\n\n\n\r Error: Incorrect Input.\n\n\r Please Choose from the given options. ";
					HAL_UART_Transmit(huart, error, sizeof(error), 500);
					break;
			}

			HAL_UART_Transmit(huart, repeat, sizeof(repeat), 500);

			var = 0;
			rx_buffer = Default;

			audio_flag = STATE_ON;
			first_flag = STATE_OFF;
			test_count++;
			if(test_count >= 57){ test_count = 49; }

			break;

		default:
			HAL_UART_Transmit(huart, repeat, sizeof(repeat), 500);

			var = 0;
			rx_buffer = Default;

			break;
		}
}


void InterfaceInit(UART_HandleTypeDef *huart, I2S_HandleTypeDef hi2s, I2C_HandleTypeDef hi2c)
{

	uint8_t greeting[] = "\n\n\n\r Audio Generator\n\n\r A sound with the selected frequency will play. \n\n\r ";
	HAL_UART_Transmit(huart, greeting, sizeof(greeting), 500);

	// Directly Get and Play frequency without showing action options
	rx_buffer = 50;

	PlayerInit(hi2c);

	PlayerInterface(huart, hi2s);

}
