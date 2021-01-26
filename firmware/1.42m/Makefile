#
#  Makefile
#
#  (c) 2012-2020 by Markus Reschke
#  based on code from Markus Frejek and Karl-Heinz Kübbeler
#

PROJECT = ComponentTester


#
# MCU settings
# - Edit to match your setup!
#

# avr-gcc: MCU model
# - ATmega 328/328P        : atmega328
# - ATmega 328PB           : atmega328pb
# - ATmega 324P/324PA      : atmega324p
# - ATmega 640             : atmega640
# - ATmega 644/644P/644PA  : atmega644
# - ATmega 1280            : atmega1280
# - ATmega 1284/1284P      : atmega1284
# - ATmega 2560            : atmega2560
MCU = atmega328

# MCU freqency:
# - 1MHz  : 1
# - 8MHz  : 8
# - 16MHz : 16
# - 20MHz : 20
FREQ = 8

# oscillator type
# - internal RC oscillator      : RC
# - external full swing crystal : Crystal
# - external low power crystal  : LowPower
OSCILLATOR = Crystal

# oscillator start-up cycles
# - Crystal and LowPower could also be 1024 or 256 based on fuse settings
ifeq (${OSCILLATOR},RC)
  OSC_STARTUP = 6
endif
ifeq (${OSCILLATOR},Crystal)
  OSC_STARTUP = 16384
endif
ifeq (${OSCILLATOR},LowPower)
  OSC_STARTUP = 16384
endif


#
# avrdude settings
# - Edit to match your setup!
#

# avrdude: part number of MCU
# - ATmega 328    : m328
# - ATmega 328P   : m328p
# - ATmega 328PB  : m328pb
# - ATmega 324P   : m324p
# - ATmega 324PA  : m324pa
# - ATmega 640    : m640
# - ATmega 644    : m644
# - ATmega 644P   : m644p
# - ATmega 644PA  : m644p
# - ATmega 1280   : m1280
# - ATmega 1284   : m1284
# - ATmega 1284P  : m1284p
# - ATmega 2560   : m2560
PARTNO = m328p

# avrdude: ISP programmer, port and options

# Arduino as ISP
#PROGRAMMER = stk500v1
#PORT = /dev/ttyACM0
#OPTIONS = -b 19200

# Bus Pirate
#PROGRAMMER = buspirate
#PORT = /dev/bus_pirate
#OPTIONS = -B 10.0

# Diamex ALL-AVR/AVR-Prog
PROGRAMMER = avrispmkII
PORT = usb
OPTIONS = -B 1.0

# Pololu USB AVR Programmer
#PROGRAMMER = stk500v2
#PORT = /dev/ttyACM0
#OPTIONS = -B 1.0

# USBasp
#PROGRAMMER = usbasp
#PORT = usb
#OPTIONS = -B 20

# USBtinyISP
#PROGRAMMER = usbtiny
#PORT = usb
#OPTIONS = -B 5.0

# Arduino Uno bootloader via serial/USB
#PROGRAMMER = arduino
#PORT = /dev/ttyACM0
#OPTIONS = -D -b 115200

# Arduino Mega2560 bootloader via serial/USB
#PROGRAMMER = wiring
#PORT = /dev/ttyACM0
#OPTIONS = -D -b 115200


#
#  global settings
#

# project name
NAME = ComponentTester

# name and version based on directory name
DIST = $(notdir ${CURDIR})

# compiler flags
CC = avr-gcc
CPP = avr-g++
CFLAGS = -mmcu=${MCU} -Wall -I. -Ibitmaps
CFLAGS += -DF_CPU=${FREQ}000000UL
CFLAGS += -DOSC_STARTUP=${OSC_STARTUP}
CFLAGS += -gdwarf-2 -std=gnu99 -Os -mcall-prologues
CFLAGS += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
#CFLAGS += -flto
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d

# linker flags
LDFLAGS = -mmcu=${MCU} -Wl,-Map=${NAME}.map

# hex file flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature
HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings

# header files
HEADERS = config.h config_328.h config_644.h config_1280.h
HEADERS += colors.h common.h functions.h variables.h $(wildcard var_*.h)
HEADERS += OneWire.h ADS7843.h
HEADERS += HD44780.h ILI9163.h ILI9341.h ILI9481.h ILI9486.h ILI9488.h
HEADERS += PCD8544.h PCF8814.h SH1106.h SSD1306.h
HEADERS += ST7036.h ST7565R.h ST7735.h ST7920.h STE2007.h

# objects
OBJECTS_C = main.o user.o pause.o adjust.o ADC.o probes.o display.o
OBJECTS_C += resistor.o cap.o semi.o inductor.o
OBJECTS_C += tools_misc.o tools_signal.o tools_LC_Meter.o
OBJECTS_C += SPI.o I2C.o serial.o commands.o OneWire.o
OBJECTS_C += IR_RX.o IR_TX.o DHTxx.o ADS7843.o
OBJECTS_C += HD44780.o ILI9163.o ILI9341.o ILI9481.o ILI9486.o ILI9488.o
OBJECTS_C += PCD8544.o PCF8814.o SH1106.o SSD1306.o
OBJECTS_C += ST7036.o ST7565R.o ST7735.o ST7920.o
OBJECTS_C += STE2007.o VT100.o TestDisplay.o
OBJECTS_S = wait.o
OBJECTS = ${OBJECTS_C} ${OBJECTS_S}


#
#  build
#

all: ${NAME} ${NAME}.hex ${NAME}.eep ${NAME}.lss size


#
#  link
#

# link firmware
$(NAME): ${OBJECTS}
	 ${CC} ${LDFLAGS} ${OBJECTS} ${LIBDIRS} ${LIBS} -o ${NAME}

# create hex file of firmware
%.hex: ${NAME}
	avr-objcopy -O ihex ${HEX_FLASH_FLAGS} $< $@

# create hex file of EEPROM data
%.eep: ${NAME}
	-avr-objcopy ${HEX_EEPROM_FLAGS} -O ihex $< $@ || exit 0

# create dump of firmware
%.lss: ${NAME}
	avr-objdump -h -S $< > $@

# output size of firmware and stuff
size: ${NAME}
	@echo
	@avr-size -C --mcu=${MCU} $<


#
#  compile source files
#

# rule for all c-files
${OBJECTS_C}: %.o: %.c ${HEADERS} ${MAKEFILE_LIST}
	${CC} ${CFLAGS} -c ${@:.o=.c}

# rule for all S-files
${OBJECTS_S}: %.o: %.S ${HEADERS} ${MAKEFILE_LIST}
	${CC} ${CFLAGS} -c ${@:.o=.S}

# external dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)


#
#  extras
#

# program firmware and EEPROM data
upload: ${NAME} ${NAME}.hex ${NAME}.eep ${NAME}.lss size
	avrdude -c ${PROGRAMMER} -P ${PORT} -p ${PARTNO} ${OPTIONS} \
	  -U flash:w:./${NAME}.hex:a -U eeprom:w:./${NAME}.eep:a

# program firmware only
prog_fw: ${NAME} ${NAME}.hex ${NAME}.lss size
	avrdude -c ${PROGRAMMER} -P ${PORT} -p ${PARTNO} ${OPTIONS} \
	  -U flash:w:./${NAME}.hex:a

# program EEPROM data only
prog_ee: ${NAME} ${NAME}.eep ${NAME}.lss size
	avrdude -c ${PROGRAMMER} -P ${PORT} -p ${PARTNO} ${OPTIONS} \
	  -U eeprom:w:./${NAME}.eep:a

# create distribution package
dist:
	rm -f *.tgz
	cd ..; tar -czf ${DIST}/${DIST}.tgz \
	  ${DIST}/*.h ${DIST}/*.c ${DIST}/*.S ${DIST}/bitmaps/*.h \
	  ${DIST}/Makefile ${DIST}/README ${DIST}/CHANGES \
	  ${DIST}/README.de ${DIST}/CHANGES.de ${DIST}/Clones \
	  ${DIST}/*.pdf

# clean up
clean:
	-rm -rf ${OBJECTS} ${NAME} dep/* *.tgz
	-rm -rf ${NAME}.hex ${NAME}.eep ${NAME}.lss ${NAME}.map


#
#  MCU fuses
#

# ATmega 328/328P
ifeq (${MCU},atmega328)
  FAMILY = atmega328_324_640
endif

# ATmega 328PB
ifeq (${MCU},atmega328pb)
  FAMILY = atmega328pb
endif

# ATmega 324P/324PA
ifeq (${MCU},atmega324p)
  FAMILY = atmega328_324_640
endif

# ATmega 640
ifeq (${MCU},atmega640)
  FAMILY = atmega328_324_640
endif

# ATmega 644/644P/644PA
ifeq (${MCU},atmega644)
  FAMILY = atmega328_324_640
endif

# ATmega 1280
ifeq (${MCU},atmega1280)
  FAMILY = atmega328_324_640
endif

# ATmega 1284/1284P
ifeq (${MCU},atmega1284)
  FAMILY = atmega328_324_640
endif

# ATmega 2560
ifeq (${MCU},atmega2560)
  FAMILY = atmega328_324_640
endif

# ATmega 328/324/640/644/1280/1284/2560
ifeq (${FAMILY},atmega328_324_640)
  # high byte: use default settings, disable JTAG
  HFUSE = -U hfuse:w:0xd9:m
  # extended byte: BOD level 4.3V
  EFUSE = -U efuse:w:0xfc:m
  # low byte: clock settings
  ifeq (${FREQ},1)
    # internal RC oscillator (8MHz) and /1 clock divider
    LFUSE_RC = -U lfuse:w:0x62:m
    # external 8MHz full swing crystal and /8 clock divider
    LFUSE_CRYSTAL = -U lfuse:w:0x77:m
    # external 8MHz low power crystal and /8 clock divider
    LFUSE_LOWPOWER = -U lfuse:w:0x7f:m
  endif
  ifeq (${FREQ},8)
    # internal RC oscillator (8MHz) and /1 clock divider
    LFUSE_RC = -U lfuse:w:0xe2:m
    # external 8MHz full swing crystal and /1 clock divider
    LFUSE_CRYSTAL = -U lfuse:w:0xf7:m
    # external 8MHz low power crystal and /1 clock divider
    LFUSE_LOWPOWER = -U lfuse:w:0xff:m
  endif
  ifeq (${FREQ},16)
    # internal RC oscillator (8MHz) not possible
    LFUSE_RC =
    # external 16MHz full swing crystal and /1 clock divider
    LFUSE_CRYSTAL = -U lfuse:w:0xf7:m
    # external 16MHz low power crystal and /1 clock divider
    LFUSE_LOWPOWER = -U lfuse:w:0xff:m
  endif
  ifeq (${FREQ},20)
    # internal RC oscillator (8MHz) not possible
    LFUSE_RC =
    # external 20MHz full swing crystal and /1 clock divider
    LFUSE_CRYSTAL = -U lfuse:w:0xf7:m
    # external 20MHz low power crystal and /1 clock divider
    LFUSE_LOWPOWER = -U lfuse:w:0xff:m
  endif
endif

# ATmega 328PB
ifeq (${FAMILY},atmega328pb)
  # high byte: use default settings
  HFUSE = -U hfuse:w:0xd9:m
  # extended byte: BOD level 4.3V, CFD disabled
  EFUSE = -U efuse:w:0xf4:m
  # low byte: clock settings
  ifeq (${FREQ},8)
    # internal RC oscillator (8MHz) and /1 clock divider
    LFUSE_RC = -U lfuse:w:0xe2:m
    # full swing crystal not supported, use low power crystal
    LFUSE_CRYSTAL = -U lfuse:w:0xff:m
    # external 8MHz low power crystal and /1 clock divider
    LFUSE_LOWPOWER = -U lfuse:w:0xff:m
  endif
  ifeq (${FREQ},16)
    # internal RC oscillator (8MHz) not possible
    LFUSE_RC =
    # full swing crystal not supported, use low power crystal
    LFUSE_CRYSTAL = -U lfuse:w:0xff:m
    # external 16MHz low power crystal and /1 clock divider
    LFUSE_LOWPOWER = -U lfuse:w:0xff:m
  endif
endif

# select low fuse byte
ifeq (${OSCILLATOR},RC)
  LFUSE = ${LFUSE_RC}
endif
ifeq (${OSCILLATOR},Crystal)
  LFUSE = ${LFUSE_CRYSTAL}
endif
ifeq (${OSCILLATOR},LowPower)
  LFUSE = ${LFUSE_LOWPOWER}
endif

# check fuses
FUSES =
ifneq ($(strip ${LFUSE}),)
  ifneq ($(strip ${HFUSE}),)
    FUSES = ${LFUSE} ${HFUSE} ${EFUSE}
  endif
endif

# set fuses
fuses:
  ifeq ($(strip ${FUSES}),)
	@echo Invalid fuse settings!
  else
	avrdude -c ${PROGRAMMER} -P ${PORT} -p ${PARTNO} ${OPTIONS} ${FUSES}
  endif
