#import <CoreMIDI/CoreMIDI.h>
#import "MaxMidi.hpp"

namespace MaxMidi {

namespace {
    MIDIClientRef client = nullptr;
    MIDIOutputPortRef outPort = nullptr;

    void ensureInitialized() {
        if (!client) {
            MIDIClientCreate(CFSTR("MaxMidiClient"), nullptr, nullptr, &client);
            MIDIOutputPortCreate(client, CFSTR("MaxMidiOutput"), &outPort);
        }
    }
}

void initialize() {
    ensureInitialized();
}

void shutdown() {
    if (outPort) {
        MIDIPortDispose(outPort);
        outPort = nullptr;
    }
    if (client) {
        MIDIClientDispose(client);
        client = nullptr;
    }
}

void sendNoteOn(int channel, int note, int velocity) {
    ensureInitialized();

    Byte buffer[3];
    buffer[0] = 0x90 | (channel & 0x0F);
    buffer[1] = note & 0x7F;
    buffer[2] = velocity & 0x7F;

    MIDIPacketList packetList;
    MIDIPacket* packet = MIDIPacketListInit(&packetList);
    MIDIPacketListAdd(&packetList, sizeof(packetList), packet, 0, sizeof(buffer), buffer);

    MIDIEndpointRef dest = MIDIGetDestination(0);
    MIDISend(outPort, dest, &packetList);
}

void sendNoteOff(int channel, int note, int velocity) {
    ensureInitialized();

    Byte buffer[3];
    buffer[0] = 0x80 | (channel & 0x0F);
    buffer[1] = note & 0x7F;
    buffer[2] = velocity & 0x7F;

    MIDIPacketList packetList;
    MIDIPacket* packet = MIDIPacketListInit(&packetList);
    MIDIPacketListAdd(&packetList, sizeof(packetList), packet, 0, sizeof(buffer), buffer);

    MIDIEndpointRef dest = MIDIGetDestination(0);
    MIDISend(outPort, dest, &packetList);
}

}
