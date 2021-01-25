# Original GM328 firmware

The GM328 AY-AT comes with the fuses of the ATmega328P configured in read protected mode, meaning we can not backup the firmware. Trying to read the chip will only result in files filled with the value `FF`. 
One user was lucky and got an unprotected chip, and uploaded the firmware (v1.12k) [here](https://www.eevblog.com/forum/testgear/$20-lcr-esr-transistor-checker-project/msg3085915/#msg3085915). The files are also available in this folder.
