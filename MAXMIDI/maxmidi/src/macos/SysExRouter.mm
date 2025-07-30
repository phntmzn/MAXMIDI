


#import <CoreMIDI/CoreMIDI.h>
#include <vector>

static MIDIClientRef sysexClient = 0;
static MIDIPortRef sysexPort = 0;
static MIDIEndpointRef sysexDest = 0;  // Should be set via selectDestination

void sendSysEx(const std::vector<uint8_t>& data) {
    if (!sysexClient) {
        MIDIClientCreate(CFSTR("SysExClient"), NULL, NULL, &sysexClient);
        MIDIOutputPortCreate(sysexClient, CFSTR("SysExOutPort"), &sysexPort);
    }

    if (!sysexDest || data.empty()) return;

    // Build SysEx message
    std::vector<uint8_t> message;
    message.push_back(0xF0);               // SysEx start
    message.insert(message.end(), data.begin(), data.end());
    message.push_back(0xF7);               // SysEx end

    Byte buffer[1024];
    MIDIPacketList* packetList = (MIDIPacketList*)buffer;
    MIDIPacket* packet = MIDIPacketListInit(packetList);
    packet = MIDIPacketListAdd(packetList, sizeof(buffer), packet, 0, message.size(), message.data());

    if (packet)
        MIDISend(sysexPort, sysexDest, packetList);
}