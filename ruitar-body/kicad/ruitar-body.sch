EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:teensy
LIBS:ruitar-body-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 2
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Teensy3.6 U1
U 1 1 5A3BB80A
P 8800 3100
F 0 "U1" H 8800 5400 60  0000 C CNN
F 1 "Teensy3.6" H 8800 800 60  0000 C CNN
F 2 "footprints:Teensy35_36" H 8800 3100 60  0000 C CNN
F 3 "" H 8800 3100 60  0000 C CNN
	1    8800 3100
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR2
U 1 1 5A3CBE2E
P 10900 700
F 0 "#PWR2" H 10900 550 50  0001 C CNN
F 1 "+5V" H 10900 840 50  0000 C CNN
F 2 "" H 10900 700 50  0001 C CNN
F 3 "" H 10900 700 50  0001 C CNN
	1    10900 700 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR3
U 1 1 5A3CBE4E
P 10900 1250
F 0 "#PWR3" H 10900 1000 50  0001 C CNN
F 1 "GND" H 10900 1100 50  0000 C CNN
F 2 "" H 10900 1250 50  0001 C CNN
F 3 "" H 10900 1250 50  0001 C CNN
	1    10900 1250
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG1
U 1 1 5A3CBE8E
P 10900 700
F 0 "#FLG1" H 10900 775 50  0001 C CNN
F 1 "PWR_FLAG" H 10900 850 50  0000 C CNN
F 2 "" H 10900 700 50  0001 C CNN
F 3 "" H 10900 700 50  0001 C CNN
	1    10900 700 
	-1   0    0    1   
$EndComp
$Comp
L PWR_FLAG #FLG2
U 1 1 5A3CBEE5
P 10900 1250
F 0 "#FLG2" H 10900 1325 50  0001 C CNN
F 1 "PWR_FLAG" H 10900 1400 50  0000 C CNN
F 2 "" H 10900 1250 50  0001 C CNN
F 3 "" H 10900 1250 50  0001 C CNN
	1    10900 1250
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR1
U 1 1 5A3CC03D
P 10550 700
F 0 "#PWR1" H 10550 550 50  0001 C CNN
F 1 "+3.3V" H 10550 840 50  0000 C CNN
F 2 "" H 10550 700 50  0001 C CNN
F 3 "" H 10550 700 50  0001 C CNN
	1    10550 700 
	1    0    0    -1  
$EndComp
Text GLabel 9800 2100 2    60   Input ~ 0
3.3V
Text GLabel 10500 850  0    60   Input ~ 0
3.3V
Wire Wire Line
	10500 850  10550 850 
Wire Wire Line
	10550 850  10550 700 
Text GLabel 7800 5000 0    60   Input ~ 0
T14
Text GLabel 7800 5100 0    60   Input ~ 0
T15
Text GLabel 7800 5200 0    60   Input ~ 0
T16
Text GLabel 9800 5200 2    60   Input ~ 0
T17
$Sheet
S 5150 2050 500  150 
U 5A3CEDF9
F0 "ADIO-0-15" 60
F1 "ADIO-0-15.sch" 60
$EndSheet
Text GLabel 9800 5100 2    60   Input ~ 0
T18
Text GLabel 9800 5000 2    60   Input ~ 0
T19
Text GLabel 9800 4900 2    60   Input ~ 0
T20
Text GLabel 9800 4800 2    60   Input ~ 0
T21
Text GLabel 9800 4700 2    60   Input ~ 0
T22
Text GLabel 9800 4600 2    60   Input ~ 0
T23
Text GLabel 9800 4000 2    60   Input ~ 0
TA10
Text GLabel 9800 3900 2    60   Input ~ 0
TA11
Text GLabel 7800 3200 0    60   Input ~ 0
T31
Text GLabel 7800 3300 0    60   Input ~ 0
T32
Text GLabel 7800 3900 0    60   Input ~ 0
T33
Text GLabel 7800 4000 0    60   Input ~ 0
T34
$EndSCHEMATC
