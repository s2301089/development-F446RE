################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/20250305_v1/STprintf.c 

OBJS += \
./Core/Inc/20250305_v1/STprintf.o 

C_DEPS += \
./Core/Inc/20250305_v1/STprintf.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/20250305_v1/%.o Core/Inc/20250305_v1/%.su Core/Inc/20250305_v1/%.cyclo: ../Core/Inc/20250305_v1/%.c Core/Inc/20250305_v1/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Inc-2f-20250305_v1

clean-Core-2f-Inc-2f-20250305_v1:
	-$(RM) ./Core/Inc/20250305_v1/STprintf.cyclo ./Core/Inc/20250305_v1/STprintf.d ./Core/Inc/20250305_v1/STprintf.o ./Core/Inc/20250305_v1/STprintf.su

.PHONY: clean-Core-2f-Inc-2f-20250305_v1

