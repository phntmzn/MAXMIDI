cmake_minimum_required(VERSION 3.16)
project(MaxMidi_Mac VERSION 1.0 LANGUAGES C CXX OBJCXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_library(COREMIDI_LIB CoreMIDI)
find_library(COREFOUNDATION_LIB CoreFoundation)

file(GLOB_RECURSE SOURCES
    "src/common/*.cpp"
    "src/macos/*.mm"
    "src/macos/*.cpp"
)

file(GLOB_RECURSE HEADERS "include/**/*.hpp")

add_library(maxmidi SHARED
    src/common/MidiEventQueue.cpp
    src/common/smf.cpp
    src/common/Sync.cpp
    src/macos/CoreMIDIWrapper.mm
    src/macos/CallbackRouter.mm
    src/macos/MIDINotifier.mm
    src/macos/MIDITimeUtil.mm
    src/macos/SysExRouter.mm
    src/macos/VirtualMIDIDevice.mm
)

target_include_directories(maxmidi PUBLIC include)
target_link_libraries(maxmidi ${COREMIDI_LIB} ${COREFOUNDATION_LIB})
set_target_properties(maxmidi PROPERTIES OUTPUT_NAME "maxmidi")

add_executable(midi_demo examples/midi_demo.cpp)
target_link_libraries(midi_demo maxmidi)

add_executable(maxmidi_agent agent/agent_main.cpp)
target_link_libraries(maxmidi_agent maxmidi)

install(TARGETS maxmidi
    LIBRARY DESTINATION lib
)

install(TARGETS maxmidi_agent
    RUNTIME DESTINATION bin
)

install(FILES agent/com.maxmidi.agent.plist
    DESTINATION share/launchagents
)