## JWSESP 3 Panel

> Prayer Time Clock (ID) Build to Nodemcu Microcontroller

### Features
- Prayer Time with Latitude, Longitude and Timezone configuration
- Hijr Day and Java Day Display
- Display Info
- Prayer Time Fix Minute
- API Usage Filesystem write
- JSON Response API
  

### Usage
- Nodemcu Microcontroller (Tested on ESP8266 v1.0 Lolin)
- DMD Panel P10 (16x32) x3
- RTC DS3231
- Buzzer

### Pin Configuration

#### DMD P10 Panel
| DMD P10 | NODEMCU | 
| ------- | ------- |
| A       | GPIO 16 |
| B       | GPIO 12 |
| CLK     | GPIO 14 |
| SCK     | GPIO 0  |
| R       | GPIO 13 |
| NOE     | GPIO 15 |
| GND     | GND     |

#### RTC DS3231
| RTC     | NODEMCU | 
| ------- | ------- |
| SDA     | GPIO 5  |
| SCL     | GPIO 4  |
| VCC     | VCC     |
| GND     | GND     |

#### BUZZER
| BUZZER  | NODEMCU | 
| ------- | ------- |
| +       | GPIO 3  |
| -       | GND     |

### Reference
📖 [API USAGE](/docs/API.md)

### Note
- Release GPIO 3 pin (Buzzer) when flash
- This Sketch is currently under testing. If there is an error, I will fix it asap