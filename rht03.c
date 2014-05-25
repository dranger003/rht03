// rht03.c
//
// RHT03 Relative Humidity/Temperature Sensor RPi Protocol Implementation
// Copyright(C) 2014, Daniel Ranger
//
// This program is free software : you can redistribute it and / or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//
//
// The RHT03 (also known by DHT-22) is a low cost humidity and temperature
// sensor with a single wire digital interface. The sensor is calibrated
// and doesn’t require extra components so you can get right to measuring
// relative humidity and temperature.
//
// Compile with:
// gcc -Wall -std=c99 rht03.c -o rht03 -lbcm2835
//
// RHT03 Digital Humidity & Temperature Sensor Homepage
// http://www.humiditycn.com/cp22.html
//
// SparkFun Product Page
// https://www.sparkfun.com/products/10167
//
// Datasheet/wire protocol (mirrors)
// http://www.humiditycn.com/pic/20135318405067570.pdf
// http://dlnmh9ip6v2uc.cloudfront.net/datasheets/Sensors/Weather/RHT03.pdf
//
// This software makes use of the C library for Broadcom BCM 2835 as used in
// Raspberry Pi
// http://www.airspayce.com/mikem/bcm2835/
//
// Changelog
//		May 25th, 2014: Initial release v0.1.
//

#include <stdio.h>
#include <bcm2835.h>

#define PIN				RPI_GPIO_P1_07
#define TIMEOUT			2000000
#define MAX_TRY			5

// wait()
//		CPU intensive wait (no yield)
// Parameter(s);
//		us		Time to wait
void wait(uint32_t us)
{
	uint64_t t = bcm2835_st_read() + us;
	while (bcm2835_st_read() < t);
}

// rht03_read()
//		Read sensor values
// Parameters:
//		*rh		Relative humidity value
//		*tp		Temperature value
// Returns:
//		0		OK
//		-1		Protocol error
//		-2		Invalid checksum
int rht03_read(double *rh, double *tp)
{
	*rh = *tp = 0;

	// 250ms standby reset
	{
		bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);
		bcm2835_gpio_set(PIN);
		wait(250000);
	}

	// Handshake
	{
		// Initiate sequence
		bcm2835_gpio_clr(PIN);
		wait(10000);
		bcm2835_gpio_set(PIN);
		bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_INPT);

		// ACK response: 20-40 uS LOW, 80 uS HIGH, 80 uS LOW
		uint64_t t = bcm2835_st_read() + TIMEOUT;
		while (bcm2835_gpio_lev(PIN) != LOW)
			if (bcm2835_st_read() > t)
				return -1;

		t = bcm2835_st_read() + TIMEOUT;
		while (bcm2835_gpio_lev(PIN) != HIGH)
			if (bcm2835_st_read() > t)
				return -1;

		t = bcm2835_st_read() + TIMEOUT;
		while (bcm2835_gpio_lev(PIN) != LOW)
			if (bcm2835_st_read() > t)
				return -1;
	}

	// Read/decode 40 bits w/bit value break at 70 uS
	// 0 = 26~28 uS, 1 = 70 uS
	{
		uint64_t ts[40] = { 0 };

		for (int i = 0; i < 40; i++) {
			uint64_t t = bcm2835_st_read() + TIMEOUT;

			while (bcm2835_gpio_lev(PIN) != HIGH)
				if (bcm2835_st_read() > t)
					return -1;

			ts[i] = bcm2835_st_read();
			{
				while (bcm2835_gpio_lev(PIN) != LOW)
					if (bcm2835_st_read() > t)
						return -1;
			}
			ts[i] = bcm2835_st_read() - ts[i];
		}

		// Decode bits into 5 bytes
		// Bytes 1-2	16-bit relative humidity value
		// Bytes 3-4	16-bit temperature value
		// Byte 5		Checksum
		uint8_t bytes[5] = { 0 };
		{
			int j = -1;
			for (int i = 0; i < 40; i++) {
				if ((i % 8) == 0)
					++j;

				bytes[j] <<= 1;
				bytes[j] |= ts[i] >= 70;
			}
		}

		// Validate checksum
		if (((bytes[0] + bytes[1] + bytes[2] + bytes[3]) & 0xff) != bytes[4])
			return -2;

		*rh = ((uint16_t)(bytes[0] << 8) + bytes[1]) / 10.0;
		*tp = ((uint16_t)(bytes[2] << 8) + bytes[3]) / 10.0;
	}

	return 0;
}

int main(int argc, char *argv[])
{
	if (!bcm2835_init()) {
		fprintf(stderr, "bcm2835_init(): Error initializing.\n");
		return -1;
	}

	int res = 0, try_count = 0;
	double rh, tp;

	// Try reading sensor values
	while (try_count++ < MAX_TRY && (res = rht03_read(&rh, &tp)) != 0);

	if (res == 0)
		printf("T: %.2f C\nH: %.2f %%\n", tp, rh);

	bcm2835_close();

	return res;
}
