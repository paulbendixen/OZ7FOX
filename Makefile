TARGET=oz7fox
CC=/usr/bin/avr-gcc
SRC=main.c timer.c key.c
OBJ=$(SRC:.c=.o)
CFLAGS=-g -O2 -Wall -mcall-prologues -mmcu=atmega16
AVRFLAGS= -p m16 -P /dev/ttyUSB0 -c stk500 -e -u -U $(TARGET).hex -v -B 10
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
