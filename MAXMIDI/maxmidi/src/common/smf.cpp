

#include "maxmidi/EventTypes.hpp"
#include <vector>
#include <fstream>
#include <cstdint>
#include <stdexcept>
#include <iostream>

namespace MaxMidi {

static uint32_t readBigEndian32(std::ifstream& stream) {
    uint8_t bytes[4];
    stream.read(reinterpret_cast<char*>(bytes), 4);
    return (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
}

static uint16_t readBigEndian16(std::ifstream& stream) {
    uint8_t bytes[2];
    stream.read(reinterpret_cast<char*>(bytes), 2);
    return (bytes[0] << 8) | bytes[1];
}

static uint32_t readVarLen(std::ifstream& stream) {
    uint32_t value = 0;
    uint8_t c;
    do {
        stream.read(reinterpret_cast<char*>(&c), 1);
        value = (value << 7) | (c & 0x7F);
    } while (c & 0x80);
    return value;
}

std::vector<MidiEvent> loadSMF(const std::string& path) {
    std::ifstream in(path, std::ios::binary);
    if (!in) throw std::runtime_error("Cannot open file: " + path);

    char header[4];
    in.read(header, 4);
    if (std::string(header, 4) != "MThd") throw std::runtime_error("Missing MThd");

    uint32_t headerSize = readBigEndian32(in);
    uint16_t formatType = readBigEndian16(in);
    uint16_t numTracks = readBigEndian16(in);
    uint16_t division = readBigEndian16(in);
    in.ignore(headerSize - 6); // skip remaining header

    std::vector<MidiEvent> events;
    for (int i = 0; i < numTracks; ++i) {
        in.read(header, 4);
        if (std::string(header, 4) != "MTrk") throw std::runtime_error("Missing MTrk");

        uint32_t trackLength = readBigEndian32(in);
        auto trackEnd = in.tellg();
        trackEnd += static_cast<std::streamoff>(trackLength);

        uint32_t time = 0;
        uint8_t status = 0;

        while (in.tellg() < trackEnd) {
            uint32_t delta = readVarLen(in);
            time += delta;

            uint8_t byte;
            in.read(reinterpret_cast<char*>(&byte), 1);
            if (byte & 0x80) {
                status = byte;
                in.read(reinterpret_cast<char*>(&byte), 1);
            }

            uint8_t data1 = byte;
            uint8_t data2 = 0;

            if ((status & 0xF0) != 0xC0 && (status & 0xF0) != 0xD0) {
                in.read(reinterpret_cast<char*>(&data2), 1);
            }

            if ((status & 0xF0) == 0x80 || (status & 0xF0) == 0x90) {
                MidiEvent ev{time, status, data1, data2};
                events.push_back(ev);
            }
        }
    }

    return events;
}

} // namespace MaxMidi