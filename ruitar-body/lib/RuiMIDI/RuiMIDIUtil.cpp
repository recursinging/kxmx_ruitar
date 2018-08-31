#include "RuiMIDIUtil.h"

const char* RuiMIDIUtil::toNoteName(uint8_t val) {
  if (val > 128 || val < 0) {
    return "";
  }
  return midi_note_name_table[val];
};
