#include <stdio.h>
#include <string.h>
#include "TSL2561.h"

int main() {
	int i;
	int rc;
	uint16_t broadband, ir;
	uint32_t lux=0;
	TSL2561 lights[3]; // we can handle 3 sensors

	// prepare the sensors
	// (the first parameter is the raspberry pi i2c master controller attached to the TSL2561, the second is the i2c selection jumper)
	// The i2c selection address can be one of: TSL2561_ADDR_LOW, TSL2561_ADDR_FLOAT or TSL2561_ADDR_HIGH
	
	// prepare all sensors
	/* cannot assign that way
	lights[0] = TSL2561_INIT(1, TSL2561_ADDR_LOW);
	lights[1] = TSL2561_INIT(1, TSL2561_ADDR_FLOAT);
	lights[2] = TSL2561_INIT(1, TSL2561_ADDR_HIGH);
	*/

	// initialize at runtime instead
	// FIRST SENSOR --> TSL2561_ADDR_LOW
	lights[0].adapter_nr=1;						// change this according to your i2c bus
	lights[0].sensor_addr=TSL2561_ADDR_LOW;				// don't change this
	lights[0].integration_time=TSL2561_INTEGRATIONTIME_402MS;	// don't change this
	lights[0].gain=TSL2561_GAIN_16X;				// don't change this
	lights[0].adapter_fd=-1;					// don't change this
	lights[0].lasterr=0;						// don't change this
	bzero(&lights[0].buf, sizeof(lights[0].buf));			// don't change this

	// SECOND SENSOR --> TSL2561_ADDR_FLOAT
	lights[1].adapter_nr=1;						// change this according to your i2c bus
	lights[1].sensor_addr=TSL2561_ADDR_FLOAT;			// don't change this
	lights[1].integration_time=TSL2561_INTEGRATIONTIME_402MS;	// don't change this
	lights[1].gain=TSL2561_GAIN_16X;				// don't change this
	lights[1].adapter_fd=-1;					// don't change this
	lights[1].lasterr=0;						// don't change this
	bzero(&lights[1].buf, sizeof(lights[1].buf));			// don't change this
	
	// THIRD SENSOR --> TSL2561_ADDR_HIGH
	lights[2].adapter_nr=1;						// change this according to your i2c bus
	lights[2].sensor_addr=TSL2561_ADDR_HIGH;			// don't change this
	lights[2].integration_time=TSL2561_INTEGRATIONTIME_402MS;	// don't change this
	lights[2].gain=TSL2561_GAIN_16X;				// don't change this
	lights[2].adapter_fd=-1;					// don't change this
	lights[2].lasterr=0;						// don't change this
	bzero(&lights[2].buf, sizeof(lights[2].buf));			// don't change this
	
	// initialize the sensors
	for(i=0; i<3; i++) {
		rc = TSL2561_OPEN(&lights[i]);
		if(rc != 0) {
			fprintf(stderr, "Error initializing TSL2561 sensor %i (%s). Check your i2c bus (es. i2cdetect)\n", i+1, strerror(lights[i].lasterr));
			return 1;
		}
		// set the gain to 1X (it can be TSL2561_GAIN_1X or TSL2561_GAIN_16X)
		// use 16X gain to get more precision in dark ambients, or enable auto gain below
		rc = TSL2561_SETGAIN(&lights[i], TSL2561_GAIN_1X);

		// set the integration time
		// (TSL2561_INTEGRATIONTIME_402MS or TSL2561_INTEGRATIONTIME_101MS or TSL2561_INTEGRATIONTIME_13MS)
		// TSL2561_INTEGRATIONTIME_402MS is slower but more precise, TSL2561_INTEGRATIONTIME_13MS is very fast but not so precise
		rc = TSL2561_SETINTEGRATIONTIME(&lights[i], TSL2561_INTEGRATIONTIME_101MS);
	}
	
	// you can now sense each sensor when you like
	for(i=0; i<3; i++) {
		// sense the luminosity from the sensors (lux is the luminosity taken in "lux" measure units)
		// the last parameter can be 1 to enable library auto gain, or 0 to disable it
		rc = TSL2561_SENSELIGHT(&lights[i], &broadband, &ir, &lux, 1);
		printf("Test sensor %i. RC: %i(%s), broadband: %i, ir: %i, lux: %i\n", i+1, rc, strerror(lights[i].lasterr), broadband, ir, lux);
	}
	
	// when you have finisched, you can close things
	for(i=0; i<3; i++) {
		TSL2561_CLOSE(&lights[i]);
	}
	
	return 0;
}
