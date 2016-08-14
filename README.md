# TSL2561_Simple_Library
 A simple library in plain C without external dependencies for TSL2561 ambient light sensor to be used with Raspberry Pi or any Microcontroller.

Taken from blog: http://dino.ciuffetti.info/2014/03/tsl2561-light-sensor-on-raspberry-pi-in-c/

This is an example:
```
/* prepare the sensor
(the first parameter is the raspberry pi i2c master controller attached to the TSL2561, the second is the i2c selection jumper)
The i2c selection address can be one of: TSL2561_ADDR_LOW, TSL2561_ADDR_FLOAT or TSL2561_ADDR_HIGH
*/
TSL2561 light1 = TSL2561_INIT(1, TSL2561_ADDR_FLOAT);

/* initialize the sensor */
rc = TSL2561_OPEN(&light1);

/* sense the luminosity from the sensor (lux is the luminosity taken in "lux" measure units)
the last parameter can be 1 to enable library auto gain, or 0 to disable it */
rc = TSL2561_SENSELIGHT(&light1, &broadband, &ir, &lux, 1);

TSL2561_CLOSE(&light1);
```

Compile:
```
gcc -Wall -O2 -o TSL2561.o -c TSL2561.c
gcc -Wall -O2 -o TSL2561_test.o -c TSL2561_test.c
gcc -Wall -O2 -o TSL2561_test TSL2561.o TSL2561_test.o
```
The output is like this:
```
root@rasponi:~/test/gpio# ./TSL2561_test
Test. RC: 0(Success), broadband: 141, ir: 34, lux: 12
```
As you can see it’s very easy at this point to get the light measures in C. Just include TSL2561.c and TSL2561.h inside your project and use the public APIs to setup and sense the IC.

p.s.1: I left the hardware stuff out of this article (just attach +vcc, gnd and i2c bus to the sensor
p.s.2: you have to load two kernel modules to get i2c bus working on you Raspberry pi:
```
modprobe i2c_bcm2708
modprobe i2c_dev
```
Author: Ciao, Dino.
