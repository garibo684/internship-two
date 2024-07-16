################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../myDrivers/Src/EXTI.c \
../myDrivers/Src/GPIO.c \
../myDrivers/Src/PWR.c \
../myDrivers/Src/RCC.c \
../myDrivers/Src/SPI.c \
../myDrivers/Src/SYSTICK.c 

OBJS += \
./myDrivers/Src/EXTI.o \
./myDrivers/Src/GPIO.o \
./myDrivers/Src/PWR.o \
./myDrivers/Src/RCC.o \
./myDrivers/Src/SPI.o \
./myDrivers/Src/SYSTICK.o 

C_DEPS += \
./myDrivers/Src/EXTI.d \
./myDrivers/Src/GPIO.d \
./myDrivers/Src/PWR.d \
./myDrivers/Src/RCC.d \
./myDrivers/Src/SPI.d \
./myDrivers/Src/SYSTICK.d 


# Each subdirectory must supply rules for building sources it contributes
myDrivers/Src/%.o myDrivers/Src/%.su myDrivers/Src/%.cyclo: ../myDrivers/Src/%.c myDrivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32G0 -DNUCLEO_G031K8 -DSTM32G031K8Tx -c -I../Inc -I"C:/Users/oguzh/STM32CubeIDE/workspace_1.15.1/nucleo_learning/myDrivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"

clean: clean-myDrivers-2f-Src

clean-myDrivers-2f-Src:
	-$(RM) ./myDrivers/Src/EXTI.cyclo ./myDrivers/Src/EXTI.d ./myDrivers/Src/EXTI.o ./myDrivers/Src/EXTI.su ./myDrivers/Src/GPIO.cyclo ./myDrivers/Src/GPIO.d ./myDrivers/Src/GPIO.o ./myDrivers/Src/GPIO.su ./myDrivers/Src/PWR.cyclo ./myDrivers/Src/PWR.d ./myDrivers/Src/PWR.o ./myDrivers/Src/PWR.su ./myDrivers/Src/RCC.cyclo ./myDrivers/Src/RCC.d ./myDrivers/Src/RCC.o ./myDrivers/Src/RCC.su ./myDrivers/Src/SPI.cyclo ./myDrivers/Src/SPI.d ./myDrivers/Src/SPI.o ./myDrivers/Src/SPI.su ./myDrivers/Src/SYSTICK.cyclo ./myDrivers/Src/SYSTICK.d ./myDrivers/Src/SYSTICK.o ./myDrivers/Src/SYSTICK.su

.PHONY: clean-myDrivers-2f-Src

