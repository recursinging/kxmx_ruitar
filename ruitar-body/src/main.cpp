#include <Arduino.h>
#include <Bounce2.h>
#include <TeensyView.h>
#include "RuiBody.h"
#include "RuiHead.h"
#include "RuiMIDI.h"
#include "RuiOSC.h"
#include "RuiPreset.h"
#include "RuiSynth.h"

#define MIDI_DEBUG 0
#define SENSOR_DEBUG 0

// Ethernet SPI -  OR  - ESP32 + SLIPSerial 
#define PIN_ETH_MOSI 0 // ESP RX1
#define PIN_ETH_MISO 1 // ESP TX1
#define PIN_ETH_RST 2
#define PIN_ETH_SCK 32
#define PIN_ETH_CS 31

// Head I2C Pins
#define PIN_HEAD_SCL 3
#define PIN_HEAD_SDA 4

// Button LED output pins
#define PIN_LED0 5
#define PIN_LED1 6 // XXX TAB SPI CS (Memory)
#define PIN_LED2 7 // XXX TAB SPI MOSI0
#define PIN_LED3 8

// Display SPI pins
#define PIN_DISPLAY_CS 10
#define PIN_DISPLAY_MOSI 11 // TAB I2S MCLK
#define PIN_DISPLAY_SCK 13 // TAB I2S RX
#define PIN_DISPLAY_RST 24 
#define PIN_DISPLAY_DC 25

// Soft-pot "string" analog input pins
#define PIN_S0 14 // XXX TAB SPI SCK0
#define PIN_S1 15
#define PIN_S2 16
#define PIN_S3 17

// FSR "pad" analog input pins
#define PIN_P0 18 // TAB I2C SDA0
#define PIN_P1 19 // TAB I2C SCL0
#define PIN_P2 20
#define PIN_P3 21 

// Joystick input pins
#define PIN_JSX 22 // TAB I2S TX
#define PIN_JSY 23 // TAB I2S LRCLK

// Fader potentiometer input pins
#define PIN_F0 33
#define PIN_F1 34
#define PIN_F2 35
#define PIN_F3 36

// Momentary button input pins (treated as toggles)
#define PIN_T0 26
#define PIN_T1 27
#define PIN_T2 28
#define PIN_T3 29

#define PIN_HEAD_RESET 9  // TAB I2S BCLK

#define PIN_UNUSED_12 12  // XXX TAB SPI MISO0
#define PIN_UNUSED_30 30  
#define PIN_UNUSED_38 38
#define PIN_UNUSED_39 39

uint32_t _elapsed;
uint16_t _rate;
uint8_t _debug;

SensorCalibration sensorCalibration;

// The display instance
// TeensyView display(PIN_DISPLAY_RST, PIN_DISPLAY_DC, PIN_DISPLAY_CS,
// PIN_DISPLAY_SCK, PIN_DISPLAY_MOSI, 64, &SPI);
TeensyView display(PIN_DISPLAY_RST, PIN_DISPLAY_DC, PIN_DISPLAY_CS,
                   PIN_DISPLAY_SCK, PIN_DISPLAY_MOSI);

// The toggle buttons (body)
Bounce toggle0 = Bounce();
Bounce toggle1 = Bounce();
Bounce toggle2 = Bounce();
Bounce toggle3 = Bounce();

// Pointer array for convienience
Bounce *toggles[] = {&toggle0, &toggle1, &toggle2, &toggle3};

uint8_t stringPins[] = {PIN_S0, PIN_S1, PIN_S2, PIN_S3};
uint8_t padPins[] = {PIN_P0, PIN_P1, PIN_P2, PIN_P3};
uint8_t faderPins[] = {PIN_F0, PIN_F1, PIN_F2, PIN_F3};
uint8_t buttonPins[] = {PIN_T0, PIN_T1, PIN_T2, PIN_T3};
uint8_t ledPins[] = {PIN_LED0, PIN_LED1, PIN_LED2, PIN_LED3};

/******** GLOBAL STATE VARIABLES *******/

// Timing and iteration
int16_t iter = 0;
uint64_t time = micros();
uint64_t iterDuration = 0;
uint64_t displayDuration = 0;
uint64_t modXDuration[10];

// The current preset
int8_t currentPreset = 0;

// Timing mode shows performance information on the display
bool timingMode = false;

// Config mode enables preset configuration changes
bool configMode = false;

/******** SETUP *******/

bool on = true;

void setup() {
  AudioMemory(100);

  Serial.begin(1000000);
  delay(100);
  // Serial.println("Welcome to the ruitar body!");

  _debug = 1;
  _elapsed = 0;
  _rate = 0;

  pinMode(PIN_JSX, INPUT);
  pinMode(PIN_JSY, INPUT);

  // Setup body buttons
  for (size_t s = 0; s < NN; s++) {
    pinMode(buttonPins[s], INPUT);
    toggles[s]->attach(buttonPins[s]);
    toggles[s]->interval(2);
    pinMode(ledPins[s], OUTPUT);
    pinMode(stringPins[s], INPUT);
    pinMode(padPins[s], INPUT);
    pinMode(faderPins[s], INPUT);
  }

  // Serial.print("Setting up the display...");
  display.begin();
  display.setFontType(0);
  delay(100);
  // Serial.println("OK");

  // Serial.print("Setting up the presets...");
  RuiPreset.begin("/ruitar/presets/");
  delay(100);
  // Serial.println("OK");

  pinMode(PIN_HEAD_RESET, OUTPUT);
  digitalWrite(PIN_HEAD_RESET, HIGH);
  RuiHead.begin();
  delay(100);

  RuiMIDI.begin();

  // Serial.print("Setting up the synth...");
  //RuiSynth.begin();
  // Serial.println("OK");

}

/******** LOOP *******/

void loop() {
  uint32_t iter_start = micros();

  // Update the head first...
if (iter % 500 == 0) {
  RuiHead.update();
}
  
  if (RuiBody.sensorMode == PHY) {
    // Iterate over the iterables...
    for (size_t s = 0; s < NN; s++) {
      // Read the strings...
      RuiBody.sensorsLast.stringsV[s] = RuiBody.sensors.stringsV[s];
      RuiBody.sensors.stringsV[s] = analogRead(stringPins[s]);
      // ..and the pads...
      RuiBody.sensorsLast.padsV[s] = RuiBody.sensors.padsV[s];
      RuiBody.sensors.padsV[s] = analogRead(padPins[s]);
      // ..and the faders...
      RuiBody.sensorsLast.fadersV[s] = RuiBody.sensors.fadersV[s];
      RuiBody.sensors.fadersV[s] = analogRead(faderPins[s]);
      // ..and the body toggle buttons...
      toggles[s]->update();
      RuiBody.sensorsLast.togglesV[s] = RuiBody.sensors.togglesV[s];
      RuiBody.sensors.togglesV[s] = toggles[s]->read();
      // ..and the head buttons...
      RuiBody.sensorsLast.buttonsV[s] = RuiBody.sensors.buttonsV[s];
      RuiBody.sensors.buttonsV[s] = RuiHead.button(s);
      // ..and the head knobs.
      RuiBody.sensorsLast.knobsV[s] = RuiBody.sensors.knobsV[s];
      RuiBody.sensors.knobsV[s] = RuiHead.knob(s);
    }
    // Now the non-iterables
    // First read the X and Y joystick axis
    RuiBody.sensorsLast.jsXv = RuiBody.sensors.jsXv;
    RuiBody.sensors.jsXv = analogRead(PIN_JSX);
    RuiBody.sensorsLast.jsYv = RuiBody.sensors.jsYv;
    RuiBody.sensors.jsYv = analogRead(PIN_JSY);

    // ...now the head accellerometer values
    RuiBody.sensorsLast.accXv = RuiBody.sensors.accXv;
    RuiBody.sensors.accXv = RuiHead.accelX();
    RuiBody.sensorsLast.accYv = RuiBody.sensors.accYv;
    RuiBody.sensors.accYv = RuiHead.accelY();
    RuiBody.sensorsLast.accZv = RuiBody.sensors.accZv;
    RuiBody.sensors.accZv = RuiHead.accelZ();
  }

  if (configMode) {
    // We're in config mode. Re-route the head knob and button values to the
    // preset class
    RuiPreset.update();
  }

  RuiMIDI.update();
  RuiMIDI.dispatch();

  //RuiOSC.update();
  //RuiOSC.dispatch();

  // RuiSynth.update();
  // RuiSynth.dispatch();


  // Dispatch any feedback now
  for (size_t s = 0; s < NN; s++) {
    if (RuiBody.feedback.toggleLeds[s] != RuiBody.feedbackLast.toggleLeds[s]) {
      digitalWrite(ledPins[s], RuiBody.feedback.toggleLeds[s]);
    }
    if (RuiBody.feedback.headLedsR[s] != RuiBody.feedbackLast.headLedsR[s]) {
      RuiHead.red(s, RuiBody.feedback.headLedsR[s]);
    }
    if (RuiBody.feedback.headLedsG[s] != RuiBody.feedbackLast.headLedsG[s]) {
      RuiHead.green(s, RuiBody.feedback.headLedsG[s]);
    }
    if (RuiBody.feedback.headLedsB[s] != RuiBody.feedbackLast.headLedsB[s]) {
      RuiHead.blue(s, RuiBody.feedback.headLedsB[s]);
    }
  }

  /////////////////////////////////////////////////////////////////
  //////////////////////////// DISPLAY ////////////////////////////
  /////////////////////////////////////////////////////////////////
  // Change this number to alter the screen refresh rate
  if (iter % 250 == 0) {
    uint32_t start = micros();
    if (configMode) {
      // Do config mode dislay
      RuiPreset.writeToDisplay(display);
    } else {
      // Do Default Display
      display.clear(PAGE);
      display.setCursor(0, 0);
      int k = 3;
      for (int8_t i = 0; i < 4; i++) {
        int8_t showNote = -1;
        display.setCursor(0, k * 8);
        // Display the note names
        if (RuiMIDI.state.notes[i] >= 0) {
          showNote = RuiMIDI.state.notes[i];
          display.setColor(BLACK);
          display.print(RuiMIDIUtil::toNoteName(showNote));
          display.setColor(WHITE);
        } else if (RuiMIDI.strings[i]->noteValue >= 0) {
          showNote = RuiMIDI.strings[i]->noteValue;
          display.print(RuiMIDIUtil::toNoteName(showNote));
        }
        // Display the raw string sensor values
        display.setCursor(18, k * 8);
        display.print("S");
        display.print(RuiBody.sensors.stringsV[i]);
        // display.print(RuiMIDI::strings[i]->rawValue);
        // Display the joystick CC values
        display.setCursor(32, k * 8);
        display.print("P");
        display.print(RuiBody.sensors.padsV[i]);

        k--;
      }
      // Write the display now.
      display.display();
    }
    displayDuration = micros() - start;
  }

  if (iter < 4096) {
    iter++;
  } else {
    iter = 0;
  };

  //////////////////////////////// TIMING //////////////////////////////
  uint32_t elapsed = (micros() - iter_start);
  _elapsed += elapsed;
  _rate++;
  if (_elapsed > 1000000) {
    
    Serial.print("AccelX: ");
    Serial.println(RuiHead.accelX());
        Serial.print("AccelY: ");
    Serial.println(RuiHead.accelY());
        Serial.print("AccelX: ");
    Serial.println(RuiHead.accelZ());
    
    RuiBody.performance.refreshRate = _rate;
    RuiBody.performance.audioCpuUsage = AudioProcessorUsage();
    RuiBody.performance.audioCpuUsageMax = AudioProcessorUsageMax();
    RuiBody.performance.audioMemUsage = AudioMemoryUsage();
    RuiBody.performance.audioMemUsageMax = AudioMemoryUsageMax();
    _elapsed = 0;
    _rate = 0;
  }
};
