################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Arm Compiler - building file: "$<"'
	"C:/TI/ti_cgt_arm_llvm_4.0.2.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"D:/TiProject/2026-Electronic-Design-Competition-master" -I"D:/TiProject/2026-Electronic-Design-Competition-master/Control" -I"D:/TiProject/2026-Electronic-Design-Competition-master/Sensor" -I"D:/TiProject/2026-Electronic-Design-Competition-master/GYRO" -I"D:/TiProject/2026-Electronic-Design-Competition-master/Encoder" -I"D:/TiProject/2026-Electronic-Design-Competition-master/sys" -I"D:/TiProject/2026-Electronic-Design-Competition-master/Debug" -I"C:/TI/mspm0_sdk_2_10_00_04/source/third_party/CMSIS/Core/Include" -I"C:/TI/mspm0_sdk_2_10_00_04/source" -I"D:/TiProject/2024-Electronic-Design-Competition-master/MPU6050" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-692245842: ../main.syscfg
	@echo 'SysConfig - building file: "$<"'
	"C:/TI/sysconfig_1.26.2/sysconfig_cli.bat" -s "C:/TI/mspm0_sdk_2_10_00_04/.metadata/product.json" --script "D:/TiProject/2026-Electronic-Design-Competition-master/main.syscfg" -o "." --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

device_linker.cmd: build-692245842 ../main.syscfg
device.opt: build-692245842
device.cmd.genlibs: build-692245842
ti_msp_dl_config.c: build-692245842
ti_msp_dl_config.h: build-692245842
Event.dot: build-692245842

%.o: ./%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Arm Compiler - building file: "$<"'
	"C:/TI/ti_cgt_arm_llvm_4.0.2.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"D:/TiProject/2026-Electronic-Design-Competition-master" -I"D:/TiProject/2026-Electronic-Design-Competition-master/Control" -I"D:/TiProject/2026-Electronic-Design-Competition-master/Sensor" -I"D:/TiProject/2026-Electronic-Design-Competition-master/GYRO" -I"D:/TiProject/2026-Electronic-Design-Competition-master/Encoder" -I"D:/TiProject/2026-Electronic-Design-Competition-master/sys" -I"D:/TiProject/2026-Electronic-Design-Competition-master/Debug" -I"C:/TI/mspm0_sdk_2_10_00_04/source/third_party/CMSIS/Core/Include" -I"C:/TI/mspm0_sdk_2_10_00_04/source" -I"D:/TiProject/2024-Electronic-Design-Competition-master/MPU6050" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0g350x_ticlang.o: C:/TI/mspm0_sdk_2_10_00_04/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Arm Compiler - building file: "$<"'
	"C:/TI/ti_cgt_arm_llvm_4.0.2.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"D:/TiProject/2026-Electronic-Design-Competition-master" -I"D:/TiProject/2026-Electronic-Design-Competition-master/Control" -I"D:/TiProject/2026-Electronic-Design-Competition-master/Sensor" -I"D:/TiProject/2026-Electronic-Design-Competition-master/GYRO" -I"D:/TiProject/2026-Electronic-Design-Competition-master/Encoder" -I"D:/TiProject/2026-Electronic-Design-Competition-master/sys" -I"D:/TiProject/2026-Electronic-Design-Competition-master/Debug" -I"C:/TI/mspm0_sdk_2_10_00_04/source/third_party/CMSIS/Core/Include" -I"C:/TI/mspm0_sdk_2_10_00_04/source" -I"D:/TiProject/2024-Electronic-Design-Competition-master/MPU6050" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


