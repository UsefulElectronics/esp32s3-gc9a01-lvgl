
[![Build Status](https://img.shields.io/badge/USEFUL%20ELECTRONICS-YOUTUBE-red)](https://www.youtube.com/user/wardzx1)

# Sponsors

### PCBWay
Tutorial Series Sponsor PCBWay Website. You can get extra free coupons using the link below:

[<img src="https://github.com/UsefulElectronics/esp32s3-gc9a01-lvgl/blob/main/banner/banner(320x100).gif">](https://www.pcbway.com/setinvite.aspx?inviteid=582640)

***

# ESP32S3 Interfacing Rotary Encoder and GC9A01 TFT Rounded Display with LVGL
***
### [Tutorial Link](https://youtu.be/77VYMpIAbq4) On [![Build Status](https://img.shields.io/badge/YouTube-FF0000?style=for-the-badge&logo=youtube&logoColor=white)](https://www.youtube.com/wardzx1) 

In this tutorial, Rotary encoder is interfaced with ESP32S3 pulse counter peripheral that allows obtaining the position and rotation direction of the rotary encoder using 2 pins. 

The obtained rotary encoder position value is shown on GC9A01 rounded display using LVGL library. 

The working principle of rotary encoder and involved hardware is explained in details with the used code. 
![Circuit Diagram](https://github.com/UsefulElectronics/esp32s3-gc9a01-lvgl/blob/main/circuit%20diagram/cover1.png)
***

# ESP32S3 GC9A01 LVGL Smart Watch
***
### [Tutorial Link](https://youtu.be/Td08fweKXwY) On [![Build Status](https://img.shields.io/badge/YouTube-FF0000?style=for-the-badge&logo=youtube&logoColor=white)](https://www.youtube.com/wardzx1) 

In this tutorial, ESP32S3 MCU is used to display time and temperature data on a round display with a nice looking user interface that is designed using LVGL library with the help of Squareline Studio.

SNTP is used in order to get real time data over TCP connection with WiFi. The MCU processes the data and prints it on the GC9A01 display that is interfaced over SPI protocol.

Temperature data, on the other hand, is obtained over MQTT connection with Node-Red that is running on a raspberry pi, Which takes a request from an MQTT topic to send HTTP GET request OpenWeather API to obtain weather related string and then filter out the JSON file to get only the temperature data to publish it to an MQTT topic that the ESP32S3 is subscribed to.

Every part regarding the user interface design is also explained in details using SquareLine Studio.
![Circuit Diagram](https://github.com/UsefulElectronics/esp32s3-gc9a01-lvgl/blob/main/circuit%20diagram/circuit%20diagram.PNG)
***

# ESP32S3 HLK-LD1125H Human Presence Sensor
***
### [Tutorial Link](https://youtu.be/RXj-JX6W-YE) On [![Build Status](https://img.shields.io/badge/YouTube-FF0000?style=for-the-badge&logo=youtube&logoColor=white)](https://www.youtube.com/wardzx1) 

In this tutorial, ESP32S3 MCU is programmed to show Human Presence Radar data that is received over UART on GC9A01 round display that is driven over SPI.

The human presence radar continuously sends detected object distance and its movement type. the MCU takes the data converts it and prints it on the round display.

The nicely looking user interface is designed using Square line studio with LVGL library.

The radar module is tested to detect moving objects and human behind obstacle like door or wall. check out the test results

![Circuit Diagram](https://github.com/UsefulElectronics/esp32s3-gc9a01-lvgl/blob/main/circuit%20diagram/HLK-LD1125H.png)

| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- | -------- |

# SPI LCD and Touch Panel Example

[esp_lcd](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/lcd.html) provides several panel drivers out-of box, e.g. ST7789, SSD1306, NT35510. However, there're a lot of other panels on the market, it's beyond `esp_lcd` component's responsibility to include them all.

`esp_lcd` allows user to add their own panel drivers in the project scope (i.e. panel driver can live outside of esp-idf), so that the upper layer code like LVGL porting code can be reused without any modifications, as long as user-implemented panel driver follows the interface defined in the `esp_lcd` component.

This example shows how to use GC9A01 or ILI9341 display driver from Component manager in esp-idf project. These components are using API provided by `esp_lcd` component. This example will draw a fancy dash board with the LVGL library. For more information about porting the LVGL library, you can also refer to [another lvgl porting example](../i80_controller/README.md).

## Touch controller STMPE610

In this example you can enable touch controller STMPE610 connected via SPI. The SPI connection is shared with LCD screen.

## How to use the example

### Hardware Required

* An ESP development board
* An GC9A01 or ILI9341 LCD panel, with SPI interface (with/without STMPE610 SPI touch)
* An USB cable for power supply and programming

### Hardware Connection

The connection between ESP Board and the LCD is as follows:

```
       ESP Board                       GC9A01/ILI9341 Panel + TOUCH
┌──────────────────────┐              ┌────────────────────┐
│             GND      ├─────────────►│ GND                │
│                      │              │                    │
│             3V3      ├─────────────►│ VCC                │
│                      │              │                    │
│             PCLK     ├─────────────►│ SCL                │
│                      │              │                    │
│             MOSI     ├─────────────►│ MOSI               │
│                      │              │                    │
│             MISO     |◄─────────────┤ MISO               │
│                      │              │                    │
│             RST      ├─────────────►│ RES                │
│                      │              │                    │
│             DC       ├─────────────►│ DC                 │
│                      │              │                    │
│             LCD CS   ├─────────────►│ LCD CS             │
│                      │              │                    │
│             TOUCH CS ├─────────────►│ TOUCH CS           │
│                      │              │                    │
│             BK_LIGHT ├─────────────►│ BLK                │
└──────────────────────┘              └────────────────────┘
```

The GPIO number used by this example can be changed in [lvgl_example_main.c](main/spi_lcd_touch_example_main.c).
Especially, please pay attention to the level used to turn on the LCD backlight, some LCD module needs a low level to turn it on, while others take a high level. You can change the backlight level macro `EXAMPLE_LCD_BK_LIGHT_ON_LEVEL` in [lvgl_example_main.c](main/spi_lcd_touch_example_main.c).

### Build and Flash

Run `idf.py -p PORT build flash monitor` to build, flash and monitor the project. A fancy animation will show up on the LCD as expected.

The first time you run `idf.py` for the example will cost extra time as the build system needs to address the component dependencies and downloads the missing components from registry into `managed_components` folder.

(To exit the serial monitor, type ``Ctrl-]``.)

See the [Getting Started Guide](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html) for full steps to configure and use ESP-IDF to build projects.

### Example Output

```bash
...
I (409) cpu_start: Starting scheduler on APP CPU.
I (419) example: Turn off LCD backlight
I (419) gpio: GPIO[2]| InputEn: 0| OutputEn: 1| OpenDrain: 0| Pullup: 0| Pulldown: 0| Intr:0
I (429) example: Initialize SPI bus
I (439) example: Install panel IO
I (439) gpio: GPIO[5]| InputEn: 0| OutputEn: 1| OpenDrain: 0| Pullup: 0| Pulldown: 0| Intr:0
I (449) example: Install GC9A01 panel driver
I (459) gpio: GPIO[3]| InputEn: 0| OutputEn: 1| OpenDrain: 0| Pullup: 0| Pulldown: 0| Intr:0
I (589) gpio: GPIO[0]| InputEn: 0| OutputEn: 1| OpenDrain: 0| Pullup: 0| Pulldown: 0| Intr:0
I (589) example: Initialize touch controller STMPE610
I (589) STMPE610: TouchPad ID: 0x0811
I (589) STMPE610: TouchPad Ver: 0x03
I (599) example: Turn on LCD backlight
I (599) example: Initialize LVGL library
I (609) example: Register display driver to LVGL
I (619) example: Install LVGL tick timer
I (619) example: Display LVGL Meter Widget
...
```
