#ifndef INC_ACCMETER_CONTROL_H_
#define INC_ACCMETER_CONTROL_H_

#include "led.h"
#include "MY_LIS3DSH.h"

typedef enum
{
	STATE_OFF = 0,
	STATE_ON = 1,
	STATE_RESET = 2,
	STATE_WARNING = 3,
	STATE_ERROR = 4,

}SimStateType;


void MeterInit(SPI_HandleTypeDef hspi);
LIS3DSH_DataScaled GetScaledData();
void MeterCalibrate();
SimStateType Simulator(UART_HandleTypeDef huart, LIS3DSH_DataScaled meter_data);
void StartSimulator(UART_HandleTypeDef huart);
void ResetSimulator(UART_HandleTypeDef huart, SimStateType sim_state);
void SimulatorLedControl(LIS3DSH_DataScaled meter_data);
float AbsFloat(float num);
void WriteData(UART_HandleTypeDef *huart, float data);


#endif /* INC_ACCMETER_CONTROL_H_ */
