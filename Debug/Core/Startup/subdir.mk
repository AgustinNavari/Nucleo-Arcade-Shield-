################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f446retx.s 

OBJS += \
./Core/Startup/startup_stm32f446retx.o 

S_DEPS += \
./Core/Startup/startup_stm32f446retx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"/home/agustin/Desktop/CESE 25/NucleoShield Arcade V01/NucleoShield Arcade/Drivers/API/Src" -I"/home/agustin/Desktop/CESE 25/NucleoShield Arcade V01/NucleoShield Arcade/Drivers/API/Inc" -I"/home/agustin/Desktop/CESE 25/NucleoShield Arcade V01/NucleoShield Arcade/Game" -I"/home/agustin/Desktop/CESE 25/NucleoShield Arcade V01/NucleoShield Arcade/Game/Inc" -I"/home/agustin/Desktop/CESE 25/NucleoShield Arcade V01/NucleoShield Arcade/Game/Src" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32f446retx.d ./Core/Startup/startup_stm32f446retx.o

.PHONY: clean-Core-2f-Startup

