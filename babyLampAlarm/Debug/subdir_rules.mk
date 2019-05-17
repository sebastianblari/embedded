################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/sebastianblari/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/sebastianblari/Downloads/Lab_01_v3" --include_path="/home/sebastianblari/ti/simplelink_msp432p4_sdk_3_10_00_08/source" --include_path="/home/sebastianblari/ti/simplelink_msp432p4_sdk_3_10_00_08/source/third_party/CMSIS/Include" --include_path="/home/sebastianblari/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --preinclude="/home/sebastianblari/Downloads/Lab_01_v3/main.hpp" --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --rtti --cpp_default --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.cpp $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/sebastianblari/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/sebastianblari/Downloads/Lab_01_v3" --include_path="/home/sebastianblari/ti/simplelink_msp432p4_sdk_3_10_00_08/source" --include_path="/home/sebastianblari/ti/simplelink_msp432p4_sdk_3_10_00_08/source/third_party/CMSIS/Include" --include_path="/home/sebastianblari/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --preinclude="/home/sebastianblari/Downloads/Lab_01_v3/main.hpp" --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --rtti --cpp_default --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --exceptions $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_msp432p401r_ccs.obj: ../startup_msp432p401r_ccs.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/sebastianblari/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/sebastianblari/Downloads/Lab_01_v3" --include_path="/home/sebastianblari/ti/simplelink_msp432p4_sdk_3_10_00_08/source" --include_path="/home/sebastianblari/ti/simplelink_msp432p4_sdk_3_10_00_08/source/third_party/CMSIS/Include" --include_path="/home/sebastianblari/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --preinclude="/home/sebastianblari/Downloads/Lab_01_v3/main.hpp" --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


