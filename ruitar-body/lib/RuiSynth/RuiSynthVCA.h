#ifndef SynthVCA_h
#define SynthVCA_h

#include "RuiSynthUtil.h"
#include "RuiBody.h"

class RuiSynthVCA {
private:

public:
  RuiSynthVCA(AudioSynthWaveformDc *t_cv_in, AudioEffectEnvelope *t_envelope,
      AudioMixer4* t_mixer, AudioEffectMultiply* t_vca);
  ~RuiSynthVCA();

  AudioSynthWaveformDc *cv_in;
  AudioEffectEnvelope* envelope;
  AudioMixer4* mixer;
  AudioEffectMultiply* vca;

  void mix(int t_idx, float gain);
  void mixCV(float gain);
  void mixEnvelope(float gain);
  void mixLFO0(float gain);
  void mixLFO1(float gain);

  void ADSR(int t_idx, float millis);

  void noteOn();
  void noteOff();

  void vcaCV(float t_vcaCV);

};

#endif
