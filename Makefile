# Makefile for programming ATmega32 using assembler
PROJECT=led
PROGRAMMER=-c avrispmkII -P usb # For the large blue AVR MKII
#PROGRAMMER=-c stk500v1 -P /dev/ttyUSB0 # For the small green programmer

default:
	avr-g++ -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o $(PROJECT).o $(PROJECT).c
	avr-g++ -mmcu=atmega328p $(PROJECT).o -o $(PROJECT)
	avr-objcopy -O ihex -R .eeprom   $(PROJECT)  $(PROJECT).hex
	avrdude -F -V -c arduino -p ATMEGA328P -P COM10 -b 115200 -U flash:w:$(PROJECT).hex