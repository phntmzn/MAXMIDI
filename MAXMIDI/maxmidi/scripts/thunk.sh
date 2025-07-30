

#!/bin/bash
set -e

echo "== MAXMIDI Thunk Runner =="

case "$1" in
  test)
    echo "[Running test_midi_io]"
    ./build/tests/test_midi_io
    ;;
  midiout)
    echo "[Running output demo]"
    ./build/examples/midi_demo
    ;;
  midiin)
    echo "[Running input callback demo]"
    ./build/examples/midi_input_demo
    ;;
  *)
    echo "Usage: $0 {test|midiout|midiin}"
    exit 1
    ;;
esac