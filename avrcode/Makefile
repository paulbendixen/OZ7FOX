TARGET=oz7fox
CC?=/usr/bin/avr-gcc
SRC=main.c timer.c key.c
OBJ=$(SRC:.c=.o)
#CFLAGS=-g -O2 -Wall -mcall-prologues -mmcu=atmega16
CFLAGS=-g -O2 -Wall -mcall-prologues -mmcu=atmega32
#AVRFLAGS= -p m16 -P /dev/ttyUSB0 -c stk500v2 -e -u -U $(TARGET).hex -v -B 10
#AVRFLAGS= -p m32 -P /dev/ttyUSB0 -c stk500v2 -e -u -U $(TARGET).hex -v -B 10
#AVRFLAGS= -p m32 -P usb -c avrispmkII -e -u -U $(TARGET).hex -v -B 10
AVRFLAGS= -p m32 -P usb -c atmelice_isp -e -u -U $(TARGET).hex -v -B 10
OBJ2HEX=/usr/bin/avr-objcopy 
UISP=/usr/bin/avrdude 

%.o: %.c
	$(CC) -c $(CFLAGS) $*.c

.SECONDARY : $(TARGET).hex
.PRECIOUS :$(OBJ)
%.obj : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.hex : %.obj
	$(OBJ2HEX) -R .eeprom -O ihex $< $@


program : $(TARGET).hex
	$(UISP) $(AVRFLAGS) 

clean :
	rm -f *.hex *.obj *.o

all: $(TARGET).hex
