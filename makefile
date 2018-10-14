#make file
ifeq ($(ENV_V),GALILEO)
CC=/opt/iot-devkit/1.7.2/sysroots/x86_64-pokysdk-linux/usr/bin/i586-poky-linux/i586-poky-linux-gcc
#SROOT=/home/SDK/sysroots/i586-poky-linux/
else
CC = gcc 
endif

CFLAGS = -g -Wall -pthread -std=c99 

TARGET = RGBLed_1

all : $(TARGET).c

	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:

	$(RM) $(TARGET)
