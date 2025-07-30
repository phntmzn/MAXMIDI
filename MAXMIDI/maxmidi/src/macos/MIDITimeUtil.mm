#import <CoreMIDI/CoreMIDI.h>
#import <mach/mach_time.h>

double timestampToSeconds(MIDITimeStamp ts) {
    static mach_timebase_info_data_t timebase;
    if (timebase.denom == 0)
        mach_timebase_info(&timebase);

    uint64_t nanos = ts * timebase.numer / timebase.denom;
    return nanos / 1e9;
}

uint64_t hostTimeToNanos(MachAbsoluteTime t) {
    static mach_timebase_info_data_t timebase;
    if (timebase.denom == 0)
        mach_timebase_info(&timebase);

    return t * timebase.numer / timebase.denom;
}
