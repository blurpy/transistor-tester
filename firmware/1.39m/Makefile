#
#  Makefile
#
#  (c) 2012-2020 by Markus Reschke
#  based on code from Markus Frejek and Karl-Heinz Kübbeler
#

PROJECT = ComponentTester

#
# MCU settings
# - Change to fit your setup!
#

# avr-gcc: MCU model
# - ATmega 328/328P        : atmega328
# - ATmega 324P/324PA      : atmega324p
# - ATmega 324PB           : atmega328pb
# - ATmega 644/644P/644PA  : atmega644
# - ATmega 1284/1284P      : atmega1284
MCU = atmega328

# MCU freqency:
# - 1MHz  : 1
# - 8MHz  : 8
# - 16MHz : 16
# - 20MHz : 20
FREQ = 16

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


# avrdude: part number of MCU
# - ATmega 328    : m328
# - ATmega 328P   : m328p
# - ATmega 328PB  : m328pb
# - ATmega 324P   : m324p
# - ATmega 324PA  : m324pa
# - ATmega 644    : m644
# - ATmega 644P   : m644p
# - ATmega 644PA  : m644p
# - ATmega 1284   : m1284
# - ATmega 1284P  : m1284p
PARTNO = m328p

# avrdude: ISP programmer
#PROGRAMMER = buspirate
#PROGRAMMER = USBasp
#PROGRAMMER = usbtiny
#PROGRAMMER = stk500v2
PROGRAMMER = avrispmkII

# avrdude: port of ISP programmer
#PORT = /dev/bus_pirate
#PORT = /dev/ttyACM0
PORT = usb

# avrdude: bitclock
BITCLOCK = 5.0
#BITCLOCK = 10.0


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
CFLAGS = -mmcu=${MCU} -Wall -mcall-prologues -I. -Ibitmaps
CFLAGS += -DF_CPU=${FREQ}000000UL
CFLAGS += -DOSC_STARTUP=${OSC_STARTUP}
CFLAGS += -gdwarf-2 -std=gnu99 -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d
#CFLAGS += -flto

# linker flags
LDFLAGS = -mmcu=${MCU} -Wl,-Map=${NAME}.map

# hex file flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature
HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings

# header files
HEADERS = config.h config_328.h config_644.h colors.h
HEADERS += common.h variables.h $(wildcard var_*.h) functions.h
HEADERS += OneWire.h
HEADERS += HD44780.h ST7565R.h ILI9341.h PCD8544.h ST7735.h ST7920.h
HEADERS += SSD1306.h ILI9163.h STE2007.h PCF8814.h ST7036.h ADS7843.h

# objects
OBJECTS_C = main.o user.o pause.o adjust.o ADC.o probes.o display.o
OBJECTS_C += resistor.o cap.o semi.o inductor.o tools_misc.o tools_signal.o
OBJECTS_C += SPI.o I2C.o serial.o commands.o OneWire.o
OBJECTS_C += IR_RX.o IR_TX.o DHTxx.o
OBJECTS_C += HD44780.o ST7565R.o ILI9341.o PCD8544.o ST7735.o ST7920.o
OBJECTS_C += SSD1306.o ILI9163.o STE2007.o PCF8814.o ST7036.o VT100.o
OBJECTS_C += ADS7843.o
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
	avrdude -c ${PROGRAMMER} -B ${BITCLOCK} -p ${PARTNO} -P ${PORT} \
	  -U flash:w:./${NAME}.hex:a -U eeprom:w:./${NAME}.eep:a

# program firmware only
prog_fw: ${NAME} ${NAME}.hex ${NAME}.lss size
	avrdude -c ${PROGRAMMER} -B ${BITCLOCK} -p ${PARTNO} -P ${PORT} \
	  -U flash:w:./${NAME}.hex:a

# program EEPROM data only
prog_ee: ${NAME} ${NAME}.eep ${NAME}.lss size
	avrdude -c ${PROGRAMMER} -B ${BITCLOCK} -p ${PARTNO} -P ${PORT} \
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
#  MCU fuse bytes
#

# ATmega 328/328P
ifeq (${MCU},atmega328)
  FAMILY = atmega328_324
endif

# ATmega 328PB
ifeq (${MCU},atmega328pb)
  FAMILY = atmega328pb
endif

# ATmega 324P/324PA
ifeq (${MCU},atmega324p)
  FAMILY = atmega328_324
endif

# ATmega 644/644P/644PA
ifeq (${MCU},atmega644)
  FAMILY = atmega328_324
endif

# ATmega 1284/1284P
ifeq (${MCU},atmega1284)
  FAMILY = atmega328_324
endif

# ATmega 328/324/644/1284
ifeq (${FAMILY},atmega328_324)
  # high byte: use default settings
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

# select LFUSE
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
	avrdude -c ${PROGRAMMER} -B ${BITCLOCK} -p ${PARTNO} -P ${PORT} ${FUSES}
  endif
