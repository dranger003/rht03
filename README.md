rht03
=======
RHT03 Relative Humidity/Temperature Sensor RPi Protocol Implementation
Copyright(C) 2014, Daniel Ranger

This program is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.


The RHT03 (also known by DHT-22) is a low cost humidity and temperature
sensor with a single wire digital interface. The sensor is calibrated
and doesn't require extra components so you can get right to measuring
relative humidity and temperature.

Compile with:
<pre>gcc -Wall -std=c99 rht03.c -o rht03 -lbcm2835</pre>

RHT03 Digital Humidity & Temperature Sensor Homepage
http://www.humiditycn.com/cp22.html

SparkFun Product Page
https://www.sparkfun.com/products/10167

Datasheet/wire protocol (mirrors)
http://www.humiditycn.com/pic/20135318405067570.pdf
http://dlnmh9ip6v2uc.cloudfront.net/datasheets/Sensors/Weather/RHT03.pdf

This software makes use of the C library for Broadcom BCM 2835 as used in
Raspberry Pi
http://www.airspayce.com/mikem/bcm2835/

Changelog
     May 25th, 2014: Initial release v0.1.
