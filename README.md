rht03
=======
RHT03 Relative Humidity/Temperature Sensor RPi Protocol Implementation<br />
Copyright(C) 2014, Daniel Ranger<br />
<br />
This program is free software : you can redistribute it and / or modify<br />
it under the terms of the GNU General Public License as published by<br />
the Free Software Foundation, either version 3 of the License, or<br />
(at your option) any later version.<br />
<br />
This program is distributed in the hope that it will be useful,<br />
but WITHOUT ANY WARRANTY; without even the implied warranty of<br />
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the<br />
GNU General Public License for more details.<br />
<br />
You should have received a copy of the GNU General Public License<br />
along with this program. If not, see <http://www.gnu.org/licenses/>.<br />
<br />
<br />
The RHT03 (also known by DHT-22) is a low cost humidity and temperature<br />
sensor with a single wire digital interface. The sensor is calibrated<br />
and doesn't require extra components so you can get right to measuring<br />
relative humidity and temperature.<br />
<br />
Compile with:<br />
<pre>gcc -Wall -std=c99 rht03.c -o rht03 -lbcm2835</pre>
<br />
RHT03 Digital Humidity & Temperature Sensor Homepage<br />
http://www.humiditycn.com/cp22.html<br />
<br />
SparkFun Product Page<br />
https://www.sparkfun.com/products/10167<br />
<br />
Datasheet/wire protocol (mirrors)<br />
http://www.humiditycn.com/pic/20135318405067570.pdf<br />
http://dlnmh9ip6v2uc.cloudfront.net/datasheets/Sensors/Weather/RHT03.pdf<br />
<br />
This software makes use of the C library for Broadcom BCM 2835 as used in<br />
Raspberry Pi<br />
http://www.airspayce.com/mikem/bcm2835/<br />
<br />
Changelog<br />
     May 25th, 2014: Initial release v0.1.<br />
