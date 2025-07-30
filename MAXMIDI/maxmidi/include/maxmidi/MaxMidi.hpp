#pragma once

namespace MaxMidi {
    /// Sends a Note On MIDI message to the first available destination.
    /// @param channel MIDI channel (0–15)
    /// @param note Note number (0–127)
    /// @param velocity Velocity (0–127)
    void sendNoteOn(int channel, int note, int velocity);

    /// Sends a Note Off MIDI message to the first available destination.
    /// @param channel MIDI channel (0–15)
    /// @param note Note number (0–127)
    /// @param velocity Release velocity (0–127)
    void sendNoteOff(int channel, int note, int velocity);
}
