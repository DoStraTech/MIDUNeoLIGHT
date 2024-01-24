# MIDUNeoLIGHT: (DIN) MIDI-UART-Controlled NeoPixel (WS2812B) Lights

## Project Overview

As ChatGPT would tell:
This project is an exciting journey into the world of music, lights, and microcontrollers. It combines the musical intricacy of MIDI (Musical Instrument Digital Interface) with the visual splendor of NeoPixel LEDs. The goal is to create a system where each key press on a MIDI instrument dynamically controls a NeoPixel LED, creating a visual representation of the music played. 

As I would say:
Here is yet another MIDI + LED + Arduino (ESP) project! Unlike multiple projects where USB to MIDI adapters are used, I wanted to wire the good old school DIN MIDI directly to the microcontroller withoud any additional hardware and - it worked!

## Journey

The development of this project was an adventurous collaboration with OpenAI's ChatGPT, a conversational AI model. ChatGPT provided coding assistance, debugging tips, and optimization strategies. We navigated through challenges such as optimizing MIDI processing, handling NeoPixel LEDs, and ensuring responsiveness and reliability of the system.

And as a human i would add: This project was more or less made over the night.

## Features

- **MIDI Input Processing**: Handles MIDI data to track the state of each key.
- **NeoPixel LED Control**: Lights up LEDs based on the MIDI input, with different colors for each MIDI channel.
- **Optimized Performance**: Efficiently manages MIDI data processing and LED control to prevent delays and stuck keys, especially crucial when using hardware with limited processing power like Arduino.
- **Modular Code**: Separate modules for MIDI handling and LED control for better maintainability.
- **Synthesia Support**: Different instruments (channels) play in different colors.

# Hardware and Wiring

### Components Needed

- MIDI Input Device (e.g., MIDI Keyboard or PC USB MIDI adapter)
- Microcontroller (Developed with D1 Mini, compatible with Arduino)
- NeoPixel LED Strip (any WS2812B)
- Appropriate power supply for the LEDs
- Wires and possibly resistors for MIDI input circuit

### Wiring Diagram

- **MIDI Input**: Connect the MIDI device's output to the microcontroller's RX pin. Recomended: Include necessary resistors or use optoisolators as per MIDI specifications to galvanically isolate the circuits and reduce potentional humming.
- Theoretically its works just by shoving the MIDI out Pin to Microcontroller UART RX Pin, e.g. the one used for USB programming. As long as not both inputs are active, you can program the controller, use serial monitor and input MIDI all through the same hardware Serial port! 
- **NeoPixel LEDs**: Connect the data input of the NeoPixel strip to a digital pin on the microcontroller (e.g., D1 on D1 Mini). Ensure the strip is powered adequately. (For singular LEDs at low brightness USB is sufficient)![Alt text](wiring-1.png)
I know that plenty of clever people will point out were specific resistors and protective diodes should go and they will be correct. At this point i wanted a quick-and-dirty solution to light up my piano without a pc and hey - it works.

## Stuck Keys Issue on Arduino

An intriguing challenge we faced was the "stuck keys" phenomenon when running the system on Arduino. This was due to the NeoPixel library disabling interrupts to control the LEDs, which interfered with the timely processing of incoming MIDI messages. The problem was mitigated by optimizing LED updates and moving to a more powerful microcontroller (D1 Mini) for better handling. Arduino Nano can handle six or seven keys at once, but sometimes, one or two key inputs get skipped, so the key, stays on until pressed again. I recomend ESP8266 due to its severly higher processing power.

## Setup and Usage

1. Clone this repository to your local machine.
2. Open the project in the Arduino IDE or compatible software.
3. Ensure all libraries used (e.g., Adafruit_NeoPixel) are installed.
4. Upload the code to your microcontroller.
5. Connect your MIDI device and NeoPixel strip as per the wiring diagram.
6. Power up the system and start playing to see the LEDs react to your music!

## Collaboration and Acknowledgements

A special thanks to the open-source community and multiple MIDI LED projects as inspiration as well as the creators of the libraries used in this project. Also thanks goes to amandaghassaei for the great [MIDI instructable](https://www.instructables.com/Send-and-Receive-MIDI-with-Arduino/). Ff you want to know how to also send MIDI, go check it out!

## Disclaimer and No Warranty

This project is provided "as is", without warranty of any kind, express or implied, including but not limited to the warranties of merchantability, fitness for a particular purpose, and noninfringement. In no event shall the authors, contributors, or copyright holders be liable for any claim, damages, or other liability, whether in an action of contract, tort or otherwise, arising from, out of, or in connection with the project or the use or other dealings in the project.


---

Enjoy creating your musical light show!
