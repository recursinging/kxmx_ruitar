#include "RuiSynth.h"

#include <Audio.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <Wire.h>

// GUItool: begin automatically generated code
AudioSynthWaveform lfo0;           // xy=63,531
AudioSynthWaveform lfo1;           // xy=63,566
AudioSynthWaveform vco3a;          // xy=205,855
AudioSynthWaveform vco3b;          // xy=205,889
AudioSynthWaveform vco3c;          // xy=205,922
AudioSynthWaveform vco3d;          // xy=205,955
AudioSynthWaveformDc cv3a;         // xy=205,1002
AudioSynthWaveformDc cv3f;         // xy=205,1049
AudioSynthWaveformDc cv2a;         // xy=207,730
AudioSynthWaveformDc cv2f;         // xy=207,777
AudioSynthWaveform vco2a;          // xy=208,583
AudioSynthWaveform vco2b;          // xy=208,617
AudioSynthWaveform vco2c;          // xy=208,650
AudioSynthWaveform vco2d;          // xy=208,683
AudioSynthWaveform vco1a;          // xy=210,308
AudioSynthWaveform vco1b;          // xy=210,342
AudioSynthWaveform vco1c;          // xy=210,375
AudioSynthWaveform vco1d;          // xy=210,408
AudioSynthWaveformDc cv1a;         // xy=210,454
AudioSynthWaveformDc cv1f;         // xy=210,497
AudioSynthWaveform vco0a;          // xy=213,36
AudioSynthWaveform vco0b;          // xy=213,70
AudioSynthWaveform vco0c;          // xy=213,103
AudioSynthWaveform vco0d;          // xy=213,136
AudioSynthWaveformDc cv0a;         // xy=213,183
AudioSynthWaveformDc cv0f;         // xy=213,228
AudioEffectEnvelope adsr3a;        // xy=335,1017
AudioEffectEnvelope adsr3f;        // xy=336,1072
AudioMixer4 bank3;                 // xy=338,909
AudioMixer4 bank2;                 // xy=341,637
AudioEffectEnvelope adsr1a;        // xy=342,469
AudioEffectEnvelope adsr1f;        // xy=342,516
AudioEffectEnvelope adsr2f;        // xy=342,798
AudioMixer4 bank1;                 // xy=344,362
AudioEffectEnvelope adsr2a;        // xy=343,746
AudioMixer4 bank0;                 // xy=346,89
AudioEffectEnvelope adsr0a;        // xy=346,200
AudioEffectEnvelope adsr0f;        // xy=346,250
AudioAnalyzePeak bankPeak2;        // xy=501,601
AudioMixer4 envelope3f;            // xy=500,1064
AudioMixer4 envelope3a;            // xy=501,989
AudioMixer4 envelope2f;            // xy=503,792
AudioMixer4 envelope2a;            // xy=504,717
AudioMixer4 envelope1f;            // xy=505,517
AudioAnalyzePeak bankPeak1;        // xy=506,336
AudioAnalyzePeak bankPeak3;        // xy=504,870
AudioMixer4 envelope1a;            // xy=506,442
AudioMixer4 envelope0f;            // xy=508,245
AudioMixer4 envelope0a;            // xy=509,170
AudioAnalyzePeak bankPeak0;        // xy=511,48
AudioEffectMultiply multiply3;     // xy=644,960
AudioEffectMultiply multiply2;     // xy=647,688
AudioEffectMultiply multiply1;     // xy=649,413
AudioEffectMultiply multiply0;     // xy=652,141
AudioFilterStateVariable filter3;  // xy=786,1020
AudioFilterStateVariable filter2;  // xy=789,748
AudioFilterStateVariable filter1;  // xy=791,473
AudioFilterStateVariable filter0;  // xy=794,201
AudioMixer4 voiceMix3;             // xy=946,978
AudioMixer4 voiceMix2;             // xy=949,706
AudioMixer4 voiceMix1;             // xy=951,431
AudioMixer4 voiceMix0;             // xy=954,159
AudioAnalyzePeak voicePeak0;       // xy=1147,159
AudioAnalyzePeak voicePeak1;       // xy=1149,432
AudioAnalyzePeak voicePeak2;       // xy=1150,706
AudioAnalyzePeak voicePeak3;       // xy=1149,978
AudioMixer4 panMixL;               // xy=1157,526
AudioMixer4 panMixR;               // xy=1158,601
AudioAnalyzePeak panPeakR;         // xy=1316,625
AudioAnalyzeRMS panRmsR;           // xy=1316,662
AudioAnalyzePeak panPeakL;         // xy=1317,501
AudioAnalyzeRMS panRmsL;           // xy=1318,464
AudioOutputAnalogStereo dacs1;     // xy=1449,526
// AudioOutputUSB           usb1;           //xy=1450,561
AudioOutputI2S i2s1;  // xy=1451,596
AudioConnection patchCord1(lfo0, 0, envelope0a, 2);
AudioConnection patchCord2(lfo0, 0, envelope0f, 2);
AudioConnection patchCord3(lfo0, 0, envelope1a, 2);
AudioConnection patchCord4(lfo0, 0, envelope1f, 2);
AudioConnection patchCord5(lfo0, 0, envelope2a, 2);
AudioConnection patchCord6(lfo0, 0, envelope2f, 2);
AudioConnection patchCord7(lfo0, 0, envelope3a, 2);
AudioConnection patchCord8(lfo0, 0, envelope3f, 2);
AudioConnection patchCord9(lfo1, 0, envelope0a, 3);
AudioConnection patchCord10(lfo1, 0, envelope0f, 3);
AudioConnection patchCord11(lfo1, 0, envelope1a, 3);
AudioConnection patchCord12(lfo1, 0, envelope1f, 3);
AudioConnection patchCord13(lfo1, 0, envelope2a, 3);
AudioConnection patchCord14(lfo1, 0, envelope2f, 3);
AudioConnection patchCord15(lfo1, 0, envelope3a, 3);
AudioConnection patchCord16(lfo1, 0, envelope3f, 3);
AudioConnection patchCord17(vco3a, 0, bank3, 0);
AudioConnection patchCord18(vco3b, 0, bank3, 1);
AudioConnection patchCord19(vco3c, 0, bank3, 2);
AudioConnection patchCord20(vco3d, 0, bank3, 3);
AudioConnection patchCord21(cv3a, 0, envelope3a, 0);
AudioConnection patchCord22(cv3a, adsr3a);
AudioConnection patchCord23(cv3f, 0, envelope3f, 0);
AudioConnection patchCord24(cv3f, adsr3f);
AudioConnection patchCord25(cv2a, 0, envelope2a, 0);
AudioConnection patchCord26(cv2a, adsr2a);
AudioConnection patchCord27(cv2f, 0, envelope2f, 0);
AudioConnection patchCord28(cv2f, adsr2f);
AudioConnection patchCord29(vco2a, 0, bank2, 0);
AudioConnection patchCord30(vco2b, 0, bank2, 1);
AudioConnection patchCord31(vco2c, 0, bank2, 2);
AudioConnection patchCord32(vco2d, 0, bank2, 3);
AudioConnection patchCord33(vco1a, 0, bank1, 0);
AudioConnection patchCord34(vco1b, 0, bank1, 1);
AudioConnection patchCord35(vco1c, 0, bank1, 2);
AudioConnection patchCord36(vco1d, 0, bank1, 3);
AudioConnection patchCord37(cv1a, 0, envelope1a, 0);
AudioConnection patchCord38(cv1a, adsr1a);
AudioConnection patchCord39(cv1f, 0, envelope1f, 0);
AudioConnection patchCord40(cv1f, adsr1f);
AudioConnection patchCord41(vco0a, 0, bank0, 0);
AudioConnection patchCord42(vco0b, 0, bank0, 1);
AudioConnection patchCord43(vco0c, 0, bank0, 2);
AudioConnection patchCord44(vco0d, 0, bank0, 3);
AudioConnection patchCord45(cv0a, 0, envelope0a, 0);
AudioConnection patchCord46(cv0a, adsr0a);
AudioConnection patchCord47(cv0f, 0, envelope0f, 0);
AudioConnection patchCord48(cv0f, adsr0f);
AudioConnection patchCord49(adsr3a, 0, envelope3a, 1);
AudioConnection patchCord50(adsr3f, 0, envelope3f, 1);
AudioConnection patchCord51(bank3, 0, multiply3, 0);
AudioConnection patchCord52(bank3, bankPeak3);
AudioConnection patchCord53(bank2, 0, multiply2, 0);
AudioConnection patchCord54(bank2, bankPeak2);
AudioConnection patchCord55(adsr1a, 0, envelope1a, 1);
AudioConnection patchCord56(adsr1f, 0, envelope1f, 1);
AudioConnection patchCord57(adsr2f, 0, envelope2f, 1);
AudioConnection patchCord58(bank1, 0, multiply1, 0);
AudioConnection patchCord59(bank1, bankPeak1);
AudioConnection patchCord60(adsr2a, 0, envelope2a, 1);
AudioConnection patchCord61(bank0, 0, multiply0, 0);
AudioConnection patchCord62(bank0, bankPeak0);
AudioConnection patchCord63(adsr0a, 0, envelope0a, 1);
AudioConnection patchCord64(adsr0f, 0, envelope0f, 1);
AudioConnection patchCord65(envelope3f, 0, filter3, 1);
AudioConnection patchCord66(envelope3a, 0, multiply3, 1);
AudioConnection patchCord67(envelope2f, 0, filter2, 1);
AudioConnection patchCord68(envelope2a, 0, multiply2, 1);
AudioConnection patchCord69(envelope1f, 0, filter1, 1);
AudioConnection patchCord70(envelope1a, 0, multiply1, 1);
AudioConnection patchCord71(envelope0f, 0, filter0, 1);
AudioConnection patchCord72(envelope0a, 0, multiply0, 1);
AudioConnection patchCord73(multiply3, 0, filter3, 0);
AudioConnection patchCord74(multiply3, 0, voiceMix3, 0);
AudioConnection patchCord75(multiply2, 0, filter2, 0);
AudioConnection patchCord76(multiply2, 0, voiceMix2, 0);
AudioConnection patchCord77(multiply1, 0, filter1, 0);
AudioConnection patchCord78(multiply1, 0, voiceMix1, 0);
AudioConnection patchCord79(multiply0, 0, filter0, 0);
AudioConnection patchCord80(multiply0, 0, voiceMix0, 0);
AudioConnection patchCord81(filter3, 0, voiceMix3, 1);
AudioConnection patchCord82(filter3, 1, voiceMix3, 2);
AudioConnection patchCord83(filter3, 2, voiceMix3, 3);
AudioConnection patchCord84(filter2, 0, voiceMix2, 1);
AudioConnection patchCord85(filter2, 1, voiceMix2, 2);
AudioConnection patchCord86(filter2, 2, voiceMix2, 3);
AudioConnection patchCord87(filter1, 0, voiceMix1, 1);
AudioConnection patchCord88(filter1, 1, voiceMix1, 2);
AudioConnection patchCord89(filter1, 2, voiceMix1, 3);
AudioConnection patchCord90(filter0, 0, voiceMix0, 1);
AudioConnection patchCord91(filter0, 1, voiceMix0, 2);
AudioConnection patchCord92(filter0, 2, voiceMix0, 3);
AudioConnection patchCord93(voiceMix3, 0, panMixL, 3);
AudioConnection patchCord94(voiceMix3, 0, panMixR, 3);
AudioConnection patchCord95(voiceMix3, voicePeak3);
AudioConnection patchCord96(voiceMix2, 0, panMixL, 2);
AudioConnection patchCord97(voiceMix2, 0, panMixR, 2);
AudioConnection patchCord98(voiceMix2, voicePeak2);
AudioConnection patchCord99(voiceMix1, 0, panMixL, 1);
AudioConnection patchCord100(voiceMix1, 0, panMixR, 1);
AudioConnection patchCord101(voiceMix1, voicePeak1);
AudioConnection patchCord102(voiceMix0, 0, panMixL, 0);
AudioConnection patchCord103(voiceMix0, 0, panMixR, 0);
AudioConnection patchCord104(voiceMix0, voicePeak0);
AudioConnection patchCord105(panMixL, 0, dacs1, 0);
AudioConnection patchCord106(panMixL, panPeakL);
// AudioConnection          patchCord107(panMixL, 0, usb1, 0);
AudioConnection patchCord108(panMixL, panRmsL);
AudioConnection patchCord109(panMixL, 0, i2s1, 0);
AudioConnection patchCord110(panMixR, 0, dacs1, 1);
AudioConnection patchCord111(panMixR, panPeakR);
// AudioConnection          patchCord112(panMixR, 0, usb1, 1);
AudioConnection patchCord113(panMixR, panRmsR);
AudioConnection patchCord114(panMixR, 0, i2s1, 1);
// GUItool: end automatically generated code

RuiSynthOscBank RuiSynthClass::oscBank0 =
    RuiSynthOscBank(&vco0a, &vco0b, &vco0c, &vco0d, &bank0, &bankPeak0);
RuiSynthOscBank RuiSynthClass::oscBank1 =
    RuiSynthOscBank(&vco1a, &vco1b, &vco1c, &vco1d, &bank1, &bankPeak1);
RuiSynthOscBank RuiSynthClass::oscBank2 =
    RuiSynthOscBank(&vco2a, &vco2b, &vco2c, &vco2d, &bank2, &bankPeak2);
RuiSynthOscBank RuiSynthClass::oscBank3 =
    RuiSynthOscBank(&vco3a, &vco3b, &vco3c, &vco3d, &bank3, &bankPeak3);

RuiSynthVCA RuiSynthClass::vca0 =
    RuiSynthVCA(&cv0a, &adsr0a, &envelope0a, &multiply0);
RuiSynthVCA RuiSynthClass::vca1 =
    RuiSynthVCA(&cv1a, &adsr1a, &envelope1a, &multiply1);
RuiSynthVCA RuiSynthClass::vca2 =
    RuiSynthVCA(&cv2a, &adsr2a, &envelope2a, &multiply2);
RuiSynthVCA RuiSynthClass::vca3 =
    RuiSynthVCA(&cv3a, &adsr3a, &envelope3a, &multiply3);

RuiSynthVCF RuiSynthClass::vcf0 =
    RuiSynthVCF(&cv0f, &adsr0f, &envelope0f, &filter0);
RuiSynthVCF RuiSynthClass::vcf1 =
    RuiSynthVCF(&cv1f, &adsr1f, &envelope0f, &filter1);
RuiSynthVCF RuiSynthClass::vcf2 =
    RuiSynthVCF(&cv2f, &adsr2f, &envelope0f, &filter2);
RuiSynthVCF RuiSynthClass::vcf3 =
    RuiSynthVCF(&cv3f, &adsr3f, &envelope0f, &filter3);

RuiSynthVoice RuiSynthClass::voice0 =
    RuiSynthVoice(&RuiSynthClass::oscBank0, &RuiSynthClass::vca0,
                  &RuiSynthClass::vcf0, &voiceMix0, &voicePeak0);
RuiSynthVoice RuiSynthClass::voice1 =
    RuiSynthVoice(&RuiSynthClass::oscBank1, &RuiSynthClass::vca1,
                  &RuiSynthClass::vcf1, &voiceMix1, &voicePeak1);
RuiSynthVoice RuiSynthClass::voice2 =
    RuiSynthVoice(&RuiSynthClass::oscBank2, &RuiSynthClass::vca2,
                  &RuiSynthClass::vcf2, &voiceMix2, &voicePeak2);
RuiSynthVoice RuiSynthClass::voice3 =
    RuiSynthVoice(&RuiSynthClass::oscBank3, &RuiSynthClass::vca3,
                  &RuiSynthClass::vcf3, &voiceMix3, &voicePeak3);

RuiSynthVoice *RuiSynthClass::voices[NN] = {
    &RuiSynthClass::voice0, &RuiSynthClass::voice1, &RuiSynthClass::voice2,
    &RuiSynthClass::voice3};

RuiSynthClass::RuiSynthClass(){

};
RuiSynthClass::~RuiSynthClass() {}

void RuiSynthClass::begin() {
//   usb1.begin();
//   dacs1.analogReference(EXTERNAL);
//   lfo0.begin(1, RuiPreset.synth.lfo_frequency[0], WAVEFORM_SINE);
//   lfo1.begin(1, RuiPreset.synth.lfo_frequency[1], WAVEFORM_SINE);

//   vco0a.begin(1, 440, WAVEFORM_SAWTOOTH);
//   bank0.gain(0, 1);
//   voice0.osc_bank->oscillators[0]->begin(1, 440, WAVEFORM_SAWTOOTH);
//   voice0.osc_bank->mixer->gain(0, 1);

//   updatePresetConfig();
}

void RuiSynthClass::updatePresetConfig() {}

void RuiSynthClass::update() {
  for (int i = 0; i < NN; i++) {
    bool recalculatScale = false;
    if (lowestNotes[i] != RuiPreset.strings.lowest_note[i]) {
      freqMin[i] = midi_note_freq_table[(int)RuiPreset.strings.lowest_note[i]];
      lowestNotes[i] = RuiPreset.strings.lowest_note[i];
      recalculatScale = true;
    }
    if (highestNotes[i] != RuiPreset.strings.highest_note[i]) {
      freqMax[i] = midi_note_freq_table[(int)RuiPreset.strings.highest_note[i]];
      highestNotes[i] = RuiPreset.strings.highest_note[i];
      recalculatScale = true;
    }
    if (recalculatScale) {
      freqScale[i] = (log(freqMax[i]) - log(freqMin[i])) /
                     (RuiBody.calibration.stringsInputMax[i] -
                      RuiBody.calibration.stringsInputMin[i]);
      
    }

    voices[i]->updatePresetConfig(i);

    panMixL.gain(i, RuiPreset.synth.voice_mix_l[i]);
    panMixR.gain(i, RuiPreset.synth.voice_mix_r[i]);

    // Strings
    int constrainedStrInputValue = constrain(
        RuiBody.sensors.stringsV[i], RuiBody.calibration.stringsInputMin[i],
        RuiBody.calibration.stringsInputMax[i]);
    frequencies[i] = exp(
        freqMin[i] + freqScale[i] * (constrainedStrInputValue -
                                     RuiBody.calibration.stringsInputMin[i]));

    // Pads
    int constrainedPadInputValue =
        constrain(RuiBody.sensors.padsV[i], RuiBody.calibration.padsInputMin[i],
                  RuiBody.calibration.padsInputMax[i]);
    cvVCA[i] =
        map(constrainedPadInputValue, RuiBody.calibration.padsInputMin[i],
            RuiBody.calibration.padsInputMax[i], 0.0F, 1.0F);
    if (constrainedPadInputValue > RuiBody.calibration.padsInputThresh[i]) {
      noteOn[i] = true;
    } else {
      noteOn[i] = false;
    }

    // Faders
    int constrainedFaderInputValue = constrain(
        RuiBody.sensors.fadersV[i], RuiBody.calibration.fadersInputMin[i],
        RuiBody.calibration.fadersInputMax[i]);
    cvVCF[i] =
        map(constrainedFaderInputValue, RuiBody.calibration.fadersInputMin[i],
            RuiBody.calibration.fadersInputMax[i], 0.0F, 1.0F);
  }
  lfo0.frequency(RuiPreset.synth.lfo_frequency[0]);
  lfo1.frequency(RuiPreset.synth.lfo_frequency[1]);
}

void RuiSynthClass::dispatch() {
  for (int i = 0; i < NN; i++) {
    voices[i]->frequency(frequencies[i]);
    voices[i]->cvVCA(cvVCA[i]);
    voices[i]->cvVCF(cvVCF[i]);
    if (noteOn[i]) {
      voices[i]->noteOn();
    } else {
      voices[i]->noteOff();
    }
  }
}

float RuiSynthClass::peakL() {
  // return panPeakL.read();
  return panRmsL.read();
}

float RuiSynthClass::peakR() {
  // return panPeakR.read();
  return panRmsR.read();
}

RuiSynthClass RuiSynth;
