################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
LcdDriver/%.obj: ../LcdDriver/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/Applications/ti/ccs901/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/du/ti/simplelink_msp432p4_sdk_3_10_00_08/source" --include_path="/Users/sebastianblanco/Downloads/LabFinalDunia" --include_path="/Users/sebastianblanco/ti/simplelink_msp432p4_sdk_3_10_00_08/source" --include_path="/Users/sebastianblanco/ti/simplelink_msp432p4_sdk_3_10_00_08/source/third_party/CMSIS/Include" --include_path="/Applications/ti/ccs901/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --preinclude="/Users/sebastianblanco/Downloads/LabFinalDunia/main.hpp" --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --rtti --cpp_default --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="LcdDriver/$(basename $(<F)).d_raw" --obj_directory="LcdDriver" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


