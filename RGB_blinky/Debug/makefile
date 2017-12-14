################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
RGB_blinky.lss \

FLASH_IMAGE += \
RGB_blinky.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: RGB_blinky.elf secondary-outputs

# Tool invocations
RGB_blinky.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,RGB_blinky.map -mmcu=atmega328p -o "RGB_blinky.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

RGB_blinky.lss: RGB_blinky.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S RGB_blinky.elf  >"RGB_blinky.lss"
	@echo 'Finished building: $@'
	@echo ' '

RGB_blinky.hex: RGB_blinky.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex RGB_blinky.elf  "RGB_blinky.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: RGB_blinky.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p RGB_blinky.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) RGB_blinky.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
