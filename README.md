# MaxMidi for macOS

A modern C++17 CoreMIDI wrapper for generating MIDI events.
# MaxMidi for macOS

A modern C++17 CoreMIDI wrapper for generating MIDI events on macOS, built by **phntmzn**.  
This library enables developers to send real-time MIDI messages (Note On/Off) from C++ applications using native CoreMIDI APIs.

---

## Features

- ✅ CoreMIDI backend for macOS
- ✅ Send Note On / Note Off messages
- ✅ Thread-safe MIDI event queue
- ✅ Real-time MIDI clock for scheduling
- ❌ No Windows/Linux support (yet)
- ❌ No Sysex or advanced message types (yet)

---

## Project Structure

```
maxmidi/
├── include/
│   └── maxmidi/         # Public API
│       ├── MaxMidi.hpp
│       ├── EventTypes.hpp
│       └── Callback.hpp
├── src/
│   ├── common/          # Clock + Queue
│   └── macos/           # CoreMIDIWrapper.mm
├── tests/               # Unit + IO Tests
├── examples/            # Usage Demos
├── LICENSE.txt
├── CMakeLists.txt
└── README.md
```

---

## Getting Started

### Build (CMake + Clang)

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```

### Run Test

```bash
./tests/test_midi_io
```

---

## Usage

```cpp
#include "maxmidi/MaxMidi.hpp"

int main() {
    MaxMidi::initialize();
    MaxMidi::sendNoteOn(0, 60, 127);   // Middle C
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    MaxMidi::sendNoteOff(0, 60, 0);
    MaxMidi::shutdown();
}
```

---

## License

This software is licensed for **non-commercial use only**.  
See [LICENSE.txt](./LICENSE.txt) for full terms.

&copy; 2025 phntmzn. All rights reserved.
