#include "RuiMIDIFader.h"
#include "RuiBody.h"
#include "RuiPreset.h"

RuiMIDIFader::RuiMIDIFader(uint8_t t_idx) {
  idx = t_idx;
  rawValue = 0;
  constrainedValue = 0;
  ccValue = 0;
  noteValue = -1;
  pitchBendValue = 0;
  stickiness = 3;
  upperBound = 0;
  lowerBound = 0;
};

void RuiMIDIFader::update() {
  rawValue = RuiBody.sensors.fadersV[idx];
  constrainedValue =
      constrain(rawValue, RuiBody.calibration.fadersInputMin[idx],
                RuiBody.calibration.fadersInputMax[idx]);
  ccValue = map(constrainedValue, RuiBody.calibration.fadersInputMin[idx],
                RuiBody.calibration.fadersInputMax[idx],
                RuiPreset.faders.lowest_cc_value[idx],
                RuiPreset.faders.highest_cc_value[idx]);

  int8_t newNote = map(
      constrainedValue, RuiBody.calibration.fadersInputMin[idx],
      RuiBody.calibration.fadersInputMax[idx],
      RuiPreset.faders.lowest_note[idx], RuiPreset.faders.highest_note[idx]);
  if (noteValue > 0 && newNote > noteValue) {
    int stepSize = (RuiBody.calibration.fadersInputMax[idx] -
                    RuiBody.calibration.fadersInputMin[idx]) /
                   (RuiPreset.faders.highest_note[idx] -
                    RuiPreset.faders.lowest_note[idx]);
    upperBound = ((stepSize * (noteValue - RuiPreset.faders.lowest_note[idx])) +
                  (stepSize / 2)) +
                 ((stepSize / 2) + (stepSize / stickiness));
    if (constrainedValue > upperBound) {
      noteValue = newNote;
    }
  } else if (noteValue > 0 && newNote < noteValue) {
    int stepSize = (RuiBody.calibration.fadersInputMax[idx] -
                    RuiBody.calibration.fadersInputMin[idx]) /
                   (RuiPreset.faders.highest_note[idx] -
                    RuiPreset.faders.lowest_note[idx]);
    lowerBound = ((stepSize * (noteValue - RuiPreset.faders.lowest_note[idx])) +
                  (stepSize / 2)) -
                 ((stepSize / 2) + (stepSize / stickiness));
    if (constrainedValue < lowerBound) {
      noteValue = newNote;
    }
  } else {
    noteValue = newNote;
  }

  pitchBendValue =
      map(constrainedValue, RuiBody.calibration.fadersInputMin[idx],
          RuiBody.calibration.fadersInputMax[idx], -8192, 8192);
};
