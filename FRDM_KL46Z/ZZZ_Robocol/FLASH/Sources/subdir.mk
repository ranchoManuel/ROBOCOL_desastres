################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Actuadores.c" \
"../Sources/Comunicacion.c" \
"../Sources/Events.c" \
"../Sources/Utiles.c" \
"../Sources/main.c" \
"../Sources/sa_mtb.c" \

C_SRCS += \
../Sources/Actuadores.c \
../Sources/Comunicacion.c \
../Sources/Events.c \
../Sources/Utiles.c \
../Sources/main.c \
../Sources/sa_mtb.c \

OBJS += \
./Sources/Actuadores.o \
./Sources/Comunicacion.o \
./Sources/Events.o \
./Sources/Utiles.o \
./Sources/main.o \
./Sources/sa_mtb.o \

C_DEPS += \
./Sources/Actuadores.d \
./Sources/Comunicacion.d \
./Sources/Events.d \
./Sources/Utiles.d \
./Sources/main.d \
./Sources/sa_mtb.d \

OBJS_QUOTED += \
"./Sources/Actuadores.o" \
"./Sources/Comunicacion.o" \
"./Sources/Events.o" \
"./Sources/Utiles.o" \
"./Sources/main.o" \
"./Sources/sa_mtb.o" \

C_DEPS_QUOTED += \
"./Sources/Actuadores.d" \
"./Sources/Comunicacion.d" \
"./Sources/Events.d" \
"./Sources/Utiles.d" \
"./Sources/main.d" \
"./Sources/sa_mtb.d" \

OBJS_OS_FORMAT += \
./Sources/Actuadores.o \
./Sources/Comunicacion.o \
./Sources/Events.o \
./Sources/Utiles.o \
./Sources/main.o \
./Sources/sa_mtb.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Actuadores.o: ../Sources/Actuadores.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Actuadores.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Actuadores.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Comunicacion.o: ../Sources/Comunicacion.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Comunicacion.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Comunicacion.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Events.o: ../Sources/Events.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Events.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Events.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Utiles.o: ../Sources/Utiles.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Utiles.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Utiles.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/sa_mtb.o: ../Sources/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/sa_mtb.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '


