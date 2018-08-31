#ifndef SynthOscBank_h
#define SynthOscBank_h

#include "RuiBody.h"
#include "AKWF_saw.h"
#include "RuiSynthUtil.h"

#define BANK_NUM_OSC 4


const int16_t* const SYNTH_WAVETABLE[][257] = {
    NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
    NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
    AKWF_saw_0001,AKWF_saw_0002,AKWF_saw_0003,AKWF_saw_0004,
    AKWF_saw_0005,AKWF_saw_0006,AKWF_saw_0007,AKWF_saw_0008,
    AKWF_saw_0009,AKWF_saw_0010,AKWF_saw_0011,AKWF_saw_0012,
    AKWF_saw_0013,AKWF_saw_0014,AKWF_saw_0015,AKWF_saw_0016,
    AKWF_saw_0017,AKWF_saw_0018,AKWF_saw_0019,AKWF_saw_0020,
    AKWF_saw_0021,AKWF_saw_0022,AKWF_saw_0023,AKWF_saw_0024,
    AKWF_saw_0025,AKWF_saw_0026,AKWF_saw_0027,AKWF_saw_0028,
    AKWF_saw_0029,AKWF_saw_0030,AKWF_saw_0031,AKWF_saw_0032,
    AKWF_saw_0033,AKWF_saw_0034,AKWF_saw_0035,AKWF_saw_0036,
    AKWF_saw_0037,AKWF_saw_0038,AKWF_saw_0039,AKWF_saw_0040,
    AKWF_saw_0041,AKWF_saw_0042,AKWF_saw_0043,AKWF_saw_0044,
    AKWF_saw_0045,AKWF_saw_0046,AKWF_saw_0047,AKWF_saw_0048,
    AKWF_saw_0049,AKWF_saw_0050
};


class RuiSynthOscBank {
private:

  const float CENT_MULT_FACTOR = 1/1200;
  short ensureIdx(short t_idx);
public:
  RuiSynthOscBank(AudioSynthWaveform *t_osc0, AudioSynthWaveform *t_osc1,
      AudioSynthWaveform *t_osc2, AudioSynthWaveform *t_osc3,
      AudioMixer4 *t_mixer, AudioAnalyzePeak *t_peak);
  // destructor
  ~RuiSynthOscBank();
  const int oscillatorCount = BANK_NUM_OSC;
  float detuneFactors[BANK_NUM_OSC];

  AudioSynthWaveform* oscillators[4];
  AudioMixer4 *mixer;
  AudioAnalyzePeak *peak;

  void frequency(short t_osc, float t_value);
  void mix(short t_osc, float amplitude);
  void waveform(short t_osc, short t_waveform);
  void detune(short t_osc, float t_cents);
  void phase(short t_osc, float t_angle);
  void pulseWidth(short t_osc, float t_duty);


};

#endif
