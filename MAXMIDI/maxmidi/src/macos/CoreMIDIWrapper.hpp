

#pragma once

#include "maxmidi/EventTypes.hpp"
#include <string>
#include <vector>

namespace MaxMidi {

// Initializes CoreMIDI client and creates input/output ports
void initializeMIDIClient();

// Tears down client and closes ports
void shutdownMIDIClient();

// Sends a raw MIDI event to the selected output
void sendMIDIEvent(uint8_t status, uint8_t data1, uint8_t data2);

// Lists available output destinations
void listDestinations();

// Lists available input sources
void listSources();

// Sets active output device index
bool selectDestination(int index);

// Sets active input device index and connects it to the input callback
bool selectInputSource(int index);

// Returns the number of available output devices
int getDestinationCount();

} // namespace MaxMidi