#include "RuiMIDIButton.h"
#include "RuiBody.h"
#include "RuiPreset.h"

RuiMIDIButton::RuiMIDIButton(uint8_t t_idx) {
  idx = t_idx;
  toggle = false;
  rose = false;
  state = false;
  ccValue = 0;
  ccValueMomentary = 0;
}

void RuiMIDIButton::update() {
  state = RuiBody.sensors.buttonsV[idx];
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
        ccValue = RuiPreset.buttons.highest_cc_value[idx];
      } else {
        ccValue = RuiPreset.buttons.lowest_cc_value[idx];
      }
    }
  }
};
