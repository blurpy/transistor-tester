# transistor-tester

Documentation of my modifications to the [AVR Transistortester](https://www.mikrocontroller.net/articles/AVR_Transistortester).

A transistor tester is a device where you can insert different kinds of electronic components and have them analyzed. It not only reads transistors and tells you whether it's NPN or PNP, but it tells you the resistance of resistors or capacitance of capacitors, and more. There are many different types, and they are usually very cheap. 

I have the [GM328 kit from Banggood](https://www.banggood.com/DIYAssembled-GM328-Transistor-Tester-Diode-Capacitance-LCR-Generator-With-Case-Kit-p-1163916.html?ID=530527&cur_warehouse=CN). It's usually called AY-AT instead, as it's not really a GM328.

<img src="resources/gm328-kit.jpg" width="600px"/>

Notable hardware:

* ATMEGA328P with 8MHz crystal
* ST7735 160x128px screen
* Rotary encoder
* 5.5mm x 2.1mm center positive barrel jack for 9V
* Terminals for frequency generator, frequency counter and voltage reader
* ZIF socket for analyzing components
* Holtek HT7550-1 voltage regulator
* WS TL431AA voltage reference

Firmware: 1.12k


## Modifications

To improve the accuracy of the tester there are some simple modifications you can do.

![](resources/AY-AT-J1.3.png)

(Image from https://github.com/Upcycle-Electronics/AVR-Transistor-Tester)

See also [this post on eevblog](https://www.eevblog.com/forum/testgear/$20-lcr-esr-transistor-checker-project/msg1286025/#msg1286025).

From the [readme of the k-firmware](https://github.com/madires/Transistortester-Warehouse/blob/master/Documentation/ttester-1.13k.English.pdf):

"_The resistors R1 to R6 are critical for measurements and this 680Ω and 470kΩ resistors should be
 measurement type resistors (tolerance of 0.1%) to get the full accuracy._"
 
 "_The additional 2.5V precision voltage reference connected at pin PC4 (ADC4) can be used to check and calibrate the VCC voltage, but is not required. You can use a LM4040-AIZ2.5 (0.1%), a LT1004CZ-2.5 (0.8%) or a LM336-Z2.5 (0.8%) as voltage reference. If you don’t install the precision voltage reference and you don’t add the relay extension, you should install a pull up resistor R16 to PC4 with a higher resistance value (47kΩ). This helps the software to detect the missing voltage reference._"

From the [readme of the m-firmware](https://github.com/madires/Transistortester-Warehouse/blob/master/Documentation/ctester-1.39m.English.pdf):
 
 "_The external 2.5V voltage reference should be only enabled if it's at least 10 times more precise than the voltage regulator. Otherwise it would make the results worse. If you're using a MCP1702 with a typical tolerance of 0.4% as voltage regulator you really don't need a 2.5V voltage reference._"

I chose to order 0.1% resistors and just the MCP1702 voltage regulator, skipping the voltage reference. Also added a 16MHz crystal for increased speed:
 
* 3x [TE Connectivity H8470KBZA - Metal Film Resistor 470K 0.1%](https://www.mouser.com/ProductDetail/279-H8470KBZA)
* 3x [TE Connectivity H8680RBYA - Metal Film Resistor 680R 0.1%](https://www.mouser.com/ProductDetail/279-H8680RBYA) 
* 1x [Microchip MCP1702-5002E/TO - LDO Voltage Regulator 5V 250mA 0.1%](https://www.mouser.com/ProductDetail/579-MCP1702-5002E-TO)  
* 1x [IQD LFXTAL003240 - 16MHz Quartz](https://www.elfadistrelec.no/en/quartz-tht-16mhz-iqd-lfxtal003240/p/17451701) 

The concrete changes, referenced to the schematics:

* Y1: 16MHz crystal instead of 8Mhz
* R1, R3, R5: 680R 0.1% tolerance instead of 1%
* R2, R4, R6: 470k 0.1% tolerance instead of 1%
* IC2: MCP1702 high precision voltage regulator instead of HT7550 low precision voltage regulator. Pin compatible.
* IC3: TL431A voltage reference is not necessary because of MCP1702.
* R16: Due to missing voltage reference, this 2k2 resistor is not necessary with the m-firmware. Need to be 47k if using k-firmware.


## Firmware

* https://www.mikrocontroller.net/svnbrowser/transistortester/Software/Markus/
* https://www.mikrocontroller.net/svnbrowser/transistortester/Software/trunk/mega328_color_kit/
* https://github.com/madires/Transistortester-Warehouse/tree/master/Firmware

TODO - choice. configure, build, flash
