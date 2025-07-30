


#import <CoreMIDI/CoreMIDI.h>
#include <iostream>

// Static reference to hold the MIDI client
static MIDIClientRef notifierClient = 0;

// Callback function triggered when MIDI objects change
void midiNotifyCallback(const MIDINotification* message, void* refCon) {
    switch (message->messageID) {
        case kMIDIMsgObjectAdded:
            std::cout << "[MIDI] Device added" << std::endl;
            break;
        case kMIDIMsgObjectRemoved:
            std::cout << "[MIDI] Device removed" << std::endl;
            break;
        case kMIDIMsgSetupChanged:
            std::cout << "[MIDI] Setup changed" << std::endl;
            break;
        default:
            break;
    }
}

// Initializes the notifier client to receive MIDI setup events
void startMIDINotifier() {
    if (!notifierClient) {
        MIDIClientCreate(CFSTR("MIDINotifier"), midiNotifyCallback, nullptr, &notifierClient);
    }
}