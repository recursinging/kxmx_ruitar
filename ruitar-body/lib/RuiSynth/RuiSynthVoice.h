#ifndef SynthVoice_h
#define SynthVoice_h

#include "RuiSynthOscBank.h"
#include "RuiSynthUtil.h"
#include "RuiSynthVCA.h"
#include "RuiSynthVCF.h"
#include "RuiBody.h"

class RuiSynthVoice {
private:

public:
  RuiSynthVoice(RuiSynthOscBank *t_osc_bank, RuiSynthVCA *t_vca, RuiSynthVCF *t_vcf,
      AudioMixer4* t_mixer, AudioAnalyzePeak *t_peak);
  ~RuiSynthVoice();

  RuiSynthOscBank *osc_bank;
  RuiSynthVCA *vca;
  RuiSynthVCF *vcf;
  AudioMixer4 *mixer;
  AudioAnalyzePeak *peak;

  void updatePresetConfig(int t_idx);

  void frequency(float t_frequency);
  void cvVCA(float t_vca_cv);
  void cvVCF(float t_vcf_cv);

  void noteOn();
  void noteOff();
};

#endif
