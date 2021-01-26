/* ************************************************************************
 *
 *   global configuration, setup and settings
 *
 *   (c) 2012-2020 by Markus Reschke
 *   based on code from Markus Frejek and Karl-Heinz Kübbeler
 *
 * ************************************************************************ */


/* source management */
#define CONFIG_H


/*
 *  For MCU specific settings (port and pin assignments) and display
 *  settings please edit also:
 *  - ATmega328:            config_328.h
 *  - ATmega324/644/1284:   config_644.h
 *  - ATmega640/1280/2560:  config_1280.h
 */



/* ************************************************************************
 *   Hardware options
 * ************************************************************************ */


/*
 *  rotary encoder for user interface
 *  - default pins: PD2 & PD3 (ATmega 328)
 *  - could be in parallel with LCD module
 *  - see ENCODER_PORT in config-<MCU>.h for port pins
 *  - uncomment to enable and also set ENCODER_PULSES & ENCODER_STEPS below
 *    to match your rotary encoder
 */

//#define HW_ENCODER


/*
 *  Number of Gray code pulses per step or detent for the rotary encoder
 *  - typical values: 2 or 4, rarely 1
 *  - a rotary encoder's pulse is the complete sequence of 4 Gray code pulses
 *  - adjust value to match your rotary encoder
 */

#define ENCODER_PULSES   4


/*
 *  Number of detents or steps
 *  - this is used by the detection of the rotary encoder's turning velocity
 *  - it doesn't have to match exactly and also allows you to finetune the
 *    the feedback (higher: slow down, lower: speed up)
 *  - typical values: 20, 24 or 30 
 *  - adjust value to match your rotary encoder
 */

#define ENCODER_STEPS    24


/*
 *  increase/decrease push buttons for user interface
 *  - alternative for rotary encoder
 *  - see KEY_PORT in config-<MCU>.h for port pins
 *  - uncomment to enable
 */

//#define HW_INCDEC_KEYS


/*
 *  2.5V voltage reference for Vcc check
 *  - default pin: PC4 (ATmega 328)
 *  - should be at least 10 times more precise than the voltage regulator
 *  - see TP_REF in config-<MCU>.h for port pin
 *  - uncomment to enable and also adjust UREF_25 below for your voltage
 *    reference
 */

//#define HW_REF25


/*
 *  Typical voltage of 2.5V voltage reference (in mV)
 *  - see datasheet of the voltage reference
 *  - or use >= 5.5 digit DMM to measure the voltage
 */

#define UREF_25           2495


/*
 *  Probe protection relay for discharging caps
 *  - default pin: PC4 (ATmega 328)
 *  - low signal: short circuit probe pins
 *    high signal via external reference: remove short circuit
 *  - see TP_REF in config_<MCU>.h for port pin
 *  - uncomment to enable
 */

//#define HW_DISCHARGE_RELAY


/*
 *  Zener check / voltage measurement up to 50V DC
 *  - default pin: PC3 (ATmega 328)
 *  - 10:1 voltage divider
 *  - DC-DC boost converter controled by test push button
 *  - see TP_ZENER in config_<MCU>.h for port pin
 *  - uncomment to enable
 */

//#define HW_ZENER


/*
 *  alternative mode for Zener check: don't switch boost converter
 *  - when the DC-DC boost converter runs all the time
 *  - when measuring an external voltage (circuit without boost converter)
 *  - uncomment to enable
 */

//#define ZENER_UNSWITCHED


/*
 *  high resolution for Zener check
 *  - 10mV instead of 0.1V
 *  - uncomment to enable
 */

#define ZENER_HIGH_RES


/*
 *  fixed signal output
 *  - in case the MCU's OC1B pin is wired as dedicated signal output
 *    instead of driving the Rl probe resistor for test pin #2
 *  - uncomment to enable
 */

//#define HW_FIXED_SIGNAL_OUTPUT


/*
 *  basic frequency counter
 *  - default pin: T0 (PD4 ATmega 328)
 *  - uses T0 directly as frequency input
 *  - counts up to 1/4 of MCU clock rate
 *  - might be in parallel with LCD module
 *  - uncomment to enable
 */

//#define HW_FREQ_COUNTER_BASIC


/*
 *  extended frequency counter
 *  - low and high frequency crystal oscillators
 *    and buffered frequency input
 *  - prescalers 1:1 and 16:1 (32:1)
 *  - uses T0 directly as frequency input
 *  - see COUNTER_CTRL_PORT in config-<MCU>.h for port pins
 *  - requires a display with more than 2 text lines
 *  - uncomment to enable
 *  - select the circuit's prescaler setting: either 16:1 or 32:1 
 */

//#define HW_FREQ_COUNTER_EXT
#define FREQ_COUNTER_PRESCALER     16   /* 16:1 */
//#define FREQ_COUNTER_PRESCALER     32   /* 32:1 */


/*
 *  event counter
 *  - default pin: T0 (PD4 ATmega 328)
 *  - uses T0 directly as event/pulse input (rising edge)
 *  - no shared operation with displays possible for T0
 *  - requires additional keys (e.g. rotary encoder) and a display with
 *    more than 5 lines
 *  - only for MCU clock of 8, 16 or 20MHz
 *  - uncomment to enable
 */

//#define HW_EVENT_COUNTER


/*
 *  trigger output for event counter
 *  - uses probe #2 as trigger output, probes #1 and #3 are Gnd
 *  - sets trigger output to high while counting
 *  - uncomment to enable
 */

//#define EVENT_COUNTER_TRIGGER_OUT


/*
 *  IR remote control detection/decoder (via dedicated MCU pin)
 *  - requires IR receiver module, e.g. TSOP series
 *  - module is connected to fixed I/O pin
 *  - see IR_PORT in config-<MCU>.h for port pin
 *  - uncomment to enable
 *  - for additional protocols also enable SW_IR_RX_EXTRA
 */

//#define HW_IR_RECEIVER


/*
 *  fixed cap for self-adjustment
 *  - see TP_CAP and ADJUST_PORT in config-<MCU>.h for port pins
 *  - uncomment to enable
 */

//#define HW_ADJUST_CAP


/*
 *  L/C meter hardware option
 *  - uses T0 directly as frequency input
 *  - see LC_CTRL_PORT in config-<MCU>.h for port pins
 *  - uncomment to enable
 */

//#define HW_LC_METER


/*
 *  L/C meter: value of reference capacitor C_p (in 0.1 pF)
 *  - should be around 1000pF
 */

#define LC_METER_C_REF        10000


/*
 *  L/C meter: also display frequency of LC oscillator
 *  - helps to spot the oscillator's frequency drifting 
 *  - requires display with more than two text lines
 *  - uncomment to enable
 */

//#define LC_METER_SHOW_FREQ


/*
 *  relay for parallel cap (sampling ADC)
 *  - uncomment to enable (not implemented yet)
 */

//#define HW_CAP_RELAY



/* ************************************************************************
 *   software options
 * ************************************************************************ */


/*
 *  PWM generator with simple user interface
 *  - signal output via OC1B
 *  - uncomment to enable
 */

#define SW_PWM_SIMPLE


/*
 *  PWM generator with fancy user interface
 *  - signal output via OC1B
 *  - requires additional keys and display with more than 2 text lines
 *  - uncomment to enable
 */

//#define SW_PWM_PLUS


/*
 *  Inductance measurement
 *  - uncomment to enable
 */

#define SW_INDUCTOR


/*
 *  ESR measurement
 *  - requires MCU clock >= 8 MHz
 *  - choose SW_OLD_ESR for old method starting at 180nF
 *  - uncomment to enable
 */

#define SW_ESR
//#define SW_OLD_ESR


/*
 *  ESR Tool (in-circuit ESR measurement)
 *  - requires SW_ESR or SW_OLD_ESR to be enabled
 *  - uncomment to enable
 */

//#define SW_ESR_TOOL


/*
 *  check for rotary encoders
 *  - uncomment to enable
 */

//#define SW_ENCODER


/*
 *  squarewave signal generator
 *  - signal output via OC1B
 *  - requires additional keys
 *  - uncomment to enable
 */

#define SW_SQUAREWAVE


/*
 *  IR remote control detection/decoder (via probes)
 *  - requires IR receiver module, e.g. TSOP series
 *  - module will be connected to probe leads
 *  - uncomment to enable
 */

#define SW_IR_RECEIVER


/*
 *  current limiting resistor for IR receiver module
 *  - for 5V only modules
 *  - Warning: any short circuit may destroy your MCU
 *  - uncomment to disable resistor
 */

//#define SW_IR_DISABLE_RESISTOR


/*
 *  additional protocols for IR remote control detection/decoder
 *  - uncommon protocols which will increase flash memory usage ;)
 *  - uncomment to enable
 */

//#define SW_IR_RX_EXTRA


/*
 *  IR remote control sender
 *  - signal output via OC1B
 *  - requires additional keys and display with more than 4 text lines
 *  - also requires an IR LED with a simple driver
 *  - uncomment to enable
 */

//#define SW_IR_TRANSMITTER


/*
 *  Alternative delay loop for IR remote control sender
 *  - in case the the C compiler screws up the default delay loop
 *    and causes incorrect pulse/pause timings
 *  - uncomment to enable
 */

//#define SW_IR_TX_ALTDELAY


/*
 *  additional protocols for IR remote control sender
 *  - uncommon protocols which will increase flash memory usage ;)
 *  - uncomment to enable
 */

//#define SW_IR_TX_EXTRA


/*
 *  check for opto couplers
 *  - uncomment to enable
 */

#define SW_OPTO_COUPLER


/*
 *  check for Unijunction Transistor
 *  - uncomment to enable
 */

#define SW_UJT


/*
 *  check for Schottky Transistor (Schottky-clamped BJT)
 *  - uncomment to enable
 */

#define SW_SCHOTTKY_BJT


/*
 *  Servo Check
 *  - signal output via OC1B
 *  - requires additional keys and display with more than 2 text lines
 *  - uncomment to enable
 */

//#define SW_SERVO


/*
 *  DS18B20 - OneWire temperature sensor 
 *  - uncomment to enable
 *  - also enable ONEWIRE_PROBES or ONEWIRE_IO_PIN (see section 'Busses')
 */

//#define SW_DS18B20


/*
 *  OneWire: read and display ROM code
 *  - option for OneWire related tools
 *  - requires display with more than 2 text lines
 *  - uncomment to enable
 */

//#define ONEWIRE_READ_ROM


/*
 *  scan OneWire bus for devices and list their ROM codes
 *  - requires display with more than 2 text lines
 *  - uncomment to enable
 *  - also enable ONEWIRE_PROBES or ONEWIRE_IO_PIN (see section 'Busses')
 */

//#define SW_ONEWIRE_SCAN


/*
 *  capacitor leakage check
 *  - requires display with more than two lines
 *  - uncomment to enable
 */

//#define SW_CAP_LEAKAGE


/*
 *  display reverse hFE for BJTs
 *  - hFE for collector and emitter reversed
 *  - uncomment to enable
 */

//#define SW_REVERSE_HFE


/*
 *  display I_C/I_E test current for hFE measurement
 *  - I_C for common emitter circuit
 *    I_E for common collector circuit
 *  - uncomment to enable
 */

//#define SW_HFE_CURRENT


/*
 *  R/C/L monitors
 *  - monitor passive components connected to probes #1 and #3
 *  - monitors for L require SW_INDUCTOR to be enabled
 *  - for ESR either SW_ESR or SW_OLD_ESR needs to be enabled
 *  - uncomment to enable (one or more)
 */

//#define SW_MONITOR_R          /* just R */
//#define SW_MONITOR_C          /* just C plus ESR */
//#define SW_MONITOR_L          /* just L */
//#define SW_MONITOR_RCL        /* R plus L, or C plus ESR */
//#define SW_MONITOR_RL         /* R plus L */


/*
 *  DHT11, DHT22 and compatible humidity & temperature sensors
 *  - uncomment to enable
 */

//#define SW_DHTXX


/*
 *  display font for test purposes
 *  - uncomment to enable
 */

//#define SW_FONT_TEST


/*
 *  check resistor for matching E series norm value
 *  - requires a display with more than 2 text lines
 *  - color-code mode requires a color graphics display
 *  - uncomment to enable (one or more)
 */

//#define SW_R_E24_5_T          /* E24 5% tolerance, text */
//#define SW_R_E24_5_CC         /* E24 5% tolerance, color-code */
//#define SW_R_E24_1_T          /* E24 1% tolerance, text */
//#define SW_R_E24_1_CC         /* E24 1% tolerance, color-code */
//#define SW_R_E96_T            /* E96 1% tolerance, text */
//#define SW_R_E96_CC           /* E96 1% tolerance, color-code */


/*
 *  check capacitor for matching E series norm value
 *  - requires a display with more than 2 text lines
 *  - uncomment to enable (one or more)
 */

//#define SW_C_E6_T             /* E6 20% tolerance, text */
//#define SW_C_E12_T            /* E12 10% tolerance, text */


/*
 *  check inductor for matching E series norm value
 *  - requires a display with more than 2 text lines
 *  - uncomment to enable (one or more)
 */

//#define SW_L_E6_T             /* E6 20% tolerance, text */
//#define SW_L_E12_T            /* E12 10% tolerance, text */



/* ************************************************************************
 *   workarounds for some testers
 * ************************************************************************ */


/*
 *  Disable hFE measurement with common collector circuit and Rl as
 *  base resistor.
 *  - problem:
 *    hFE values are way too high.
 *  - affected testers:
 *    Hiland M644 (under investigation)
 *  - uncomment to enable
 */

//#define NO_HFE_C_RL



/* ************************************************************************
 *   workarounds for some IDEs 
 * ************************************************************************ */


/*
 *  Oscillator startup cycles (after wakeup from power-safe mode):
 *  - typical values
 *    - internal RC:              6
 *    - full swing crystal:   16384 (also 256 or 1024 based on fuse settings)
 *    - low power crystal:    16384 (also 256 or 1024 based on fuse settings)
 *  - Please change value if it doesn't match your tester!
 */

#ifndef OSC_STARTUP
  #define OSC_STARTUP    16384
#endif



/* ************************************************************************
 *   user interface
 * ************************************************************************ */


/*
 *  Language of user interface. Available languages:
 *  - English (default)
 *  - Czech (based on ISO 8859-1)
 *  - Czech 2 (with Czech characters based on ISO 8859-2)
 *  - Danish
 *  - German
 *  - Polish (based on ISO 8859-1)
 *  - Polish 2 (with Polish characters based on ISO 8859-2)
 *  - Spanish
 *  - Romanian
 *  - Russian (with cyrillic characters based on Windows-1251)
 *  - Russian 2 (with cyrillic characters based on Windows-1251)
 */

#define UI_ENGLISH
//#define UI_CZECH
//#define UI_CZECH_2
//#define UI_DANISH
//#define UI_GERMAN
//#define UI_ITALIAN
//#define UI_POLISH
//#define UI_POLISH_2
//#define UI_ROMANIAN
//#define UI_RUSSIAN
//#define UI_RUSSIAN_2
//#define UI_SPANISH


/*
 *  Use comma instead of dot to indicate a decimal fraction.
 *  - uncomment to enable
 */

//#define UI_COMMA


/*
 *  Display temperatures in Fahrenheit instead of Celsius.
 *  - uncomment to enable
 */

//#define UI_FAHRENHEIT


/*
 *  Display hexadecimal values in uppercase instead of lowercase
 *  - uncomment to enable
 */

//#define UI_HEX_UPPERCASE


/*
 *  Set the default operation mode to auto-hold.
 *  - instead of continous mode
 *  - uncomment to enable
 */

//#define UI_AUTOHOLD


/*
 *  Trigger the menu also by a short circuit of all three probes.
 *  - former default behaviour
 *  - uncomment to enable
 */

//#define UI_SHORT_CIRCUIT_MENU


/*
 *  Show key hints instead of cursor if available.
 *  - currently only "Menu/Test"
 *  - requires additional keys and display with a sufficient number of
 *    text lines (recommended: >= 8 lines)
 *  - uncomment to enable
 */

//#define UI_KEY_HINTS


/*
 *  Enter menu to select adjustment profile after powering on.
 *  - uncomment to enable
 */

//#define UI_CHOOSE_PROFILE


/*
 *  Output components found also via TTL serial interface.
 *  - uncomment to enable
 *  - also enable SERIAL_BITBANG or SERIAL_HARDWARE (see section 'Busses')
 */

//#define UI_SERIAL_COPY


/*
 *  Control tester via TTL serial interface.
 *  - uncomment to enable
 *  - also enable SERIAL_BITBANG or SERIAL_HARDWARE, plus SERIAL_RW
 *    (see section 'Busses') 
 */

//#define UI_SERIAL_COMMANDS


/*
 *  Maximum time to wait after probing (in ms).
 *  - applies to continuous mode only
 *  - Time between printing the result and starting a new probing cycle.
 */

#define CYCLE_DELAY      3000


/*
 *  Maximum number of probing runs without any component found in a row.
 *  - applies to continuous mode only
 *  - If this number is reached the tester will power off.
 *  - When set to zero the tester will run only once and turn off
 *    after CYCLE_DELAY.
 *  - When set to 255 this feature will be disabled and the tester runs
 *    until it's powered off manually.
 */

#define CYCLE_MAX        5


/*
 *  Automatic power-off when no button is pressed for a while (in s).
 *  - applies to auto-hold mode only
 *  - uncomment to enable, also adjust timeout (in s)
 */

//#define POWER_OFF_TIMEOUT     60


/*
 *  component symbols for fancy pinout
 *  - for 3-pin semiconductors
 *  - requires graphics display and symbol bitmap
 *  - uncomment to enable
 */

#define SW_SYMBOLS


/*
 *  color coding for probes
 *  - requires color graphics LCD
 *  - uncomment to enable
 *  - edit colors.h to select correct probe colors
 */

#define SW_PROBE_COLORS


/*
 *  main menu: power off tester
 *  - uncomment to enable
 */

//#define SW_POWER_OFF


/*
 *  Round some values if appropriate.
 *  - for
 *    - DS18B20 (0.1 °C/F)
 *  - uncomment to enable
 */

//#define UI_ROUND_DS18B20


/*
 *  storage of firmware data (texts, tables etc)
 *  - self-adjustment data is always stored in EEPROM
 *  - fonts and symbols are always stored in Flash
 *  - uncomment one
 */ 

#define DATA_EEPROM           /* store data in EEPROM */
//#define DATA_FLASH            /* store data in Flash */



/* ************************************************************************
 *   power management
 * ************************************************************************ */


/*
 *  type of power switch
 *  - soft-latching power switch (default)
 *    - as in the tester's reference circuit 
 *    - tester is able to power itself off
 *  - manual power switch
 *    - tester isn't able to power itself off
 *  - enable one
 */

#define POWER_SWITCH_SOFT
//#define POWER_SWITCH_MANUAL


/*
 *  Battery monitoring mode:
 *  - BAT_NONE     disable battery monitoring completely
 *  - BAT_DIRECT   direct measurement of battary voltage (< 5V)
 *  - BAT_DIVIDER  measurement via voltage divider
 *  - uncomment one of the modes
 */

//#define BAT_NONE
//#define BAT_DIRECT
#define BAT_DIVIDER


/*
 *  Unmonitored optional external power supply
 *  - Some circuits supporting an additional external power supply are designed
 *    in a way that prevents the battery monitoring to measure the voltage of
 *    the external power supply. This would trigger the low battery shut-down.
 *    The switch below will prevent the shut-down when the measured voltage is
 *    below 0.9V (caused by the diode's leakage current).
 *  - uncomment to enable
 */

//#define BAT_EXT_UNMONITORED


/*
 *  Voltage divider for battery monitoring
 *  - BAT_R1: top resistor in Ohms
 *  - BAT_R2: bottom resistor in Ohms
 */

#define BAT_R1           10000
#define BAT_R2           3300


/*
 *  Voltage drop by reverse voltage protection diode and power management
 *  transistor (in mV):
 *  - or any other circuitry in the power section
 *  - Get your DMM and measure the voltage drop!
 *  - Schottky diode about 200mV / PNP BJT about 100mV.
 */  

#define BAT_OFFSET       290


/*
 *  Battery weak voltage (in mV).
 *  - Tester warns if BAT_WEAK is reached.
 *  - Voltage drop BAT_OFFSET is considered in calculation.
 */

#define BAT_WEAK         7400


/*
 *  Battery low voltage (in mV).
 *  - Tester powers off if BAT_LOW is reached.
 *  - Voltage drop BAT_OFFSET is considered in calculation.
 */

#define BAT_LOW          6400 


/*
 *  Enter sleep mode when idle to save power.
 *  - uncomment to enable
 */

#define SAVE_POWER



/* ************************************************************************
 *   measurement settings and offsets
 * ************************************************************************ */


/*
 *  ADC voltage reference based on Vcc (in mV). 
 */

#define UREF_VCC         5001


/*
 * Offset for the internal bandgap voltage reference (in mV): -100 up to 100
 *  - To compensate any difference between real value and measured value.
 *  - The ADC has a resolution of about 4.88mV for V_ref = 5V (Vcc) and
 *    1.07mV for V_ref = 1.1V (bandgap).
 *  - Will be added to measured voltage of bandgap reference.
 */

#define UREF_OFFSET      0


/*
 *  Exact values of probe resistors.
 *  - Standard value for Rl is 680 Ohms.
 *  - Standard value for Rh is 470k Ohms.
 */

/* Rl in Ohms */
#define R_LOW            680

/* Rh in Ohms */
#define R_HIGH           470000


/*
 *  Offset for systematic error of resistor measurement with Rh (470k) 
 *  in Ohms.
 *  - if resistors >20k measure too high or low adjust the offset accordingly
 *  - standard offset is 350 Ohms
 */

#define RH_OFFSET        350


/*
 *  Resistance of probes (in 0.01 Ohms).
 *  - default offset for PCB tracks and probe leads
 *  - resistance of two probes in series
 *  - assuming all probes have same/similar resistance
 *  - will be updated by self-adjustment
 */

#define R_ZERO           20


/*
 *  Use probe pair specific resistance offsets instead of an
 *  average value for all probes.
 *  - uncomment to enable
 */

//#define R_MULTIOFFSET


/* 
 *  Capacitance of probes (in pF).
 *  - default offset for MCU, PCB tracks and probe leads
 *  - Examples:
 *    capacitance  length
 *    -------------------------
 *     3pF         about 10cm
 *     9pF         about 30cm
 *    15pF         about 50cm
 *  - maximum value: 100
 *  - will be updated by self-adjustment
 */

#define C_ZERO           43


/*
 *  Use probe pair specific capacitance offsets instead of an
 *  average value for all probes.
 *  - uncomment to enable
 */

//#define CAP_MULTIOFFSET


/*
 *  Maximum voltage at which we consider a capacitor being
 *  discharged (in mV).
 */

#define CAP_DISCHARGED   2


/*
 *  Correction factors for capacitors (in 0.1%)
 *  - positive factor increases capacitance value
 *    negative factor decreases capacitance value
 *  - CAP_FACTOR_SMALL for caps < 4.7µF
 *  - CAP_FACTOR_MID for caps 4.7 - 47µF
 *  - CAP_FACTOR_LARGE for caps > 47µF
 */

#define CAP_FACTOR_SMALL      0      /* no correction */ 
#define CAP_FACTOR_MID        -40    /* -4.0% */
#define CAP_FACTOR_LARGE      -90    /* -9.0% */


/*
 *  Number of ADC samples to perform for each mesurement.
 *  - Valid values are in the range of 1 - 255.
 */

#define ADC_SAMPLES      25


/*
 *  100nF AREF buffer capacitor
 *  - used by some MCU boards
 *  - will increase measurement time
 *  - recommendation: replace with 1nF capacitor
 *  - uncomment to enable
 */

//#define ADC_LARGE_BUFFER_CAP



/* ************************************************************************
 *   R & D - meant for firmware developers
 * ************************************************************************ */


/*
 *  Enable read functions for display module.
 *  - display driver and interface settings have to support this
 *  - uncomment to enable
 */

//#define LCD_READ


/*
 *  Read ID of display controller.
 *  - ID is shown at welcome screen (after firmware version)
 *  - requires display read functions (LCD_READ)
 *  - recommended: serial output (UI_SERIAL_COPY)
 *  - uncomment to enable
 */

//#define SW_DISPLAY_ID


/*
 *  Read registers of display controller and output them via TTL serial.
 *  - requires display read functions (LCD_READ) and
 *    serial output (UI_SERIAL_COPY)
 *  - uncomment to enable
 */

//#define SW_DISPLAY_REG



/* ************************************************************************
 *   MCU specific setup to support different AVRs
 * ************************************************************************ */


/* MCU clock */
#define CPU_FREQ    F_CPU


/*
 *  ATmega 328/328P
 */

#if defined(__AVR_ATmega328__)
  #include "config_328.h"


/*
 *  ATmega 324P/324PA/644/644P/644PA/1284/1284P
 */

#elif defined(__AVR_ATmega324P__) || defined(__AVR_ATmega644__) || defined(__AVR_ATmega1284__)
  #include "config_644.h"


/*
 *  ATmega 640/1280/2560
 */

#elif defined(__AVR_ATmega640__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  #include "config_1280.h"


/*
 *  missing or unsupported MCU
 */

#else
  #error <<< No or wrong MCU type selected! >>>
#endif



/* ************************************************************************
 *   Busses
 * ************************************************************************ */


/*
 *  I2C bus
 *  - might be required by some hardware
 *  - could be enabled already in display section (config_<MCU>.h)
 *  - for bit-bang I2C port and pins see I2C_PORT (config_<MCU>.h)
 *  - hardware I2C (TWI) uses automatically the proper MCU pins
 *  - uncomment either I2C_BITBANG or I2C_HARDWARE to enable
 *  - uncomment one of the bus speed modes
 */

//#define I2C_BITBANG                /* bit-bang I2C */
//#define I2C_HARDWARE               /* MCU's hardware TWI */
//#define I2C_STANDARD_MODE          /* 100kHz bus speed */
//#define I2C_FAST_MODE              /* 400kHz bus speed */
//#define I2C_RW                     /* enable I2C read support (untested) */


/*
 *  SPI bus
 *  - might be required by some hardware
 *  - could be enabled already in display section (config_<MCU>.h)
 *  - for bit-bang SPI port and pins see SPI_PORT (config_<MCU>.h)
 *  - hardware SPI uses automatically the proper MCU pins
 *  - uncomment either SPI_BITBANG or SPI_HARDWARE to enable
 */

//#define SPI_BITBANG                /* bit-bang SPI */
//#define SPI_HARDWARE               /* hardware SPI */
//#define SPI_RW                     /* enable SPI read support */


/*
 *  TTL serial interface
 *  - could be enabled already in display section (config_<MCU>.h)
 *  - for bit-bang serial port and pins see SERIAL_PORT (config_<MCU>.h)
 *  - hardware serial uses automatically the proper MCU pins
 *  - uncomment either SERIAL_BITBANG or SERIAL_HARDWARE to enable
 */

//#define SERIAL_BITBANG             /* bit-bang serial */
//#define SERIAL_HARDWARE            /* hardware serial */
//#define SERIAL_RW                  /* enable serial read support */


/*
 *  OneWire bus
 *  - for dedicated I/O pin please see ONEWIRE_PORT (config_<MCU>.h)
 *  - uncomment either ONEWIRE_PROBES or ONEWIRE_IO_PIN to enable
 */

//#define ONEWIRE_PROBES             /* via probes */
//#define ONEWIRE_IO_PIN             /* via dedicated I/O pin */



/* ************************************************************************
 *   ADC clock
 * ************************************************************************ */


/*
 *  ADC clock 
 *  - The ADC clock is 125000Hz by default.
 *  - You could also set 250000Hz, but that exceeds the max. ADC clock
 *    of 200kHz for 10 bit resolution!
 *  - Special case for 20MHz MCU clock: 156250Hz
 */

#if CPU_FREQ == 20000000
  /* 20MHz MCU clock */
  #define ADC_FREQ    156250
#else
  /* all other MCU clocks */
  #define ADC_FREQ    125000
#endif


/*
 *  define clock divider
 *  - supports 1MHz, 2MHz, 4MHz, 8MHz, 16MHz and 20MHz MCU clocks
 *  - we got only 7 fixed prescalers from 2 up to 128
 */

/* 1MHz/250kHz */
#if CPU_FREQ / ADC_FREQ == 4
  #define ADC_CLOCK_DIV (1 << ADPS1) 
#endif

/* 1MHz/125kHz 2MHz/250kHz */
#if CPU_FREQ / ADC_FREQ == 8
  #define ADC_CLOCK_DIV (1 << ADPS1) | (1 << ADPS0)
#endif

/* 2MHz/125kHz 4MHz/250kHz */
#if CPU_FREQ / ADC_FREQ == 16
  #define ADC_CLOCK_DIV (1 << ADPS2)
#endif

/* 4MHz/125kHz 8MHz/250kHz */
#if CPU_FREQ / ADC_FREQ == 32
  #define ADC_CLOCK_DIV (1 << ADPS2) | (1 << ADPS0)
#endif

/* 8MHz/125kHz 16MHz/250kHz */
#if CPU_FREQ / ADC_FREQ == 64
  #define ADC_CLOCK_DIV (1 << ADPS2) | (1 << ADPS1)
#endif

/* 16MHz/125kHz 20MHz/156.25kHz */
#if CPU_FREQ / ADC_FREQ == 128
  #define ADC_CLOCK_DIV (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0)
#endif



/* ************************************************************************
 *   derived values
 * ************************************************************************ */


/*
 *  number of MCU cycles per µs
 *  - min. 1 (for 1MHz)
 *  - max. 20 (for 20MHz)
 */

#define MCU_CYCLES_PER_US     (CPU_FREQ / 1000000)


/*
 *  number of MCU cycles per ADC cycle
 *  - min. 4
 *  - max. 128
 */ 

#define MCU_CYCLES_PER_ADC    (CPU_FREQ / ADC_FREQ)


/*
 *  time of a MCU cycle (in 0.1 ns)
 */

#define MCU_CYCLE_TIME        (10000 / (CPU_FREQ / 1000000))



/* ************************************************************************
 *   options management
 * ************************************************************************ */


/*
 *  storage of program data (EEPROM/Flash)
 */

#if defined (DATA_EEPROM)
  /* memory type */
  #define MEM_TYPE            EEMEM

  /* read functions */
  #define DATA_read_byte(addr)     eeprom_read_byte(addr)
  #define DATA_read_word(addr)     eeprom_read_word(addr)
#elif defined (DATA_FLASH)
  /* memory type */
  #define MEM_TYPE            PROGMEM

  /* read functions */
  #define DATA_read_byte(addr)     pgm_read_byte(addr)
  #define DATA_read_word(addr)     pgm_read_word(addr)
#endif



/*
 *  hardware/software options
 */

/* power switch: prefer soft-latching type */
#ifdef POWER_SWITCH_SOFT
  #ifdef POWER_SWITCH_MANUAL
    #undef POWER_SWITCH_MANUAL
  #endif
#endif


/* additional keys */
/* rotary encoder, increase/decrease push buttons or touch screen */
#if defined (HW_ENCODER) || defined (HW_INCDEC_KEYS) | defined (HW_TOUCH)
  #define HW_KEYS
#endif

/* options which require additional keys */
#ifndef HW_KEYS

  /* key hints */
  #ifdef UI_KEY_HINTS
    #undef UI_KEY_HINTS
  #endif

  /* PWM+ */
  #ifdef SW_PWM_PLUS
    #undef SW_PWM_PLUS
    #define SW_PWM_SIMPLE   
  #endif

  /* squarewave generator */
  #ifdef SW_SQUAREWAVE
    #undef SW_SQUAREWAVE
  #endif

  /* Servo Check */
  #ifdef SW_SERVO
    #undef SW_SERVO
  #endif

  /* IR Sender */
  #ifdef SW_IR_TRANSMITTER
    #undef SW_IR_TRANSMITTER
  #endif

#endif


/* options which require inductance measurement */
#ifndef SW_INDUCTOR

  /* L monitor */
  #ifdef SW_MONITOR_L
    #undef SW_MONITOR_L
  #endif

  /* RCL Monitor */
  #ifdef SW_MONITOR_RCL
    #undef SW_MONITOR_RCL
  #endif

  /* RL Monitor */
  #ifdef SW_MONITOR_RL
    #undef SW_MONITOR_RL
  #endif

#endif


/* options which require ESR measurement */
#if ! defined (SW_ESR) && ! defined (SW_OLD_ESR)
  /* ESR tool */
  #ifdef SW_ESR_TOOL
    #undef SW_ESR_TOOL
  #endif
#endif


/* options which require a MCU clock >= 8MHz */
#if CPU_FREQ < 8000000

  /* ESR measurement */
  #ifdef SW_ESR
    #undef SW_ESR
  #endif

  /* old ESR measurement */
  #ifdef SW_OLD_ESR
    #undef SW_OLD_ESR
  #endif

#endif


/* SPI */
#if defined (SPI_BITBANG) && defined (SPI_HARDWARE)
  #error <<< Select either bitbang or hardware SPI! >>>
#endif

#if defined (SPI_BITBANG) || defined (SPI_HARDWARE)
  #define HW_SPI
#endif

/* 9-Bit SPI requires bit-bang mode */
#ifdef SPI_9
  #ifndef SPI_BITBANG
    #error <<< 9-Bit SPI requires bit-bang mode! >>>
  #endif
#endif


/* I2C */
#if defined (I2C_BITBANG) && defined (I2C_HARDWARE)
  #error <<< Select either bitbang or hardware I2C! >>>
#endif

#if defined (I2C_BITBANG) || defined (I2C_HARDWARE)
  #define HW_I2C
#endif


/* TTL serial */
#if defined (SERIAL_BITBANG) && defined (SERIAL_HARDWARE)
  #error <<< Select either bitbang or hardware serial interface! >>>
#endif

#if defined (SERIAL_BITBANG) || defined (SERIAL_HARDWARE)
  #define HW_SERIAL
#endif

/* VT100 display driver disables other options for serial interface */
#ifdef LCD_VT100
  #ifdef UI_SERIAL_COPY
    #undef UI_SERIAL_COPY
  #endif
  #ifdef UI_SERIAL_COMMANDS
    #undef UI_SERIAL_COMMANDS
  #endif  
#endif

/* options which require TTL serial */
#ifndef HW_SERIAL
  /* VT100 display */
  #ifdef LCD_VT100
    #undef LCD_VT100
  #endif
  /* serial copy */
  #ifdef UI_SERIAL_COPY
    #undef UI_SERIAL_COPY
  #endif
  /* remote commands */
  #ifdef UI_SERIAL_COMMANDS
    #undef UI_SERIAL_COMMANDS
  #endif
#endif

/* options which require TTL serial RW */
#ifndef SERIAL_RW
  #ifdef UI_SERIAL_COMMANDS
    #undef UI_SERIAL_COMMANDS
  #endif
#endif


/* OneWire */
#if defined (ONEWIRE_PROBES) && defined (ONEWIRE_IO_PIN)
  #error <<< Select either probes or dedicated IO pin for Onewire! >>>
#endif

/* options which require OneWire */
#if ! defined (ONEWIRE_PROBES) && ! defined (ONEWIRE_IO_PIN)

  /* DS18B20 */
  #ifdef SW_DS18B20
    #undef SW_DS18B20
  #endif

  /* OneWire scan */
  #ifdef SW_ONEWIRE_SCAN
    #undef SW_ONEWIRE_SCAN
  #endif

#endif


/* touchscreen */
#ifdef TOUCH_PORT
  #define HW_TOUCH
#endif


/* LCD module */
#ifdef LCD_CONTRAST
  #define SW_CONTRAST
#else
  #define LCD_CONTRAST        0
#endif


/* options which require a color display */
#ifndef LCD_COLOR

  /* color coding for probes */
  #ifdef SW_PROBE_COLORS
    #undef SW_PROBE_COLORS
  #endif

#endif


/* options which require a color graphics display */
#if ! defined (LCD_COLOR) || ! defined (LCD_GRAPHIC)

  /* resistor color-codes */
  #ifdef SW_R_E24_5_CC
    #undef SW_R_E24_5_CC
  #endif
  #ifdef SW_R_E24_1_CC
    #undef SW_R_E24_1_CC
  #endif
  #ifdef SW_R_E96_CC
    #undef SW_R_E96_CC
  #endif

#endif


/* component symbols for fancy pinout */
#if defined (SYMBOLS_24X24_H)
  #define SYMBOLS_SELECTED
#endif
#if defined (SYMBOLS_24X24_HF) || defined (SYMBOLS_30X32_HF) || defined (SYMBOLS_32X32_HF)
  #define SYMBOLS_SELECTED
#endif
#if defined (SYMBOLS_24X24_VFP)
  #define SYMBOLS_SELECTED
#endif
#if defined (SYMBOLS_24X24_VP_F)
  #define SYMBOLS_SELECTED
#endif

/* fancy pinout requires graphic display and symbol set */
#ifdef SW_SYMBOLS

  /* graphic display */
  #ifndef LCD_GRAPHIC
    #undef SW_SYMBOLS
  #endif

  /* symbol set */
  #ifndef SYMBOLS_SELECTED
    #undef SW_SYMBOLS
  #endif

#endif


/* frequency counter */
#if defined (HW_FREQ_COUNTER_BASIC) || defined (HW_FREQ_COUNTER_EXT)
  #define HW_FREQ_COUNTER
#endif


/* IR detector/decoder */
#if defined (SW_IR_RECEIVER) && defined (HW_IR_RECEIVER)
  #error <<< Select either probes or dedicated IO pin for IR detector! >>>
#endif


/* rounding for DS18B20 requires DS18B20 support */
#ifdef UI_ROUND_DS18B20
  #ifndef SW_DS18B20
    #undef UI_ROUND_DS18B20
  #endif
#endif


/* read functions for display require bus with read support enabled */
#ifdef LCD_READ
  #if defined(LCD_SPI) && ! defined(SPI_RW)
    #undef LCD_READ
  #endif
  #if defined(LCD_I2C) && ! defined(I2C_RW)
    #undef LCD_READ
  #endif
  /* can't check parallel busses */
#endif

/* display ID requires read functions for display */
#ifdef SW_DISPLAY_ID
  #ifndef LCD_READ
    #undef SW_DISPLAY_ID
  #endif
#endif

/* output of display registers requires read functions for display
   and serial output */
#ifdef SW_DISPLAY_REG
  #ifndef LCD_READ
    #undef SW_DISPLAY_REG
  #endif
  #ifndef UI_SERIAL_COPY
    #undef SW_DISPLAY_REG
  #endif
#endif



/* ************************************************************************
 *   simplify ifdefs
 * ************************************************************************ */


/* E6 norm values */
#if defined (SW_C_E6_T) || defined (SW_L_E6_T)
  #define SW_E6
#endif

/* E12 norm values */
#if defined (SW_C_E12_T) || defined (SW_L_E12_T)
  #define SW_E12
#endif

/* E24 norm values */
#if defined (SW_R_E24_5_T) || defined (SW_R_E24_5_CC) || defined (SW_R_E24_1_T) || defined (SW_R_E24_1_CC)
  #define SW_E24
#endif

/* E96 norm values */
#if defined (SW_R_E96_T) || defined (SW_R_E96_CC)
  #define SW_E96
#endif


/* Show_ENormValues(), Display_EValue() */
#if defined (SW_R_E24_5_T) || defined (SW_R_E24_1_T) || defined (SW_R_E96_T)
  #ifndef FUNC_EVALUE
    #define FUNC_EVALUE
  #endif
  #ifndef SW_R_EXX
    #define SW_R_EXX
  #endif
#endif

#if defined (SW_C_E6_T) || defined (SW_C_E12_T) || defined (SW_L_E6_T) || defined (SW_L_E12_T)
  #ifndef FUNC_EVALUE
    #define FUNC_EVALUE
  #endif
#endif


/* Show_ENormCodes(), Display_ColorCode() */
#if defined (SW_R_E24_5_CC) || defined (SW_R_E24_1_CC) || defined (SW_R_E96_CC)
  #ifndef FUNC_COLORCODE
    #define FUNC_COLORCODE
  #endif
  #ifndef SW_R_EXX
    #define SW_R_EXX
  #endif
#endif


/* SmoothLongKeyPress() */
#if defined (SW_PWM_PLUS) || defined (SW_SERVO) || defined (HW_EVENT_COUNTER) || defined (HW_LC_METER)
  #ifndef FUNC_SMOOTHLONGKEYPRESS
    #define FUNC_SMOOTHLONGKEYPRESS
  #endif
#endif


/* Display_FullValue() */
#if defined (SW_SQUAREWAVE) || defined (SW_PWM_PLUS) || defined (HW_FREQ_COUNTER_EXT) || defined (SW_SERVO)
  #ifndef FUNC_DISPLAY_FULLVALUE
    #define FUNC_DISPLAY_FULLVALUE
  #endif
#endif

#if defined (SW_DS18B20) || defined (HW_EVENT_COUNTER) || defined (SW_DHTXX)
  #ifndef FUNC_DISPLAY_FULLVALUE
    #define FUNC_DISPLAY_FULLVALUE
  #endif
#endif

#if defined (FUNC_EVALUE) || defined (FUNC_COLORCODE) || defined (LC_METER_SHOW_FREQ)
  #ifndef FUNC_DISPLAY_FULLVALUE
    #define FUNC_DISPLAY_FULLVALUE
  #endif
#endif


/* Display_HexByte() */
#if defined (SW_IR_RECEIVER) || defined (HW_IR_RECEIVER) || defined (ONEWIRE_READ_ROM) || defined (SW_ONEWIRE_SCAN) || defined (SW_FONT_TEST) || defined (SW_DISPLAY_REG)
  #ifndef FUNC_DISPLAY_HEXBYTE
    #define FUNC_DISPLAY_HEXBYTE
  #endif
#endif

/* Display_HexValue() */
#if defined (SW_IR_TRANSMITTER) || defined (SW_DISPLAY_ID)
  #ifndef FUNC_DISPLAY_HEXVALUE
    #define FUNC_DISPLAY_HEXVALUE
  #endif
#endif



/* ************************************************************************
 *   EOF
 * ************************************************************************ */
