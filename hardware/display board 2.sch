EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 3 4
Title "Hacked Clock"
Date ""
Rev ""
Comp ""
Comment1 "Display board #1"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:+5V #PWR?
U 1 1 60169232
P 2600 4850
AR Path="/60169232" Ref="#PWR?"  Part="1" 
AR Path="/6014418F/60169232" Ref="#PWR?"  Part="1" 
AR Path="/6016F5EB/60169232" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 2600 4700 50  0001 C CNN
F 1 "+5V" V 2500 4850 50  0000 L CNN
F 2 "" H 2600 4850 50  0001 C CNN
F 3 "" H 2600 4850 50  0001 C CNN
	1    2600 4850
	0    1    1    0   
$EndComp
Text Label 1650 4850 2    50   ~ 0
VCC
Wire Wire Line
	1650 5450 2150 5450
$Comp
L power:GND #PWR?
U 1 1 6016923C
P 2650 5500
AR Path="/6016923C" Ref="#PWR?"  Part="1" 
AR Path="/6014418F/6016923C" Ref="#PWR?"  Part="1" 
AR Path="/6016F5EB/6016923C" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 2650 5250 50  0001 C CNN
F 1 "GND" H 2655 5327 50  0000 C CNN
F 2 "" H 2650 5500 50  0001 C CNN
F 3 "" H 2650 5500 50  0001 C CNN
	1    2650 5500
	1    0    0    -1  
$EndComp
Text Label 1650 5450 2    50   ~ 0
GND
$Comp
L Interface_Expansion:MCP23017_SP U?
U 1 1 6016925B
P 5300 4750
AR Path="/6016925B" Ref="U?"  Part="1" 
AR Path="/6014418F/6016925B" Ref="U?"  Part="1" 
AR Path="/6016F5EB/6016925B" Ref="U?"  Part="1" 
F 0 "U?" H 5000 5750 50  0000 C CNN
F 1 "MCP23017" H 5600 5750 50  0000 C CNN
F 2 "Package_DIP:DIP-28_W7.62mm" H 5500 3750 50  0001 L CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/20001952C.pdf" H 5500 3650 50  0001 L CNN
	1    5300 4750
	1    0    0    -1  
$EndComp
NoConn ~ 4600 4550
NoConn ~ 4600 4650
Text Label 4600 3950 2    50   ~ 0
SDA_5V
Text Label 4600 4050 2    50   ~ 0
SCL_5V
Text Label 3750 4850 2    50   ~ 0
VCC
$Comp
L Device:R_Small_US R_RST?
U 1 1 60169266
P 4150 4850
AR Path="/60169266" Ref="R_RST?"  Part="1" 
AR Path="/6014418F/60169266" Ref="R_RST1"  Part="1" 
AR Path="/6016F5EB/60169266" Ref="R_RST1"  Part="1" 
F 0 "R_RST1" V 4050 4850 50  0000 C CNN
F 1 "10K" V 4250 4850 50  0000 C CNN
F 2 "" H 4150 4850 50  0001 C CNN
F 3 "~" H 4150 4850 50  0001 C CNN
	1    4150 4850
	0    1    1    0   
$EndComp
Wire Wire Line
	4250 4850 4600 4850
Wire Wire Line
	3750 4850 4050 4850
Text Label 4300 5550 2    50   ~ 0
VCC
Text Label 4300 5400 2    50   ~ 0
GND
Text Notes 4050 5500 2    70   ~ 0
ADDR = 0x21
$Comp
L power:GND #PWR?
U 1 1 60169278
P 5300 5950
AR Path="/60169278" Ref="#PWR?"  Part="1" 
AR Path="/6014418F/60169278" Ref="#PWR?"  Part="1" 
AR Path="/6016F5EB/60169278" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 5300 5700 50  0001 C CNN
F 1 "GND" H 5305 5777 50  0000 C CNN
F 2 "" H 5300 5950 50  0001 C CNN
F 3 "" H 5300 5950 50  0001 C CNN
	1    5300 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 5850 5300 5950
Wire Wire Line
	6000 4850 6200 4850
Wire Wire Line
	6200 4950 6000 4950
Wire Wire Line
	6000 5050 6200 5050
Wire Wire Line
	6200 5150 6000 5150
Wire Wire Line
	6200 5250 6000 5250
Wire Wire Line
	6000 5350 6200 5350
Wire Wire Line
	6000 5450 6200 5450
Wire Wire Line
	6000 5550 6200 5550
Wire Wire Line
	6000 4650 6200 4650
Wire Wire Line
	6000 4550 6200 4550
Wire Wire Line
	6000 4450 6200 4450
Wire Wire Line
	6000 4350 6200 4350
Wire Wire Line
	6000 4250 6200 4250
Wire Wire Line
	6000 4150 6200 4150
Wire Wire Line
	6000 4050 6200 4050
Wire Wire Line
	6000 3950 6200 3950
Wire Wire Line
	5300 2950 5300 3050
$Comp
L power:+5V #PWR?
U 1 1 60169290
P 5300 2950
AR Path="/60169290" Ref="#PWR?"  Part="1" 
AR Path="/6014418F/60169290" Ref="#PWR?"  Part="1" 
AR Path="/6016F5EB/60169290" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 5300 2800 50  0001 C CNN
F 1 "+5V" H 5250 3100 50  0000 L CNN
F 2 "" H 5300 2950 50  0001 C CNN
F 3 "" H 5300 2950 50  0001 C CNN
	1    5300 2950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 60169296
P 4800 3200
AR Path="/60169296" Ref="C?"  Part="1" 
AR Path="/6014418F/60169296" Ref="C10"  Part="1" 
AR Path="/6016F5EB/60169296" Ref="C10"  Part="1" 
F 0 "C10" H 4915 3246 50  0000 L CNN
F 1 "0.1uF" H 4915 3155 50  0000 L CNN
F 2 "" H 4838 3050 50  0001 C CNN
F 3 "~" H 4800 3200 50  0001 C CNN
	1    4800 3200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6016929C
P 4800 3350
AR Path="/6016929C" Ref="#PWR?"  Part="1" 
AR Path="/6014418F/6016929C" Ref="#PWR?"  Part="1" 
AR Path="/6016F5EB/6016929C" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 4800 3100 50  0001 C CNN
F 1 "GND" H 4805 3177 50  0000 C CNN
F 2 "" H 4800 3350 50  0001 C CNN
F 3 "" H 4800 3350 50  0001 C CNN
	1    4800 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 3050 5300 3050
Connection ~ 5300 3050
Wire Wire Line
	5300 3050 5300 3650
$Comp
L Device:LED DSEG_x_?
U 1 1 601692A5
P 8700 4250
AR Path="/601692A5" Ref="DSEG_x_?"  Part="1" 
AR Path="/6014418F/601692A5" Ref="DSEG_x_?"  Part="1" 
AR Path="/6016F5EB/601692A5" Ref="DSEG_x_?"  Part="1" 
F 0 "DSEG_x_?" H 8700 4350 50  0000 C CNN
F 1 "LED" H 8693 4086 50  0001 C CNN
F 2 "" H 8700 4250 50  0001 C CNN
F 3 "~" H 8700 4250 50  0001 C CNN
	1    8700 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:LED DSEG_x_?
U 1 1 601692CF
P 8700 4550
AR Path="/601692CF" Ref="DSEG_x_?"  Part="1" 
AR Path="/6014418F/601692CF" Ref="DSEG_x_?"  Part="1" 
AR Path="/6016F5EB/601692CF" Ref="DSEG_x_?"  Part="1" 
F 0 "DSEG_x_?" H 8700 4650 50  0000 C CNN
F 1 "LED" H 8693 4386 50  0001 C CNN
F 2 "" H 8700 4550 50  0001 C CNN
F 3 "~" H 8700 4550 50  0001 C CNN
	1    8700 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8850 4250 9050 4250
Wire Wire Line
	9050 4250 9050 4400
Wire Wire Line
	9050 4550 8850 4550
Wire Wire Line
	8550 4250 8250 4250
Wire Wire Line
	8250 4250 8250 4400
Wire Wire Line
	8250 4550 8550 4550
Connection ~ 8250 4400
Wire Wire Line
	8250 4400 8250 4550
Text Label 7500 4400 2    50   ~ 0
GPIO
Wire Wire Line
	9200 4400 9050 4400
Connection ~ 9050 4400
Wire Wire Line
	9050 4400 9050 4550
Wire Notes Line
	7250 4850 9650 4850
Wire Notes Line
	9650 4850 9650 3700
Wire Notes Line
	9650 3700 7250 3700
Wire Notes Line
	7250 3700 7250 4850
$Comp
L Device:R_Small_US R_SEG?
U 1 1 601692EB
P 7900 4400
AR Path="/601692EB" Ref="R_SEG?"  Part="1" 
AR Path="/6014418F/601692EB" Ref="R_SEG?"  Part="1" 
AR Path="/6016F5EB/601692EB" Ref="R_SEG?"  Part="1" 
F 0 "R_SEG?" V 7800 4400 50  0000 C CNN
F 1 "470" V 8000 4400 50  0000 C CNN
F 2 "" H 7900 4400 50  0001 C CNN
F 3 "~" H 7900 4400 50  0001 C CNN
	1    7900 4400
	0    1    1    0   
$EndComp
Wire Wire Line
	8000 4400 8250 4400
Wire Wire Line
	7800 4400 7500 4400
Text Notes 7350 4000 0    70   ~ 0
Every segment\n(U1: GPx0 to GPx6)
$Comp
L Device:LED D?
U 1 1 601692F4
P 8750 5700
AR Path="/601692F4" Ref="D?"  Part="1" 
AR Path="/6014418F/601692F4" Ref="D_IND"  Part="1" 
AR Path="/6016F5EB/601692F4" Ref="D_IND"  Part="1" 
F 0 "D_IND" H 8750 5800 50  0000 C CNN
F 1 "LED" H 8743 5536 50  0001 C CNN
F 2 "" H 8750 5700 50  0001 C CNN
F 3 "~" H 8750 5700 50  0001 C CNN
	1    8750 5700
	1    0    0    -1  
$EndComp
Text Label 7500 5700 2    50   ~ 0
GPIO
Wire Notes Line
	7250 6150 9650 6150
Wire Notes Line
	9650 6150 9650 5000
Wire Notes Line
	9650 5000 7250 5000
Wire Notes Line
	7250 5000 7250 6150
$Comp
L Device:R_Small_US R_IND?
U 1 1 60169305
P 7900 5700
AR Path="/60169305" Ref="R_IND?"  Part="1" 
AR Path="/6014418F/60169305" Ref="R_IND?"  Part="1" 
AR Path="/6016F5EB/60169305" Ref="R_IND?"  Part="1" 
F 0 "R_IND?" V 7800 5700 50  0000 C CNN
F 1 "1K" V 8000 5700 50  0000 C CNN
F 2 "" H 7900 5700 50  0001 C CNN
F 3 "~" H 7900 5700 50  0001 C CNN
	1    7900 5700
	0    1    1    0   
$EndComp
Wire Wire Line
	7800 5700 7500 5700
Text Notes 7350 5300 0    70   ~ 0
Every indicators (Dots)\n(U1: GPx7)
Wire Wire Line
	8000 5700 8600 5700
Wire Wire Line
	8900 5700 9200 5700
Text Notes 7250 3500 0    100  ~ 0
Display is wired up like that\nand there's nothing I can do\nbut deal with it. (A.k.a. resistors).
Text Notes 800  1000 0    200  ~ 0
Display Board #2 (Digits 2-3)
Wire Wire Line
	4300 5550 4600 5550
Wire Wire Line
	4450 5450 4450 5400
Wire Wire Line
	4450 5350 4600 5350
Wire Wire Line
	4450 5450 4600 5450
Wire Wire Line
	4300 5400 4450 5400
Connection ~ 4450 5400
Wire Wire Line
	4450 5400 4450 5350
Text Notes 1550 1450 0    138  ~ 0
- Display is Common Anode.
Text Notes 1550 1750 0    138  ~ 0
- P-FET is driven by N-FET on main PCB.
Text Notes 1550 2050 0    138  ~ 0
- 5V SCL/SDA downstream of the i²c level shifter.
$Comp
L Device:CP1 C1
U 1 1 6004EBF6
P 2150 5150
F 0 "C1" H 2200 5250 50  0000 L CNN
F 1 "47uF" H 1900 5050 50  0000 L CNN
F 2 "" H 2150 5150 50  0001 C CNN
F 3 "~" H 2150 5150 50  0001 C CNN
	1    2150 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 5000 2150 4850
Connection ~ 2150 4850
Wire Wire Line
	2150 4850 1650 4850
Wire Wire Line
	2150 5300 2150 5450
Connection ~ 2150 5450
Text Notes 1550 2350 0    138  ~ 0
- 5V SCL/SDA downstream of the i²c level shifter.
$Comp
L power:VDD #PWR?
U 1 1 6008084D
P 9200 4400
F 0 "#PWR?" H 9200 4250 50  0001 C CNN
F 1 "VDD" V 9200 4550 50  0000 L CNN
F 2 "" H 9200 4400 50  0001 C CNN
F 3 "" H 9200 4400 50  0001 C CNN
	1    9200 4400
	0    1    1    0   
$EndComp
$Comp
L power:VDD #PWR?
U 1 1 60083200
P 9200 5700
F 0 "#PWR?" H 9200 5550 50  0001 C CNN
F 1 "VDD" V 9200 5850 50  0000 L CNN
F 2 "" H 9200 5700 50  0001 C CNN
F 3 "" H 9200 5700 50  0001 C CNN
	1    9200 5700
	0    1    1    0   
$EndComp
Wire Wire Line
	2650 5450 2650 5500
Wire Wire Line
	2000 3750 2300 3750
Wire Wire Line
	2000 3850 2300 3850
Wire Wire Line
	2000 3950 2300 3950
Text Label 2300 3750 0    50   ~ 0
GND
Text Label 2300 3850 0    50   ~ 0
SDA_5V
$Comp
L Connector:Conn_01x04_Male J_OUT_D?
U 1 1 600D409F
P 1800 3850
AR Path="/600D409F" Ref="J_OUT_D?"  Part="1" 
AR Path="/6014418F/600D409F" Ref="J_OUT_D?"  Part="1" 
AR Path="/6016F5EB/600D409F" Ref="J_OUT_D?"  Part="1" 
F 0 "J_OUT_D?" H 1500 3800 50  0000 C CNN
F 1 "Conn_01x04_Male" H 1908 4040 50  0001 C CNN
F 2 "" H 1800 3850 50  0001 C CNN
F 3 "~" H 1800 3850 50  0001 C CNN
	1    1800 3850
	1    0    0    1   
$EndComp
Text Notes 1250 3400 0    100  ~ 0
From display board #1
Text Label 2300 3950 0    50   ~ 0
SCL_5V
Wire Wire Line
	2000 3650 2300 3650
Text Label 2300 3650 0    50   ~ 0
VCC
Wire Wire Line
	2150 4850 2600 4850
Wire Wire Line
	2150 5450 2650 5450
$EndSCHEMATC
