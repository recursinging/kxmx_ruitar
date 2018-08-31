#ifndef RuiPreset_h
#define RuiPreset_h

#include <Arduino.h>
#include <SD.h>
#include <TeensyView.h>

#include "RuiBody.h"
#include "RuiMIDIUtil.h"

#define MAX_PRESETS ((size_t)64)
#define MAX_PRESET_LINE_LENGTH ((size_t)128)
#define MAX_PRESET_KEY_SIZE ((size_t)64)
#define MAX_PRESET_VALUE_SIZE ((size_t)64)
#define MAX_PRESET_PATH_SIZE ((size_t)64)
#define MAX_PRESET_NAME_SIZE ((size_t)8)
#define MAX_ERROR_SIZE ((size_t)256)

#define NN 4

// There are a couple of different display modes for navigation.
enum PresetState {
  INITIALIZING,
  ERROR,
  PRESET_SELECT,
  PRESET_NAME_CHANGE,
  CONFIG_GROUP_SELECT,
  CONFIG_SELECT,
  CONFIG_EDIT
};

// The supported configuration types
enum ConfigType {
  SBYTE,
  UBYTE,
  SSHORT,
  USHORT,
  SINT,
  UINT,
  FLOAT,
  BOOL,
  CHAN,
  NOTE,
  CC,
  STRING_MODE,
  PAD_MODE,
  JOY_MODE,
  FADER_MODE,
  TOGGLE_MODE,
  KNOB_MODE,
  BUTTON_MODE,
  FREQ,
  AMPL,
  CENT,
  MILLISECOND,
  WAVEFORM
};

// The configuration meta info container class
struct ConfigMeta {
  float* idx;
  uint8_t group;
  const char* name;
  ConfigType type;
  float initialValues[NN];
};

// The configuration meta info container class
struct ConfigGroupMeta {
  ConfigMeta* idx;
  const char* name;
  size_t size;
};

struct StringsConfig {
  float string_mode[NN];
  float channel[NN];
  float play_open[NN];
  float lowest_note[NN];
  float highest_note[NN];
  float cc_channel[NN];
  float cc_number[NN];
  float lowest_cc_value[NN];
  float highest_cc_value[NN];
  float initial_cc_value[NN];
  float cc_value_step[NN];
};

struct PadsConfig {
  float pad_mode[NN];
  float channel[NN];
  float fixed_mode_note[NN];
  float external_mode_channel[NN];
  float external_mode_note[NN];
  float send_aftertouch[NN];
  float cc_channel[NN];
  float cc_number[NN];
  float lowest_cc_value[NN];
  float highest_cc_value[NN];
  float initial_cc_value[NN];
  float cc_value_step[NN];
};

struct JoystickConfig {
  float joystick_mode[NN];
  float channel[NN];
  float cc_channel[NN];
  float cc_number[NN];
  float lowest_cc_value[NN];
  float highest_cc_value[NN];
  float initial_cc_value[NN];
  float cc_value_step[NN];
};

struct FaderConfig {
  float fader_mode[NN];
  float channel[NN];
  float lowest_note[NN];
  float highest_note[NN];
  float cc_channel[NN];
  float cc_number[NN];
  float lowest_cc_value[NN];
  float highest_cc_value[NN];
  float initial_cc_value[NN];
  float cc_value_step[NN];
};

struct ToggleConfig {
  float toggle_mode[NN];
  float channel[NN];
  float cc_channel[NN];
  float cc_number[NN];
  float lowest_cc_value[NN];
  float highest_cc_value[NN];
  float initial_cc_value[NN];
};

struct KnobConfig {
  float knob_mode[NN];
  float channel[NN];
  float lowest_note[NN];
  float highest_note[NN];
  float cc_channel[NN];
  float cc_number[NN];
  float lowest_cc_value[NN];
  float highest_cc_value[NN];
  float initial_cc_value[NN];
  float cc_value_step[NN];
};

struct ButtonConfig {
  float button_mode[NN];
  float channel[NN];
  float cc_channel[NN];
  float cc_number[NN];
  float lowest_cc_value[NN];
  float highest_cc_value[NN];
  float initial_cc_value[NN];
};

struct SynthVoiceConfig {
  float osc_frequency[NN];
  float osc_amplitude[NN];
  float osc_waveform[NN];
  float osc_detune[NN];
  float osc_mix[NN];
  float vca_adsr[NN];          // attack, decay, sustain, release in ms
  float vca_envelope_mix[NN];  // cv, adsr, lfo0, lfo1
  float vcf_adsr[NN];          // attack, decay, sustain, release in ms
  float vcf_envelope_mix[NN];  // cv, adsr, lfo0, lfo1
  float vca_vcf_mix[NN];       // vca, vcf_lp, vcf_bp, vcf_hp
};

struct SynthConfig {
  float voice_mix_l[NN];
  float voice_mix_r[NN];
  float lfo_frequency[NN];  // lfo0, lfo1, NA, NA
};

class RuiPresetClass {
 private:
  static bool initialized;
  static bool initialize();

  static PresetState state;
  static unsigned int presetCursor;
  static unsigned int presetNameCursor;
  static unsigned int configGroupCursor;
  static unsigned int configCursor;
  static unsigned int btn0EventTS;
  static unsigned int btn1EventTS;
  static unsigned int btn2EventTS;
  static unsigned int btn3EventTS;
  static unsigned int btnDisableMicros;

  static char errorMessage[];
  static char rootPath[];
  static char fullPath[];
  static char presetReName[];

  void updateEncoders(int value0, int value1, int value2, int value3);
  void updateButtons(bool value0, bool value1, bool value2, bool value3);

 public:
  static unsigned int currentPreset;
  static unsigned int numberOfPresets;

  static const char* PRESETS[];

  static const char* STRING_MODES[];
  static const char* PAD_MODES[];
  static const char* JOYSTICK_MODES[];
  static const char* FADER_MODES[];
  static const char* TOGGLE_MODES[];
  static const char* KNOB_MODES[];
  static const char* BUTTON_MODES[];

  static const char* PRESET_EDIT_MODES[];

  static ConfigMeta STRINGS_META[];
  static ConfigMeta PADS_META[];
  static ConfigMeta JOYSTICK_META[];
  static ConfigMeta FADERS_META[];
  static ConfigMeta TOGGLES_META[];
  static ConfigMeta KNOBS_META[];
  static ConfigMeta BUTTONS_META[];
  static ConfigMeta VOICE0_META[];
  static ConfigMeta VOICE1_META[];
  static ConfigMeta VOICE2_META[];
  static ConfigMeta VOICE3_META[];
  static ConfigMeta SYNTH_META[];
  static ConfigGroupMeta META[];

  static int numSections;

  static float typeMin(ConfigType type);
  static float typeMax(ConfigType type);
  static void formatType(char* buffer, float val, ConfigType type);

  static char presetName[];
  static StringsConfig strings;
  static PadsConfig pads;
  static JoystickConfig joystick;
  static FaderConfig faders;
  static ToggleConfig toggles;
  static KnobConfig knobs;
  static ButtonConfig buttons;
  static SynthVoiceConfig voice0;
  static SynthVoiceConfig voice1;
  static SynthVoiceConfig voice2;
  static SynthVoiceConfig voice3;
  static SynthConfig synth;

  RuiPresetClass();

  void begin(const char* path);

  void update();

  void writeToDisplay(TeensyView& display);

  bool isValidFileName(const char* t_fileName);
  void toFileName(char* t_fileName, const char* t_presetName);
  void fromFileName(char* t_presetName, const char* t_fileName);
  void toCanonicalFilePath(char* t_filePath, const char* t_presetName);

  void loadPreset(unsigned int idx);
  void copyPreset(unsigned int idx);
  void savePreset(const char* t_fileName);
  void renamePreset(unsigned int t_idx, const char* t_newName);

  // destructor
  ~RuiPresetClass();
};

extern RuiPresetClass RuiPreset;

#endif
