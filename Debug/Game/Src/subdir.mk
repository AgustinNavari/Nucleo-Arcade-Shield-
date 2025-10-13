################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Game/Src/game.c \
../Game/Src/snake.c 

OBJS += \
./Game/Src/game.o \
./Game/Src/snake.o 

C_DEPS += \
./Game/Src/game.d \
./Game/Src/snake.d 


# Each subdirectory must supply rules for building sources it contributes
Game/Src/%.o Game/Src/%.su Game/Src/%.cyclo: ../Game/Src/%.c Game/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/agustin/Desktop/CESE 25/NucleoShield Arcade V01/NucleoShield Arcade/Drivers/API/Src" -I"/home/agustin/Desktop/CESE 25/NucleoShield Arcade V01/NucleoShield Arcade/Drivers/API/Inc" -I"/home/agustin/Desktop/CESE 25/NucleoShield Arcade V01/NucleoShield Arcade/Game" -I"/home/agustin/Desktop/CESE 25/NucleoShield Arcade V01/NucleoShield Arcade/Game/Inc" -I"/home/agustin/Desktop/CESE 25/NucleoShield Arcade V01/NucleoShield Arcade/Game/Src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Game-2f-Src

clean-Game-2f-Src:
	-$(RM) ./Game/Src/game.cyclo ./Game/Src/game.d ./Game/Src/game.o ./Game/Src/game.su ./Game/Src/snake.cyclo ./Game/Src/snake.d ./Game/Src/snake.o ./Game/Src/snake.su

.PHONY: clean-Game-2f-Src

