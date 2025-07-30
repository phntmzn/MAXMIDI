#include "include/maxmidi/MaxMidi.hpp"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    if (!maxmidi::initialize()) {
        std::cerr << "Failed to initialize maxmidi" << std::endl;
        return 1;
    }

    auto outputs = maxmidi::getOutputNames();
    if (outputs.empty()) {
        std::cout << "No MIDI outputs found.\n";
        return 0;
    }

    std::cout << "Available outputs:\n";
    for (size_t i = 0; i < outputs.size(); ++i)
        std::cout << " [" << i << "] " << outputs[i] << "\n";

    maxmidi::selectOutput(0);
    std::cout << "Selected: " << outputs[0] << "\n";

    maxmidi::sendNoteOn(0, 60, 127);  // C4
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    maxmidi::sendNoteOff(0, 60, 0);

    return 0;
}
