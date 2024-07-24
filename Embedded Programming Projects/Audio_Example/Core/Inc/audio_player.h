#ifndef INC_AUDIO_PLAYER_H_
#define INC_AUDIO_PLAYER_H_

#include "MY_CS43L22.h"
#include "main.h"
#include <math.h>


#define PI 3.14159f
#define F_SAMPLE	48000.0f

typedef enum
{
	PLAYER_ON = 1,
	PLAYER_OFF = 0,

}PlayerState;


void PlayerInit(I2C_HandleTypeDef hi2c);
void AudioPlay(I2S_HandleTypeDef hi2s, float freq);
void AudioToggle();


#endif /* INC_AUDIO_PLAYER_H_ */
