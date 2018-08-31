#include "RuiSynthVCA.h"

RuiSynthVCA::RuiSynthVCA(AudioSynthWaveformDc *t_cv_in,
    AudioEffectEnvelope *t_envelope, AudioMixer4* t_mixer,
    AudioEffectMultiply* t_vca) {
  cv_in = t_cv_in;
  envelope = t_envelope;
  mixer = t_mixer;
  vca = t_vca;
}
;
RuiSynthVCA::~RuiSynthVCA() {
}

void RuiSynthVCA::mix(int t_idx, float gain) {
  mixer->gain(t_idx, gain);
}
void RuiSynthVCA::mixCV(float gain) {
  mixer->gain(0, gain);
}
void RuiSynthVCA::mixEnvelope(float gain) {
  mixer->gain(1, gain);
}
void RuiSynthVCA::mixLFO0(float gain) {
  mixer->gain(2, gain);
}
void RuiSynthVCA::mixLFO1(float gain) {
  mixer->gain(3, gain);
}

void RuiSynthVCA::ADSR(int t_idx, float millis) {
  if (t_idx == 0) {
    envelope->attack(millis);
  } else if (t_idx == 1) {
    envelope->decay(millis);
  } else if (t_idx == 2) {
    envelope->sustain(millis);
  } else if (t_idx == 3) {
    envelope->release(millis);
  }
}

void RuiSynthVCA::noteOn() {
  envelope->noteOn();
}
void RuiSynthVCA::noteOff() {
  envelope->noteOff();
}

void RuiSynthVCA::vcaCV(float t_vcaCV) {
  cv_in->amplitude(t_vcaCV);
}
