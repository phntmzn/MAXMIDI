

#pragma once

#include "EventTypes.hpp"
#include <vector>
#include <string>

namespace MaxMidi {

// Load a Standard MIDI File (.mid) and return a list of decoded events
std::vector<MidiEvent> loadSMF(const std::string& filepath);

// Optional: Write MIDI events to a .mid file
void saveSMF(const std::string& filepath, const std::vector<MidiEvent>& events);

} // namespace MaxMidi