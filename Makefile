TARGET=main
CC=/usr/bin/avr-gcc
SRC=main.c 
CFLAGS=-g -O2 -Wall -mcall-prologues -mmcu=atmega16
AVRFLAGS= -p m16 -P /dev/ttyUSB0 -c stk500v2 -e -u -U $(TARGET).hex -v -B 10
OBJ2HEX=/usr/bin/avr-objcopy 
UISP=/usr/bin/avrdude 

%.obj : %.o
	$(CC) $(CFLAGS) $< -o $@

%.hex : %.obj
	$(OBJ2HEX) -R .eeprom -O ihex $< $@

program : $(TARGET).hex
	$(UISP) $(AVRFLAGS) 

clean :
	rm -f *.hex *.obj *.o
