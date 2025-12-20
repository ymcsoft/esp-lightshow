# ESP32 Christmas Light Show

This project is a port from a Sample Raspberry Pi Pico project that uses the Adafruit Neopixel library to create various light show effects. The project demonstrates how to control NeoPixel LEDs using the ESP32-C3/ESP32-C6 chipset.

## Features

- Solid color effect
- Glowing effect
- Sparkle effect
- Color wipe effect
- Theater chase effect
- Rainbow effect
- Rainbow chase effect

## Prerequisites

- ESP32-C3/ESP32-C6 chipset
- NeoPixel LEDs
- CMake (version 3.13 or higher)
- ESP-IDF
- PlatformIO installed
- GCC (GNU Compiler Collection)
- Python 3 (for ESP-IDF setup)
- Git (for cloning repositories)

## Building the Project

1. Install PlatformIO:
    Follow the instructions on the [PlatformIO installation page](https://platformio.org/install) to set up PlatformIO on your system. Minimum required version of PlatformIO is 1.6.16 or higher.

2. Clone the Repository:

   ```sh
   git clone https://github.com/ymcsoft/esp-lightshow.git
   cd esp-lightshow
    ```
3. Connect the ESP32-C3/ESP32-C6 to your computer via USB.
4. Build and Upload the Code:
     Run the following command to build and upload the code to the ESP32-C6 chipset: 
    ```sh
    pio run -t upload -e esp32c6
    ```
    Run the following command to build and upload the code to the ESP32-C3 chipset: 
    ```sh
    pio run -t upload -e esp32c3
    ```

## Usage
Once the code is uploaded to the chipset, it will start running the light show effects on the connected NeoPixel LEDs.
## License
This project is licensed under the MIT License.
## Developed By
This project was developed by Yuri Moiseyenko, © YMC Software Inc. All rights reserved.