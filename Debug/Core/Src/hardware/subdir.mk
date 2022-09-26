################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/hardware/button.c \
../Core/Src/hardware/led.c \
../Core/Src/hardware/uart.c 

OBJS += \
./Core/Src/hardware/button.o \
./Core/Src/hardware/led.o \
./Core/Src/hardware/uart.o 

C_DEPS += \
./Core/Src/hardware/button.d \
./Core/Src/hardware/led.d \
./Core/Src/hardware/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/hardware/%.o Core/Src/hardware/%.su: ../Core/Src/hardware/%.c Core/Src/hardware/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F427xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-hardware

clean-Core-2f-Src-2f-hardware:
	-$(RM) ./Core/Src/hardware/button.d ./Core/Src/hardware/button.o ./Core/Src/hardware/button.su ./Core/Src/hardware/led.d ./Core/Src/hardware/led.o ./Core/Src/hardware/led.su ./Core/Src/hardware/uart.d ./Core/Src/hardware/uart.o ./Core/Src/hardware/uart.su

.PHONY: clean-Core-2f-Src-2f-hardware

