#include "accmeter_control.h"

SimStateType state = STATE_OFF;
LIS3DSH_DataScaled temp_data = {12.5,12.5,250.0};

float AbsFloat(float num)
{
	if(num < 0)
	{
		return (num * -1);
	}
	else
	{
		return num;
	}
}

void WriteData(UART_HandleTypeDef *huart, float data)
{
	SimStateType data_state = STATE_OFF;
	uint8_t temp_data;
	if( data < 0)
	{
		temp_data = (uint8_t)AbsFloat(data);
		data_state = STATE_ON;
	}
	else if( data < 1 && data > 1)
	{
		temp_data = 0;
	}
	else
	{
		temp_data = data;
	}
	uint8_t digit = 0;
	uint8_t temp = temp_data;

	while (temp)
	{
		// Increment number of digits
		digit++;

	   // Truncate the last
	   // digit from the number
	    temp /= 10;
	}
	if(digit == 0)
	{
		digit = 1;
		HAL_UART_Transmit(huart, (uint8_t *)"0", 1, 500);
		return;
	}

	uint8_t dataArray[digit];
    uint8_t count = digit - 1;
    while (temp_data)
    {
        // Separate last digit from
        // the number and add ASCII
        // value of character '0' is 48
        dataArray[count] = temp_data % 10 + 48;

        count--;
        // Truncate the last
        // digit from the number
        temp_data /= 10;
    }

    if(data_state)
    {
    	HAL_UART_Transmit(huart, (uint8_t *)"-", 1, 500);
    }
    for( uint8_t i = 0; i < sizeof(dataArray); i++)
    {
   		HAL_UART_Transmit(huart, &dataArray[i], 1, 500);
    }
}

void MeterInit(SPI_HandleTypeDef hspi)
{
	LIS3DSH_InitTypeDef accmeter;

	accmeter.dataRate = LIS3DSH_DATARATE_25;
	accmeter.fullScale = LIS3DSH_FULLSCALE_4;
	accmeter.antiAliasingBW = LIS3DSH_FILTER_BW_50;
	accmeter.enableAxes = LIS3DSH_XYZ_ENABLE;
	accmeter.interruptEnable = true;

	LIS3DSH_Init(&hspi, &accmeter);
}

LIS3DSH_DataScaled GetScaledData()
{
	LIS3DSH_DataScaled ret;
	if( LIS3DSH_PollDRDY(1000) == true )
	{
		ret = LIS3DSH_GetDataScaled();
	}
	return ret;
}

void MeterCalibrate()
{
		LIS3DSH_X_calibrate(-242.5, 237.5);
		LIS3DSH_Y_calibrate(-251.25, 247.5);
		LIS3DSH_Z_calibrate(-247.5, 241.25);
}

void SimulatorLedControl(LIS3DSH_DataScaled meter_data)
{
	if(state == STATE_ON)
	{
		if( meter_data.x > -150 && meter_data.x <= -50 )
		{
			HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
		}
		else if( meter_data.x < 150 && meter_data.x >= 50 )
		{
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
		}
		else if( meter_data.y > -150 && meter_data.y <= -50 )
		{
			HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET);
		}
		else if( meter_data.y < 150 && meter_data.y >= 50 )
		{
			HAL_GPIO_WritePin(LED_ORANGE_GPIO_Port, LED_ORANGE_Pin, GPIO_PIN_SET);
		}
		else
		{
			HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED_ORANGE_GPIO_Port, LED_ORANGE_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);
		}
	}

	if(state == STATE_WARNING)
	{
		if( meter_data.x <= -150 )
		{
			LedBlinkFast(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
			HAL_Delay(50);
		}
		else if( meter_data.x >= 150 )
		{
			LedBlinkFast(LED_RED_GPIO_Port, LED_RED_Pin);
			HAL_Delay(50);
		}
		else if( meter_data.y <= -150 )
		{
			LedBlinkFast(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
			HAL_Delay(50);
		}
		else if( meter_data.y >= 150 )
		{
			LedBlinkFast(LED_ORANGE_GPIO_Port, LED_ORANGE_Pin);
			HAL_Delay(50);
		}
		else
		{
			LedBlinkFast(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
			LedBlinkFast(LED_ORANGE_GPIO_Port, LED_ORANGE_Pin);
			LedBlinkFast(LED_RED_GPIO_Port, LED_RED_Pin);
			LedBlinkFast(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
			HAL_Delay(50);
		}

	}


	if(state == STATE_ERROR)
	{
		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED_ORANGE_GPIO_Port, LED_ORANGE_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);

		HAL_Delay(250);

		for(uint8_t i = 0; i<5; i++)
		{
			LedBlinkFast(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
			LedBlinkFast(LED_ORANGE_GPIO_Port, LED_ORANGE_Pin);
			LedBlinkFast(LED_RED_GPIO_Port, LED_RED_Pin);
			LedBlinkFast(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
			HAL_Delay(50);
		}

		state = STATE_OFF;
	}

	if(state == STATE_OFF)
	{
		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED_ORANGE_GPIO_Port, LED_ORANGE_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);
	}


}

SimStateType Simulator(UART_HandleTypeDef huart, LIS3DSH_DataScaled meter_data)
{
	LIS3DSH_DataScaled diff_data;

	if(state)
	{
		if( (meter_data.x >= 205 || meter_data.x <= -205) || (meter_data.y >= 205 || meter_data.y <= -205) || meter_data.z <= 25 )
		{
			uint8_t crash[] = "\n\n\r ERROR: The angle is too steep. Simulation is over.";
			HAL_UART_Transmit(&huart, crash, sizeof(crash), 500);

			 state = STATE_ERROR;
			 SimulatorLedControl(meter_data);

			 return STATE_OFF;
		}

		diff_data.x = (meter_data.x - temp_data.x);
		diff_data.y = (meter_data.y - temp_data.y);
		diff_data.z = (meter_data.z - temp_data.z);

		if( AbsFloat(diff_data.x) > 50 || AbsFloat(diff_data.y) > 50 || AbsFloat(diff_data.z) > 50 )
		{
			uint8_t warning_change[] = "\n\n\r WARNING: Sudden change in the tilt angle.\n\r Do not change the tilt angle too suddenly.";
			HAL_UART_Transmit(&huart, warning_change, sizeof(warning_change), 500);

			state = STATE_WARNING;
			  SimulatorLedControl(meter_data);
			HAL_Delay(700);

		}
		else if( (meter_data.x >= 150 || meter_data.x <= -150) || (meter_data.y >= 150 || meter_data.y <= -150) || meter_data.z <= 100 )
		{
			uint8_t warning_zone[] = "\n\n\r WARNING: The tilt angle is dangerously steep. Lower the tilt angle.";
			HAL_UART_Transmit(&huart, warning_zone, sizeof(warning_zone), 500);

			state = STATE_WARNING;
			  SimulatorLedControl(meter_data);
			HAL_Delay(500);


		}
		else
		{
			state = STATE_ON;
			  SimulatorLedControl(meter_data);
		}

		HAL_UART_Transmit(&huart, (uint8_t *)"\n\r   X = ", 11, 500);
		WriteData(&huart, meter_data.x);
		HAL_UART_Transmit(&huart, (uint8_t *)"   Y = ", 7, 500);
		WriteData(&huart, meter_data.y);
		HAL_UART_Transmit(&huart, (uint8_t *)"   Z = ", 7, 500);
		WriteData(&huart, meter_data.z);
		HAL_Delay(500);

		temp_data = meter_data;
		  SimulatorLedControl(meter_data);
		return STATE_ON;
	}
	return STATE_OFF;

}

void StartSimulator(UART_HandleTypeDef huart)
{

	state = STATE_ON;

		LedBlink(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
		LedBlink(LED_ORANGE_GPIO_Port, LED_ORANGE_Pin);
		LedBlink(LED_RED_GPIO_Port, LED_RED_Pin);
		LedBlink(LED_BLUE_GPIO_Port, LED_BLUE_Pin);

		LedBlinkMid(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
		LedBlinkMid(LED_ORANGE_GPIO_Port, LED_ORANGE_Pin);
		LedBlinkMid(LED_RED_GPIO_Port, LED_RED_Pin);
		LedBlinkMid(LED_BLUE_GPIO_Port, LED_BLUE_Pin);

	uint8_t start[] = "\n\n\n\rSimulator Started\n\n\r If the tilt angle is too steep the simulation will be over.\n\n\r";
	HAL_UART_Transmit(&huart, start, sizeof(start), 500);


}

void ResetSimulator(UART_HandleTypeDef huart, SimStateType sim_state)
{
	if(sim_state == STATE_OFF)
	{
		uint8_t ask_reset[] = "\n\n\r To restart the simulator press SPACE";
		HAL_UART_Transmit(&huart, ask_reset, sizeof(ask_reset), 500);

		uint8_t reset_var = 0;
		HAL_UART_Receive(&huart, &reset_var, 1, HAL_MAX_DELAY);

		if( reset_var == 32)
		{
			StartSimulator(huart);
		}
	}
}
