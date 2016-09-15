# huzzah-8x8led-gol
Conway's Game of Life for the Adafruit
[Huzzah](https://www.adafruit.com/product/2821) / [8x8 LED matrix](https://www.adafruit.com/product/902).
Will almost certainly work on near variations too.

# Build

Install [platformio](http://platformio.org/) if you haven't already:

```console
% virtualenv -p python2.7 ~/platformio
% ~/platformio/bin/pip install -U platformio
% PATH=$PATH:$HOME/platformio/bin
```

To build and upload this project:
```console
% platformio run --target upload
```