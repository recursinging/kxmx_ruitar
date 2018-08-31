#include "RuiMIDIenc.h"
#include "RuiBody.h"
#include "RuiPreset.h"

RuiMIDIenc::RuiMIDIenc(uint8_t t_idx) {
  idx = t_idx;
  buffer = 0;
  ccValue = 0;
}

void RuiMIDIenc::update() {
  if (RuiBody.sensorsLast.knobsV[idx] != RuiBody.sensors.knobsV[idx]) {
    int8_t ccValue = constrain(ccValue + RuiBody.sensors.knobsV[idx],
                               RuiPreset.knobs.lowest_cc_value[idx],
                               RuiPreset.knobs.highest_cc_value[idx]);
    if (RuiPreset.knobs.cc_value_step[idx] > 1) {
      int steps = (RuiPreset.knobs.highest_cc_value[idx] -
                   RuiPreset.knobs.lowest_cc_value[idx]) /
                  RuiPreset.knobs.cc_value_step[idx];
      ccValue = map(ccValue, RuiPreset.knobs.lowest_cc_value[idx],
                    RuiPreset.knobs.highest_cc_value[idx], 1, steps) *
                RuiPreset.knobs.cc_value_step[idx];
    }
  }
};
