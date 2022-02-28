################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/VL53L0X/core/src/vl53l0x_api.c \
../Drivers/VL53L0X/core/src/vl53l0x_api_calibration.c \
../Drivers/VL53L0X/core/src/vl53l0x_api_core.c \
../Drivers/VL53L0X/core/src/vl53l0x_api_ranging.c \
../Drivers/VL53L0X/core/src/vl53l0x_api_strings.c 

OBJS += \
./Drivers/VL53L0X/core/src/vl53l0x_api.o \
./Drivers/VL53L0X/core/src/vl53l0x_api_calibration.o \
./Drivers/VL53L0X/core/src/vl53l0x_api_core.o \
./Drivers/VL53L0X/core/src/vl53l0x_api_ranging.o \
./Drivers/VL53L0X/core/src/vl53l0x_api_strings.o 

C_DEPS += \
./Drivers/VL53L0X/core/src/vl53l0x_api.d \
./Drivers/VL53L0X/core/src/vl53l0x_api_calibration.d \
./Drivers/VL53L0X/core/src/vl53l0x_api_core.d \
./Drivers/VL53L0X/core/src/vl53l0x_api_ranging.d \
./Drivers/VL53L0X/core/src/vl53l0x_api_strings.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/VL53L0X/core/src/%.o: ../Drivers/VL53L0X/core/src/%.c Drivers/VL53L0X/core/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/VL53L0X/core/inc -I../Drivers/VL53L0X/platform/inc -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-VL53L0X-2f-core-2f-src

clean-Drivers-2f-VL53L0X-2f-core-2f-src:
	-$(RM) ./Drivers/VL53L0X/core/src/vl53l0x_api.d ./Drivers/VL53L0X/core/src/vl53l0x_api.o ./Drivers/VL53L0X/core/src/vl53l0x_api_calibration.d ./Drivers/VL53L0X/core/src/vl53l0x_api_calibration.o ./Drivers/VL53L0X/core/src/vl53l0x_api_core.d ./Drivers/VL53L0X/core/src/vl53l0x_api_core.o ./Drivers/VL53L0X/core/src/vl53l0x_api_ranging.d ./Drivers/VL53L0X/core/src/vl53l0x_api_ranging.o ./Drivers/VL53L0X/core/src/vl53l0x_api_strings.d ./Drivers/VL53L0X/core/src/vl53l0x_api_strings.o

.PHONY: clean-Drivers-2f-VL53L0X-2f-core-2f-src

