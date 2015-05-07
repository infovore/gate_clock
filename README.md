# GateClock

GateClock is a little clock for synthesizers and the like. At the moment it does almost - but not quite - nothing, but is a starting point.

## Hardware

I used a TeensyLC, but I'm sure you could adapt this to any *duino like system. Otherwise, there's:

* 3.5mm mono out between ground and pin 11 (`pulsePin`)
* Rotary encoder with A/B pins on 5 and 6, and ground
* poteniometer with power, ground, and then wiper connected to pin 15 (A0 on a Teensy)
* built in LED on pin 13

## Usage

Starts at 120bpm. LED will blink for 50ms once per beat (quarter note). Mono jack will be high for 50ms every eighth note. Connected to a Korg Volca's sync in jack, that'll clock it for you.

Rotate the encoder to adjust the tempo.

The poteniometer does its best to apply something approximating swing, but because the Volca is clocked on 8ths, it's a bit rubbish. Sorry.

It'd probably also work with anything else.

## Next steps

I'd like some CV out too.