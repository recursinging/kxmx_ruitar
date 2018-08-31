#include "RuiSynthVCF.h"

RuiSynthVCF::RuiSynthVCF(AudioSynthWaveformDc *t_cv_in, AudioEffectEnvelope *t_envelope,
    AudioMixer4* t_mixer, AudioFilterStateVariable *t_filter) {

  cv_in = t_cv_in;
  envelope = t_envelope;
  mixer = t_mixer;
  filter = t_filter;

}
;
RuiSynthVCF::~RuiSynthVCF() {
}

void RuiSynthVCF::mix(int t_idx, float gain) {
  mixer->gain(t_idx, gain);
}
void RuiSynthVCF::mixCV(float gain) {
  mixer->gain(0, gain);
}
void RuiSynthVCF::mixEnvelope(float gain) {
  mixer->gain(1, gain);
}
void RuiSynthVCF::mixLFO0(float gain) {
  mixer->gain(2, gain);
}
void RuiSynthVCF::mixLFO1(float gain) {
  mixer->gain(3, gain);
}

void RuiSynthVCF::ADSR(int t_idx, float millis) {
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
void RuiSynthVCF::noteOn() {
  envelope->noteOn();
}
void RuiSynthVCF::noteOff() {
  envelope->noteOff();
}

void RuiSynthVCF::vcfCV(float t_vcfCV) {
  cv_in->amplitude(t_vcfCV);
}
