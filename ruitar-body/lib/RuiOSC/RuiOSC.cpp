#include "RuiOSC.h"
#include "RuiMIDI.h"

SLIPEncodedUSBSerial RuiOSCClass::SLIPSerial(Serial);

const char *chIdx[NN] = {"0", "1", "2", "3"};

unsigned int RuiOSCClass::lastCalMsg = 0;
unsigned int RuiOSCClass::lastSenMsg = 0;
unsigned int RuiOSCClass::lastPreMsg = 0;
unsigned int RuiOSCClass::lastFbkMsg = 0;
unsigned int RuiOSCClass::lastPrfMsg = 0;
unsigned int RuiOSCClass::lastDbgMsg = 0;
unsigned int RuiOSCClass::lastMidMsg = 0;

RuiOSCClass::RuiOSCClass() {}

char RuiOSCClass::debugMsg[512];
int RuiOSCClass::debugIdx = 0;

void RuiOSCClass::handleCalibration(OSCMessage &msg, int initialOffset) {
  initialOffset++;  // Skip the leading slash in the address
  for (size_t i = 0; i < NN; i++) {
    int stringsInputMinOffset = msg.match("strings/input_min", initialOffset);
    if (stringsInputMinOffset) {
      if (msg.match(chIdx[i], initialOffset + stringsInputMinOffset + 1)) {
        int16_t val = msg.getInt(0);
        RuiBody.calibration.stringsInputMin[i] = val;
      }
    }
    int stringsInputMaxOffset = msg.match("strings/input_max", initialOffset);
    if (stringsInputMaxOffset) {
      if (msg.match(chIdx[i], initialOffset + stringsInputMaxOffset + 1)) {
        int16_t val = msg.getInt(0);
        RuiBody.calibration.stringsInputMax[i] = val;
      }
    }
    int stringsInputChangeThresh =
        msg.match("strings/change_thresh", initialOffset);
    if (stringsInputChangeThresh) {
      if (msg.match(chIdx[i], initialOffset + stringsInputChangeThresh + 1)) {
        int16_t val = msg.getInt(0);
        RuiBody.calibration.stringsInputMax[i] = val;
      }
    }
    int padsInputMinOffset = msg.match("pads/input_min", initialOffset);
    if (padsInputMinOffset) {
      if (msg.match(chIdx[i], initialOffset + padsInputMinOffset + 1)) {
        int16_t val = msg.getInt(0);
        RuiBody.calibration.padsInputMin[i] = val;
      }
    }
    int padsInputMaxOffset = msg.match("pads/input_max", initialOffset);
    if (padsInputMaxOffset) {
      if (msg.match(chIdx[i], initialOffset + padsInputMaxOffset + 1)) {
        int16_t val = msg.getInt(0);
        RuiBody.calibration.padsInputMax[i] = val;
      }
    }
    int padsInputChangeThresh = msg.match("pads/change_thresh/", initialOffset);
    if (padsInputChangeThresh) {
      if (msg.match(chIdx[i], initialOffset + padsInputChangeThresh + 1)) {
        int16_t val = msg.getInt(0);
        RuiBody.calibration.padsInputMax[i] = val;
      }
    }
    int fadersInputMinOffset = msg.match("faders/input_min/", initialOffset);
    if (fadersInputMinOffset) {
      if (msg.match(chIdx[i], initialOffset + fadersInputMinOffset + 1)) {
        int16_t val = msg.getInt(0);
        RuiBody.calibration.fadersInputMin[i] = val;
      }
    }
    int fadersInputMaxOffset = msg.match("faders/input_max/", initialOffset);
    if (fadersInputMaxOffset) {
      if (msg.match(chIdx[i], initialOffset + fadersInputMaxOffset + 1)) {
        int16_t val = msg.getInt(0);
        RuiBody.calibration.fadersInputMax[i] = val;
      }
    }
    int fadersInputChangeThresh =
        msg.match("faders/change_thresh/", initialOffset);
    if (fadersInputChangeThresh) {
      if (msg.match(chIdx[i], initialOffset + fadersInputChangeThresh + 1)) {
        int16_t val = msg.getInt(0);
        RuiBody.calibration.fadersInputMax[i] = val;
      }
    }
  }

  if (msg.match("joystick/x_center", initialOffset)) {
    RuiBody.calibration.joystickXMiddle = msg.getInt(0);
  }
  if (msg.match("joystick/y_center", initialOffset)) {
    RuiBody.calibration.joystickYMiddle = msg.getInt(0);
  }
  if (msg.match("joystick/change_thresh", initialOffset)) {
    RuiBody.calibration.joystickChangeThresh = msg.getInt(0);
  }
  if (msg.match("accel/change_thresh", initialOffset)) {
    RuiBody.calibration.accelChangeThresh = msg.getInt(0);
  }

  if (msg.match("osc/update_rate/cal", initialOffset)) {
    RuiBody.calibration.calMsgRate = msg.getInt(0);
  }
  if (msg.match("osc/update_rate/sen", initialOffset)) {
    RuiBody.calibration.senMsgRate = msg.getInt(0);
  }
  if (msg.match("osc/update_rate/pre", initialOffset)) {
    RuiBody.calibration.preMsgRate = msg.getInt(0);
  }
  if (msg.match("osc/update_rate/fbk", initialOffset)) {
    RuiBody.calibration.fbkMsgRate = msg.getInt(0);
  }
  if (msg.match("osc/update_rate/prf", initialOffset)) {
    RuiBody.calibration.prfMsgRate = msg.getInt(0);
  }
  if (msg.match("osc/update_rate/dbg", initialOffset)) {
    RuiBody.calibration.dbgMsgRate = msg.getInt(0);
  }
}

void RuiOSCClass::handlePreset(OSCMessage &msg, int initialOffset) {
  initialOffset++;  // Skip the leading slash in the address

  if (msg.match("number", initialOffset)) {
    RuiPreset.loadPreset(msg.getInt(0));
    debug("Changed Preset Number");
  }
  if (msg.match("copy", initialOffset)) {
    RuiPreset.copyPreset(RuiPreset.currentPreset);
    debug("Copied Preset");
  } else if (msg.match("name", initialOffset)) {
    char buff[9];
    msg.getString(0, buff);
    RuiPreset.renamePreset(RuiPreset.currentPreset, buff);
    debug("Changed Preset Name");
  } else {
    // Dynamic preset property resolution...
    int totalOffset = initialOffset;
    for (int s = 0; s < RuiPreset.numSections; s++) {
      int sectionOffset = msg.match(RuiPreset.META[s].name, initialOffset);
      if (sectionOffset) totalOffset += sectionOffset + 1;
      {
        for (size_t c = 0; c < RuiPreset.META[s].size; c++) {
          int configOffset =
              msg.match(RuiPreset.META[s].idx[c].name, totalOffset);
          if (configOffset) {
            totalOffset += configOffset + 1;
            for (size_t i = 0; i < NN; i++) {
              if (msg.match(chIdx[i], totalOffset)) {
                if (msg.getType(0) == 'f') {
                  RuiPreset.META[s].idx[c].idx[i] = msg.getFloat(0);
                } else if (msg.getType(0) == 'i') {
                  RuiPreset.META[s].idx[c].idx[i] = (float)msg.getInt(0);
                }
                return;
              }
            }
          }
        }
      }
    }
  }
}

void RuiOSCClass::handleSensors(OSCMessage &msg, int initialOffset) {
  initialOffset++;  // Skip the leading slash in the address
  int stringsOffset = msg.match("strings", initialOffset);
  if (stringsOffset) {
    for (size_t i = 0; i < NN; i++) {
      if (msg.match(chIdx[i], initialOffset + stringsOffset + 1)) {
        int16_t val = (int16_t)constrain(
            msg.getInt(0), RuiBody.calibration.stringsInputMin[i],
            RuiBody.calibration.stringsInputMax[i]);
        RuiBody.sensorsLast.stringsV[i] = RuiBody.sensors.stringsV[i];
        RuiBody.sensors.stringsV[i] = val;
      }
    }
  }

  int padsOffset = msg.match("pads", initialOffset);
  if (padsOffset) {
    for (size_t i = 0; i < NN; i++) {
      if (msg.match(chIdx[i], initialOffset + padsOffset + 1)) {
        int16_t val = (int16_t)constrain(msg.getInt(0),
                                         RuiBody.calibration.padsInputMin[i],
                                         RuiBody.calibration.padsInputMax[i]);
        RuiBody.sensorsLast.padsV[i] = RuiBody.sensors.padsV[i];
        RuiBody.sensors.padsV[i] = val;
      }
    }
  }

  int fadersOffset = msg.match("faders", initialOffset);
  if (fadersOffset) {
    for (size_t i = 0; i < NN; i++) {
      if (msg.match(chIdx[i], initialOffset + fadersOffset + 1)) {
        int16_t val = (int16_t)constrain(msg.getInt(0),
                                         RuiBody.calibration.fadersInputMin[i],
                                         RuiBody.calibration.fadersInputMax[i]);
        RuiBody.sensorsLast.fadersV[i] = RuiBody.sensors.fadersV[i];
        RuiBody.sensors.fadersV[i] = val;
      }
    }
  }

  int toggleOffset = msg.match("toggles", initialOffset);
  if (toggleOffset) {
    for (size_t i = 0; i < NN; i++) {
      if (msg.match(chIdx[i], initialOffset + toggleOffset + 1)) {
        float val = msg.getFloat(0);
        RuiBody.sensorsLast.togglesV[i] = RuiBody.sensors.togglesV[i];
        RuiBody.sensors.togglesV[i] = (bool)val;
      }
    }
  }

  int knobOffset = msg.match("knobs", initialOffset);
  if (knobOffset) {
    for (size_t i = 0; i < NN; i++) {
      if (msg.match(chIdx[i], initialOffset + knobOffset + 1)) {
        int16_t val = msg.getInt(0);
        RuiBody.sensorsLast.knobsV[i] = RuiBody.sensors.knobsV[i];
        RuiBody.sensors.knobsV[i] = val;
      }
    }
  }

  int buttonsOffset = msg.match("buttons", initialOffset);
  if (buttonsOffset) {
    for (size_t i = 0; i < NN; i++) {
      if (msg.match(chIdx[i], initialOffset + buttonsOffset + 1)) {
        bool val = msg.getBoolean(0);
        RuiBody.sensorsLast.buttonsV[i] = RuiBody.sensors.buttonsV[i];
        RuiBody.sensors.buttonsV[i] = val;
      }
    }
  }
  
  if (msg.match("joystick", initialOffset)) {
    int16_t x = msg.getInt(0);
    int16_t y = msg.getInt(1);
    RuiBody.sensorsLast.jsXv = RuiBody.sensors.jsXv;
    RuiBody.sensors.jsXv = x;
    RuiBody.sensorsLast.jsYv = RuiBody.sensors.jsYv;
    RuiBody.sensors.jsYv = y;
  }

  if (msg.match("accel/x", initialOffset)) {
    int16_t val = msg.getInt(0);
    RuiBody.sensorsLast.accXv = RuiBody.sensors.accXv;
    RuiBody.sensors.accXv = val;
  }
  if (msg.match("accel/y", initialOffset)) {
    int16_t val = msg.getInt(0);
    RuiBody.sensorsLast.accYv = RuiBody.sensors.accYv;
    RuiBody.sensors.accYv = val;
  }
  if (msg.match("accel/z", initialOffset)) {
    int16_t val = msg.getInt(0);
    RuiBody.sensorsLast.accZv = RuiBody.sensors.accZv;
    RuiBody.sensors.accZv = val;
  }
}

void RuiOSCClass::handleFeedback(OSCMessage &msg, int initialOffset) {
  for (size_t i = 0; i < NN; i++) {
    int ledHeadBlueOffset = msg.match("led/head/blu", initialOffset);
    if (ledHeadBlueOffset) {
      if (msg.match(chIdx[i], initialOffset + ledHeadBlueOffset + 1)) {
        int16_t val = (int16_t)constrain(msg.getInt(0), 0, 4096);
        RuiBody.feedbackLast.headLedsB[i] = RuiBody.feedback.headLedsB[i];
        RuiBody.feedback.headLedsB[i] = val;
      }
    }
    int ledHeadGreenOffset = msg.match("led/head/grn", initialOffset);
    if (ledHeadGreenOffset) {
      if (msg.match(chIdx[i], initialOffset + ledHeadGreenOffset + 1)) {
        int16_t val = (int16_t)constrain(msg.getInt(0), 0, 4096);
        RuiBody.feedbackLast.headLedsG[i] = RuiBody.feedback.headLedsG[i];
        RuiBody.feedback.headLedsG[i] = val;
      }
    }
    int ledHeadRedOffset = msg.match("led/head/red", initialOffset);
    if (ledHeadRedOffset) {
      if (msg.match(chIdx[i], initialOffset + ledHeadRedOffset + 1)) {
        int16_t val = (int16_t)constrain(msg.getInt(0), 0, 4096);
        RuiBody.feedbackLast.headLedsR[i] = RuiBody.feedback.headLedsR[i];
        RuiBody.feedback.headLedsR[i] = val;
      }
    }
    int ledBodyTogOffset = msg.match("led/body/toggle", initialOffset);
    if (ledBodyTogOffset) {
      if (msg.match(chIdx[i], initialOffset + ledBodyTogOffset + 1)) {
        int16_t val = (int16_t)constrain(msg.getInt(0), 0, 4096);
        RuiBody.feedbackLast.toggleLeds[i] = RuiBody.feedback.toggleLeds[i];
        RuiBody.feedback.toggleLeds[i] = val;
      }
    }
  }
}

void RuiOSCClass::update() {
  OSCMessage msg;
  int size;
  if (SLIPSerial.available()) {
    while (!SLIPSerial.endofPacket()) {
      if ((size = SLIPSerial.available()) > 0) {
        while (size--) {
          msg.fill(SLIPSerial.read());
        }
      }
      if (!msg.hasError() && msg.size()) {
        if (msg.route("/pre", handlePreset)) {
          return;
        }
        if (msg.route("/sen", handleSensors)) {
          return;
        }
        if (msg.route("/fbk", handleFeedback)) {
          return;
        }
        if (msg.route("/cal", handleCalibration)) {
          return;
        }
      }
    }
  }
}

void RuiOSCClass::dispatch() { dispatch(ALL_MSG); }

void RuiOSCClass::dispatch(MsgClass t_msgClass) {
  switch (t_msgClass) {
    case CAL_MSG:
      dispatchCal();
      break;
    case SEN_MSG:
      dispatchSen();
      break;
    case PRE_MSG:
      dispatchPre();
      break;
    case FBK_MSG:
      dispatchFbk();
      break;
    case PRF_MSG:
      dispatchPrf();
      break;
    case DBG_MSG:
      dispatchDbg();
      break;
    case MID_MSG:
      dispatchMid();
      break;
    default:
      dispatchCal();
      dispatchSen();
      dispatchPre();
      dispatchFbk();
      dispatchPrf();
      dispatchDbg();
      dispatchMid();
      break;
  }
}

void RuiOSCClass::dispatchCal() {
  if ((millis() - lastCalMsg) < RuiBody.calibration.calMsgRate) {
    return;
  }

  char addr[32];
  OSCMessage msg("");
  for (size_t i = 0; i < NN; i++) {
    strcpy(addr, "/cal/strings/input_min/");
    strcat(addr, chIdx[i]);
    dispatchOSC(
        msg.setAddress(addr).add(RuiBody.calibration.stringsInputMin[i]));

    strcpy(addr, "/cal/strings/input_max/");
    strcat(addr, chIdx[i]);
    dispatchOSC(
        msg.setAddress(addr).add(RuiBody.calibration.stringsInputMax[i]));

    strcpy(addr, "/cal/strings/change_thresh/");
    strcat(addr, chIdx[i]);
    dispatchOSC(
        msg.setAddress(addr).add(RuiBody.calibration.stringsChangeThresh[i]));

    strcpy(addr, "/cal/pads/input_min/");
    strcat(addr, chIdx[i]);
    dispatchOSC(msg.setAddress(addr).add(RuiBody.calibration.padsInputMin[i]));

    strcpy(addr, "/cal/pads/input_max/");
    strcat(addr, chIdx[i]);
    dispatchOSC(msg.setAddress(addr).add(RuiBody.calibration.padsInputMax[i]));

    strcpy(addr, "/cal/pads/change_thresh/");
    strcat(addr, chIdx[i]);
    dispatchOSC(
        msg.setAddress(addr).add(RuiBody.calibration.padsChangeThresh[i]));

    strcpy(addr, "/cal/faders/input_min/");
    strcat(addr, chIdx[i]);
    dispatchOSC(
        msg.setAddress(addr).add(RuiBody.calibration.fadersInputMin[i]));

    strcpy(addr, "/cal/faders/input_max/");
    strcat(addr, chIdx[i]);
    dispatchOSC(
        msg.setAddress(addr).add(RuiBody.calibration.fadersInputMax[i]));

    strcpy(addr, "/cal/faders/change_thresh/");
    strcat(addr, chIdx[i]);
    dispatchOSC(
        msg.setAddress(addr).add(RuiBody.calibration.fadersChangeThresh[i]));
  }

  dispatchOSC(msg.setAddress("/cal/joystick/x_center")
                  .add(RuiBody.calibration.joystickXMiddle));
  dispatchOSC(msg.setAddress("/cal/joystick/y_center")
                  .add(RuiBody.calibration.joystickYMiddle));
  dispatchOSC(msg.setAddress("/cal/joystick/change_thresh")
                  .add(RuiBody.calibration.joystickChangeThresh));
  dispatchOSC(msg.setAddress("/cal/accel/change_thresh")
                  .add(RuiBody.calibration.accelChangeThresh));
  dispatchOSC(msg.setAddress("/cal/osc/update_rate/cal")
                  .add(RuiBody.calibration.calMsgRate));
  dispatchOSC(msg.setAddress("/cal/osc/update_rate/sen")
                  .add(RuiBody.calibration.senMsgRate));
  dispatchOSC(msg.setAddress("/cal/osc/update_rate/pre")
                  .add(RuiBody.calibration.preMsgRate));
  dispatchOSC(msg.setAddress("/cal/osc/update_rate/fbk")
                  .add(RuiBody.calibration.fbkMsgRate));
  dispatchOSC(msg.setAddress("/cal/osc/update_rate/prf")
                  .add(RuiBody.calibration.prfMsgRate));
  dispatchOSC(msg.setAddress("/cal/osc/update_rate/dbg")
                  .add(RuiBody.calibration.dbgMsgRate));

  lastCalMsg = millis();
}

void RuiOSCClass::dispatchSen() {
  if ((millis() - lastSenMsg) < RuiBody.calibration.senMsgRate) {
    return;
  }
  char addr[32];
  OSCMessage msg(addr);
  for (size_t s = 0; s < NN; s++) {
    if (abs(RuiBody.sensorsLast.stringsV[s] - RuiBody.sensors.stringsV[s]) >
        RuiBody.calibration.stringsChangeThresh[s]) {
      strcpy(addr, "/sen/strings/");
      strcat(addr, chIdx[s]);
      dispatchOSC(msg.setAddress(addr).add(RuiBody.sensors.stringsV[s]));
    }
    if (RuiBody.sensors.padsV[s] > RuiBody.calibration.padsInputThresh[s] &&
        abs(RuiBody.sensorsLast.padsV[s] + RuiBody.sensors.padsV[s]) >
            RuiBody.calibration.padsChangeThresh[s]) {
      strcpy(addr, "/sen/pads/");
      strcat(addr, chIdx[s]);
      dispatchOSC(msg.setAddress(addr).add(RuiBody.sensors.padsV[s]));
    }
    if (abs(RuiBody.sensorsLast.fadersV[s] - RuiBody.sensors.fadersV[s]) >
        RuiBody.calibration.fadersChangeThresh[s]) {
      strcpy(addr, "/sen/faders/");
      strcat(addr, chIdx[s]);
      dispatchOSC(msg.setAddress(addr).add(RuiBody.sensors.fadersV[s]));
    }
    if (RuiBody.sensorsLast.togglesV[s] != RuiBody.sensors.togglesV[s]) {
      strcpy(addr, "/sen/toggles/");
      strcat(addr, chIdx[s]);
      dispatchOSC(msg.setAddress(addr).add(RuiBody.sensors.togglesV[s]));
    }
    if (RuiBody.sensorsLast.buttonsV[s] != RuiBody.sensors.buttonsV[s]) {
      strcpy(addr, "/sen/buttons/");
      strcat(addr, chIdx[s]);
      dispatchOSC(msg.setAddress(addr).add(RuiBody.sensors.buttonsV[s]));
    }
    if (RuiBody.sensorsLast.knobsV[s] != RuiBody.sensors.knobsV[s]) {
      strcpy(addr, "/sen/knobs/");
      strcat(addr, chIdx[s]);
      dispatchOSC(msg.setAddress(addr).add(RuiBody.sensors.knobsV[s]));
    }
    lastSenMsg = millis();
  }
  if ((abs(RuiBody.sensorsLast.jsXv - RuiBody.sensors.jsXv) >
       RuiBody.calibration.joystickChangeThresh) ||
      (abs(RuiBody.sensorsLast.jsYv - RuiBody.sensors.jsYv) >
       RuiBody.calibration.joystickChangeThresh)) {
    dispatchOSC(msg.setAddress("/sen/joystick")
                    .add(RuiBody.sensors.jsXv)
                    .add(RuiBody.sensors.jsYv));
  }

  if ((abs(RuiBody.sensorsLast.accXv - RuiBody.sensors.accXv) >
       RuiBody.calibration.accelChangeThresh) ||
      (abs(RuiBody.sensorsLast.accYv - RuiBody.sensors.accYv) >
       RuiBody.calibration.accelChangeThresh) ||
      (abs(RuiBody.sensorsLast.accZv - RuiBody.sensors.accZv) >
       RuiBody.calibration.accelChangeThresh)) {
    dispatchOSC(msg.setAddress("/sen/accel")
                    .add(RuiBody.sensors.accXv)
                    .add(RuiBody.sensors.accYv)
                    .add(RuiBody.sensors.accZv));
  }
}

void RuiOSCClass::dispatchPre() {
  if ((millis() - lastPreMsg) < RuiBody.calibration.preMsgRate) {
    return;
  }

  char addr[64];
  OSCMessage msg(addr);
  for (int s = 0; s < RuiPreset.numSections; s++) {
    for (size_t c = 0; c < RuiPreset.META[s].size; c++) {
      for (size_t i = 0; i < NN; i++) {
        strcpy(addr, "/pre/");
        strcat(addr, RuiPreset.META[s].name);
        strcat(addr, "/");
        strcat(addr, RuiPreset.META[s].idx[c].name);
        strcat(addr, "/");
        strcat(addr, chIdx[i]);
        msg.setAddress(addr);
        msg.add(RuiPreset.META[s].idx[c].idx[i]);
        dispatchOSC(msg);
      }
    }
  }

  dispatchOSC(msg.setAddress("/pre/name").add(RuiPreset.presetName));
  dispatchOSC(msg.setAddress("/pre/number").add(RuiPreset.currentPreset));
  dispatchOSC(msg.setAddress("/pre/total").add(RuiPreset.numberOfPresets));

  msg.setAddress("/pre/all");
  for (unsigned int i = 0; i < MAX_PRESETS; i++) {
    if (RuiPreset.PRESETS[i]) {
      msg.add(RuiPreset.PRESETS[i]);
    }
  }
  dispatchOSC(msg);

  lastPreMsg = millis();
}

void RuiOSCClass::dispatchFbk() {
  if ((millis() - lastFbkMsg) < RuiBody.calibration.fbkMsgRate) {
    return;
  }
  char addr[32];
  OSCMessage msg("");
  for (size_t i = 0; i < NN; i++) {
    if (RuiBody.feedbackLast.headLedsB[i] != RuiBody.feedback.headLedsB[i]) {
      strcpy(addr, "/fbk/led/head/blu/");
      strcat(addr, chIdx[i]);
      dispatchOSC(msg.setAddress(addr).add(RuiBody.feedback.headLedsB[i]));
    }
    if (RuiBody.feedbackLast.headLedsG[i] != RuiBody.feedback.headLedsG[i]) {
      strcpy(addr, "/fbk/led/head/grn/");
      strcat(addr, chIdx[i]);
      dispatchOSC(msg.setAddress(addr).add(RuiBody.feedback.headLedsG[i]));
    }
    if (RuiBody.feedbackLast.headLedsR[i] != RuiBody.feedback.headLedsR[i]) {
      strcpy(addr, "/fbk/led/head/red/");
      strcat(addr, chIdx[i]);
      dispatchOSC(msg.setAddress(addr).add(RuiBody.feedback.headLedsR[i]));
    }
    if (RuiBody.feedbackLast.toggleLeds[i] != RuiBody.feedback.toggleLeds[i]) {
      strcpy(addr, "/fbk/led/body/toggle/");
      strcat(addr, chIdx[i]);
      dispatchOSC(msg.setAddress(addr).add(RuiBody.feedback.toggleLeds[i]));
    }
  }

  lastFbkMsg = millis();
}

void RuiOSCClass::dispatchPrf() {
  if ((millis() - lastPrfMsg) < RuiBody.calibration.prfMsgRate) {
    return;
  }

  OSCMessage msg("");
  dispatchOSC(
      msg.setAddress("/prf/refresh").add(RuiBody.performance.refreshRate));
  dispatchOSC(
      msg.setAddress("/prf/audio/cpu").add(RuiBody.performance.audioCpuUsage));
  dispatchOSC(msg.setAddress("/prf/audio/cpu_max")
                  .add(RuiBody.performance.audioCpuUsageMax));
  dispatchOSC(
      msg.setAddress("/prf/audio/mem").add(RuiBody.performance.audioMemUsage));
  dispatchOSC(msg.setAddress("/prf/audio/mem_max")
                  .add(RuiBody.performance.audioMemUsageMax));

  lastPrfMsg = millis();
}

void RuiOSCClass::dispatchDbg() {
  if ((millis() - lastDbgMsg) < RuiBody.calibration.dbgMsgRate) {
    return;
  }

  if (debugIdx > 0) {
    OSCMessage dbgmsg("/dbg/message");
    dbgmsg.add(debugMsg);
    dispatchOSC(dbgmsg);
    debugIdx = 0;
  }

  lastDbgMsg = millis();
}

void RuiOSCClass::dispatchMid() {
  if ((millis() - lastMidMsg) < RuiBody.calibration.midMsgRate) {
    return;
  }

  char addr[32];
  OSCMessage msg("");
  // Use the same change validation logic as the sensors since they feed these
  // values anyhow.
  for (size_t s = 0; s < NN; s++) {
    if (abs(RuiBody.sensorsLast.stringsV[s] - RuiBody.sensors.stringsV[s]) >
        RuiBody.calibration.stringsChangeThresh[s]) {
      strcpy(addr, "/mid/strings/note/");
      strcat(addr, chIdx[s]);
      dispatchOSC(msg.setAddress(addr).add(RuiMIDI.strings[s]->noteValue));
      strcpy(addr, "/mid/strings/cc/");
      strcat(addr, chIdx[s]);
      dispatchOSC(msg.setAddress(addr).add(RuiMIDI.strings[s]->ccValue));
    }
    if (RuiBody.sensors.padsV[s] > RuiBody.calibration.padsInputThresh[s] &&
        abs(RuiBody.sensorsLast.padsV[s] + RuiBody.sensors.padsV[s]) >
            RuiBody.calibration.padsChangeThresh[s]) {
      strcpy(addr, "/mid/pads/note_on/");
      strcat(addr, chIdx[s]);
      dispatchOSC(msg.setAddress(addr).add(RuiMIDI.pads[s]->noteOn));
      strcpy(addr, "/mid/pads/velocity/");
      strcat(addr, chIdx[s]);
      dispatchOSC(msg.setAddress(addr).add(RuiMIDI.pads[s]->velocityValue));
      strcpy(addr, "/mid/pads/aftertouch/");
      strcat(addr, chIdx[s]);
      dispatchOSC(msg.setAddress(addr).add(RuiMIDI.pads[s]->afterTouchValue));
      strcpy(addr, "/mid/pads/cc/");
      strcat(addr, chIdx[s]);
      dispatchOSC(msg.setAddress(addr).add(RuiMIDI.pads[s]->ccValue));
    }
    if (abs(RuiBody.sensorsLast.fadersV[s] - RuiBody.sensors.fadersV[s]) >
        RuiBody.calibration.fadersChangeThresh[s]) {
      strcpy(addr, "/mid/faders/note/");
      strcat(addr, chIdx[s]);
      dispatchOSC(msg.setAddress(addr).add(RuiMIDI.faders[s]->noteValue));
      strcpy(addr, "/mid/faders/cc/");
      strcat(addr, chIdx[s]);
      dispatchOSC(msg.setAddress(addr).add(RuiMIDI.faders[s]->ccValue));
    }
    if (RuiBody.sensorsLast.togglesV[s] != RuiBody.sensors.togglesV[s]) {
      strcpy(addr, "/mid/toggles/cc/");
      strcat(addr, chIdx[s]);
      dispatchOSC(msg.setAddress(addr).add(RuiMIDI.toggles[s]->ccValue));
    }
    if (RuiBody.sensorsLast.buttonsV[s] != RuiBody.sensors.buttonsV[s]) {
      strcpy(addr, "/mid/buttons/cc/");
      strcat(addr, chIdx[s]);
      dispatchOSC(msg.setAddress(addr).add(RuiMIDI.buttons[s]->ccValue));
    }
    if (RuiBody.sensorsLast.knobsV[s] != RuiBody.sensors.knobsV[s]) {
      strcpy(addr, "/mid/knobs/cc/");
      strcat(addr, chIdx[s]);
      dispatchOSC(msg.setAddress(addr).add(RuiMIDI.knobs[s]->ccValue));
    }
  }
  if ((abs(RuiBody.sensorsLast.jsXv - RuiBody.sensors.jsXv) >
       RuiBody.calibration.joystickChangeThresh) ||
      (abs(RuiBody.sensorsLast.jsYv - RuiBody.sensors.jsYv) >
       RuiBody.calibration.joystickChangeThresh)) {
    dispatchOSC(
        msg.setAddress("/mid/joystick/x/cc").add(RuiMIDI.joystick->ccXValue));
    dispatchOSC(
        msg.setAddress("/mid/joystick/y/cc").add(RuiMIDI.joystick->ccYValue));
  }

  if ((abs(RuiBody.sensorsLast.accXv - RuiBody.sensors.accXv) >
       RuiBody.calibration.accelChangeThresh) ||
      (abs(RuiBody.sensorsLast.accYv - RuiBody.sensors.accYv) >
       RuiBody.calibration.accelChangeThresh) ||
      (abs(RuiBody.sensorsLast.accZv - RuiBody.sensors.accZv) >
       RuiBody.calibration.accelChangeThresh)) {
    // dispatchOSC(msg.setAddress("/mid/accel/x/cc").add(RuiMIDI.accel->ccXValue));
    // dispatchOSC(msg.setAddress("/mid/accel/y/cc").add(RuiMIDI.accel->ccYValue));
    // dispatchOSC(msg.setAddress("/mid/accel//cc").add(RuiMIDI.accel->ccZValue));
  }

  lastMidMsg = millis();
}

void RuiOSCClass::dispatchOSC(OSCMessage &msg) {
  SLIPSerial.beginPacket();
  msg.send(SLIPSerial);
  SLIPSerial.endPacket();
  msg.empty();
}

void RuiOSCClass::debug(const char *src) {
  if (debugIdx == 0) {
    debugMsg[0] = '\0';
  }
  size_t i, j;
  for (i = 0; debugMsg[i] != '\0'; i++)
    ;
  for (j = 0; src[j] != '\0' && j < 511; j++) {
    debugIdx = i + j;
    debugMsg[debugIdx] = src[j];
  }

  debugMsg[i + j] = '\0';
}

RuiOSCClass RuiOSC;