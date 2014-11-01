################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti_5.5/ccsv5/tools/compiler/msp430_4.2.1/bin/cl430" -vmsp --abi=eabi -g --include_path="C:/ti_5.5/ccsv5/ccs_base/msp430/include" --include_path="C:/github/reflow-toaster/sbac121a/430BOOST-ADS1118-SFT/ADS1118_LaunchPad_CCS5.3/usr" --include_path="C:/ti_5.5/ccsv5/tools/compiler/msp430_4.2.1/include" --advice:power="all" --define=__MSP430G2553__ --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/linker.cmd: ../main.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"C:/ti_5.5/xdctools_3_25_03_72/xs" --xdcpath="C:/ti_5.5/grace_2_20_01_12/packages;C:/ti_5.5/ccsv5/ccs_base;C:/ti_5.5/ccsv5/ccs_base/msp430/msp430ware_1_40_01_44/packages;" xdc.tools.configuro -o configPkg -t ti.targets.msp430.elf.MSP430 -p ti.platforms.msp430:MSP430G2553 -r debug -c "C:/ti_5.5/ccsv5/tools/compiler/msp430_4.2.1" --compileOptions "--symdebug:dwarf --optimize_with_debug" "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/compiler.opt: | configPkg/linker.cmd
configPkg/: | configPkg/linker.cmd


