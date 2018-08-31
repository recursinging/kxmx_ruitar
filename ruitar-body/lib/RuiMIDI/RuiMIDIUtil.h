#ifndef MIDIUtil_h
#define MIDIUtil_h

#ifndef ARDUINO

#include <stdio.h>
#include <cstdint>

#define constrain(amt, low, high)                           \
  ({                                                        \
    typeof(amt) _amt = (amt);                               \
    typeof(low) _low = (low);                               \
    typeof(high) _high = (high);                            \
    (_amt < _low) ? _low : ((_amt > _high) ? _high : _amt); \
  })

inline long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#include <chrono>
inline long micros() {
  std::chrono::time_point<std::chrono::system_clock> now =
      std::chrono::system_clock::now();
  auto duration = now.time_since_epoch();
  auto microseconds =
      std::chrono::duration_cast<std::chrono::microseconds>(duration);
  duration -= microseconds;
  return (long)(microseconds.count());
}

#else

#include <Arduino.h>

class RuiMIDIUtil {
 public:
  static const char* toNoteName(uint8_t val);
};

#endif

const char* const midi_note_name_table[128] = {
    "C-1",  "C#-1", "D-1", "D#-1", "E-1", "F-1", "F#-1", "G-1", "G#-1", "A-1",
    "A#-1", "B-1",  "C0",  "C#0",  "D0",  "D#0", "E0",   "F0",  "F#0",  "G0",
    "G#0",  "A0",   "A#0", "B0",   "C1",  "C#1", "D1",   "D#1", "E1",   "F1",
    "F#1",  "G1",   "G#1", "A1",   "A#1", "B1",  "C2",   "C#2", "D2",   "D#2",
    "E2",   "F2",   "F#2", "G2",   "G#2", "A2",  "A#2",  "B2",  "C3",   "C#3",
    "D3",   "D#3",  "E3",  "F3",   "F#3", "G3",  "G#3",  "A3",  "A#3",  "B3",
    "C4",   "C#4",  "D4",  "D#4",  "E4",  "F4",  "F#4",  "G4",  "G#4",  "A4",
    "A#4",  "B4",   "C5",  "C#5",  "D5",  "D#5", "E5",   "F5",  "F#5",  "G5",
    "G#5",  "A5",   "A#5", "B5",   "C6",  "C#6", "D6",   "D#6", "E6",   "F6",
    "F#6",  "G6",   "G#6", "A6",   "A#6", "B6",  "C7",   "C#7", "D7",   "D#7",
    "E7",   "F7",   "F#7", "G7",   "G#7", "A7",  "A#7",  "B7",  "C8",   "C#8",
    "D8",   "D#8",  "E8",  "F8",   "F#8", "G8",  "G#8",  "A8",  "A#8",  "B8",
    "C9",   "C#9",  "D9",  "D#9",  "E9",  "F9",  "F#9",  "G9"};

// Table of midi note frequencies * 2
//   They are times 2 for greater accuracy, yet still fits in a word.
//   Generated from Excel by =ROUND(2*440/32*(2^((x-9)/12)),0) for 0<x<128
// The lowest notes might not work, depending on the Arduino clock frequency
// This is for the Teensy Audio library which specifies
// frequencies as floating point. See make_notetab.xlsx
const float midi_note_freq_table[128] = {
    8.1758,     8.6620,    9.1770,    9.7227,    10.3009,    10.9134,
    11.5623,    12.2499,   12.9783,   13.7500,   14.5676,    15.4339,
    16.3516,    17.3239,   18.3540,   19.4454,   20.6017,    21.8268,
    23.1247,    24.4997,   25.9565,   27.5000,   29.1352,    30.8677,
    32.7032,    34.6478,   36.7081,   38.8909,   41.2034,    43.6535,
    46.2493,    48.9994,   51.9131,   55.0000,   58.2705,    61.7354,
    65.4064,    69.2957,   73.4162,   77.7817,   82.4069,    87.3071,
    92.4986,    97.9989,   103.8262,  110.0000,  116.5409,   123.4708,
    130.8128,   138.5913,  146.8324,  155.5635,  164.8138,   174.6141,
    184.9972,   195.9977,  207.6523,  220.0000,  233.0819,   246.9417,
    261.6256,   277.1826,  293.6648,  311.1270,  329.6276,   349.2282,
    369.9944,   391.9954,  415.3047,  440.0000,  466.1638,   493.8833,
    523.2511,   554.3653,  587.3295,  622.2540,  659.2551,   698.4565,
    739.9888,   783.9909,  830.6094,  880.0000,  932.3275,   987.7666,
    1046.5023,  1108.7305, 1174.6591, 1244.5079, 1318.5102,  1396.9129,
    1479.9777,  1567.9817, 1661.2188, 1760.0000, 1864.6550,  1975.5332,
    2093.0045,  2217.4610, 2349.3181, 2489.0159, 2637.0205,  2793.8259,
    2959.9554,  3135.9635, 3322.4376, 3520.0000, 3729.3101,  3951.0664,
    4186.0090,  4434.9221, 4698.6363, 4978.0317, 5274.0409,  5587.6517,
    5919.9108,  6271.9270, 6644.8752, 7040.0000, 7458.6202,  7902.1328,
    8372.0181,  8869.8442, 9397.2726, 9956.0635, 10548.0818, 11175.3034,
    11839.8215, 12543.8540};

const float midi_velocity_amplitude_table[127] = {
    0.01778, 0.01966, 0.02164, 0.02371, 0.02588, 0.02814, 0.03049, 0.03294,
    0.03549, 0.03812, 0.04086, 0.04369, 0.04661, 0.04963, 0.05274, 0.05594,
    0.05924, 0.06264, 0.06613, 0.06972, 0.07340, 0.07717, 0.08104, 0.08500,
    0.08906, 0.09321, 0.09746, 0.10180, 0.10624, 0.11077, 0.11539, 0.12011,
    0.12493, 0.12984, 0.13484, 0.13994, 0.14513, 0.15042, 0.15581, 0.16128,
    0.16685, 0.17252, 0.17828, 0.18414, 0.19009, 0.19613, 0.20227, 0.20851,
    0.21484, 0.22126, 0.22778, 0.23439, 0.24110, 0.24790, 0.25480, 0.26179,
    0.26887, 0.27605, 0.28333, 0.29070, 0.29816, 0.30572, 0.31337, 0.32112,
    0.32896, 0.33690, 0.34493, 0.35306, 0.36128, 0.36960, 0.37801, 0.38651,
    0.39511, 0.40381, 0.41260, 0.42148, 0.43046, 0.43953, 0.44870, 0.45796,
    0.46732, 0.47677, 0.48631, 0.49595, 0.50569, 0.51552, 0.52544, 0.53546,
    0.54557, 0.55578, 0.56609, 0.57648, 0.58697, 0.59756, 0.60824, 0.61902,
    0.62989, 0.64085, 0.65191, 0.66307, 0.67432, 0.68566, 0.69710, 0.70863,
    0.72026, 0.73198, 0.74380, 0.75571, 0.76771, 0.77981, 0.79201, 0.80430,
    0.81668, 0.82916, 0.84174, 0.85440, 0.86717, 0.88003, 0.89298, 0.90602,
    0.91917, 0.93240, 0.94573, 0.95916, 0.97268, 0.98629, 1.00000};
/*
 #! /usr/bin/perl
 # The Interpretation of MIDI Velocity
 # Roger B. Dannenberg
 # School of Computer Science, Carnegie Mellon University
 $dynamic_range = 35;
 $r = 10 ** ($dynamic_range / 20);
 $b = 127 / (126 * sqrt($r)) - 1/126;
 $m = (1 - $b) / 127;
 print "const float velocity2amplitude[127] = {\n";
 for ($v=1; $v <= 127; $v++) {
 $a = ($m * $v + $b) ** 2;
 printf "%.5f", $a;
 print "," if $v < 127;
 print "\n" if ($v % 10) == 0;
 }
 print "\n};\n";
 */

#endif