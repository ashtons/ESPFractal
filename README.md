# ESPFractal
Simple implementation of a Mandelbrot fractal on an ESP with a TFT display

## Setup

Install the ESP32 board support and the `TFT_eSPI` library in Arduino IDE.

`TFT_eSPI` must be configured in the library's setup file because the library is
compiled separately from the sketch. 

![Sample Result](docs/fractal.png)

![Sample Animation](docs/animation.gif)

![Sample Electric Animation](docs/electric.gif)