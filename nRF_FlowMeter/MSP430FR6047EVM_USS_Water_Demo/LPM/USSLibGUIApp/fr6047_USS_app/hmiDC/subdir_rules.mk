################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
USSLibGUIApp/fr6047_USS_app/hmiDC/hmi.obj: C:/ti/msp/UltrasonicWaterFR604x_02_40_00_00/examples/USS_Water_Demo/USSLibGUIApp/fr6047_USS_app/hmiDC/hmi.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/bin/cl430" -vmspx --code_model=large --data_model=large -O3 --use_hw_mpy=F5 --include_path="C:/ti/ccs1250/ccs/ccs_base/msp430/include" --include_path="C:/Users/adhil/OneDrive/Desktop/Train/test3/nrf52-sensors/nRF_FlowMeter/MSP430FR6047EVM_USS_Water_Demo" --include_path="C:/ti/msp/UltrasonicWaterFR604x_02_40_00_00/examples/USS_Water_Demo/" --include_path="C:/ti/msp/UltrasonicWaterFR604x_02_40_00_00/examples/USS_Water_Demo/USSLibGUIApp/fr6047_USS_app" --include_path="C:/ti/msp/UltrasonicWaterFR604x_02_40_00_00/examples/USS_Water_Demo/USS_Config" --include_path="C:/ti/msp/UltrasonicWaterFR604x_02_40_00_00/include/" --include_path="C:/ti/msp/UltrasonicWaterFR604x_02_40_00_00/lib/USS/source/USS_HAL" --include_path="C:/ti/msp/UltrasonicWaterFR604x_02_40_00_00/lib/USS/source" --include_path="C:/ti/msp/UltrasonicWaterFR604x_02_40_00_00/examples/common/hal/fr6047EVM" --include_path="C:/ti/msp/UltrasonicWaterFR604x_02_40_00_00/examples/common/DesignCenter/comm" --include_path="C:/ti/msp/UltrasonicWaterFR604x_02_40_00_00/examples/common/DesignCenter/ussDC" --include_path="C:/ti/msp/UltrasonicWaterFR604x_02_40_00_00/examples/common/gui" --include_path="C:/ti/msp/UltrasonicWaterFR604x_02_40_00_00/driverlib/MSP430FR5xx_6xx" --include_path="C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/include" --advice:power="none" --advice:hw_config=all --define=__MSP430FR6047__ --define=__WATCHDOG_ENABLE__ --define=__EVM430_ID__=0x47 --define=__SVSH_ENABLE__ --define=xDEBUG_CLOCK_CORRECTION --define=__ENABLE_LPM__ --define=__EVM430_VER__=0x20 --define=__EXTRA_VERSION__=0x00,0x00 --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="USSLibGUIApp/fr6047_USS_app/hmiDC/$(basename $(<F)).d_raw" --obj_directory="USSLibGUIApp/fr6047_USS_app/hmiDC" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


