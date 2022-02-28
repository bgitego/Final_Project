################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/console.c \
../Src/consoleCommands.c \
../Src/consoleIo.c \
../Src/gpio.c \
../Src/i2c.c \
../Src/main.c \
../Src/nrf24l01.c \
../Src/spi.c \
../Src/stm32g4xx_hal_msp.c \
../Src/stm32g4xx_it.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_stm32g4xx.c \
../Src/tim.c \
../Src/usb_device.c \
../Src/usbd_cdc_if.c \
../Src/usbd_conf.c \
../Src/usbd_desc.c \
../Src/user_algorithm.c \
../Src/user_delays.c \
../Src/user_main.c \
../Src/user_nrf24l01.c \
../Src/user_retarget.c \
../Src/user_spi.c \
../Src/user_statemachine.c \
../Src/user_vl53l0x.c 

OBJS += \
./Src/console.o \
./Src/consoleCommands.o \
./Src/consoleIo.o \
./Src/gpio.o \
./Src/i2c.o \
./Src/main.o \
./Src/nrf24l01.o \
./Src/spi.o \
./Src/stm32g4xx_hal_msp.o \
./Src/stm32g4xx_it.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_stm32g4xx.o \
./Src/tim.o \
./Src/usb_device.o \
./Src/usbd_cdc_if.o \
./Src/usbd_conf.o \
./Src/usbd_desc.o \
./Src/user_algorithm.o \
./Src/user_delays.o \
./Src/user_main.o \
./Src/user_nrf24l01.o \
./Src/user_retarget.o \
./Src/user_spi.o \
./Src/user_statemachine.o \
./Src/user_vl53l0x.o 

C_DEPS += \
./Src/console.d \
./Src/consoleCommands.d \
./Src/consoleIo.d \
./Src/gpio.d \
./Src/i2c.d \
./Src/main.d \
./Src/nrf24l01.d \
./Src/spi.d \
./Src/stm32g4xx_hal_msp.d \
./Src/stm32g4xx_it.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32g4xx.d \
./Src/tim.d \
./Src/usb_device.d \
./Src/usbd_cdc_if.d \
./Src/usbd_conf.d \
./Src/usbd_desc.d \
./Src/user_algorithm.d \
./Src/user_delays.d \
./Src/user_main.d \
./Src/user_nrf24l01.d \
./Src/user_retarget.d \
./Src/user_spi.d \
./Src/user_statemachine.d \
./Src/user_vl53l0x.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/VL53L0X/core/inc -I../Drivers/VL53L0X/platform/inc -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/console.d ./Src/console.o ./Src/consoleCommands.d ./Src/consoleCommands.o ./Src/consoleIo.d ./Src/consoleIo.o ./Src/gpio.d ./Src/gpio.o ./Src/i2c.d ./Src/i2c.o ./Src/main.d ./Src/main.o ./Src/nrf24l01.d ./Src/nrf24l01.o ./Src/spi.d ./Src/spi.o ./Src/stm32g4xx_hal_msp.d ./Src/stm32g4xx_hal_msp.o ./Src/stm32g4xx_it.d ./Src/stm32g4xx_it.o ./Src/syscalls.d ./Src/syscalls.o ./Src/sysmem.d ./Src/sysmem.o ./Src/system_stm32g4xx.d ./Src/system_stm32g4xx.o ./Src/tim.d ./Src/tim.o ./Src/usb_device.d ./Src/usb_device.o ./Src/usbd_cdc_if.d ./Src/usbd_cdc_if.o ./Src/usbd_conf.d ./Src/usbd_conf.o ./Src/usbd_desc.d ./Src/usbd_desc.o ./Src/user_algorithm.d ./Src/user_algorithm.o ./Src/user_delays.d ./Src/user_delays.o ./Src/user_main.d ./Src/user_main.o ./Src/user_nrf24l01.d ./Src/user_nrf24l01.o ./Src/user_retarget.d ./Src/user_retarget.o ./Src/user_spi.d ./Src/user_spi.o ./Src/user_statemachine.d ./Src/user_statemachine.o ./Src/user_vl53l0x.d ./Src/user_vl53l0x.o

.PHONY: clean-Src

