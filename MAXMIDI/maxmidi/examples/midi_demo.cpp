#include "../include/maxmidi/MaxMidi.hpp"
#include <thread>
#include <chrono>
#include <iostream>

int main() {
    // Initialize MIDI system
    if (!maxmidi::initialize()) {
        std::cerr << "Failed to initialize maxmidi" << std::endl;
        return 1;
    }

    // List output devices
    auto outputs = maxmidi::getOutputNames();
    if (outputs.empty()) {
        std::cerr << "No MIDI output devices available." << std::endl;
        return 1;
    }

    std::cout << "Available MIDI Outputs:" << std::endl;
    for (size_t i = 0; i < outputs.size(); ++i) {
        std::cout << " [" << i << "] " << outputs[i] << std::endl;
    }

    // Select the first output
    maxmidi::selectOutput(0);
    std::cout << "Selected: " << outputs[0] << std::endl;

    // Play a C major triad
    maxmidi::sendNoteOn(0, 60, 100); // C4
    maxmidi::sendNoteOn(0, 64, 100); // E4
    maxmidi::sendNoteOn(0, 67, 100); // G4
    std::this_thread::sleep_for(std::chrono::seconds(1));
    maxmidi::sendNoteOff(0, 60, 0);
    maxmidi::sendNoteOff(0, 64, 0);
    maxmidi::sendNoteOff(0, 67, 0);

    return 0;
}
