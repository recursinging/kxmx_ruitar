#include "RuiSynthOscBank.h"


RuiSynthOscBank::RuiSynthOscBank(AudioSynthWaveform *t_osc0,
    AudioSynthWaveform *t_osc1, AudioSynthWaveform *t_osc2,
    AudioSynthWaveform *t_osc3, AudioMixer4 *t_mixer, AudioAnalyzePeak *t_peak) {
  oscillators[0] = t_osc0;
  oscillators[1] = t_osc1;
  oscillators[2] = t_osc2;
  oscillators[3] = t_osc3;
  mixer = t_mixer;
  peak = t_peak;

  detuneFactors[0] = 1.0f;
  detuneFactors[1] = 1.0f;
  detuneFactors[2] = 1.0f;
  detuneFactors[3] = 1.0f;
}
;
RuiSynthOscBank::~RuiSynthOscBank() {
}

void RuiSynthOscBank::mix(short t_osc, float amplitude) {
  mixer->gain(ensureIdx(t_osc), amplitude);
}
void RuiSynthOscBank::waveform(short t_osc, short t_waveform) {
  if (t_waveform >= 20) {
    //oscillators[ensureIdx(t_osc)]->arbitraryWaveform(AKWF_saw_0004, midi_note_freq_table[127]);
    const int16_t* wave = *SYNTH_WAVETABLE[(uint8_t)t_waveform];
    oscillators[ensureIdx(t_osc)]->arbitraryWaveform(wave, midi_note_freq_table[127]);
  } else {
    oscillators[ensureIdx(t_osc)]->begin(t_waveform);
  }

}
void RuiSynthOscBank::detune(short t_osc, float t_cents) {
  detuneFactors[ensureIdx(t_osc)] = pow(2, t_cents * CENT_MULT_FACTOR);
}
void RuiSynthOscBank::phase(short t_osc, float t_angle) {
  oscillators[ensureIdx(t_osc)]->phase(t_angle);
}
void RuiSynthOscBank::pulseWidth(short t_osc, float t_duty) {
  oscillators[ensureIdx(t_osc)]->pulseWidth(t_duty);
}
void RuiSynthOscBank::frequency(short t_osc, float t_frequency) {
  oscillators[ensureIdx(t_osc)]->frequency(t_frequency * detuneFactors[ensureIdx(t_osc)]);
}

short inline RuiSynthOscBank::ensureIdx(short t_idx) {
  if (t_idx < 0) {
    return 0;
  } else if (t_idx >= BANK_NUM_OSC) {
    return 3;
  }
  return t_idx;
}
