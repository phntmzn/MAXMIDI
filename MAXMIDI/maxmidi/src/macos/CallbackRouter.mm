


#import <CoreMIDI/CoreMIDI.h>
#include "maxmidi/EventTypes.hpp"
#include "maxmidi/Callback.hpp"
#include <atomic>

using namespace MaxMidi;

static std::atomic<MidiCallback*> registeredCallback{nullptr};

extern "C" void midiInputHandler(
    const MIDIPacketList *pktlist,
    void *readProcRefCon,
    void *srcConnRefCon)
{
    auto cbPtr = registeredCallback.load();
    if (!cbPtr || !*cbPtr) return;

    const MIDIPacket *packet = &pktlist->packet[0];
    for (unsigned int i = 0; i < pktlist->numPackets; ++i) {
        if (packet->length >= 3) {
            uint8_t status = packet->data[0];
            uint8_t data1 = packet->data[1];
            uint8_t data2 = packet->data[2];
            uint32_t time = 0; // placeholder, CoreMIDI timestamps can be added later
            MidiEvent ev{time, status, data1, data2};
            (*cbPtr)(ev);
        }
        packet = MIDIPacketNext(packet);
    }
}

namespace MaxMidi {

void registerInputCallback(MidiCallback callback) {
    static MidiCallback globalCb;
    globalCb = callback;
    registeredCallback.store(&globalCb);
}

}