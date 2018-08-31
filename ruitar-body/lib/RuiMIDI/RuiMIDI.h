#ifndef MIDITools_h
#define MIDITools_h
#include <SD.h>
#include <TeensyView.h>

#include "RuiBody.h"
#include "RuiMIDIAccel.h"
#include "RuiMIDIButton.h"
#include "RuiMIDIFSR.h"
#include "RuiMIDIFader.h"
#include "RuiMIDIJoystick.h"
#include "RuiMIDISoftPot.h"
#include "RuiMIDIToggle.h"
#include "RuiMIDIenc.h"
#include "RuiPreset.h"

#define NN 4

typedef struct MIDIStateStruct {
  int8_t notes[NN] = {-1, -1, -1, -1};
  int8_t ccStrings[NN] = {-1, -1, -1, -1};
  int8_t ccPads[NN] = {-1, -1, -1, -1};
  int8_t ccKnobs[NN] = {-1, -1, -1, -1};
  int8_t ccFaders[NN] = {-1, -1, -1, -1};
  int8_t ccToggles[NN] = {-1, -1, -1, -1};
  int8_t ccButtons[NN] = {-1, -1, -1, -1};
  int8_t ccJoystick[NN] = {-1, -1, -1, -1};  // X+ X- Y+ Y-
  int16_t joystickXPitchBend = 0;
  int16_t joystickYPitchBend = 0;
  int8_t pressurePads[NN] = {-1, -1, -1, -1};
  int8_t inputNotes[16] = {-1, -1, -1, -1, -1, -1, -1, -1,
                           -1, -1, -1, -1, -1, -1, -1};
  int8_t inputVelocity[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
} MIDIState;

class RuiMIDIClass {
 public:
  static RuiMIDISoftPot* strings[];
  static RuiMIDIFSR* pads[];
  static RuiMIDIenc* knobs[];
  static RuiMIDIFader* faders[];
  static RuiMIDIToggle* toggles[];
  static RuiMIDIButton* buttons[];
  static RuiMIDIJoystick* joystick;
  static RuiMIDIAccel* accel;
  static MIDIState state;
  static void updatePresetConfig();
  static void update();
  static void dispatch();
  static void sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel);
  static void sendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel);
  static void sendControlChange(uint8_t control, uint8_t value,
                                uint8_t channel);
  static void sendAfterTouchPoly(uint8_t note, uint8_t pressure,
                                 uint8_t channel);
  static void sendPitchBend(int value, uint8_t channel);
};

extern RuiMIDIClass RuiMIDI;

#endif
