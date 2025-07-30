#pragma once

#include <cstdint>

namespace MaxMidi {

// Represents a MIDI message with timestamp and 3 bytes of data
struct MidiEvent {
    uint32_t time;    // Timestamp in ticks or ms
    uint8_t status;   // Status byte (e.g. 0x90 = Note On)
    uint8_t data1;    // First data byte (e.g. note number)
    uint8_t data2;    // Second data byte (e.g. velocity)
};

} // namespace MaxMidi
