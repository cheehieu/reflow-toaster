################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
usr/ADS1118.obj: ../usr/ADS1118.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti_5.5/ccsv5/tools/compiler/msp430_4.2.1/bin/cl430" -vmsp --abi=eabi -g --include_path="C:/ti_5.5/ccsv5/ccs_base/msp430/include" --include_path="C:/github/reflow-toaster/sbac121a/430BOOST-ADS1118-SFT/ADS1118_LaunchPad_CCS5.3/usr" --include_path="C:/ti_5.5/ccsv5/tools/compiler/msp430_4.2.1/include" --advice:power="all" --define=__MSP430G2553__ --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="usr/ADS1118.pp" --obj_directory="usr" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

usr/LCD_driver.obj: ../usr/LCD_driver.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti_5.5/ccsv5/tools/compiler/msp430_4.2.1/bin/cl430" -vmsp --abi=eabi -g --include_path="C:/ti_5.5/ccsv5/ccs_base/msp430/include" --include_path="C:/github/reflow-toaster/sbac121a/430BOOST-ADS1118-SFT/ADS1118_LaunchPad_CCS5.3/usr" --include_path="C:/ti_5.5/ccsv5/tools/compiler/msp430_4.2.1/include" --advice:power="all" --define=__MSP430G2553__ --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="usr/LCD_driver.pp" --obj_directory="usr" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

usr/UART_TxRx.obj: ../usr/UART_TxRx.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti_5.5/ccsv5/tools/compiler/msp430_4.2.1/bin/cl430" -vmsp --abi=eabi -g --include_path="C:/ti_5.5/ccsv5/ccs_base/msp430/include" --include_path="C:/github/reflow-toaster/sbac121a/430BOOST-ADS1118-SFT/ADS1118_LaunchPad_CCS5.3/usr" --include_path="C:/ti_5.5/ccsv5/tools/compiler/msp430_4.2.1/include" --advice:power="all" --define=__MSP430G2553__ --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="usr/UART_TxRx.pp" --obj_directory="usr" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


