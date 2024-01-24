// MidiHandler.h
#ifndef MidiHandler_h
#define MidiHandler_h

#include <Arduino.h>

class MidiHandler {
public:
    MidiHandler() {
        for (int i = 0; i < numKeys; i++) {
            keyStates[i] = false;
            keyChannels[i] = 0;
        }
    }

    void update() {
        while (Serial.available() > 0) {
            byte midiByte = Serial.read();

            if (midiByte >= 0x80) { // Status byte
                statusByte = midiByte;
                expectingDataByte = true;
            } else if (expectingDataByte) { // First data byte
                dataByte1 = midiByte;
                expectingDataByte = false;
            } else { // Second data byte
                byte command = statusByte & 0xF0;
                byte channel = statusByte & 0x0F;
                if (command == 0x90 || command == 0x80) { // Note On or Note Off message
                    bool isNoteOn = (command == 0x90) && (midiByte != 0x00);
                    keyStates[dataByte1] = isNoteOn;
                    keyChannels[dataByte1] = channel;
                }
            }
        }
    }

    void printStatus() {
        Serial.print("Active Keys: ");
        for (int i = 0; i < numKeys; i++) {
            if (keyStates[i]) {
                Serial.print(i);
                Serial.print(" [");
                Serial.print(keyChannels[i]);
                Serial.print("], ");
            }
        }
        Serial.println();
    }

    bool isKeyPressed(int key) const {
        return key >= 0 && key < numKeys && keyStates[key];
    }

    byte getKeyChannel(int key) const {
        return key >= 0 && key < numKeys ? keyChannels[key] : 0;
    }

private:
    static const int numKeys = 128;
    bool keyStates[numKeys];
    byte keyChannels[numKeys];
    byte statusByte, dataByte1;
    bool expectingDataByte = false;
};

#endif
