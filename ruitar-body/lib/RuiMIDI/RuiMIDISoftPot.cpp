#include "RuiMIDISoftPot.h"
#include "RuiBody.h"
#include "RuiPreset.h"

RuiMIDISoftPot::RuiMIDISoftPot(uint8_t t_idx) {
  idx = t_idx;
  rawValue = 0;
  constrainedValue = 0;
  ccValue = 0;
  noteValue = -1;
  pitchBendValue = 0;
  pitchBendMiddle = 400;
  stickiness = 10;  // 10%
  upperBound = 0;
  lowerBound = 0;
};

void RuiMIDISoftPot::update() {
  rawValue = RuiBody.sensors.stringsV[idx];
  constrainedValue =
      constrain(rawValue, RuiBody.calibration.stringsInputMin[idx],
                RuiBody.calibration.stringsInputMax[idx]);
  ccValue = map(constrainedValue, RuiBody.calibration.stringsInputMin[idx],
                RuiBody.calibration.stringsInputMax[idx],
                RuiPreset.strings.lowest_cc_value[idx],
                RuiPreset.strings.highest_cc_value[idx]);

  if (constrainedValue > RuiBody.calibration.stringsInputThresh[idx]) {
    int8_t newNote =
        map(constrainedValue, RuiBody.calibration.stringsInputMin[idx],
            RuiBody.calibration.stringsInputMax[idx],
            RuiPreset.strings.lowest_note[idx],
            RuiPreset.strings.highest_note[idx]);
    if (noteValue > 0 && newNote > noteValue) {
      int stepSize = (RuiBody.calibration.stringsInputMax[idx] -
                      RuiBody.calibration.stringsInputMin[idx]) /
                     (RuiPreset.strings.highest_note[idx] -
                      RuiPreset.strings.lowest_note[idx]);
      upperBound =
          ((stepSize * (noteValue - RuiPreset.strings.lowest_note[idx])) +
           (stepSize / 2)) +
          ((stepSize / 2) + (stepSize / stickiness));
      if (constrainedValue > upperBound) {
        noteValue = newNote;
      }
    } else if (noteValue > 0 && newNote < noteValue) {
      int stepSize = (RuiBody.calibration.stringsInputMax[idx] -
                      RuiBody.calibration.stringsInputMin[idx]) /
                     (RuiPreset.strings.highest_note[idx] -
                      RuiPreset.strings.lowest_note[idx]);
      lowerBound =
          ((stepSize * (noteValue - RuiPreset.strings.lowest_note[idx])) +
           (stepSize / 2)) -
          ((stepSize / 2) + (stepSize / stickiness));
      if (constrainedValue < lowerBound) {
        noteValue = newNote;
      }
    } else {
      noteValue = newNote;
    }
    if (pitchBendValue == 0 && noteValue >= 0) {
      pitchBendMiddle = constrainedValue;
    }
    if (noteValue >= 0) {
      if (constrainedValue <= pitchBendMiddle) {
        pitchBendValue =
            map(constrainedValue, pitchBendMiddle,
                RuiBody.calibration.stringsInputMin[idx], -1, -8192);
      } else {
        pitchBendValue = map(constrainedValue, pitchBendMiddle,
                             RuiBody.calibration.stringsInputMax[idx], 1, 8192);
      }
    }
  } else {
    noteValue = -1;
    pitchBendValue = 0;
  }
};
