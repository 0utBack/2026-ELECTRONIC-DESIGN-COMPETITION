################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Sensor/%.o: ../Sensor/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Arm Compiler - building file: "$<"'
	"C:/TI/ti_cgt_arm_llvm_4.0.2.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"D:/TiProject/2026-ELECTRONIC-DESIGN-COMPETITION" -I"D:/TiProject/2026-ELECTRONIC-DESIGN-COMPETITION/Control" -I"D:/TiProject/2026-ELECTRONIC-DESIGN-COMPETITION/Sensor" -I"D:/TiProject/2026-ELECTRONIC-DESIGN-COMPETITION/GYRO" -I"D:/TiProject/2026-ELECTRONIC-DESIGN-COMPETITION/Encoder" -I"D:/TiProject/2026-ELECTRONIC-DESIGN-COMPETITION/Key" -I"D:/TiProject/2026-ELECTRONIC-DESIGN-COMPETITION/sys" -I"D:/TiProject/2026-ELECTRONIC-DESIGN-COMPETITION/Debug" -I"C:/TI/mspm0_sdk_2_10_00_04/source/third_party/CMSIS/Core/Include" -I"C:/TI/mspm0_sdk_2_10_00_04/source" -I"D:/TiProject/2024-Electronic-Design-Competition-master/MPU6050" -gdwarf-3 -MMD -MP -MF"Sensor/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


