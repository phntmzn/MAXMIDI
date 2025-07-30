

#!/bin/bash

PLIST="/Library/LaunchAgents/com.maxmidi.agent.plist"

if [ -f "$PLIST" ]; then
    echo "[MaxMIDI] LaunchAgent found. Attempting to load..."
    /bin/launchctl bootstrap gui/$(id -u) "$PLIST"
else
    echo "[MaxMIDI] LaunchAgent not found at $PLIST. Skipping launchctl load."
fi

exit 0