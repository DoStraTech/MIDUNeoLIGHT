#include "MidiHandler.h"
#include "LightController.h"

MidiHandler midiHandler;
LightController lightController(78, D1); // Update with the correct pin for NeoPixels

void setup() {
    Serial.begin(31250); // MIDI baud rate
}

void loop() {
    midiHandler.update();
    lightController.update(midiHandler);

    if (lightController.updateRequired) {
        midiHandler.printStatus();
        lightController.updateRequired = false; // Reset the flag
    }
}
