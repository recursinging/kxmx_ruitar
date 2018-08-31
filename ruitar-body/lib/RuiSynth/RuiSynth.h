#ifndef SynthTools_h
#define SynthTools_h

#include "RuiPreset.h"
#include "RuiBody.h"
#include "RuiSynthOscBank.h"
#include "RuiSynthUtil.h"
#include "RuiSynthVCA.h"
#include "RuiSynthVCF.h"
#include "RuiSynthVoice.h"

struct SynthState {

};


class RuiSynthClass {
public:
  RuiSynthClass();
  ~RuiSynthClass();

  static RuiSynthOscBank oscBank0;
  static RuiSynthOscBank oscBank1;
  static RuiSynthOscBank oscBank2;
  static RuiSynthOscBank oscBank3;

  static RuiSynthVCA vca0;
  static RuiSynthVCA vca1;
  static RuiSynthVCA vca2;
  static RuiSynthVCA vca3;

  static RuiSynthVCF vcf0;
  static RuiSynthVCF vcf1;
  static RuiSynthVCF vcf2;
  static RuiSynthVCF vcf3;

  static RuiSynthVoice voice0;
  static RuiSynthVoice voice1;
  static RuiSynthVoice voice2;
  static RuiSynthVoice voice3;

  static RuiSynthVoice *voices[NN];

  float lowestNotes[NN] = {0,0,0,0};
  float highestNotes[NN] = {0,0,0,0};
  float frequencies[NN] = {0,0,0,0};
  float freqMin[NN] = {0,0,0,0};
  float freqMax[NN] = {0,0,0,0};
  float freqScale[NN] = {0,0,0,0};
  float amplitudes[NN] = {0,0,0,0};
  float cvVCA[NN] = {0,0,0,0};
  float cvVCF[NN] = {0,0,0,0};
  bool noteOn[NN] = {false,false,false,false};

  void begin();
  void updatePresetConfig();
  void update();
  void dispatch();
  float peakL();
  float peakR();
};

extern RuiSynthClass RuiSynth;

#endif
