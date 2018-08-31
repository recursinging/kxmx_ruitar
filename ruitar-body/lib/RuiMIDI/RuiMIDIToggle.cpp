#include "RuiMIDIToggle.h"
#include "RuiBody.h"
#include "RuiPreset.h"

RuiMIDIToggle::RuiMIDIToggle(uint8_t t_idx) {
  idx = t_idx;
  toggle = false;
  rose = false;
  state = false;
  ccValue = 0;
  ccValueMomentary = 0;
}

void RuiMIDIToggle::update() {
  state = RuiBody.sensors.togglesV[idx];
  if (state) {
    ccValueMomentary = RuiPreset.buttons.highest_cc_value[idx];
    if (!rose) {
      rose = true;
    }
  } else {
    ccValueMomentary = RuiPreset.buttons.lowest_cc_value[idx];
    if (rose) {
      toggle = !toggle;
      rose = false;
      if (toggle) {
        ccValue = RuiPreset.toggles.highest_cc_value[idx];
      } else {
        ccValue = RuiPreset.toggles.lowest_cc_value[idx];
      }
    }
  }
};
