# ESPFractal
Simple implementation of a Mandelbrot fractal on an ESP with a TFT display

## Setup

Install the ESP32 board support and the `TFT_eSPI` library in Arduino IDE.

`TFT_eSPI` must be configured in the library's setup file because the library is
compiled separately from the sketch. 

![Sample Result](docs/fractal.png)

![Sample Animation](docs/animation.gif)

## Animated preview

The companion Python script can render a short, seamless zoom-and-orbit animation:

```bash
python3 -m pip install Pillow
python3 animate_fractal.py
```

This creates `fractal_animation.gif` with 12 frames. The frame count and playback
speed can be changed, for example:

```bash
python3 animate_fractal.py preview.gif --frames 15 --duration 80
```
