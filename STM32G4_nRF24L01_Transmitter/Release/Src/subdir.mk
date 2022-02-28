################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/gpio.c \
../Src/i2c.c \
../Src/main.c \
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
../Src/usbd_desc.c 

OBJS += \
./Src/gpio.o \
./Src/i2c.o \
./Src/main.o \
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
./Src/usbd_desc.o 

C_DEPS += \
./Src/gpio.d \
./Src/i2c.d \
./Src/main.d \
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
./Src/usbd_desc.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/gpio.d ./Src/gpio.o ./Src/i2c.d ./Src/i2c.o ./Src/main.d ./Src/main.o ./Src/spi.d ./Src/spi.o ./Src/stm32g4xx_hal_msp.d ./Src/stm32g4xx_hal_msp.o ./Src/stm32g4xx_it.d ./Src/stm32g4xx_it.o ./Src/syscalls.d ./Src/syscalls.o ./Src/sysmem.d ./Src/sysmem.o ./Src/system_stm32g4xx.d ./Src/system_stm32g4xx.o ./Src/tim.d ./Src/tim.o ./Src/usb_device.d ./Src/usb_device.o ./Src/usbd_cdc_if.d ./Src/usbd_cdc_if.o ./Src/usbd_conf.d ./Src/usbd_conf.o ./Src/usbd_desc.d ./Src/usbd_desc.o

.PHONY: clean-Src

