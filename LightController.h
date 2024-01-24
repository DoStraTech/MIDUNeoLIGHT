// LightController.h
#ifndef LightController_h
#define LightController_h

#include <Adafruit_NeoPixel.h>
#include "MidiHandler.h"

class LightController {
public:
  LightController(uint16_t numPixels, uint8_t pin)
    : pixels(numPixels, pin, NEO_GRB + NEO_KHZ800) {
    pixels.begin();
    pixels.setBrightness(10);
    memset(lastKeyStates, 0, sizeof(lastKeyStates));
    updateRequired = false;
  }

  void update(const MidiHandler& midiHandler) {
    unsigned long currentTime = millis();
    if (currentTime - lastUpdateTime > 10) {
      updateRequired = false;  // Reset update flag
      for (int i = 0; i < pixels.numPixels(); i++) {
        int key = i + 21;  // Starting key 21 so MIDI 21 --> LED 0
        bool keyPressed = midiHandler.isKeyPressed(key);
        if (keyPressed != lastKeyStates[i]) {
          lastKeyStates[i] = keyPressed;
          updateRequired = true;  // Set flag if any state changed
          if (keyPressed) {
            byte channel = midiHandler.getKeyChannel(key);
            pixels.setPixelColor(i, channelColors[channel]);
          } else {
            pixels.setPixelColor(i, pixels.Color(0, 0, 0));  // Off
          }
        }
      }
      if (updateRequired) {
        pixels.show();
      }
      lastUpdateTime = currentTime;
    }
  }

  bool updateRequired;  // Flag to indicate if an update was performed

private:
  Adafruit_NeoPixel pixels;
  unsigned long lastUpdateTime = 0;
  bool lastKeyStates[78];  // Track the last state of each key

  // Define colors for each MIDI channel
    uint32_t channelColors[16] = {
      pixels.Color(0, 255, 0),   // Channel 0: Green
      pixels.Color(0, 0, 255),   // Channel 1: Blue
      pixels.Color(255, 165, 0), // Channel 2: Orange
      pixels.Color(255, 255, 0), // Channel 3: Yellow
      pixels.Color(238, 130, 238), // Channel 4: Violet
      pixels.Color(255, 0, 0),   // Channel 5: Red
      pixels.Color(0, 255, 255), // Cyan
      pixels.Color(255, 20, 147), // Deep Pink
      pixels.Color(255, 140, 0), // Dark Orange
      pixels.Color(173, 255, 47), // Green Yellow
      pixels.Color(138, 43, 226), // Blue Violet
      pixels.Color(72, 209, 204), // Medium Turquoise
      pixels.Color(75, 0, 130), // Indigo
      pixels.Color(255, 99, 71), // Tomato
      pixels.Color(127, 255, 0), // Chartreuse
      pixels.Color(0, 191, 255)  // Deep Sky Blue
    };
};

#endif
