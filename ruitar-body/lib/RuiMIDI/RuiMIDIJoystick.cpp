#include "RuiMIDIJoystick.h"
#include "RuiBody.h"
#include "RuiPreset.h"

RuiMIDIJoystick::RuiMIDIJoystick() {
  xPitchBendValue = 0;
  yPitchBendValue = 0;
  ccXValue = 0;
  ccYValue = 0;
  ccXPlusValue = 0;
  ccXMinusValue = 0;
  ccYPlusValue = 0;
  ccYMinusValue = 0;
  xRaw = 0;
  yRaw = 0;
  xConstrained = 0;
  yConstrained = 0;
}

void RuiMIDIJoystick::update() {
  xRaw = RuiBody.sensors.jsXv;
  yRaw = RuiBody.sensors.jsYv;
  xConstrained =
      constrain(RuiBody.sensors.jsXv, RuiBody.calibration.joystickInputMin,
                RuiBody.calibration.joystickInputMax);
  yConstrained =
      constrain(RuiBody.sensors.jsXv, RuiBody.calibration.joystickInputMin,
                RuiBody.calibration.joystickInputMax);

  // X axis
  if (abs(RuiBody.sensorsLast.jsXv - RuiBody.sensors.jsXv) >
      RuiBody.calibration.joystickChangeThresh) {
    ccXValue = map(xConstrained, RuiBody.calibration.joystickInputMin,
                   RuiBody.calibration.joystickInputMax,
                   RuiPreset.joystick.lowest_cc_value[0],
                   RuiPreset.joystick.highest_cc_value[1]);
    if (xConstrained > (RuiBody.calibration.joystickXMiddle -
                        RuiBody.calibration.joystickChangeThresh) &&
        xConstrained < (RuiBody.calibration.joystickXMiddle +
                        RuiBody.calibration.joystickChangeThresh)) {
      xPitchBendValue = 0;
      ccXPlusValue = RuiPreset.joystick.lowest_cc_value[0];
      ccXMinusValue = RuiPreset.joystick.lowest_cc_value[1];
    } else {
      if (xConstrained > RuiBody.calibration.joystickXMiddle) {
        ccXPlusValue = map(xConstrained, RuiBody.calibration.joystickXMiddle,
                           RuiBody.calibration.joystickInputMax,
                           RuiPreset.joystick.lowest_cc_value[0],
                           RuiPreset.joystick.highest_cc_value[0]);
        ccXMinusValue = RuiPreset.joystick.lowest_cc_value[1];
      } else {
        ccXPlusValue = RuiPreset.joystick.lowest_cc_value[0];
        ccXMinusValue = map(xConstrained, RuiBody.calibration.joystickXMiddle,
                            RuiBody.calibration.joystickInputMin,
                            RuiPreset.joystick.lowest_cc_value[1],
                            RuiPreset.joystick.highest_cc_value[1]);
      }

      xPitchBendValue = map(xConstrained, RuiBody.calibration.joystickInputMin,
                            RuiBody.calibration.joystickInputMax, -8192, 8192);
    }
  }

  // Y axis
  if (abs(RuiBody.sensorsLast.jsYv - RuiBody.sensors.jsYv) >
      RuiBody.calibration.joystickChangeThresh) {
    ccYValue = map(yConstrained, RuiBody.calibration.joystickInputMin,
                   RuiBody.calibration.joystickInputMax,
                   RuiPreset.joystick.lowest_cc_value[2],
                   RuiPreset.joystick.highest_cc_value[3]);
    if (yConstrained > (RuiBody.calibration.joystickYMiddle -
                        RuiBody.calibration.joystickChangeThresh) &&
        yConstrained < (RuiBody.calibration.joystickYMiddle +
                        RuiBody.calibration.joystickChangeThresh)) {
      yPitchBendValue = 0;
      ccYPlusValue = RuiPreset.joystick.lowest_cc_value[2];
      ccYMinusValue = RuiPreset.joystick.lowest_cc_value[3];
    } else {
      if (yConstrained > RuiBody.calibration.joystickYMiddle) {
        ccYPlusValue = map(yConstrained, RuiBody.calibration.joystickYMiddle,
                           RuiBody.calibration.joystickInputMax,
                           RuiPreset.joystick.lowest_cc_value[2],
                           RuiPreset.joystick.highest_cc_value[2]);
        ccYMinusValue = RuiPreset.joystick.lowest_cc_value[3];
      } else {
        ccYPlusValue = RuiPreset.joystick.lowest_cc_value[2];
        ccYMinusValue = map(yConstrained, RuiBody.calibration.joystickYMiddle,
                            RuiBody.calibration.joystickInputMin,
                            RuiPreset.joystick.lowest_cc_value[3],
                            RuiPreset.joystick.highest_cc_value[3]);
      }

      yPitchBendValue = map(yConstrained, RuiBody.calibration.joystickInputMin,
                            RuiBody.calibration.joystickInputMax, -8192, 8192);
    }
  }
};
