################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/API/Src/boardConfig.c \
../Drivers/API/Src/max7219.c \
../Drivers/API/Src/max7219_port_stm32.c 

OBJS += \
./Drivers/API/Src/boardConfig.o \
./Drivers/API/Src/max7219.o \
./Drivers/API/Src/max7219_port_stm32.o 

C_DEPS += \
./Drivers/API/Src/boardConfig.d \
./Drivers/API/Src/max7219.d \
./Drivers/API/Src/max7219_port_stm32.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/API/Src/%.o Drivers/API/Src/%.su Drivers/API/Src/%.cyclo: ../Drivers/API/Src/%.c Drivers/API/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/agustin/Desktop/CESE 25/NucleoShield Arcade V01/NucleoShield Arcade/Drivers/API/Src" -I"/home/agustin/Desktop/CESE 25/NucleoShield Arcade V01/NucleoShield Arcade/Drivers/API/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-API-2f-Src

clean-Drivers-2f-API-2f-Src:
	-$(RM) ./Drivers/API/Src/boardConfig.cyclo ./Drivers/API/Src/boardConfig.d ./Drivers/API/Src/boardConfig.o ./Drivers/API/Src/boardConfig.su ./Drivers/API/Src/max7219.cyclo ./Drivers/API/Src/max7219.d ./Drivers/API/Src/max7219.o ./Drivers/API/Src/max7219.su ./Drivers/API/Src/max7219_port_stm32.cyclo ./Drivers/API/Src/max7219_port_stm32.d ./Drivers/API/Src/max7219_port_stm32.o ./Drivers/API/Src/max7219_port_stm32.su

.PHONY: clean-Drivers-2f-API-2f-Src

