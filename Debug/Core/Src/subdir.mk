################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/font_Arial.c \
../Core/Src/font_Times_New_Roman.c \
../Core/Src/fonts.c \
../Core/Src/main.c \
../Core/Src/menu.c \
../Core/Src/menu1.c \
../Core/Src/ssd_1309.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c 

OBJS += \
./Core/Src/font_Arial.o \
./Core/Src/font_Times_New_Roman.o \
./Core/Src/fonts.o \
./Core/Src/main.o \
./Core/Src/menu.o \
./Core/Src/menu1.o \
./Core/Src/ssd_1309.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o 

C_DEPS += \
./Core/Src/font_Arial.d \
./Core/Src/font_Times_New_Roman.d \
./Core/Src/fonts.d \
./Core/Src/main.d \
./Core/Src/menu.d \
./Core/Src/menu1.d \
./Core/Src/ssd_1309.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"C:/Users/sovetnikov/Downloads/GNU MCU Eclipse/ARM Embedded GCC/8.2.1-1.4-20190214-0604/arm-none-eabi/include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/sovetnikov/STM32CubeIDE/workspace_1.8.0/OLED_ssd1309/MY_LIS3DSH" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/font_Arial.d ./Core/Src/font_Arial.o ./Core/Src/font_Times_New_Roman.d ./Core/Src/font_Times_New_Roman.o ./Core/Src/fonts.d ./Core/Src/fonts.o ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/menu.d ./Core/Src/menu.o ./Core/Src/menu1.d ./Core/Src/menu1.o ./Core/Src/ssd_1309.d ./Core/Src/ssd_1309.o ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o

.PHONY: clean-Core-2f-Src

