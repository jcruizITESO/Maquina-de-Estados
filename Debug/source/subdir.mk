################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Maquina_Estados.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/Maquina_Estados.d \
./source/semihost_hardfault.d 

OBJS += \
./source/Maquina_Estados.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DFRDM_K64F -DFREEDOM -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\jcro_\Documents\MCUXpressoIDE_11.6.0_8187\workspace\frdmk64f_Maquina_Estados\source" -I"C:\Users\jcro_\Documents\MCUXpressoIDE_11.6.0_8187\workspace\frdmk64f_Maquina_Estados\utilities" -I"C:\Users\jcro_\Documents\MCUXpressoIDE_11.6.0_8187\workspace\frdmk64f_Maquina_Estados\drivers" -I"C:\Users\jcro_\Documents\MCUXpressoIDE_11.6.0_8187\workspace\frdmk64f_Maquina_Estados\device" -I"C:\Users\jcro_\Documents\MCUXpressoIDE_11.6.0_8187\workspace\frdmk64f_Maquina_Estados\component\uart" -I"C:\Users\jcro_\Documents\MCUXpressoIDE_11.6.0_8187\workspace\frdmk64f_Maquina_Estados\component\lists" -I"C:\Users\jcro_\Documents\MCUXpressoIDE_11.6.0_8187\workspace\frdmk64f_Maquina_Estados\CMSIS" -I"C:\Users\jcro_\Documents\MCUXpressoIDE_11.6.0_8187\workspace\frdmk64f_Maquina_Estados\board" -I"C:\Users\jcro_\Documents\MCUXpressoIDE_11.6.0_8187\workspace\frdmk64f_Maquina_Estados\frdmk64f\driver_examples\gpio\input_interrupt" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/Maquina_Estados.d ./source/Maquina_Estados.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source

