#include "RuiPreset.h"

#define PRESET_DBG 0

  ///////// const members ///////////////////////////////////////////////////////
  const char* RuiPresetClass::PRESETS[MAX_PRESETS];

  const char* RuiPresetClass::STRING_MODES[] = {
      "Disable",
      "Note Change",
      "Legato Note Change",
      "Pitch Bend"
      "CC"
  };

  const char* RuiPresetClass::PAD_MODES[] = {
      "Disable",
      "String Note",
      "Fixed Note"
      "External Trigger",
      "CC"
  };

  const char* RuiPresetClass::JOYSTICK_MODES[] = {
      "Disable",
      "CC",
      "Pitch Bend"
  };

  const char* RuiPresetClass::FADER_MODES[] = {
      "Disable",
      "Note Change",
      "Legato Note Change",
      "Pitch Bend",
      "CC"
  };

  const char* RuiPresetClass::TOGGLE_MODES[] = {
      "Disable",
      "CC"
  };

  const char* RuiPresetClass::KNOB_MODES[] = {
      "Disable",
      "CC"
  };

  const char* RuiPresetClass::BUTTON_MODES[] = {
      "Disable",
      "CC"
  };

  const char* RuiPresetClass::PRESET_EDIT_MODES[] = {
      "Select",
      "Edit",
      "Rename",
      "Copy"
  };

  ConfigMeta RuiPresetClass::STRINGS_META[] = {
      {RuiPresetClass::strings.string_mode, 0, "string_mode", STRING_MODE, {2,2,2,2}},
      {RuiPresetClass::strings.channel, 0, "channel", CHAN,  {1,1,1,1}},
      {RuiPresetClass::strings.play_open, 0, "play_open", BOOL, {1,1,1,1}},
      {RuiPresetClass::strings.lowest_note, 0, "lowest_note", NOTE, {40,45,50,55}},
      {RuiPresetClass::strings.highest_note, 0, "highest_note", NOTE, {60,65,70,75}},
      {RuiPresetClass::strings.cc_channel, 0, "cc_channel", CHAN, {0,0,0,0}},
      {RuiPresetClass::strings.cc_number, 0, "cc_number", CC, 1,1,1,1},
      {RuiPresetClass::strings.lowest_cc_value, 0, "lowest_cc_value", SBYTE, {0,0,0,0}},
      {RuiPresetClass::strings.highest_cc_value, 0, "highest_cc_value", SBYTE, {127,127,127,11}},
      {RuiPresetClass::strings.initial_cc_value, 0, "initial_cc_value", SBYTE, {0,0,0,0}},
      {RuiPresetClass::strings.cc_value_step, 0, "cc_value_step", SBYTE, {1,1,1,1}}
  };

  ConfigMeta RuiPresetClass::PADS_META[] = {
      {RuiPresetClass::pads.pad_mode, 1, "pad_mode", PAD_MODE, {1,1,1,1}},
      {RuiPresetClass::pads.channel, 1, "channel", CHAN, {1,1,1,1}},
      {RuiPresetClass::pads.fixed_mode_note, 1, "fixed_mode_note", NOTE, {40,40,40,40}},
      {RuiPresetClass::pads.external_mode_channel, 1, "external_mode_channel", CHAN, {0,0,0,0}},
      {RuiPresetClass::pads.external_mode_note, 1, "external_mode_note", NOTE, {36,36,36,36}},
      {RuiPresetClass::pads.send_aftertouch, 1, "send_aftertouch", BOOL, {0,0,0,0}},
      {RuiPresetClass::pads.cc_channel, 1, "cc_channel", CHAN, {0,0,0,0}},
      {RuiPresetClass::pads.cc_number, 1, "cc_number", CC, 1,1,1,1},
      {RuiPresetClass::pads.lowest_cc_value, 1, "lowest_cc_value", SBYTE, {0,0,0,0}},
      {RuiPresetClass::pads.highest_cc_value, 1, "highest_cc_value", SBYTE, {127,127,127,127}},
      {RuiPresetClass::pads.initial_cc_value, 1, "initial_cc_value", SBYTE, {0,0,0,0}},
      {RuiPresetClass::pads.cc_value_step, 1, "cc_value_step", SBYTE, {1,1,1,1}}
  };

  ConfigMeta RuiPresetClass::JOYSTICK_META[] = {
      {RuiPresetClass::joystick.joystick_mode, 2, "joystick_mode", JOY_MODE, {2,2,1,1}},  // X+ X- Y+ Y-
      {RuiPresetClass::joystick.channel, 2, "channel", CHAN, {1,1,1,1}}, // X+ X- Y+ Y-
      {RuiPresetClass::joystick.cc_channel, 2, "cc_channel", CC, {1,1,1,1}},
      {RuiPresetClass::joystick.cc_number, 2, "cc_number", CC, {0,0,105,105}}, // X+ X- Y+ Y-
      {RuiPresetClass::joystick.lowest_cc_value, 2, "lowest_cc_value", SBYTE, {0,0,0,0}}, // X+ X- Y+ Y-
      {RuiPresetClass::joystick.highest_cc_value, 2, "highest_cc_value", SBYTE, {127,127,127,127}}, // X+ X- Y+ Y-
      {RuiPresetClass::joystick.initial_cc_value, 2, "initial_cc_value", SBYTE, {0,0,0,0}}, // X+ X- Y+ Y-
      {RuiPresetClass::joystick.cc_value_step, 2, "cc_value_step", SBYTE, {1,1,1,1}}// X+ X- Y+ Y-
  };

  ConfigMeta RuiPresetClass::FADERS_META[] = {
      {RuiPresetClass::faders.fader_mode, 3, "fader_mode", FADER_MODE, {4,4,4,4}},
      {RuiPresetClass::faders.channel, 3, "channel", CHAN, {1,1,1,1}},
      {RuiPresetClass::faders.lowest_note, 3, "lowest_note", NOTE, {64,64,64,64}},
      {RuiPresetClass::faders.highest_note, 3, "highest_note", NOTE, {84,84,84,84}},
      {RuiPresetClass::faders.cc_channel, 3, "cc_channel", CC, {1,1,1,1}},
      {RuiPresetClass::faders.cc_number, 3, "cc_number", CC, {91,62,105,12}},
      {RuiPresetClass::faders.lowest_cc_value, 3, "lowest_cc_value", SBYTE, {0,0,0,0}},
      {RuiPresetClass::faders.highest_cc_value, 3, "highest_cc_value", SBYTE, {127,127,127,127}},
      {RuiPresetClass::faders.initial_cc_value, 3, "initial_cc_value", SBYTE, {0,0,0,0}},
      {RuiPresetClass::faders.cc_value_step, 3, "cc_value_step", SBYTE, {1,1,1,1}}
  };

  ConfigMeta RuiPresetClass::TOGGLES_META[] = {
      {RuiPresetClass::toggles.toggle_mode, 4, "toggle_mode", TOGGLE_MODE, {1,1,1,1}},
      {RuiPresetClass::toggles.channel, 4, "channel", CHAN, {1,1,1,1}},
      {RuiPresetClass::toggles.cc_channel, 4, "cc_channel", CC, {1,1,1,1}},
      {RuiPresetClass::toggles.cc_number, 4, "cc_number", CC, {107,116,104,111}},
      {RuiPresetClass::toggles.lowest_cc_value, 4, "lowest_cc_value", SBYTE, {0,0,0,0}},
      {RuiPresetClass::toggles.highest_cc_value, 4, "highest_cc_value", SBYTE, {127,127,127,127}},
      {RuiPresetClass::toggles.initial_cc_value, 4, "initial_cc_value", SBYTE, {0,0,0,0}}
  };

  ConfigMeta RuiPresetClass::KNOBS_META[] = {
      {RuiPresetClass::knobs.knob_mode, 5, "knob_mode", KNOB_MODE, {1,1,1,1}},
      {RuiPresetClass::knobs.channel, 5, "channel", CHAN, {1,1,1,1}},
      {RuiPresetClass::knobs.lowest_note, 5, "lowest_note", NOTE, {64,64,64,64}},
      {RuiPresetClass::knobs.highest_note, 5, "highest_note", NOTE, {84,84,84,84}},
      {RuiPresetClass::knobs.cc_channel, 5, "cc_channel", CC, {1,1,1,1}},
      {RuiPresetClass::knobs.cc_number, 5, "cc_number", CC, {1,1,1,1}},
      {RuiPresetClass::knobs.lowest_cc_value, 5, "lowest_cc_value", SBYTE, {0,0,0,0}},
      {RuiPresetClass::knobs.highest_cc_value, 5, "highest_cc_value", SBYTE, {127,127,127,127}},
      {RuiPresetClass::knobs.initial_cc_value, 5, "initial_cc_value", SBYTE, {0,0,0,0}},
      {RuiPresetClass::knobs.cc_value_step, 5, "cc_value_step", SBYTE, {1,1,1,1}}
  };

  ConfigMeta RuiPresetClass::BUTTONS_META[] = {
      {RuiPresetClass::buttons.button_mode, 6, "button_mode", BUTTON_MODE, {1,1,1,1}},
      {RuiPresetClass::buttons.channel, 6, "channel", CHAN, {1,1,1,1}},
      {RuiPresetClass::buttons.cc_channel, 6, "cc_channel", CC, {1,1,1,1}},
      {RuiPresetClass::buttons.cc_number, 6, "cc_number", CC, {1,1,1,1}},
      {RuiPresetClass::buttons.lowest_cc_value, 6, "lowest_cc_value", SBYTE, {0,0,0,0}},
      {RuiPresetClass::buttons.highest_cc_value, 6, "highest_cc_value", SBYTE, {127,127,127,127}},
      {RuiPresetClass::buttons.initial_cc_value, 6, "initial_cc_value", SBYTE, {0,0,0,0}},
  };

  ConfigMeta RuiPresetClass::VOICE0_META[] = {
      {RuiPresetClass::voice0.osc_frequency, 7, "osc_frequency", FREQ, {82.41,82.41,82.41,82.41}},
      {RuiPresetClass::voice0.osc_amplitude, 7, "osc_amplitude", AMPL, {1,1,1,1}},
      {RuiPresetClass::voice0.osc_waveform, 7, "osc_waveform", WAVEFORM, {1,1,1,1}},
      {RuiPresetClass::voice0.osc_detune, 7, "osc_detune", CENT, {0,0,0,0}},
      {RuiPresetClass::voice0.osc_mix, 7, "osc_mix", AMPL, {1,1,1,0.5}},
      {RuiPresetClass::voice0.vca_adsr, 7, "vca_adsr", MILLISECOND, {10.5,35,0.5,300}},
      {RuiPresetClass::voice0.vca_envelope_mix, 7, "vca_envelope_mix", AMPL, {1,1,1,0}},
      {RuiPresetClass::voice0.vcf_adsr, 7, "vcf_adsr", MILLISECOND, {10.5,35,0.5,300}},
      {RuiPresetClass::voice0.vcf_envelope_mix, 7, "vcf_envelope_mix", AMPL, {1,0,0,0}},
      {RuiPresetClass::voice0.vca_vcf_mix, 7, "vca_vcf_mix", AMPL, {1,1,0,0}},
  };

  ConfigMeta RuiPresetClass::VOICE1_META[] = {
      {RuiPresetClass::voice1.osc_frequency, 7, "osc_frequency", FREQ, {110,110,110,110}},
      {RuiPresetClass::voice1.osc_amplitude, 7, "osc_amplitude", AMPL, {1,1,1,1}},
      {RuiPresetClass::voice1.osc_waveform, 7, "osc_waveform", WAVEFORM, {1,1,1,1}},
      {RuiPresetClass::voice1.osc_detune, 7, "osc_detune", CENT, {0,0,0,0}},
      {RuiPresetClass::voice1.osc_mix, 7, "osc_mix", AMPL, {1,1,1,1}},
      {RuiPresetClass::voice1.vca_adsr, 7, "vca_adsr", MILLISECOND, {10.5,35,0.5,300}},
      {RuiPresetClass::voice1.vca_envelope_mix, 7, "vca_envelope_mix", AMPL, {1,1,0,0}},
      {RuiPresetClass::voice1.vcf_adsr, 7, "vcf_adsr", MILLISECOND, {10.5,35,0.5,300}},
      {RuiPresetClass::voice1.vcf_envelope_mix, 7, "vcf_envelope_mix", AMPL, {1,0,0,0}},
      {RuiPresetClass::voice1.vca_vcf_mix, 7, "vca_vcf_mix", AMPL, {1,0,0,0}},
  };

  ConfigMeta RuiPresetClass::VOICE2_META[] = {
      {RuiPresetClass::voice2.osc_frequency, 7, "osc_frequency", FREQ, {146.8,146.8,146.8,146.8}},
      {RuiPresetClass::voice2.osc_amplitude, 7, "osc_amplitude", AMPL, {1,1,1,1}},
      {RuiPresetClass::voice2.osc_waveform, 7, "osc_waveform", WAVEFORM, {1,1,1,1}},
      {RuiPresetClass::voice2.osc_detune, 7, "osc_detune", CENT, {0,0,0,0}},
      {RuiPresetClass::voice2.osc_mix, 7, "osc_mix", AMPL, {1,1,1,1}},
      {RuiPresetClass::voice2.vca_adsr, 7, "vca_adsr", MILLISECOND, {10.5,35,0.5,300}},
      {RuiPresetClass::voice2.vca_envelope_mix, 7, "vca_envelope_mix", AMPL, {1,1,1,0}},
      {RuiPresetClass::voice2.vcf_adsr, 7, "vcf_adsr", MILLISECOND, {10.5,35,0.5,300}},
      {RuiPresetClass::voice2.vcf_envelope_mix, 7, "vcf_envelope_mix", AMPL, {1,0,0,0}},
      {RuiPresetClass::voice2.vca_vcf_mix, 7, "vca_vcf_mix", AMPL, {1,1,0,0}},
  };

  ConfigMeta RuiPresetClass::VOICE3_META[] = {
      {RuiPresetClass::voice3.osc_frequency, 7, "osc_frequency", FREQ, {196,196,196,196}},
      {RuiPresetClass::voice3.osc_amplitude, 7, "osc_amplitude", AMPL, {1,1,1,1}},
      {RuiPresetClass::voice3.osc_waveform, 7, "osc_waveform", WAVEFORM, {1,1,1,1}},
      {RuiPresetClass::voice3.osc_detune, 7, "osc_detune", CENT, {0,0,0,0}},
      {RuiPresetClass::voice3.osc_mix, 7, "osc_mix", AMPL, {1,1,1,1}},
      {RuiPresetClass::voice3.vca_adsr, 7, "vca_adsr", MILLISECOND, {10.5,35,0.5,300}},
      {RuiPresetClass::voice3.vca_envelope_mix, 7, "vca_envelope_mix", AMPL, {1,1,0,0}},
      {RuiPresetClass::voice3.vcf_adsr, 7, "vcf_adsr", MILLISECOND, {10.5,35,0.5,300}},
      {RuiPresetClass::voice3.vcf_envelope_mix, 7, "vcf_envelope_mix", AMPL, {1,0,0,0}},
      {RuiPresetClass::voice3.vca_vcf_mix, 7, "vca_vcf_mix", AMPL, {1,0,0,0}},
  };

  ConfigMeta RuiPresetClass::SYNTH_META[] = {
      {RuiPresetClass::synth.lfo_frequency, 8, "lfo_frequency", FREQ, {5,10,0,0}},
      {RuiPresetClass::synth.voice_mix_l, 8, "voice_mix_l", AMPL, {1,1,1,1}},
      {RuiPresetClass::synth.voice_mix_r, 8, "voice_mix_r", AMPL, {1,1,1,1}},
  };

  ConfigGroupMeta RuiPresetClass::META[] = {
      {RuiPresetClass::STRINGS_META, "strings", (sizeof(RuiPresetClass::STRINGS_META)/sizeof(ConfigMeta))},
      {RuiPresetClass::PADS_META, "pads", (sizeof(RuiPresetClass::PADS_META)/sizeof(ConfigMeta))},
      {RuiPresetClass::JOYSTICK_META, "joystick", (sizeof(RuiPresetClass::JOYSTICK_META)/sizeof(ConfigMeta))},
      {RuiPresetClass::FADERS_META, "faders", (sizeof(RuiPresetClass::FADERS_META)/sizeof(ConfigMeta))},
      {RuiPresetClass::TOGGLES_META, "toggles", (sizeof(RuiPresetClass::TOGGLES_META)/sizeof(ConfigMeta))},
      {RuiPresetClass::KNOBS_META, "knobs", (sizeof(RuiPresetClass::KNOBS_META)/sizeof(ConfigMeta))},
      {RuiPresetClass::BUTTONS_META, "buttons", (sizeof(RuiPresetClass::BUTTONS_META)/sizeof(ConfigMeta))},
      {RuiPresetClass::VOICE0_META, "voice0", (sizeof(RuiPresetClass::VOICE0_META)/sizeof(ConfigMeta))},
      {RuiPresetClass::VOICE1_META, "voice1", (sizeof(RuiPresetClass::VOICE1_META)/sizeof(ConfigMeta))},
      {RuiPresetClass::VOICE2_META, "voice2", (sizeof(RuiPresetClass::VOICE2_META)/sizeof(ConfigMeta))},
      {RuiPresetClass::VOICE3_META, "voice3", (sizeof(RuiPresetClass::VOICE3_META)/sizeof(ConfigMeta))},
      {RuiPresetClass::SYNTH_META, "synth", (sizeof(RuiPresetClass::SYNTH_META)/sizeof(ConfigMeta))},
  };

  int RuiPresetClass::numSections = (sizeof(META) / sizeof(ConfigGroupMeta));


  unsigned int RuiPresetClass::btnDisableMicros = 500000; //500ms

  ///////// Non-const members ///////////////////////////////////////////////////
  PresetState RuiPresetClass::state = INITIALIZING;
  unsigned int RuiPresetClass::currentPreset = 0;
  unsigned int RuiPresetClass::numberOfPresets = 0;
  unsigned int RuiPresetClass::presetCursor = 0;
  unsigned int RuiPresetClass::presetNameCursor = 0;
  unsigned int RuiPresetClass::configGroupCursor = 0;
  unsigned int RuiPresetClass::configCursor = 0;
  unsigned int RuiPresetClass::btn0EventTS = 0;
  unsigned int RuiPresetClass::btn1EventTS = 0;
  unsigned int RuiPresetClass::btn2EventTS = 0;
  unsigned int RuiPresetClass::btn3EventTS = 0;

  char RuiPresetClass::errorMessage[MAX_ERROR_SIZE] = {0};
  char RuiPresetClass::rootPath[MAX_PRESET_PATH_SIZE] = {0};
  char RuiPresetClass::presetName[MAX_PRESET_NAME_SIZE + 1] = {0};
  char RuiPresetClass::presetReName[MAX_PRESET_NAME_SIZE + 1] = {0};
  char RuiPresetClass::fullPath[MAX_PRESET_PATH_SIZE + MAX_PRESET_NAME_SIZE + 4] = {0};

  StringsConfig RuiPresetClass::strings = {};
  PadsConfig RuiPresetClass::pads = {};
  JoystickConfig RuiPresetClass::joystick = {};
  FaderConfig RuiPresetClass::faders = {};
  ToggleConfig RuiPresetClass::toggles = {};
  KnobConfig RuiPresetClass::knobs = {};
  ButtonConfig RuiPresetClass::buttons = {};
  SynthVoiceConfig RuiPresetClass::voice0 = {};
  SynthVoiceConfig RuiPresetClass::voice1 = {};
  SynthVoiceConfig RuiPresetClass::voice2 = {};
  SynthVoiceConfig RuiPresetClass::voice3 = {};
  SynthConfig RuiPresetClass::synth = {};


//////// Methods //////////////////////////////////////////////////////////////
bool RuiPresetClass::initialize() {
  strcpy(presetName, "DEFAULT");
  PRESETS[0] = "DEFAULT";
  for (int i = 0; i < numSections; ++i) {
    ConfigGroupMeta grp_meta = META[i];
    ConfigMeta *grp = grp_meta.idx;
    for (size_t k = 0; k < grp_meta.size; ++k) {
      ConfigMeta m = grp[k];
      for (size_t v = 0; v < 4; v++) {
        m.idx[v] = m.initialValues[v];
      }
    }
  }
  state = PRESET_SELECT;
  return true;
};
//bool PresetClass::initialized = PresetClass::initialize();

void RuiPresetClass::formatType(char* buffer, float val, ConfigType type) {
  switch (type) {
  case (STRING_MODE):
    strcpy(buffer, STRING_MODES[(int)val]);
    break;
  case (PAD_MODE):
    strcpy(buffer, PAD_MODES[(int)val]);
    break;
  case (JOY_MODE):
    strcpy(buffer, PAD_MODES[(int)val]);
    break;
  case (FADER_MODE):
    strcpy(buffer, FADER_MODES[(int)val]);
    break;
  case (TOGGLE_MODE):
    strcpy(buffer, TOGGLE_MODES[(int)val]);
    break;
  case (KNOB_MODE):
    strcpy(buffer, KNOB_MODES[(int)val]);
    break;
  case (BUTTON_MODE):
    strcpy(buffer, BUTTON_MODES[(int)val]);
    break;
  case (NOTE):
     strcpy(buffer, RuiMIDIUtil::toNoteName((int)val));
    break;
   case (FREQ):
     sprintf(buffer, "%fHz", val);
    break;
    case (AMPL):
    sprintf(buffer, "%f", val);
      break;
    case (CENT):
      sprintf(buffer, "%d cents", (int)val);
      break;
    case (MILLISECOND):
      sprintf(buffer, "%dMs", (int)val);
      break;
    case (WAVEFORM):
      itoa(val, buffer, 10);
      break;
  default:
    itoa(val, buffer, 10);
    break;
  }
}
float RuiPresetClass::typeMin(ConfigType type) {
    float min;
    switch (type) {
    case (SBYTE):
      min = 0;
      break;
    case (UBYTE):
      min = 0;
      break;
    case (BOOL):
      min = 0;
      break;
    case (FLOAT):
      min = -10000;
      break;
    case (CHAN):
      min = 1;
      break;
    case (NOTE):
      min = 0;
      break;
    case (CC):
      min = 0;
      break;
    case (STRING_MODE):
      min = 0;
      break;
    case (PAD_MODE):
      min = 0;
      break;
    case (JOY_MODE):
      min = 0;
      break;
    case (FADER_MODE):
      min = 0;
      break;
    case (TOGGLE_MODE):
      min = 0;
      break;
    case (KNOB_MODE):
      min = 0;
      break;
    case (BUTTON_MODE):
      min = 0;
      break;
    case (FREQ):
      min = -20000;
      break;
    case (AMPL):
      min = 0;
      break;
    case (CENT):
      min = -1200;
      break;
    case (MILLISECOND):
      min = 0;
      break;
    case (WAVEFORM):
      min = 0;
      break;
    default:
      min = 0;
      break;
    }
    return min;
  }

float RuiPresetClass::typeMax(ConfigType type) {
    float max;
    switch (type) {
    case (SBYTE):
      max = 127;
      break;
    case (UBYTE):
      max = 255;
      break;
    case (BOOL):
      max = 1;
      break;
    case (CHAN):
      max = 16;
      break;
    case (NOTE):
      max = 127;
      break;
    case (CC):
      max = 127;
      break;
    case (STRING_MODE):
      max = (sizeof(STRING_MODES) / sizeof(STRING_MODES[0])) - 1;
      break;
    case (PAD_MODE):
      max = (sizeof(PAD_MODES) / sizeof(PAD_MODES[0])) - 1;
      break;
    case (JOY_MODE):
      max = (sizeof(JOYSTICK_MODES) / sizeof(JOYSTICK_MODES[0])) - 1;
      break;
    case (FADER_MODE):
      max = (sizeof(FADER_MODES) / sizeof(FADER_MODES[0])) - 1;
      break;
    case (TOGGLE_MODE):
      max = (sizeof(TOGGLE_MODES) / sizeof(TOGGLE_MODES[0])) - 1;
      break;
    case (KNOB_MODE):
      max = (sizeof(KNOB_MODES) / sizeof(KNOB_MODES[0])) - 1;
      break;
    case (BUTTON_MODE):
      max = (sizeof(BUTTON_MODES) / sizeof(BUTTON_MODES[0])) - 1;
      break;
    case (FREQ):
      max = 20000;
      break;
    case (AMPL):
      max = 1;
      break;
    case (CENT):
      max = 1200;
      break;
    case (MILLISECOND):
      max = 1000;
      break;
    case (WAVEFORM):
      max = 100;
      break;
    default:
      max = 255;
      break;
    }
    return max;
  }

// Constructor
RuiPresetClass::RuiPresetClass() {
  btn0EventTS = btn1EventTS = btn2EventTS = btn3EventTS = micros();
  initialize();
}

// Destructor
RuiPresetClass::~RuiPresetClass(){
};

void RuiPresetClass::begin(const char* t_path) {
  strcpy(rootPath, t_path);

#if PRESET_DBG
  Serial.print("Initializing preset with root: ");
  Serial.println(rootPath);
#endif

  while (!SD.begin(BUILTIN_SDCARD)) {
    #if PRESET_DBG
    Serial.println(F("Failed to initialize SD library"));
    #endif
    delay(1000);
  }

  File dir = SD.open(rootPath);
  if (!dir) {
    SD.mkdir(rootPath);
    #if PRESET_DBG
    Serial.print("Failed to open directory ");
    Serial.println(rootPath);
    #endif
  }
  if (!dir.isDirectory()) {
    #if PRESET_DBG
    Serial.print(rootPath);
    Serial.println(" is not a directory.");
    #endif
  }
  int i = 1;
  while (true) {
    File file = dir.openNextFile();
    if (!file) {
      break;
    }
    char* fileName = file.name();
    if (isValidFileName(fileName)) {
      char presetName[MAX_PRESET_NAME_SIZE + 1];
      fromFileName(presetName, fileName);
      PRESETS[i] = strdup(presetName);
      i++;
    } else {
      #if PRESET_DBG
      Serial.print("Invalid file name: ");
      Serial.println(fileName);
      #endif
    }
  }
  numberOfPresets = i;

#if PRESET_DBG
  Serial.println("Found presets:");
  for (size_t i = 0; i < MAX_PRESETS; i++) {
    if (PRESETS[i]) {
      Serial.print(i);
      Serial.print(" = ");
      Serial.print(PRESETS[i]);
      Serial.println();
    }
  }
  Serial.println();
#endif
}

// Loads a preset at the given index by reading and parsing the file
void RuiPresetClass::loadPreset(size_t t_idx) {
  uint32_t start = micros();
  if (t_idx > MAX_PRESETS || !PRESETS[t_idx]) {
#if PRESET_DBG
    Serial.print(t_idx);
    Serial.println(" is an invalid preset index");
#endif
    return;
  }

  if (t_idx == 0) {
    // Load the default preset;
    for (size_t i = 0; i < (sizeof(META) / sizeof(ConfigGroupMeta));
        ++i) {
      ConfigGroupMeta grp_meta = META[i];
      ConfigMeta *grp = grp_meta.idx;
      for (size_t k = 0; k < grp_meta.size; ++k) {
        ConfigMeta m = grp[k];
        for (size_t v = 0; v < NN; v++) {
          m.idx[v] = m.initialValues[v];
        }
      }
    }
    strcpy(presetName, "DEFAULT");
    currentPreset = t_idx;
    return;
  }

  ConfigMeta *currentSection = NULL;
  uint8_t currentSectionSize = 0;

  toCanonicalFilePath(fullPath, PRESETS[t_idx]);

  File file = SD.open(fullPath);

  if (!file) {
#if PRESET_DBG
    Serial.print(fullPath);
    Serial.println(" was not able to be read");
#endif
    state = ERROR;
    strcpy(errorMessage, "Unable to open ");
    strcat(errorMessage, fullPath);
    return;
  }

#if PRESET_DBG
  Serial.print("Reading preset file: ");
  Serial.println(fullPath);
#endif

  // This is a simple parser for the ini style preset config files.
  // I've tried to make it somewhat tolerant to syntax mistakes,
  // but it's not thoroughly tested.

  // These are the necessary buffers
  char buffer[MAX_PRESET_LINE_LENGTH];
  char key[MAX_PRESET_KEY_SIZE];
  char value[MAX_PRESET_VALUE_SIZE];

  // Loop char for char over the file and parse accordingly.
  size_t bufferidx = 0;
  while (file.available()) {
    char c = (char) file.read();

    if (c == '\n' || (bufferidx >= (MAX_PRESET_LINE_LENGTH - 1))) {
      buffer[bufferidx] = '\0';

      bool ignore = false;
      bool isSection = false;
      bool inKey = true;

      key[0] = '\0';
      value[0] = '\0';

      int i = 0;
      int k = 0;
      int v = 0;
      while (buffer[i] != '\0') {
        char c = buffer[i];
        if (c == '#' || c == '\n') {
          // ignore empty lines and comments completely...
          ignore = true;
          break;
        }
        if (c == ' ' || c == '\t') {
          // Skip whitespace
          i++;
          continue;
        }
        if (c == '[') {
          // Section start
          isSection = true;
          i++;
          continue;
        }
        if (c == ']') {
          // Section end
          i++;
          continue;
        }
        if (c == '=') {
          // Switch from key to value
          inKey = false;
          i++;
          key[k] = '\0';
          continue;
        }

        if (inKey) {
          // Add char to the key
          if ((c >= 'a' && c <= 'z') || (c == '_')) {
            key[k] = c;
            k++;
          }
        } else {
          // Add char to the value
          if ((c >= '0' && c <= '9') || (c == ',')) {
            value[v] = c;
            v++;
          }
        }
        i++;
      }
      if (ignore || k == 0) {
        // We want to ignore this line, continue the loop here.
        continue;
      }
      // Terminate the char arrays as C strings
      key[k++] = '\0';
      value[v++] = '\0';

      if (isSection) {
        // Section key. loop over all known sections and compare names
        bool foundSection = false;
        for (int m = 0; m < numSections; m++) {
          if (strcmp(META[m].name, key) == 0) {
            foundSection = true;
            currentSection = META[m].idx;
            currentSectionSize = META[m].size;
            break;
          }
        }

        if (!foundSection) {
          // If we have no matching section, ignore the rest of the KV pairs
#if PRESET_DBG
          Serial.print("Could not resolve section with the name: ");
          Serial.println(key);
#endif
          currentSection = NULL;
          currentSectionSize = 0;
        }

      } else {
        if (currentSection) {
          bool foundConfig = false;
          for (size_t s = 0; s < currentSectionSize; ++s) {
            if (strcmp(currentSection[s].name, key) == 0) {
              foundConfig = true;
              // Pointer to the actual configuration values
              float *vals = currentSection[s].idx;
              // Now we do a basic string to float number conversion...
              // This will parse a string like 1,2,3,4
              int i = 0;
              int nbi = 0;
              int vi = 0;
              float num = 0;
              char numBuffer[16];
              while (value[i] != '\0') {
                if (vi == NN) {
                  // We only have space for N bytes in the config arrays
                  break;
                }
                numBuffer[nbi] = value[i];
                nbi++;
                if (c == ',' || value[i + 1] == '\0') {
                  numBuffer[nbi++] = '\0';
                  num = strtod(numBuffer, NULL);
                  // We have our decimal number. Clamp to min and max;

                  num = constrain(num, typeMin(currentSection[s].type), typeMax(currentSection[s].type));

                  // Set the number value at the appropriate offset
                  vals[vi] = num;
                  vi++;
                  nbi = 0;
                  num = 0;
                }
                i++;
              }

              if (vi == 0) {
                vals[vi] = 0;
                vi++;
              }

              if (vi < NN - 1) {
                // If < N values were given in the preset file, expand them now
                for (size_t q = vi; q < NN; q++) {
                  vals[q] = vals[vi - 1];
                }
              }
              break;
            }
          }
          if (!foundConfig) {
#if PRESET_DBG
            Serial.print("Could not resolve config with the name: ");
            Serial.println(key);
#endif
          }

        }
      }
      bufferidx = 0;
    } else {
      buffer[bufferidx] = c;
      bufferidx++;
    }
  }

  file.close();

  currentPreset = t_idx;
  strcpy(presetName, PRESETS[t_idx]);

  uint32_t duration = micros() - start;

#if PRESET_DBG
  Serial.print("Loaded preset: ");
  Serial.print(presetName);
  Serial.print(" - took: ");
  Serial.print(duration);
  Serial.println("us\n");
#endif
}

bool RuiPresetClass::isValidFileName(const char* t_fileName) {
  size_t i = 0;
  size_t e = 0;
  bool inExt = false;
  while (t_fileName[i] != '\0') {
    if (inExt) {
      if (e == 0 && t_fileName[i] != 'P') {
        return false;
      } else if (e == 1 && t_fileName[i] != 'R') {
        return false;
      } else if (e == 2 && t_fileName[i] != 'E') {
        return false;
      } else if (e == 3) {
        return false;
      } else {
        e++;
      }
    }
    if (t_fileName[i] == '.') {
      inExt = true;
    }
    if (i >= MAX_PRESET_NAME_SIZE && !inExt) {
      return false;
    }
    i++;
  }
  return true;
}

void RuiPresetClass::toFileName(char* t_fileName, const char* t_presetName) {
  strcpy(t_fileName, t_presetName);
  strcat(t_fileName, ".pre");
}
void RuiPresetClass::fromFileName(char* t_presetName, const char* t_fileName) {
  size_t i = 0;
  while (t_fileName[i] != '.') {
    t_presetName[i] = t_fileName[i];
    i++;
  }
  t_presetName[i++] = '\0';
}

void RuiPresetClass::toCanonicalFilePath(char* t_filePath, const char* t_presetName){
  strcpy(t_filePath, rootPath);
  strcat(t_filePath, t_presetName);
  strcat(t_filePath, ".pre");
}

void RuiPresetClass::renamePreset(size_t t_idx, const char* t_newName){
  if (t_idx > MAX_PRESETS || !PRESETS[t_idx]) {
  #if PRESET_DBG
      Serial.print(t_idx);
      Serial.println(" is an invalid preset index");
  #endif
      return;
  }
  loadPreset(t_idx);
  char originalPresetPath[MAX_PRESET_PATH_SIZE + MAX_PRESET_NAME_SIZE + 4];
  toCanonicalFilePath(originalPresetPath, PRESETS[t_idx]);
  SD.remove(originalPresetPath);
  PRESETS[t_idx] = strdup(t_newName);

#if PRESET_DBG
  Serial.print("Renamed preset: ");
  Serial.println(PRESETS[t_idx]);
#endif

  savePreset(t_newName);
  loadPreset(t_idx);
}

void RuiPresetClass::savePreset(const char* t_presetName) {

  if (currentPreset == 0) {
#if PRESET_DBG
  Serial.println("The default preset cannot be saved");
#endif
    return;
  }
  char fullFilePath[MAX_PRESET_PATH_SIZE + MAX_PRESET_NAME_SIZE + 4];
  toCanonicalFilePath(fullFilePath, t_presetName);

#if PRESET_DBG
  Serial.print("Saving preset file: ");
  Serial.println(fullFilePath);
#endif
  // Ensure the folder exists
  SD.mkdir(rootPath);
  // Remove the old file if neccessary
  SD.remove(fullFilePath);
  // Open file for writing
  File file = SD.open(fullFilePath, FILE_WRITE);

  if (!file) {
    #if PRESET_DBG
    Serial.println("Failed to create file");
    #endif
    return;
  }

  for (size_t i = 0; i < (sizeof(META) / sizeof(ConfigGroupMeta)); ++i) {
    ConfigGroupMeta grp_meta = META[i];
    ConfigMeta *grp = grp_meta.idx;
    file.print("[");
    file.print(grp_meta.name);
    file.print("]\n\n");
    for (size_t k = 0; k < grp_meta.size; ++k) {
      ConfigMeta m = grp[k];
      file.print(m.name);
      file.print(" = ");
      file.print(m.idx[0]);
      file.print(", ");
      file.print(m.idx[1]);
      file.print(", ");
      file.print(m.idx[2]);
      file.print(", ");
      file.print(m.idx[3]);
      file.print("\n");
    }
    file.print("\n");
  }
  file.print("\n");

  // Close the file (File's destructor doesn't close the file)
  file.close();
}

void RuiPresetClass::copyPreset(size_t t_idx) {
  if (numberOfPresets + 1 >= MAX_PRESETS) {
    state = ERROR;
    strcpy(errorMessage, "Max presets reached. Not copying.");
    return;
   }
#if PRESET_DBG
  Serial.print("Copying preset: ");
  Serial.print(PRESETS[t_idx]);
  Serial.print(" - at index: ");
  Serial.println(t_idx);
#endif

  loadPreset(t_idx);
  currentPreset = presetCursor = numberOfPresets;
  numberOfPresets = numberOfPresets + 1;
  strcpy(presetName, "PRESET");
  char buffer[3];
  itoa(currentPreset, buffer, 10);
  strcat(presetName, buffer);
  PRESETS[currentPreset] = strdup(presetName);

#if PRESET_DBG
  Serial.print("Created new preset: ");
  Serial.print(PRESETS[currentPreset]);
  Serial.print(" - at index: ");
  Serial.println(currentPreset);
#endif

  savePreset(presetName);
}

void RuiPresetClass::update() {
  updateEncoders(RuiBody.sensors.knobsV[0], RuiBody.sensors.knobsV[1], RuiBody.sensors.knobsV[2],
      RuiBody.sensors.knobsV[3]);
  updateButtons(RuiBody.sensors.buttonsV[0], RuiBody.sensors.buttonsV[1],
      RuiBody.sensors.buttonsV[2], RuiBody.sensors.buttonsV[3]);
}


void RuiPresetClass::updateEncoders(int t_incr0, int t_incr1, int t_incr2, int t_incr3) {
  switch (state) {
  case (INITIALIZING):
    break;
  case (ERROR):
    break;
  case (PRESET_SELECT):
      if (t_incr0 != 0 && !(presetCursor == 0 && t_incr0 < 0)) {
        size_t max = numberOfPresets - 1;
        presetCursor += t_incr0;
        if (presetCursor >= max) {
          presetCursor = max;
        }
      }
    break;
  case (PRESET_NAME_CHANGE):
    // Knob0 moves the cursor
    if (t_incr0 != 0 && !(presetNameCursor == 0 && t_incr0 < 0)) {
      size_t max = MAX_PRESET_NAME_SIZE - 1;
      presetNameCursor += t_incr0;
      if (presetNameCursor >= max) {
        presetNameCursor = max;
      }
    }
    // Knob1 changes the letter under the cursor
    if (t_incr1 != 0
        && !(presetReName[presetNameCursor] == 'A' && t_incr1 < 0)) {
      presetReName[presetNameCursor] += t_incr1;
      if (presetReName[presetNameCursor] < 'A') {
        presetReName[presetNameCursor] = 'A';
      }
      if (presetReName[presetNameCursor] > 'Z') {
        presetReName[presetNameCursor] = 'Z';
      }
    }
    break;
  case (CONFIG_GROUP_SELECT):
    if (t_incr0 != 0 && !(configGroupCursor == 0 && t_incr0 < 0)) {
      size_t max = (sizeof(META) / sizeof(ConfigGroupMeta)) - 1;
      configGroupCursor += t_incr0;
      if (configGroupCursor >= max) {
        configGroupCursor = max;
      }
    }
     break;
  case (CONFIG_SELECT):
    if (t_incr0 != 0 && !(configCursor == 0 && t_incr0 < 0)) {
      size_t max = META[configGroupCursor].size;
      configCursor += t_incr0;
      if (configCursor >= max) {
        configCursor = max;
      }
    }
    break;
  case (CONFIG_EDIT):
    ConfigMeta meta = META[configGroupCursor].idx[configCursor];
    size_t max = typeMax(meta.type);
    if (t_incr0 != 0 && !(meta.idx[0] == 0 && t_incr0 < 0)) {
      meta.idx[0] += t_incr0;
      if (meta.idx[0] >= max) {
        meta.idx[0] = max;
      }
    }
    if (t_incr1 != 0 && !(meta.idx[1] == 0 && t_incr1 < 0)) {
      meta.idx[1] += t_incr1;
      if (meta.idx[1] >= max) {
        meta.idx[1] = max;
      }
    }
    if (t_incr2 != 0 && !(meta.idx[2] == 0 && t_incr2 < 0)) {
      meta.idx[2] += t_incr2;
      if (meta.idx[2] >= max) {
        meta.idx[2] = max;
      }
    }
    if (t_incr3 != 0 && !(meta.idx[3] == 0 && t_incr3 < 0)) {
      meta.idx[3] += t_incr3;
      if (meta.idx[3] >= max) {
        meta.idx[3] = max;
      }
    }
    break;
  }
}


void RuiPresetClass::updateButtons(bool t_btn0, bool t_btn1, bool t_btn2, bool t_btn3) {
  size_t ts = micros();

  if (t_btn0) {
    if (ts - btn0EventTS < btnDisableMicros) {
      t_btn0 = false;
    } else {
      btn0EventTS = ts;
    }
  }

  if (t_btn1) {
    if (ts - btn1EventTS < btnDisableMicros) {
      t_btn1 = false;
    } else {
      btn1EventTS = ts;
    }
  }

  if (t_btn2) {
    if (ts - btn2EventTS < btnDisableMicros) {
      t_btn2 = false;
    } else {
      btn2EventTS = ts;
    }
  }

  if (t_btn3) {
    if (ts - btn3EventTS < btnDisableMicros) {
      t_btn3 = false;
    } else {
      btn3EventTS = ts;
    }
  }

  // Button 0 is typically select, button 1 is back/cancel.
  switch (state) {
  case (INITIALIZING):
    break;
  case (ERROR):
    if (t_btn0) {
      // reset the error message
      errorMessage[0] = '\n';
    }
    break;
  case (PRESET_SELECT):
    if (t_btn0) {
      // Select
      loadPreset(presetCursor);
    }
    if (t_btn1) {
      // Edit
      loadPreset(presetCursor);
      state = CONFIG_GROUP_SELECT;
    }
    if (t_btn2) {
      // Rename
      loadPreset(presetCursor);
      strcpy(presetReName, presetName);
      state = PRESET_NAME_CHANGE;
    }
    if (t_btn3) {
      // Copy
      copyPreset(presetCursor);
      strcpy(presetReName, presetName);
      state = PRESET_NAME_CHANGE;
    }
    break;
  case (PRESET_NAME_CHANGE):
    if (t_btn0) {
      // OK
      renamePreset(currentPreset, presetReName);
      state = PRESET_SELECT;
    }
    if (t_btn1) {
      // Cancel
      loadPreset(presetCursor);
      state = PRESET_SELECT;
    }
    if (t_btn3) {
      presetReName[presetNameCursor] = '\0';
      presetNameCursor = constrain(presetNameCursor - 1, ((size_t)0), MAX_PRESET_NAME_SIZE -1);
    }
    break;
  case (CONFIG_GROUP_SELECT):
     if (t_btn0) {
       // Select
       state = CONFIG_SELECT;
     }
     if (t_btn1) {
       // Back
       state = PRESET_SELECT;
     }
     break;
  case (CONFIG_SELECT):
    if (t_btn0) {
      // Select
      state = CONFIG_EDIT;
    }
    if (t_btn1) {
      // Back
      state = CONFIG_GROUP_SELECT;
    }
    break;
  case (CONFIG_EDIT):
    if (t_btn0) {
      // OK
      savePreset(presetName);
      state = CONFIG_SELECT;
    }
    if (t_btn1) {
      // Cancel
      loadPreset(presetCursor);
      state = CONFIG_SELECT;
    }
    break;
  }
}

void RuiPresetClass::writeToDisplay(TeensyView &display) {
#if PRESET_DBG
//  Serial.print("Writing to display at state: ");
//  Serial.println(state);

  Serial.print("##### ");
  Serial.print(presetName);
  Serial.println(" #####");
  display.clear(ALL);
  display.setCursor(0, 0);

  size_t x = 0;
  size_t q = 0;

  switch (state) {
  case (INITIALIZING):
    Serial.print("Initializing...");
    break;
  case (ERROR):
    Serial.println("--- ERROR ---");
    Serial.println(errorMessage);
    Serial.println("Clear");
    break;
  case (PRESET_SELECT):
    Serial.println("--- PRESET_SELECT ---");
    if (presetCursor > 0) {
      Serial.println(PRESETS[presetCursor - 1]);
    }
    Serial.print(PRESETS[presetCursor]);
    Serial.println(" *");
    if (presetCursor < numberOfPresets - 1) {
      Serial.println(PRESETS[presetCursor + 1]);
    }
    Serial.println("Select | Edit | Rename | Copy");
    break;
  case (PRESET_NAME_CHANGE):
    Serial.println("--- PRESET_NAME_CHANGE ---");

    while (presetReName[x] != '\0'){
      Serial.print(presetReName[x]);
      x++;
    }
    Serial.println();

    while (q < presetNameCursor) {
      Serial.print(" ");
      q++;
    }
    Serial.println("*");

    Serial.println("Save | Cancel | | Del.");

    break;
  case (CONFIG_GROUP_SELECT):
    Serial.println("--- CONFIG_GROUP_SELECT ---");
    if (configGroupCursor > 0) {
      Serial.println(META[configGroupCursor - 1].name);
    }
    Serial.print(META[configGroupCursor].name);
    Serial.println(" *");
    if (configGroupCursor < (sizeof(META) / sizeof(ConfigGroupMeta)) - 1) {
      Serial.println(META[configGroupCursor + 1].name);
    }
    Serial.println("Select | Back ");
    break;
  case (CONFIG_SELECT):
    Serial.println("--- CONFIG_SELECT ---");
    Serial.print(presetName);
    Serial.print(" >> ");
    Serial.print(META[configGroupCursor].name);
    Serial.println();

    if (configCursor > 0) {
      Serial.println(META[configGroupCursor].idx[configCursor - 1].name);
    }
    Serial.print(META[configGroupCursor].idx[configCursor].name);
    Serial.println(" *");
    if (configCursor < (META[configGroupCursor].size) - 1) {
      Serial.println(META[configGroupCursor].idx[configCursor + 1].name);
    }
    Serial.println("Select | Back ");
    break;
  case (CONFIG_EDIT):
    Serial.println("--- CONFIG_EDIT ---");
    Serial.print(presetName);
    Serial.print(" >> ");
    Serial.print(META[configGroupCursor].name);
    Serial.print(" >> ");
    Serial.print(META[configGroupCursor].idx[configCursor].name);
    Serial.println();

    ConfigMeta config = META[configGroupCursor].idx[configCursor];

    char buffer[80];
    char buffer2[80];
    formatType(buffer, config.idx[0], config.type);
    Serial.print(buffer);
    Serial.print(" | ");
    formatType(buffer2, config.idx[1], config.type);
    Serial.print(buffer2);
    Serial.print(" | ");
    formatType(buffer, config.idx[2], config.type);
    Serial.print(buffer);
    Serial.print(" | ");
    formatType(buffer, config.idx[3], config.type);
    Serial.print(buffer);
    Serial.println();
    Serial.println("Save | Cancel ");

    break;
  }

  Serial.println();
  #endif

  display.display();

#if PRESET_DBG
//  Serial.println("...done!");
#endif
}

RuiPresetClass RuiPreset;
