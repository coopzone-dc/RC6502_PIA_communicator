New version of the Arduino sketch, for communicating with the PIA 6821 chip on an Apple 1 replica. Mainly the RC6502 but others will be able to use it if that are using the same type of Arduino Nano setup

I have to say credit to Tor-Eirik Bakke Lunde, for creating the replica to begin with. It's great fun going back to the 70's

This software is for use with:

https://github.com/tebl/RC6502-Apple-1-Replica

# INSTALL OPTIONS

You can install it from the command line, see below, or build and install the source code from Arduino IDE. If you use avrdude then you only need to download the HEX file above.

On Linux or Mac OS (sorry don't do windows, but I guess it's simelar). The port may be different on your setup.

avrdude -c arduino -p atmega328p -P /dev/ttyUSB0 -b 115200 -U flash:w:pia_communicator_v3.hex

avrdude: AVR device initialized and ready to accept instructions

Reading | ################################################## | 100% 0.00s

avrdude: Device signature = 0x1e950f (probably m328p)

avrdude: NOTE: "flash" memory has been specified, an erase cycle will be performed

         To disable this feature, specify the -D option.
         
avrdude: erasing chip

avrdude: reading input file "pia_communicator_v3.hex"

avrdude: input file pia_communicator_v3.hex auto detected as Intel Hex

avrdude: writing flash (2804 bytes):

Writing | ################################################## | 100% 0.46s

avrdude: 2804 bytes of flash written

avrdude: verifying flash memory against pia_communicator_v3.hex:

avrdude: load data flash data from input file pia_communicator_v3.hex:

avrdude: input file pia_communicator_v3.hex auto detected as Intel Hex

avrdude: input file pia_communicator_v3.hex contains 2804 bytes

avrdude: reading on-chip flash data:

Reading | ################################################## | 100% 0.37s

avrdude: verifying ...

avrdude: 2804 bytes of flash verified

avrdude: safemode: Fuses OK (E:00, H:00, L:00)

avrdude done.


Thank you.
Have fun.

