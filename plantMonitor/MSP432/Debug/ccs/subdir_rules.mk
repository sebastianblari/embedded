################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
ccs/startup_msp432p401r_ccs.obj: ../ccs/startup_msp432p401r_ccs.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/laura/ti/ccs901/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/du/ti/simplelink_msp432p4_sdk_3_10_00_08/source" --include_path="/home/laura/Documents/Sistemas_Incrustados/Source_gitSebas/plantMonitor" --include_path="/home/laura/ti/simplelink_msp432p4_sdk_3_10_00_08/source" --include_path="/home/laura/ti/simplelink_msp432p4_sdk_3_10_00_08/source/third_party/CMSIS/Include" --include_path="/home/laura/ti/ccs901/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --preinclude="/home/laura/Documents/Sistemas_Incrustados/Source_gitSebas/plantMonitor/main.hpp" --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="ccs/$(basename $(<F)).d_raw" --obj_directory="ccs" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


