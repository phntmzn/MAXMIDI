#pragma once

#include <cstdint>

namespace MaxMidi {
    struct MidiEvent {
        /// Time in milliseconds or ticks
        uint32_t time;
        /// MIDI status byte (e.g., Note On, Note Off)
        uint8_t status;
        /// First data byte (e.g., note number)
        uint8_t data1;
        /// Second data byte (e.g., velocity)
        uint8_t data2;
    };
}
