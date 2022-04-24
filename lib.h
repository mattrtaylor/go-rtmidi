#include <stdlib.h>
#include <stdint.h>
#include "rtmidi/rtmidi_c.h"

extern void goMIDIInCallback(double ts, unsigned char *msg, size_t msgsz, void *arg);

static inline void midiInCallback(double ts, const unsigned char *msg, size_t msgsz, void *arg) {
    goMIDIInCallback(ts, (unsigned char*) msg, msgsz, arg);
}

static inline void cgoSetCallback(RtMidiPtr in, int cb_id) {
    rtmidi_in_set_callback(in, midiInCallback, (void*)(uintptr_t) cb_id);
}

static void testCallback(int arg) {
    double ts = 3.14159;
    unsigned char buf[] = {0x90, 0x30, 0x00};

    goMIDIInCallback(ts, buf, sizeof(buf), (void *)(uintptr_t) arg);
}
