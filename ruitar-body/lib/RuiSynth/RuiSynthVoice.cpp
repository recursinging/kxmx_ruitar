#include "RuiSynthVoice.h"

#define SERIAL_DEBUG_OUTPUT 0

RuiSynthVoice::RuiSynthVoice(RuiSynthOscBank *t_osc_bank, RuiSynthVCA *t_vca,
    RuiSynthVCF *t_vcf, AudioMixer4* t_mixer, AudioAnalyzePeak *t_peak) {

  osc_bank = t_osc_bank;
  vca = t_vca;
  vcf = t_vcf;
  mixer = t_mixer;
  peak = t_peak;

}
;
RuiSynthVoice::~RuiSynthVoice() {
}

void RuiSynthVoice::updatePresetConfig(int t_idx) {
  SynthVoiceConfig *cfg;
  if (t_idx == 0) {
    cfg = &RuiPreset.voice0;
  } else if (t_idx == 1) {
    cfg = &RuiPreset.voice1;
  } else if (t_idx == 2) {
    cfg = &RuiPreset.voice2;
  } else if (t_idx == 3) {
    cfg = &RuiPreset.voice3;
  } else {
    cfg = &RuiPreset.voice0;
  }
  for (int i = 0; i < NN; i++) {
    osc_bank->oscillators[i]->begin(1, 1, WAVEFORM_SINE);
    osc_bank->detune(i, cfg->osc_detune[i]);
    osc_bank->frequency(i, cfg->osc_frequency[i]);
    osc_bank->waveform(i, cfg->osc_waveform[i]);
    osc_bank->mix(i, cfg->osc_mix[i]);
    vca->ADSR(i, cfg->vca_adsr[i]);
    vca->mix(i, cfg->vca_envelope_mix[i]);
    vcf->ADSR(i, cfg->vcf_adsr[i]);
    vcf->mix(i, cfg->vcf_envelope_mix[i]);
    mixer->gain(i, cfg->vca_vcf_mix[i]);

#if SERIAL_DEBUG_OUTPUT
    Serial.print("frequency: ");
    Serial.print(i);
    Serial.print(" - ");
    Serial.println(cfg->osc_frequency[i]);
    Serial.print("detune: ");
    Serial.print(i);
    Serial.print(" - ");
    Serial.println(cfg->osc_detune[i]);
    Serial.print("waveform: ");
    Serial.print(i);
    Serial.print(" - ");
    Serial.println(cfg->osc_waveform[i]);
    Serial.print("osc_mix: ");
    Serial.print(i);
    Serial.print(" - ");
    Serial.println(cfg->osc_mix[i]);
    Serial.print("vca_adsr: ");
    Serial.print(i);
    Serial.print(" - ");
    Serial.println(cfg->vca_adsr[i]);
    Serial.print("vca_env: ");
    Serial.print(i);
    Serial.print(" - ");
    Serial.println(cfg->vca_envelope_mix[i]);
    Serial.print("vcf_adsr: ");
    Serial.print(i);
    Serial.print(" - ");
    Serial.println(cfg->vcf_adsr[i]);
    Serial.print("vcf_env: ");
    Serial.print(i);
    Serial.print(" - ");
    Serial.println(cfg->vcf_envelope_mix[i]);
    Serial.print("vca_vcf: ");
    Serial.print(i);
    Serial.print(" - ");
    Serial.println(cfg->vca_vcf_mix[i]);
#endif
  }
}

void RuiSynthVoice::frequency(float t_frequency) {
  for (int i = 0; i < osc_bank->oscillatorCount; i++) {
    osc_bank->frequency(i, t_frequency);
  }
}

void RuiSynthVoice::cvVCA(float t_vca_cv) {
  vca->vcaCV(t_vca_cv);
}
void RuiSynthVoice::cvVCF(float t_vcf_cv) {
  vcf->vcfCV(t_vcf_cv);
}

void RuiSynthVoice::noteOn() {
  vca->noteOn();
  vcf->noteOn();
}
void RuiSynthVoice::noteOff() {
  vca->noteOff();
  vcf->noteOff();
}
