#include "RuiMIDIFSR.h"
#include "RuiPreset.h"

RuiMIDIFSR::RuiMIDIFSR(int t_idx) {
  idx = t_idx;
  noteOn = false;
  rawValue = 0;
  constrainedValue = 0;
  ccValue = 0;
  velocityValue = 0;
  velocityWindow = 500;  // micros
  peakValue = 0;
  waiting = false;
  waitTime = 2500;  // micros
  timer = 0;
  calculatingVelocity = false;
  afterTouchValue = 0;
};

void RuiMIDIFSR::update() {
  rawValue = RuiBody.sensors.padsV[idx];
  constrainedValue = constrain(rawValue, RuiBody.calibration.padsInputMin[idx],
                               RuiBody.calibration.padsInputMax[idx]);
  ccValue = map(constrainedValue, RuiBody.calibration.padsInputMin[idx],
                RuiBody.calibration.padsInputMax[idx],
                RuiPreset.pads.lowest_cc_value[idx],
                RuiPreset.pads.highest_cc_value[idx]);
  // After a note off, wait until signal hits floor to eliminate double triggers
  // on hits near the threshold & wait a few msecs to eliminate phase shift.
  if (waiting) {
    if (micros() - timer > waitTime) {
      waiting = false;
      timer = micros();
    }
  } else {
    if (noteOn) {  // A note is on so...
      if (constrainedValue <
          RuiBody.calibration
              .padsInputThresh[idx]) {  // Set noteOn = false when signal drops.
        noteOn = false;
        waiting = true;
        peakValue = 0;
        timer = micros();
      } else {
        afterTouchValue =
            map(constrainedValue, RuiBody.calibration.padsInputMin[idx],
                RuiBody.calibration.padsInputMax[idx], 0, 127);
      }
    } else if (calculatingVelocity) {
      if (constrainedValue > peakValue) {  // Keep track of the highest value...
        peakValue = constrainedValue;
      }
      if (micros() - timer >= velocityWindow) {
        velocityValue =
            map(constrainedValue, RuiBody.calibration.padsInputMin[idx],
                RuiBody.calibration.padsInputMax[idx], 0, 127);
        calculatingVelocity = false;
        noteOn = true;
      }
    } else {  // Check for user input.
      if (constrainedValue > RuiBody.calibration.padsInputThresh[idx]) {
        peakValue = constrainedValue;
        calculatingVelocity = true;
        timer = micros();
      }
    }
  }
};
