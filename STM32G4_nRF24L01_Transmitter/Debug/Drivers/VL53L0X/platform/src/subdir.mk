################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/VL53L0X/platform/src/vl53l0x_platform.c 

OBJS += \
./Drivers/VL53L0X/platform/src/vl53l0x_platform.o 

C_DEPS += \
./Drivers/VL53L0X/platform/src/vl53l0x_platform.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/VL53L0X/platform/src/%.o: ../Drivers/VL53L0X/platform/src/%.c Drivers/VL53L0X/platform/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/VL53L0X/core/inc -I../Drivers/VL53L0X/platform/inc -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-VL53L0X-2f-platform-2f-src

clean-Drivers-2f-VL53L0X-2f-platform-2f-src:
	-$(RM) ./Drivers/VL53L0X/platform/src/vl53l0x_platform.d ./Drivers/VL53L0X/platform/src/vl53l0x_platform.o

.PHONY: clean-Drivers-2f-VL53L0X-2f-platform-2f-src

