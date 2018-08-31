#ifndef SynthVCF_h
#define SynthVCF_h

#include "RuiSynthUtil.h"
#include "RuiBody.h"

class RuiSynthVCF {
private:

public:
  RuiSynthVCF(AudioSynthWaveformDc *t_cv_in, AudioEffectEnvelope *t_envelope,
      AudioMixer4* t_mixer, AudioFilterStateVariable *t_filter);
  ~RuiSynthVCF();

  AudioSynthWaveformDc *cv_in;
  AudioEffectEnvelope *envelope;
  AudioMixer4 *mixer;
  AudioFilterStateVariable *filter;
  
  void mix(int t_idx, float gain);
  void mixCV(float gain);
  void mixEnvelope(float gain);
  void mixLFO0(float gain);
  void mixLFO1(float gain);

  void ADSR(int t_idx, float millis);

  void noteOn();
  void noteOff();

  void vcfCV(float t_vcfCV);
};

#endif
