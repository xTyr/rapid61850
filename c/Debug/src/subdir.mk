################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ctypes.c \
../src/decodePacket.c \
../src/encodePacket.c \
../src/gseDecodeBasic.c \
../src/gseDecodePacket.c \
../src/gseEncodeBasic.c \
../src/gseEncodePacket.c \
../src/iec61850.c \
../src/main.c \
../src/svDecodeBasic.c \
../src/svDecodePacket.c \
../src/svEncodeBasic.c \
../src/svEncodePacket.c 

OBJS += \
./src/ctypes.o \
./src/decodePacket.o \
./src/encodePacket.o \
./src/gseDecodeBasic.o \
./src/gseDecodePacket.o \
./src/gseEncodeBasic.o \
./src/gseEncodePacket.o \
./src/iec61850.o \
./src/main.o \
./src/svDecodeBasic.o \
./src/svDecodePacket.o \
./src/svEncodeBasic.o \
./src/svEncodePacket.o 

C_DEPS += \
./src/ctypes.d \
./src/decodePacket.d \
./src/encodePacket.d \
./src/gseDecodeBasic.d \
./src/gseDecodePacket.d \
./src/gseEncodeBasic.d \
./src/gseEncodePacket.d \
./src/iec61850.d \
./src/main.d \
./src/svDecodeBasic.d \
./src/svDecodePacket.d \
./src/svEncodeBasic.d \
./src/svEncodePacket.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


