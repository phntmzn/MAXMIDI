

#include "maxmidi/EventTypes.hpp"
#include <iostream>
#include <cassert>

using namespace MaxMidi;

int main() {
    // Test default MidiEvent values
    MidiEvent e1 {100, 0x90, 60, 100}; // Note On for Middle C

    assert(e1.time == 100);
    assert(e1.status == 0x90);  // Note On
    assert(e1.data1 == 60);     // Note number
    assert(e1.data2 == 100);    // Velocity

    std::cout << "MidiEvent test passed." << std::endl;
    return 0;
}