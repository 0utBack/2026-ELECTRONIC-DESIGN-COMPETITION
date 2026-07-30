################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Arm Compiler - building file: "$<"'
	"C:/TI/ti_cgt_arm_llvm_4.0.2.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"D:/TiProject/2026-ELECTRONIC-DESIGN-COMPETITION" -I"D:/TiProject/2026-ELECTRONIC-DESIGN-COMPETITION/Control" -I"D:/TiProject/2026-ELECTRONIC-DESIGN-COMPETITION/Sensor" -I"D:/TiProject/2026-ELECTRONIC-DESIGN-COMPETITION/GYRO" -I"D:/TiProject/2026-ELECTRONIC-DESIGN-COMPETITION/Encoder" -I"D:/TiProject/2026-ELECTRONIC-DESIGN-COMPETITION/sys" -I"D:/TiProject/2026-ELECTRONIC-DESIGN-COMPETITION/Debug" -I"C:/TI/mspm0_sdk_2_10_00_04/source/third_party/CMSIS/Core/Include" -I"C:/TI/mspm0_sdk_2_10_00_04/source" -I"D:/TiProject/2024-Electronic-Design-Competition-master/MPU6050" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1770700588: ../main.syscfg
	@echo 'SysConfig - building file: "$<"'
	"C:/TI/sysconfig_1.26.2/sysconfig_cli.bat" -s "C:/TI/mspm0_sdk_2_10_00_04/.metadata/product.json" --script "D:/TiProject/2026-ELECTRONIC-DESIGN-COMPETITION/main.syscfg" -o "." --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

device_linker.cmd: build-1770700588 ../main.syscfg
device.opt: build-1770700588
device.cmd.genlibs: build-1770700588
ti_msp_dl_config.c: build-1770700588
ti_msp_dl_config.h: build-1770700588
Event.dot: build-1770700588

%.o: ./%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Arm Compiler - building file: "$<"'
	"C:/TI/ti_cgt_arm_llvm_4.0.2.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"D:/TiProject/2026-ELECTRONIC-DESIGN-COMPETITION" -I"D:/TiProject/2026-ELECTRONIC-DESIGN-COMPETITION/Control" -I"D:/TiProject/2026-ELECTRONIC-DESIGN-COMPETITION/Sensor" -I"D:/TiProject/2026-ELECTRONIC-DESIGN-COMPETITION/GYRO" -I"D:/TiProject/2026-ELECTRONIC-DESIGN-COMPETITION/Encoder" -I"D:/TiProject/2026-ELECTRONIC-DESIGN-COMPETITION/sys" -I"D:/TiProject/2026-ELECTRONIC-DESIGN-COMPETITION/Debug" -I"C:/TI/mspm0_sdk_2_10_00_04/source/third_party/CMSIS/Core/Include" -I"C:/TI/mspm0_sdk_2_10_00_04/source" -I"D:/TiProject/2024-Electronic-Design-Competition-master/MPU6050" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0g350x_ticlang.o: C:/TI/mspm0_sdk_2_10_00_04/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Arm Compiler - building file: "$<"'
	"C:/TI/ti_cgt_arm_llvm_4.0.2.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"D:/TiProject/2026-ELECTRONIC-DESIGN-COMPETITION" -I"D:/TiProject/2026-ELECTRONIC-DESIGN-COMPETITION/Control" -I"D:/TiProject/2026-ELECTRONIC-DESIGN-COMPETITION/Sensor" -I"D:/TiProject/2026-ELECTRONIC-DESIGN-COMPETITION/GYRO" -I"D:/TiProject/2026-ELECTRONIC-DESIGN-COMPETITION/Encoder" -I"D:/TiProject/2026-ELECTRONIC-DESIGN-COMPETITION/sys" -I"D:/TiProject/2026-ELECTRONIC-DESIGN-COMPETITION/Debug" -I"C:/TI/mspm0_sdk_2_10_00_04/source/third_party/CMSIS/Core/Include" -I"C:/TI/mspm0_sdk_2_10_00_04/source" -I"D:/TiProject/2024-Electronic-Design-Competition-master/MPU6050" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


