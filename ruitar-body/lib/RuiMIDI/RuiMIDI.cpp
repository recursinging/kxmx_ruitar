#include "RuiMIDI.h"

//#define MIDI_DEBUG

RuiMIDISoftPot* RuiMIDIClass::strings[] = {
    new RuiMIDISoftPot(0), new RuiMIDISoftPot(1), new RuiMIDISoftPot(2),
    new RuiMIDISoftPot(3)};
RuiMIDIFSR* RuiMIDIClass::pads[] = {new RuiMIDIFSR(0), new RuiMIDIFSR(1),
                                    new RuiMIDIFSR(2), new RuiMIDIFSR(3)};
RuiMIDIenc* RuiMIDIClass::knobs[] = {new RuiMIDIenc(0), new RuiMIDIenc(1),
                                     new RuiMIDIenc(2), new RuiMIDIenc(3)};
RuiMIDIFader* RuiMIDIClass::faders[] = {
    new RuiMIDIFader(0), new RuiMIDIFader(1), new RuiMIDIFader(2),
    new RuiMIDIFader(3)};
RuiMIDIToggle* RuiMIDIClass::toggles[] = {
    new RuiMIDIToggle(0), new RuiMIDIToggle(1), new RuiMIDIToggle(2),
    new RuiMIDIToggle(3)};
RuiMIDIButton* RuiMIDIClass::buttons[] = {
    new RuiMIDIButton(0), new RuiMIDIButton(1), new RuiMIDIButton(2),
    new RuiMIDIButton(3)};
RuiMIDIJoystick* RuiMIDIClass::joystick = new RuiMIDIJoystick();
RuiMIDIAccel* RuiMIDIClass::accel = new RuiMIDIAccel();

MIDIState RuiMIDIClass::state = MIDIState();

void RuiMIDIClass::begin() {
#if defined(USB_MIDI_SERIAL)
  usbMIDI.setHandleNoteOn(handleNoteOn);
  usbMIDI.setHandleNoteOff(handleNoteOff);
#endif
}

void RuiMIDIClass::handleNoteOn(uint8_t channel, uint8_t note,
                                uint8_t velocity) {
  for (uint8_t s = 0; s < NN; s++) {
    uint8_t extChan = RuiPreset.pads.external_mode_channel[s];
    if (extChan > 0 && extChan == channel) {
      if (RuiPreset.pads.external_mode_note[s] == note) {
        state.extNoteOn[s] = 1;
        state.extNoteVelocity[s] = velocity;
      }
    }
  }
}

void RuiMIDIClass::handleNoteOff(byte channel, byte note, byte velocity) {
  for (uint8_t s = 0; s < NN; s++) {
    uint8_t extChan = RuiPreset.pads.external_mode_channel[s];
    if (extChan > 0 && extChan == channel) {
      if (RuiPreset.pads.external_mode_note[s] == note) {
        state.extNoteOn[s] = 0;
        state.extNoteVelocity[s] = 0;
      }
    }
  }
}

void RuiMIDIClass::sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel) {
#if defined(USB_MIDI_SERIAL)
  usbMIDI.sendNoteOn(note, velocity, channel);
#elif defined(MIDI_DEBUG)
#ifdef ARDUINO
  Serial.print("ON\t");
  Serial.print(RuiMIDIUtil::toNoteName(note));
  Serial.print('\t');
  Serial.print(velocity);
  Serial.print('\t');
  Serial.println(channel);
#else
  printf("ON\t%s\t%i\t%i\n", RuiMIDIClass::toNoteName(note), velocity, channel);
#endif
#endif
}

void RuiMIDIClass::sendNoteOff(uint8_t note, uint8_t velocity,
                               uint8_t channel) {
#ifdef USB_MIDI_SERIAL
  usbMIDI.sendNoteOff(note, velocity, channel);
#elif defined(MIDI_DEBUG)
#ifdef ARDUINO
  Serial.print("OF\t");
  Serial.print(RuiMIDIUtil::toNoteName(note));
  Serial.print('\t');
  Serial.print(velocity);
  Serial.print('\t');
  Serial.println(channel);
#else
  printf("OF\t%s\t%i\t%i\n", RuiMIDIClass::toNoteName(note), velocity, channel);
#endif
#endif
}

void RuiMIDIClass::sendControlChange(uint8_t control, uint8_t value,
                                     uint8_t channel) {
#ifdef USB_MIDI_SERIAL
  usbMIDI.sendControlChange(control, value, channel);
#elif defined(MIDI_DEBUG)
#ifdef ARDUINO
  Serial.print("CC\t");
  Serial.print(control);
  Serial.print('\t');
  Serial.print(value);
  Serial.print('\t');
  Serial.println(channel);
#else
  printf("CC\t%i\t%i\t%i\n", control, value, channel);
#endif
#endif
}

void RuiMIDIClass::sendAfterTouchPoly(uint8_t note, uint8_t pressure,
                                      uint8_t channel) {
#ifdef USB_MIDI_SERIAL
  // usbMIDI.sendAfterTouchPoly(note, pressure, channel);
#elif defined(MIDI_DEBUG)
#ifdef ARDUINO
  Serial.print("AT\t");
  Serial.print(RuiMIDIUtil::toNoteName(note));
  Serial.print('\t');
  Serial.print(pressure);
  Serial.print('\t');
  Serial.println(channel);
#else
  printf("AT\t%s\t%i\t%i\n", RuiMIDIClass::toNoteName(note), pressure, channel);
#endif
#endif
}

void RuiMIDIClass::sendPitchBend(int value, uint8_t channel) {
#ifdef USB_MIDI_SERIAL
  usbMIDI.sendPitchBend(value, channel);
#elif defined(MIDI_DEBUG)
#ifdef ARDUINO
  Serial.print("PB\t");
  Serial.print(value);
  Serial.print('\t');
  Serial.println(channel);
#else
  printf("PB\t%i\t%i\n", value, channel);
#endif
#endif
}

void RuiMIDIClass::update() {
#if defined(USB_MIDI_SERIAL)
  // Read any midi messages to keep the buffer free
  while (usbMIDI.read()) {
  };
#endif
  // Iterate over the iterables...
  for (uint8_t s = 0; s < NN; s++) {
    strings[s]->update();
    pads[s]->update();
    faders[s]->update();
    toggles[s]->update();
    knobs[s]->update();
  }
  // joystick->update();
  // accel->update();
}

void RuiMIDIClass::dispatch() {
  for (uint8_t s = 0; s < NN; s++) {
    int8_t note = state.notes[s];
    RuiMIDISoftPot* string = strings[s];
    RuiMIDIFSR* pad = pads[s];
    RuiMIDIenc* knob = knobs[s];
    RuiMIDIFader* fader = faders[s];
    RuiMIDIToggle* toggle = toggles[s];
    RuiMIDIButton* button = buttons[s];

    uint8_t noteChannel = RuiPreset.strings.channel[s];

    int8_t noteOn = pad->noteOn;
    int8_t newNote = string->noteValue;
    int8_t velocity = pad->velocityValue;
    int8_t pressure = pad->afterTouchValue;

    if (RuiPreset.pads.pad_mode[s] == 1) {
      // String note mode
      if (RuiPreset.strings.play_open[s] && newNote < 0) {
        // This is an open string note
        newNote = RuiPreset.strings.lowest_note[s];
      }
    } else if (RuiPreset.pads.pad_mode[s] == 2) {
      // Fixed Note Mode - Override the string note with the preset value
      newNote = RuiPreset.pads.fixed_mode_note[s];
    } else if (RuiPreset.pads.pad_mode[s] == 3) {
      // External Trigger Mode - We supplement the pad triggering with MIDI input
      if (state.extNoteOn[s] && pad->noteOn) {
        noteOn = 1;
        velocity = state.extNoteVelocity[s];
      } else {
        noteOn = 0;
        velocity = 0;
      }
    }

    // Handle Notes and aftertouch
    if (note >= 0) {
      // Note is already on from a previous iteration...
      if (!noteOn || newNote < 0) {
        // Pad or string says note should be off. Turn 'er off then...
        sendNoteOff(note, velocity, noteChannel);
        note = state.notes[s] = -1;
      } else {
        // The note is still on... check for slide
        uint8_t stringMode = RuiPreset.strings.string_mode[s];
        if (stringMode == 3) {
          // Pitch Bend...
          sendPitchBend(string->pitchBendValue, noteChannel);
        } else if (newNote != note) {
          // Sliding note change...
          if (stringMode == 1) {
            // Normal note change
            sendNoteOff(note, velocity, noteChannel);
            sendNoteOn(newNote, velocity, noteChannel);
            note = state.notes[s] = newNote;
          } else if (stringMode == 2) {
            // Legato note change
            sendNoteOn(newNote, velocity, noteChannel);
            sendNoteOff(note, velocity, noteChannel);
            note = state.notes[s] = newNote;
          }
        }
        // Send aftertouch
        if (RuiPreset.pads.send_aftertouch[s] &&
            pressure != state.pressurePads[s]) {
          sendAfterTouchPoly(note, pressure, noteChannel);
          state.pressurePads[s] = pressure;
        }
      }
    } else {
      // Note is off
      if (noteOn && newNote > 0) {
        sendNoteOn(newNote, velocity, noteChannel);
        note = state.notes[s] = newNote;
      }
    }

    // Handle String CC
    if (RuiPreset.strings.cc_channel[s] > 0 &&
        string->ccValue != state.ccStrings[s]) {
      sendControlChange(RuiPreset.strings.cc_number[s], string->ccValue,
                        RuiPreset.strings.cc_channel[s]);
      state.ccStrings[s] = string->ccValue;
    }

    // Handle Pad CC
    if (RuiPreset.pads.cc_channel[s] > 0 && pad->ccValue != state.ccPads[s]) {
      sendControlChange(RuiPreset.pads.cc_number[s], pad->ccValue,
                        RuiPreset.pads.cc_channel[s]);
      state.ccPads[s] = pad->ccValue;
    }

    // Handle Faders
    if (RuiPreset.faders.fader_mode[s] == 4 &&
        RuiPreset.faders.cc_channel[s] > 0 &&
        state.ccFaders[s] != fader->ccValue &&
        state.ccFaders[s] != fader->ccValue + 1 &&
        state.ccFaders[s] != fader->ccValue - 1) {
      sendControlChange(RuiPreset.faders.cc_number[s], fader->ccValue,
                        RuiPreset.faders.cc_channel[s]);
      state.ccFaders[s] = fader->ccValue;
    }

    // Handle Knobs
    if (RuiPreset.knobs.cc_channel[s] > 0 &&
        state.ccKnobs[s] != knob->ccValue) {
      sendControlChange(RuiPreset.knobs.cc_number[s], knob->ccValue,
                        RuiPreset.knobs.cc_channel[s]);
      state.ccKnobs[s] = knob->ccValue;
    }

    // Handle Toggle Buttons
    if (RuiPreset.toggles.cc_channel[s] > 0 &&
        state.ccToggles[s] != toggle->ccValue) {
      sendControlChange(RuiPreset.toggles.cc_number[s], toggle->ccValue,
                        RuiPreset.toggles.cc_channel[s]);
      state.ccToggles[s] = toggle->ccValue;
      RuiBody.feedbackLast.toggleLeds[s] = RuiBody.feedback.toggleLeds[s];
      RuiBody.feedback.toggleLeds[s] = toggles[s]->toggle;
    }

    // Handle Joystick
    // if (RuiPreset.joystick.joystick_mode[s] > 0) {
    //   if (RuiPreset.joystick.joystick_mode[s] == 1) {
    //     // CC Mode
    //     if (s == 0) {
    //       if (joystick->ccXPlusValue != state.ccJoystick[s]) {
    //         sendControlChange(RuiPreset.joystick.cc_number[s],
    //                           joystick->ccXPlusValue,
    //                           RuiPreset.joystick.cc_channel[s]);
    //         state.ccJoystick[s] = joystick->ccXPlusValue;
    //       }
    //     } else if (s == 1) {
    //       if (joystick->ccXMinusValue != state.ccJoystick[s]) {
    //         sendControlChange(RuiPreset.joystick.cc_number[s],
    //                           joystick->ccXMinusValue,
    //                           RuiPreset.joystick.cc_channel[s]);
    //         state.ccJoystick[s] = joystick->ccXMinusValue;
    //       }
    //     } else if (s == 2) {
    //       if (joystick->ccYPlusValue != state.ccJoystick[s]) {
    //         sendControlChange(RuiPreset.joystick.cc_number[s],
    //                           joystick->ccYPlusValue,
    //                           RuiPreset.joystick.cc_channel[s]);
    //         state.ccJoystick[s] = joystick->ccYPlusValue;
    //       }
    //     } else if (s == 3) {
    //       if (joystick->ccYMinusValue != state.ccJoystick[s]) {
    //         sendControlChange(RuiPreset.joystick.cc_number[s],
    //                           joystick->ccYMinusValue,
    //                           RuiPreset.joystick.cc_channel[s]);
    //         state.ccJoystick[s] = joystick->ccYMinusValue;
    //       }
    //     }
    //   } else if (RuiPreset.joystick.joystick_mode[s] == 2) {
    //     // Pitch Bend Mode
    //     if (s == 0 || s == 1) {
    //       if (joystick->xPitchBendValue != 0 &&
    //           joystick->xPitchBendValue != state.joystickXPitchBend) {
    //         sendPitchBend(joystick->xPitchBendValue,
    //                       RuiPreset.joystick.channel[s]);
    //         state.joystickXPitchBend = joystick->xPitchBendValue;
    //       }
    //     } else if (s == 3 || s == 4) {
    //       if (joystick->yPitchBendValue != 0 &&
    //           joystick->yPitchBendValue != state.joystickYPitchBend) {
    //         sendPitchBend(joystick->yPitchBendValue,
    //                       RuiPreset.joystick.channel[s]);
    //         state.joystickYPitchBend = joystick->yPitchBendValue;
    //       }
    //     }
    //   }
    // }
  }
}

RuiMIDIClass RuiMIDI;
