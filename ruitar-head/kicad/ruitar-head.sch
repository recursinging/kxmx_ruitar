EESchema Schematic File Version 2
LIBS:ruitar-head-rescue
LIBS:power
LIBS:device
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
LIBS:rgb-enc
LIBS:tlc5947
LIBS:teensy
LIBS:adxl345
LIBS:ruitar-head-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Ruitar Headstock Control"
Date "04.10.2017"
Rev "1"
Comp ""
Comment1 "4 RGB LED Quadratic Rotary Encoders"
Comment2 "24 Channel PWM LED Controller"
Comment3 "3 Axis Accelerometer"
Comment4 "Teensy LC with Custom Firmware + I²C Interface"
$EndDescr
$Comp
L ROTENC U2
U 1 1 59944237
P 4900 1650
F 0 "U2" H 4600 1950 50  0000 L CNN
F 1 "ROTENC" H 4600 1350 50  0000 L CNN
F 2 "footprints:SF_ROTENC" H 4600 1250 50  0001 L CNN
F 3 "" H 5300 1850 50  0001 C CNN
F 4 "COM-10982" H 4600 1150 50  0001 L CNN "SparkFun"
	1    4900 1650
	1    0    0    -1  
$EndComp
$Comp
L ROTENC U3
U 1 1 5994446D
P 4900 3200
F 0 "U3" H 4600 3500 50  0000 L CNN
F 1 "ROTENC" H 4600 2900 50  0000 L CNN
F 2 "footprints:SF_ROTENC" H 4600 2800 50  0001 L CNN
F 3 "" H 5300 3400 50  0001 C CNN
F 4 "COM-10982" H 4600 2700 50  0001 L CNN "SparkFun"
	1    4900 3200
	1    0    0    -1  
$EndComp
$Comp
L ROTENC U4
U 1 1 59944497
P 4900 4600
F 0 "U4" H 4600 4900 50  0000 L CNN
F 1 "ROTENC" H 4600 4300 50  0000 L CNN
F 2 "footprints:SF_ROTENC" H 4600 4200 50  0001 L CNN
F 3 "" H 5300 4800 50  0001 C CNN
F 4 "COM-10982" H 4600 4100 50  0001 L CNN "SparkFun"
	1    4900 4600
	1    0    0    -1  
$EndComp
$Comp
L ROTENC U5
U 1 1 599444C9
P 4900 6050
F 0 "U5" H 4600 6350 50  0000 L CNN
F 1 "ROTENC" H 4600 5750 50  0000 L CNN
F 2 "footprints:SF_ROTENC" H 4600 5650 50  0001 L CNN
F 3 "" H 5300 6250 50  0001 C CNN
F 4 "COM-10982" H 4600 5550 50  0001 L CNN "SparkFun"
	1    4900 6050
	1    0    0    -1  
$EndComp
$Comp
L TLC5947PWP U1
U 1 1 5994459F
P 1900 2850
F 0 "U1" H 1900 1900 50  0000 C CNN
F 1 "TLC5947PWP" H 1900 3750 50  0000 C CNN
F 2 "Housings_SSOP:TSSOP-32_6.1x11mm_Pitch0.65mm" H 1900 1800 60  0000 C CNN
F 3 "" H 1900 2850 60  0000 C CNN
	1    1900 2850
	1    0    0    -1  
$EndComp
$Comp
L Teensy-LC U8
U 1 1 5994466A
P 8400 3550
F 0 "U8" H 8400 4700 60  0000 C CNN
F 1 "Teensy-LC" H 8400 2400 60  0000 C CNN
F 2 "Teensy:Teensy30_31_32_LC" H 8400 3000 60  0000 C CNN
F 3 "" H 8400 3000 60  0000 C CNN
	1    8400 3550
	1    0    0    -1  
$EndComp
Text GLabel 10500 3450 0    60   Input ~ 0
+5V
$Comp
L GND #PWR11
U 1 1 599453C8
P 10550 1800
F 0 "#PWR11" H 10550 1550 50  0001 C CNN
F 1 "GND" H 10550 1650 50  0000 C CNN
F 2 "" H 10550 1800 50  0001 C CNN
F 3 "" H 10550 1800 50  0001 C CNN
	1    10550 1800
	1    0    0    -1  
$EndComp
Text GLabel 10050 1800 0    60   Input ~ 0
GND
$Comp
L +3.3V #PWR10
U 1 1 5994548D
P 10550 1300
F 0 "#PWR10" H 10550 1150 50  0001 C CNN
F 1 "+3.3V" H 10550 1440 50  0000 C CNN
F 2 "" H 10550 1300 50  0001 C CNN
F 3 "" H 10550 1300 50  0001 C CNN
	1    10550 1300
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR12
U 1 1 599454B3
P 10800 1300
F 0 "#PWR12" H 10800 1150 50  0001 C CNN
F 1 "+5V" H 10800 1440 50  0000 C CNN
F 2 "" H 10800 1300 50  0001 C CNN
F 3 "" H 10800 1300 50  0001 C CNN
	1    10800 1300
	1    0    0    -1  
$EndComp
Text GLabel 10050 1550 0    60   Input ~ 0
+5V
Text GLabel 10050 1300 0    60   Input ~ 0
+3.3V
Text GLabel 10500 3550 0    60   Input ~ 0
GND
Text GLabel 9500 3500 2    60   Input ~ 0
+3.3V
Text GLabel 7350 4100 0    60   Input ~ 0
+3.3V
Text GLabel 7350 4200 0    60   Input ~ 0
GND
Text GLabel 7350 2600 0    60   Input ~ 0
GND
Text GLabel 9500 3400 2    60   Input ~ 0
GND
Text GLabel 1400 2100 0    60   Input ~ 0
GND
Text GLabel 2400 2100 2    60   Input ~ 0
+3.3V
Text GLabel 4350 6250 0    60   Input ~ 0
+5V
Text GLabel 4350 4800 0    60   Input ~ 0
+5V
Text GLabel 4350 3400 0    60   Input ~ 0
+5V
Text GLabel 4350 1850 0    60   Input ~ 0
+5V
Text GLabel 9500 3300 2    60   Input ~ 0
+5V
Text GLabel 7350 2700 0    60   Input ~ 0
MOSI
Text GLabel 9500 3900 2    60   Input ~ 0
SCK
Text GLabel 7350 2800 0    60   Input ~ 0
LAT
Text GLabel 9500 4100 2    60   Input ~ 0
SDA
Text GLabel 9500 4000 2    60   Input ~ 0
SCL
Text GLabel 10500 3750 0    60   Input ~ 0
SDA
Text GLabel 10500 3650 0    60   Input ~ 0
SCL
Text GLabel 3650 1750 0    60   Input ~ 0
SW0
Text GLabel 3650 3300 0    60   Input ~ 0
SW1
Text GLabel 3650 4700 0    60   Input ~ 0
SW2
Text GLabel 3650 6150 0    60   Input ~ 0
SW3
Text GLabel 9500 4300 2    60   Input ~ 0
SW0
Text GLabel 9500 4200 2    60   Input ~ 0
SW1
Text GLabel 9500 3800 2    60   Input ~ 0
SW2
Text GLabel 9500 3700 2    60   Input ~ 0
SW3
Text GLabel 1400 2400 0    60   Input ~ 0
MOSI
Text GLabel 2400 2300 2    60   Input ~ 0
LAT
Text GLabel 1400 2300 0    60   Input ~ 0
SCK
Text GLabel 1350 3600 0    60   Input ~ 0
R0
Text GLabel 1350 3500 0    60   Input ~ 0
G0
Text GLabel 1350 3400 0    60   Input ~ 0
B0
Text GLabel 1350 3300 0    60   Input ~ 0
R1
Text GLabel 1350 3100 0    60   Input ~ 0
B1
Text GLabel 1350 3200 0    60   Input ~ 0
G1
Text GLabel 1350 3000 0    60   Input ~ 0
R2
Text GLabel 1350 2800 0    60   Input ~ 0
B2
Text GLabel 1350 2900 0    60   Input ~ 0
G2
Text GLabel 1350 2700 0    60   Input ~ 0
R3
Text GLabel 1350 2600 0    60   Input ~ 0
G3
Text GLabel 1350 2500 0    60   Input ~ 0
B3
Text GLabel 4350 1450 0    60   Input ~ 0
R0
Text GLabel 4350 1550 0    60   Input ~ 0
G0
Text GLabel 4350 1650 0    60   Input ~ 0
B0
Text GLabel 4350 3000 0    60   Input ~ 0
R1
Text GLabel 4350 3200 0    60   Input ~ 0
B1
Text GLabel 4350 3100 0    60   Input ~ 0
G1
Text GLabel 4350 4400 0    60   Input ~ 0
R2
Text GLabel 4350 4600 0    60   Input ~ 0
B2
Text GLabel 4350 4500 0    60   Input ~ 0
G2
Text GLabel 4350 5850 0    60   Input ~ 0
R3
Text GLabel 4350 5950 0    60   Input ~ 0
G3
Text GLabel 4350 6050 0    60   Input ~ 0
B3
$Comp
L C C7
U 1 1 5994B40B
P 5500 1400
F 0 "C7" H 5525 1500 50  0000 L CNN
F 1 "0.1uF" H 5525 1300 50  0001 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 5538 1250 50  0001 C CNN
F 3 "" H 5500 1400 50  0001 C CNN
	1    5500 1400
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 5994B62F
P 5450 1700
F 0 "C1" H 5475 1800 50  0000 L CNN
F 1 "0.1uF" H 5475 1600 50  0001 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 5488 1550 50  0001 C CNN
F 3 "" H 5450 1700 50  0001 C CNN
	1    5450 1700
	1    0    0    -1  
$EndComp
$Comp
L C C8
U 1 1 5994B8E8
P 5500 2950
F 0 "C8" H 5525 3050 50  0000 L CNN
F 1 "0.1uF" H 5525 2850 50  0001 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 5538 2800 50  0001 C CNN
F 3 "" H 5500 2950 50  0001 C CNN
	1    5500 2950
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 5994BA94
P 5450 3250
F 0 "C2" H 5475 3350 50  0000 L CNN
F 1 "0.1uF" H 5475 3150 50  0001 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 5488 3100 50  0001 C CNN
F 3 "" H 5450 3250 50  0001 C CNN
	1    5450 3250
	1    0    0    -1  
$EndComp
$Comp
L C C9
U 1 1 5994BE95
P 5500 4350
F 0 "C9" H 5525 4450 50  0000 L CNN
F 1 "0.1uF" H 5525 4250 50  0001 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 5538 4200 50  0001 C CNN
F 3 "" H 5500 4350 50  0001 C CNN
	1    5500 4350
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 5994BF01
P 5450 4650
F 0 "C3" H 5475 4750 50  0000 L CNN
F 1 "0.1uF" H 5475 4550 50  0001 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 5488 4500 50  0001 C CNN
F 3 "" H 5450 4650 50  0001 C CNN
	1    5450 4650
	1    0    0    -1  
$EndComp
$Comp
L C C10
U 1 1 5994C1E2
P 5500 5800
F 0 "C10" H 5525 5900 50  0000 L CNN
F 1 "0.1uF" H 5525 5700 50  0001 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 5538 5650 50  0001 C CNN
F 3 "" H 5500 5800 50  0001 C CNN
	1    5500 5800
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 5994C248
P 5450 6100
F 0 "C4" H 5475 6200 50  0000 L CNN
F 1 "0.1uF" H 5475 6000 50  0001 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 5488 5950 50  0001 C CNN
F 3 "" H 5450 6100 50  0001 C CNN
	1    5450 6100
	1    0    0    -1  
$EndComp
$Comp
L C C13
U 1 1 599BC18D
P 2350 1950
F 0 "C13" H 2375 2050 50  0000 L CNN
F 1 "0.1uF" H 2375 1850 50  0001 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 2388 1800 50  0001 C CNN
F 3 "" H 2350 1950 50  0001 C CNN
	1    2350 1950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR3
U 1 1 599BC267
P 2150 1650
F 0 "#PWR3" H 2150 1400 50  0001 C CNN
F 1 "GND" H 2150 1500 50  0000 C CNN
F 2 "" H 2150 1650 50  0001 C CNN
F 3 "" H 2150 1650 50  0001 C CNN
	1    2150 1650
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 599BC3C3
P 2900 1900
F 0 "R1" V 2980 1900 50  0000 C CNN
F 1 "3.3K" V 2900 1900 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2830 1900 50  0001 C CNN
F 3 "" H 2900 1900 50  0001 C CNN
	1    2900 1900
	-1   0    0    1   
$EndComp
$Comp
L R R6
U 1 1 59A51288
P 6050 1400
F 0 "R6" V 6130 1400 50  0000 C CNN
F 1 "10K" V 6050 1400 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 5980 1400 50  0001 C CNN
F 3 "" H 6050 1400 50  0001 C CNN
	1    6050 1400
	1    0    0    -1  
$EndComp
$Comp
L R R10
U 1 1 59A5151F
P 6150 1700
F 0 "R10" V 6230 1700 50  0000 C CNN
F 1 "10K" V 6150 1700 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 6080 1700 50  0001 C CNN
F 3 "" H 6150 1700 50  0001 C CNN
	1    6150 1700
	1    0    0    -1  
$EndComp
$Comp
L R R7
U 1 1 59A51600
P 6050 2950
F 0 "R7" V 6130 2950 50  0000 C CNN
F 1 "10K" V 6050 2950 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 5980 2950 50  0001 C CNN
F 3 "" H 6050 2950 50  0001 C CNN
	1    6050 2950
	1    0    0    -1  
$EndComp
$Comp
L R R11
U 1 1 59A51649
P 6150 3250
F 0 "R11" V 6230 3250 50  0000 C CNN
F 1 "10K" V 6150 3250 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 6080 3250 50  0001 C CNN
F 3 "" H 6150 3250 50  0001 C CNN
	1    6150 3250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR8
U 1 1 59A66553
P 5700 6750
F 0 "#PWR8" H 5700 6500 50  0001 C CNN
F 1 "GND" H 5700 6600 50  0000 C CNN
F 2 "" H 5700 6750 50  0001 C CNN
F 3 "" H 5700 6750 50  0001 C CNN
	1    5700 6750
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR9
U 1 1 59A675E3
P 5850 1050
F 0 "#PWR9" H 5850 900 50  0001 C CNN
F 1 "+3.3V" H 5850 1190 50  0000 C CNN
F 2 "" H 5850 1050 50  0001 C CNN
F 3 "" H 5850 1050 50  0001 C CNN
	1    5850 1050
	1    0    0    -1  
$EndComp
$Comp
L R R8
U 1 1 59A68412
P 6050 4350
F 0 "R8" V 6130 4350 50  0000 C CNN
F 1 "10K" V 6050 4350 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 5980 4350 50  0001 C CNN
F 3 "" H 6050 4350 50  0001 C CNN
	1    6050 4350
	1    0    0    -1  
$EndComp
$Comp
L R R12
U 1 1 59A68418
P 6150 4650
F 0 "R12" V 6230 4650 50  0000 C CNN
F 1 "10K" V 6150 4650 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 6080 4650 50  0001 C CNN
F 3 "" H 6150 4650 50  0001 C CNN
	1    6150 4650
	1    0    0    -1  
$EndComp
$Comp
L R R9
U 1 1 59A6851D
P 6050 5800
F 0 "R9" V 6130 5800 50  0000 C CNN
F 1 "10K" V 6050 5800 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 5980 5800 50  0001 C CNN
F 3 "" H 6050 5800 50  0001 C CNN
	1    6050 5800
	1    0    0    -1  
$EndComp
$Comp
L R R13
U 1 1 59A68523
P 6150 6100
F 0 "R13" V 6230 6100 50  0000 C CNN
F 1 "10K" V 6150 6100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 6080 6100 50  0001 C CNN
F 3 "" H 6150 6100 50  0001 C CNN
	1    6150 6100
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 59A698EC
P 3750 2000
F 0 "R2" V 3830 2000 50  0000 C CNN
F 1 "10K" V 3750 2000 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3680 2000 50  0001 C CNN
F 3 "" H 3750 2000 50  0001 C CNN
	1    3750 2000
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR4
U 1 1 59A69D14
P 3750 2150
F 0 "#PWR4" H 3750 1900 50  0001 C CNN
F 1 "GND" H 3750 2000 50  0000 C CNN
F 2 "" H 3750 2150 50  0001 C CNN
F 3 "" H 3750 2150 50  0001 C CNN
	1    3750 2150
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 59A6A548
P 3750 3550
F 0 "R3" V 3830 3550 50  0000 C CNN
F 1 "10K" V 3750 3550 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3680 3550 50  0001 C CNN
F 3 "" H 3750 3550 50  0001 C CNN
	1    3750 3550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR5
U 1 1 59A6A55A
P 3750 3700
F 0 "#PWR5" H 3750 3450 50  0001 C CNN
F 1 "GND" H 3750 3550 50  0000 C CNN
F 2 "" H 3750 3700 50  0001 C CNN
F 3 "" H 3750 3700 50  0001 C CNN
	1    3750 3700
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 59A6AA1B
P 3750 4950
F 0 "R4" V 3830 4950 50  0000 C CNN
F 1 "10K" V 3750 4950 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3680 4950 50  0001 C CNN
F 3 "" H 3750 4950 50  0001 C CNN
	1    3750 4950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR6
U 1 1 59A6AA2D
P 3750 5100
F 0 "#PWR6" H 3750 4850 50  0001 C CNN
F 1 "GND" H 3750 4950 50  0000 C CNN
F 2 "" H 3750 5100 50  0001 C CNN
F 3 "" H 3750 5100 50  0001 C CNN
	1    3750 5100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR7
U 1 1 59A6AC7F
P 3750 6550
F 0 "#PWR7" H 3750 6300 50  0001 C CNN
F 1 "GND" H 3750 6400 50  0000 C CNN
F 2 "" H 3750 6550 50  0001 C CNN
F 3 "" H 3750 6550 50  0001 C CNN
	1    3750 6550
	1    0    0    -1  
$EndComp
$Comp
L ADXL345 IC1
U 1 1 59AE8737
P 1900 5200
F 0 "IC1" H 1600 5600 50  0000 L CNN
F 1 "ADXL345" H 1600 4600 50  0000 L CNN
F 2 "footprints:ADXL3x5" H 1600 4500 50  0001 L CNN
F 3 "" H 1500 4700 50  0001 C CNN
F 4 "1853935" H 1600 4400 50  0001 L CNN "Farnell"
	1    1900 5200
	1    0    0    -1  
$EndComp
Text GLabel 7350 3900 0    60   Input ~ 0
SDO
Text GLabel 7350 3800 0    60   Input ~ 0
SDI
Text GLabel 2300 5500 2    60   Input ~ 0
SDO
Text GLabel 2300 5600 2    60   Input ~ 0
SDI
Text GLabel 9500 4500 2    60   Input ~ 0
SCLK
$Comp
L C C14
U 1 1 59AF15CD
P 1150 5150
F 0 "C14" H 1175 5250 50  0000 L CNN
F 1 "0.1uF" H 1175 5050 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 1188 5000 50  0001 C CNN
F 3 "" H 1150 5150 50  0001 C CNN
	1    1150 5150
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR1
U 1 1 59AF175E
P 1150 4650
F 0 "#PWR1" H 1150 4500 50  0001 C CNN
F 1 "+3.3V" H 1150 4790 50  0000 C CNN
F 2 "" H 1150 4650 50  0001 C CNN
F 3 "" H 1150 4650 50  0001 C CNN
	1    1150 4650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR2
U 1 1 59AF1C93
P 1150 5750
F 0 "#PWR2" H 1150 5500 50  0001 C CNN
F 1 "GND" H 1150 5600 50  0000 C CNN
F 2 "" H 1150 5750 50  0001 C CNN
F 3 "" H 1150 5750 50  0001 C CNN
	1    1150 5750
	1    0    0    -1  
$EndComp
Text GLabel 7350 3700 0    60   Input ~ 0
CS
Text GLabel 2300 5400 2    60   Input ~ 0
CS
Text GLabel 2300 5700 2    60   Input ~ 0
SCLK
Text GLabel 10500 3850 0    60   Input ~ 0
INT
$Comp
L Conn_01x05 J1
U 1 1 59B0FC30
P 10700 3650
F 0 "J1" H 10700 3950 50  0000 C CNN
F 1 "IO Headers 01x05" H 10700 3350 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x05_Pitch2.54mm" H 10700 3650 50  0001 C CNN
F 3 "" H 10700 3650 50  0001 C CNN
	1    10700 3650
	1    0    0    -1  
$EndComp
Text GLabel 9500 4400 2    60   Input ~ 0
INT
NoConn ~ 9500 2700
NoConn ~ 9500 2800
NoConn ~ 9500 2900
NoConn ~ 9500 3000
NoConn ~ 9500 3100
NoConn ~ 9500 3200
NoConn ~ 9500 3600
NoConn ~ 7350 4400
NoConn ~ 7350 4500
NoConn ~ 7350 4300
NoConn ~ 7350 4000
NoConn ~ 1500 5500
NoConn ~ 1500 5600
NoConn ~ 1500 5700
NoConn ~ 2300 4900
NoConn ~ 2300 5000
NoConn ~ 2300 2400
NoConn ~ 2300 2500
NoConn ~ 2300 2600
NoConn ~ 2300 2700
NoConn ~ 2300 2800
NoConn ~ 2300 2900
NoConn ~ 2300 3000
NoConn ~ 2300 3100
NoConn ~ 2300 3200
NoConn ~ 2300 3300
NoConn ~ 2300 3400
NoConn ~ 2300 3500
NoConn ~ 2300 3600
NoConn ~ 1500 2200
$Comp
L PWR_FLAG #FLG1
U 1 1 59B118F2
P 10250 1300
F 0 "#FLG1" H 10250 1375 50  0001 C CNN
F 1 "PWR_FLAG" H 10250 1450 50  0000 C CNN
F 2 "" H 10250 1300 50  0001 C CNN
F 3 "" H 10250 1300 50  0001 C CNN
	1    10250 1300
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG2
U 1 1 59B11F09
P 10250 1550
F 0 "#FLG2" H 10250 1625 50  0001 C CNN
F 1 "PWR_FLAG" H 10250 1700 50  0000 C CNN
F 2 "" H 10250 1550 50  0001 C CNN
F 3 "" H 10250 1550 50  0001 C CNN
	1    10250 1550
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG3
U 1 1 59B122F5
P 10250 1800
F 0 "#FLG3" H 10250 1875 50  0001 C CNN
F 1 "PWR_FLAG" H 10250 1950 50  0000 C CNN
F 2 "" H 10250 1800 50  0001 C CNN
F 3 "" H 10250 1800 50  0001 C CNN
	1    10250 1800
	1    0    0    -1  
$EndComp
Text GLabel 6350 1250 2    60   Input ~ 0
E0A
Text GLabel 6350 1850 2    60   Input ~ 0
E0B
Text GLabel 6350 4200 2    60   Input ~ 0
E2A
Text GLabel 6350 4800 2    60   Input ~ 0
E2B
Text GLabel 6350 2800 2    60   Input ~ 0
E1A
Text GLabel 6350 3400 2    60   Input ~ 0
E1B
Text GLabel 6350 5650 2    60   Input ~ 0
E3A
Text GLabel 6350 6250 2    60   Input ~ 0
E3B
Text GLabel 7350 2900 0    60   Input ~ 0
E3B
Text GLabel 7350 3000 0    60   Input ~ 0
E3A
Text GLabel 7350 3100 0    60   Input ~ 0
E2B
Text GLabel 7350 3200 0    60   Input ~ 0
E2A
Text GLabel 7350 3300 0    60   Input ~ 0
E1B
Text GLabel 7350 3400 0    60   Input ~ 0
E1A
Text GLabel 7350 3500 0    60   Input ~ 0
E0B
Text GLabel 7350 3600 0    60   Input ~ 0
E0A
$Comp
L R R14
U 1 1 5A311C90
P 3950 1750
F 0 "R14" V 4030 1750 50  0000 C CNN
F 1 "5K" V 3950 1750 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3880 1750 50  0001 C CNN
F 3 "" H 3950 1750 50  0001 C CNN
	1    3950 1750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10800 1550 10800 1300
Wire Wire Line
	5300 1550 5700 1550
Wire Wire Line
	5300 3100 5700 3100
Wire Wire Line
	5700 4500 5300 4500
Wire Wire Line
	5700 5950 5300 5950
Wire Wire Line
	4350 1850 4500 1850
Wire Wire Line
	4500 3400 4350 3400
Wire Wire Line
	4500 4800 4350 4800
Wire Wire Line
	4500 6250 4350 6250
Wire Wire Line
	1500 2100 1400 2100
Wire Wire Line
	1400 2300 1500 2300
Wire Wire Line
	1500 2400 1400 2400
Wire Wire Line
	2300 2300 2400 2300
Wire Wire Line
	2300 2100 2400 2100
Wire Wire Line
	4350 6050 4500 6050
Wire Wire Line
	4350 5950 4500 5950
Wire Wire Line
	4500 5850 4350 5850
Wire Wire Line
	4500 3200 4350 3200
Wire Wire Line
	4500 3100 4350 3100
Wire Wire Line
	4500 3000 4350 3000
Wire Wire Line
	4500 1650 4350 1650
Wire Wire Line
	4500 1550 4350 1550
Wire Wire Line
	4500 1450 4350 1450
Wire Wire Line
	4500 4400 4350 4400
Wire Wire Line
	4500 4500 4350 4500
Wire Wire Line
	4500 4600 4350 4600
Wire Wire Line
	5300 1450 5350 1450
Wire Wire Line
	5350 1450 5350 1250
Connection ~ 5500 1250
Connection ~ 5500 1550
Wire Wire Line
	5300 1650 5350 1650
Wire Wire Line
	5350 1650 5350 1850
Connection ~ 5500 3100
Wire Wire Line
	5300 3000 5300 2800
Connection ~ 5500 2800
Wire Wire Line
	5300 3400 5300 3200
Connection ~ 5450 3100
Connection ~ 5450 3400
Connection ~ 5450 1850
Connection ~ 5450 1550
Wire Wire Line
	5300 4400 5300 4200
Connection ~ 5500 4200
Wire Wire Line
	5300 4600 5300 4800
Connection ~ 5450 4800
Connection ~ 5450 4500
Connection ~ 5500 4500
Wire Wire Line
	5300 5850 5300 5650
Connection ~ 5500 5650
Connection ~ 5500 5950
Connection ~ 5450 5950
Wire Wire Line
	5300 6050 5300 6250
Connection ~ 5450 6250
Wire Wire Line
	1350 2500 1500 2500
Wire Wire Line
	1350 2600 1500 2600
Wire Wire Line
	1350 2700 1500 2700
Wire Wire Line
	1350 2800 1500 2800
Wire Wire Line
	1350 2900 1500 2900
Wire Wire Line
	1500 3000 1350 3000
Wire Wire Line
	1350 3100 1500 3100
Wire Wire Line
	1500 3200 1350 3200
Wire Wire Line
	1350 3300 1500 3300
Wire Wire Line
	1500 3400 1350 3400
Wire Wire Line
	1350 3500 1500 3500
Wire Wire Line
	1500 3600 1350 3600
Wire Wire Line
	2350 1800 2350 1650
Wire Wire Line
	2150 1650 2900 1650
Wire Wire Line
	2300 2200 2900 2200
Connection ~ 2350 1650
Connection ~ 2350 2100
Wire Wire Line
	2900 2200 2900 2050
Wire Wire Line
	2900 1650 2900 1750
Wire Wire Line
	5700 1550 5700 6750
Connection ~ 5700 3100
Connection ~ 5700 4500
Connection ~ 5700 5950
Wire Wire Line
	5850 1050 5850 5950
Wire Wire Line
	5850 1550 6150 1550
Connection ~ 6050 1550
Connection ~ 6050 1250
Connection ~ 6150 1850
Wire Wire Line
	5850 3100 6150 3100
Connection ~ 5850 1550
Connection ~ 6050 3100
Connection ~ 6150 3400
Connection ~ 6050 2800
Wire Wire Line
	5850 4500 6150 4500
Connection ~ 6050 4500
Wire Wire Line
	5850 5950 6150 5950
Connection ~ 6050 5950
Connection ~ 5850 3100
Connection ~ 6050 4200
Connection ~ 6150 4800
Connection ~ 6050 5650
Connection ~ 5850 4500
Connection ~ 6150 6250
Wire Wire Line
	1150 4650 1150 5000
Wire Wire Line
	1150 5000 1500 5000
Wire Wire Line
	1400 5000 1400 4900
Wire Wire Line
	1400 4900 1500 4900
Connection ~ 1400 5000
Wire Wire Line
	1150 5300 1500 5300
Wire Wire Line
	1400 5100 1400 5300
Wire Wire Line
	1400 5200 1500 5200
Connection ~ 1400 5300
Wire Wire Line
	1400 5100 1500 5100
Connection ~ 1400 5200
Wire Wire Line
	1150 5750 1150 5300
Connection ~ 1150 5300
Connection ~ 1150 5000
Wire Wire Line
	10050 1300 10550 1300
Connection ~ 10250 1300
Wire Wire Line
	10050 1550 10800 1550
Connection ~ 10250 1550
Wire Wire Line
	10050 1800 10550 1800
Connection ~ 10250 1800
Wire Wire Line
	5350 1250 6350 1250
Wire Wire Line
	5350 1850 6350 1850
Wire Wire Line
	5300 2800 6350 2800
Wire Wire Line
	5300 3400 6350 3400
Wire Wire Line
	5300 4200 6350 4200
Wire Wire Line
	5300 4800 6350 4800
Wire Wire Line
	5300 5650 6350 5650
Wire Wire Line
	5300 6250 6350 6250
Wire Wire Line
	4500 1750 4100 1750
Wire Wire Line
	3750 1850 3750 1750
Connection ~ 3750 1750
Wire Wire Line
	3650 1750 3800 1750
Wire Wire Line
	4100 3300 4500 3300
$Comp
L R R15
U 1 1 5A312E83
P 3950 3300
F 0 "R15" V 4030 3300 50  0000 C CNN
F 1 "5K" V 3950 3300 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3880 3300 50  0001 C CNN
F 3 "" H 3950 3300 50  0001 C CNN
	1    3950 3300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3800 3300 3650 3300
Wire Wire Line
	3750 3400 3750 3300
Connection ~ 3750 3300
$Comp
L R R16
U 1 1 5A3137CE
P 3950 4700
F 0 "R16" V 4030 4700 50  0000 C CNN
F 1 "5K" V 3950 4700 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3880 4700 50  0001 C CNN
F 3 "" H 3950 4700 50  0001 C CNN
	1    3950 4700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4500 4700 4100 4700
Wire Wire Line
	3800 4700 3650 4700
Wire Wire Line
	3750 4800 3750 4700
Connection ~ 3750 4700
$Comp
L R R5
U 1 1 59A6AC6D
P 3750 6400
F 0 "R5" V 3830 6400 50  0000 C CNN
F 1 "10K" V 3750 6400 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3680 6400 50  0001 C CNN
F 3 "" H 3750 6400 50  0001 C CNN
	1    3750 6400
	1    0    0    -1  
$EndComp
$Comp
L R R17
U 1 1 5A313E67
P 3950 6150
F 0 "R17" V 4030 6150 50  0000 C CNN
F 1 "5K" V 3950 6150 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3880 6150 50  0001 C CNN
F 3 "" H 3950 6150 50  0001 C CNN
	1    3950 6150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3650 6150 3800 6150
Wire Wire Line
	4100 6150 4500 6150
Wire Wire Line
	3750 6250 3750 6150
Connection ~ 3750 6150
$EndSCHEMATC
