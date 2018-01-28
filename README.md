Overview
----------------------
Porting FreeRTOS to AT91RM9200 kit

What we need
---------------------
1.Git
2.Cross compiling gcc
3.FreeRTOS distribution pack v.9.0.0rc2

Using
--------------------
Kit has same memory eqipment as the original Atmel AT..-EK testing board with
the exception of using next flash the same type on CS2. Peripherial connections
are different, LEDs in original board are pretty simle on PIO-B0-2. This simple
test can be used with original board redefining LED_GREEN to LED_RED.
For further working with project is graphics lcd panel based on Toshiba T6963C
using CS3 initialized in startup.

Notes
-------------------
Porting is based on AT91FR4800 demo. Peripherial memory map similar.
Porting code needed to be adapted to propriety arm header file (using Rousset
wide using files - don't like this thousand lines files - but external software
it's the semplest way. Seems to be quite complet but nevertheless I had to add
some defs to simply adapt demo code). Startup file completely new - tested on
bare metal project. Master clock initialization troubleshot is described in
AT91RM9200 errata. (To explain strange MCK setting in startup).
Makefile can build project in debug and release configuration - each has own
ld configuration file. Debug conf link to SDRAM, is ready for using JTAG
debugging through OpenOCD with jtag.cfg and AT91RM9200-EK.cfg. Build syntax
is the make CONF=DBG or make CONF=REL. (Makefile is also able to link to
internal RAM for direct upload by serial DBG interface, but it's not usable
for this project. Max size of binary in this case is to 12kB. Build syntax is
make CONF=IRA.) Each build has its own output dir. 
For succesfull build unzipped FreeRTOS release somwhere in directory space
must exist and link in git repository must be readjusted. Output name is set to
test and after build test.elf and test.bin are in CONF dir.
Conditional clock and memories configuration is for not conflict reason in DBG
configuration vi OpenOCD cfg file - has it's own.

Git branches
-----------------
"master" - main branch, always contain latest version

Contact info
----------------
Author: Zdenek Kotalik
E-mail: zkotalik@yahoo.com
