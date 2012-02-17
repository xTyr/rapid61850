################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ctypes.c \
../src/datatypes.c \
../src/decodePacket.c \
../src/encodePacket.c \
../src/gse.c \
../src/gseDecode.c \
../src/gseDecodeBasic.c \
../src/gseDecodePacket.c \
../src/gseEncode.c \
../src/gseEncodeBasic.c \
../src/gseEncodePacket.c \
../src/iec61850.c \
../src/ied.c \
../src/main.c \
../src/sv.c \
../src/svDecode.c \
../src/svDecodeBasic.c \
../src/svDecodePacket.c \
../src/svEncode.c \
../src/svEncodeBasic.c \
../src/svEncodePacket.c 

OBJS += \
./src/ctypes.o \
./src/datatypes.o \
./src/decodePacket.o \
./src/encodePacket.o \
./src/gse.o \
./src/gseDecode.o \
./src/gseDecodeBasic.o \
./src/gseDecodePacket.o \
./src/gseEncode.o \
./src/gseEncodeBasic.o \
./src/gseEncodePacket.o \
./src/iec61850.o \
./src/ied.o \
./src/main.o \
./src/sv.o \
./src/svDecode.o \
./src/svDecodeBasic.o \
./src/svDecodePacket.o \
./src/svEncode.o \
./src/svEncodeBasic.o \
./src/svEncodePacket.o 

C_DEPS += \
./src/ctypes.d \
./src/datatypes.d \
./src/decodePacket.d \
./src/encodePacket.d \
./src/gse.d \
./src/gseDecode.d \
./src/gseDecodeBasic.d \
./src/gseDecodePacket.d \
./src/gseEncode.d \
./src/gseEncodeBasic.d \
./src/gseEncodePacket.d \
./src/iec61850.d \
./src/ied.d \
./src/main.d \
./src/sv.d \
./src/svDecode.d \
./src/svDecodeBasic.d \
./src/svDecodePacket.d \
./src/svEncode.d \
./src/svEncodeBasic.d \
./src/svEncodePacket.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/patrick/rapid61850/c/Include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


