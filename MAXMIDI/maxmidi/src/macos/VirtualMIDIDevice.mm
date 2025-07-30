


#import <CoreMIDI/CoreMIDI.h>
#include <string>

static MIDIClientRef virtualClient = 0;
static MIDIPortRef virtualOutPort = 0;
static MIDIEndpointRef virtualDest = 0;
static MIDIEndpointRef virtualSource = 0;

bool createVirtualOutputDevice(const std::string& name) {
    if (virtualClient == 0) {
        OSStatus err = MIDIClientCreate(CFSTR("MaxMidiVirtualClient"), nullptr, nullptr, &virtualClient);
        if (err != noErr) return false;
    }

    OSStatus portErr = MIDIOutputPortCreate(virtualClient, CFSTR("VirtualOutPort"), &virtualOutPort);
    if (portErr != noErr) return false;

    virtualDest = MIDISourceCreate(virtualClient, (__bridge CFStringRef)[NSString stringWithUTF8String:name.c_str()]);
    return virtualDest != 0;
}

bool createVirtualInputDevice(const std::string& name) {
    if (virtualClient == 0) {
        OSStatus err = MIDIClientCreate(CFSTR("MaxMidiVirtualClient"), nullptr, nullptr, &virtualClient);
        if (err != noErr) return false;
    }

    virtualSource = MIDIDestinationCreate(virtualClient, (__bridge CFStringRef)[NSString stringWithUTF8String:name.c_str()],
        [](const MIDIPacketList* pktlist, void* readProcRefCon, void* srcConnRefCon) {
            // Add custom packet handling here or route to CallbackRouter
        }, nullptr, &virtualSource);
    
    return virtualSource != 0;
}