#include "audio_player.h"

float mySinVal;
float sample_dt;
uint16_t sample_N;
uint16_t i_t;
uint32_t myDacVal;
int16_t dataI2S[1000];
PlayerState player_state = PLAYER_OFF;

void PlayerInit(I2C_HandleTypeDef hi2c)
{
// Initialize and Configure Audio Codec

	CS43_Init(hi2c, MODE_I2S);
	CS43_SetVolume(10); //0 - 100,
	CS43_Enable_RightLeft(CS43_RIGHT_LEFT);
	CS43_Start();
}


void AudioPlay(I2S_HandleTypeDef hi2s, float freq)
{
	player_state = PLAYER_ON;

	// Reset Signal
	HAL_I2S_DMAStop(&hi2s);
	AudioToggle();

	for(uint16_t i = 0; i < 1000; i++)
	{
		dataI2S[i] = 0;
	}

	// Set Sample Rates
	sample_dt = freq / F_SAMPLE;
	sample_N = F_SAMPLE / freq;

	// Set Signal
	for(uint16_t i=0; i<sample_N; i++)
	{
		mySinVal = sinf(i*2*PI*sample_dt);
		dataI2S[i*2] = (mySinVal )*8000;    //Right data (0 2 4 6 8 10 12)
		dataI2S[i*2 + 1] =(mySinVal )*8000; //Left data  (1 3 5 7 9 11 13)
	}

	// Send Signal as Audio
	HAL_I2S_Transmit_DMA(&hi2s, (uint16_t *)dataI2S, sample_N*2);
	AudioToggle();
}

void AudioToggle()
{
	if(player_state == PLAYER_OFF)
	{
		CS43_Start();
		player_state = PLAYER_ON;
	}
	else
	{
		CS43_Stop();
		player_state = PLAYER_OFF;
	}
}
