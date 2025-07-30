#include "maxmidi/MaxMidi.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <CoreMIDI/CoreMIDI.h>
#include "maxmidi/MaxMidi.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <CoreMIDI/CoreMIDI.h>

// Forward declarations for MaxMidi functions used in this test
namespace MaxMidi {
    void initialize();
    void shutdown();
    void sendNoteOn(int channel, int note, int velocity);
    void sendNoteOff(int channel, int note, int velocity);
    void listDestinations();
    int getDestinationCount();
}

int main() {
    try {
        MaxMidi::initialize();

        std::cout << "Available MIDI Output Destinations:\n";
        MaxMidi::listDestinations();

        if (MaxMidi::getDestinationCount() == 0) {
            std::cerr << "No MIDI destinations found. Exiting test.\n";
            MaxMidi::shutdown();
            return 1;
        }

        std::cout << "Testing sendNoteOn..." << std::endl;
        MaxMidi::sendNoteOn(0, 64, 100);  // E4

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        std::cout << "Testing sendNoteOff..." << std::endl;
        MaxMidi::sendNoteOff(0, 64, 0);

        MaxMidi::shutdown();

        std::cout << "Test completed without errors." << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }
}