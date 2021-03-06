EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 2 4
Title "Hacked Clock"
Date ""
Rev ""
Comp ""
Comment1 "Display Board #2"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Interface_Expansion:MCP23017_SP U?
U 1 1 6013E151
P 5300 4900
AR Path="/6013E151" Ref="U?"  Part="1" 
AR Path="/6014418F/6013E151" Ref="U?"  Part="1" 
AR Path="/6016F5EB/6013E151" Ref="U2"  Part="1" 
F 0 "U?" H 5000 5900 50  0000 C CNN
F 1 "MCP23017" H 5600 5900 50  0000 C CNN
F 2 "Package_DIP:DIP-28_W7.62mm" H 5500 3900 50  0001 L CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/20001952C.pdf" H 5500 3800 50  0001 L CNN
	1    5300 4900
	1    0    0    -1  
$EndComp
NoConn ~ 4600 4700
NoConn ~ 4600 4800
Text Label 4600 4100 2    50   ~ 0
SDA_5V
Text Label 4600 4200 2    50   ~ 0
SCL_5V
Text Label 3750 5000 2    50   ~ 0
VCC
$Comp
L Device:R_Small_US R_RST?
U 1 1 6013E15C
P 4150 5000
AR Path="/6013E15C" Ref="R_RST?"  Part="1" 
AR Path="/6014418F/6013E15C" Ref="R_RST?"  Part="1" 
AR Path="/6016F5EB/6013E15C" Ref="R_RST2"  Part="1" 
F 0 "R_RST?" V 4050 5000 50  0000 C CNN
F 1 "10K" V 4250 5000 50  0000 C CNN
F 2 "" H 4150 5000 50  0001 C CNN
F 3 "~" H 4150 5000 50  0001 C CNN
	1    4150 5000
	0    1    1    0   
$EndComp
Wire Wire Line
	4250 5000 4600 5000
Wire Wire Line
	3750 5000 4050 5000
Text Label 4300 5700 2    50   ~ 0
VCC
Text Label 4300 5600 2    50   ~ 0
GND
Text Notes 4050 5650 2    70   ~ 0
ADDR = 0x25
$Comp
L power:GND #PWR?
U 1 1 6013E167
P 5300 6100
AR Path="/6013E167" Ref="#PWR?"  Part="1" 
AR Path="/6014418F/6013E167" Ref="#PWR?"  Part="1" 
AR Path="/6016F5EB/6013E167" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 5300 5850 50  0001 C CNN
F 1 "GND" H 5305 5927 50  0000 C CNN
F 2 "" H 5300 6100 50  0001 C CNN
F 3 "" H 5300 6100 50  0001 C CNN
	1    5300 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 6000 5300 6100
Wire Wire Line
	6000 5000 6200 5000
Wire Wire Line
	6200 5100 6000 5100
Wire Wire Line
	6000 5200 6200 5200
Wire Wire Line
	6200 5300 6000 5300
Wire Wire Line
	6200 5400 6000 5400
Wire Wire Line
	6000 5500 6200 5500
Wire Wire Line
	6000 5600 6200 5600
Wire Wire Line
	6000 5700 6200 5700
Wire Wire Line
	6000 4800 6200 4800
Wire Wire Line
	6000 4700 6200 4700
Wire Wire Line
	6000 4600 6200 4600
Wire Wire Line
	6000 4500 6200 4500
Wire Wire Line
	6000 4400 6200 4400
Wire Wire Line
	6000 4300 6200 4300
Wire Wire Line
	6000 4200 6200 4200
Wire Wire Line
	6000 4100 6200 4100
Wire Wire Line
	5300 3100 5300 3200
$Comp
L power:+5V #PWR?
U 1 1 6013E17F
P 5300 3100
AR Path="/6013E17F" Ref="#PWR?"  Part="1" 
AR Path="/6014418F/6013E17F" Ref="#PWR?"  Part="1" 
AR Path="/6016F5EB/6013E17F" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 5300 2950 50  0001 C CNN
F 1 "+5V" H 5250 3250 50  0000 L CNN
F 2 "" H 5300 3100 50  0001 C CNN
F 3 "" H 5300 3100 50  0001 C CNN
	1    5300 3100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 6013E185
P 4800 3350
AR Path="/6013E185" Ref="C?"  Part="1" 
AR Path="/6014418F/6013E185" Ref="C?"  Part="1" 
AR Path="/6016F5EB/6013E185" Ref="C3"  Part="1" 
F 0 "C?" H 4915 3396 50  0000 L CNN
F 1 "0.1uF" H 4915 3305 50  0000 L CNN
F 2 "" H 4838 3200 50  0001 C CNN
F 3 "~" H 4800 3350 50  0001 C CNN
	1    4800 3350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6013E18B
P 4800 3500
AR Path="/6013E18B" Ref="#PWR?"  Part="1" 
AR Path="/6014418F/6013E18B" Ref="#PWR?"  Part="1" 
AR Path="/6016F5EB/6013E18B" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 4800 3250 50  0001 C CNN
F 1 "GND" H 4805 3327 50  0000 C CNN
F 2 "" H 4800 3500 50  0001 C CNN
F 3 "" H 4800 3500 50  0001 C CNN
	1    4800 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 3200 5300 3200
Connection ~ 5300 3200
Wire Wire Line
	5300 3200 5300 3800
$Comp
L Device:LED DSEG_x_?
U 1 1 6013E194
P 8700 4400
AR Path="/6013E194" Ref="DSEG_x_?"  Part="1" 
AR Path="/6014418F/6013E194" Ref="DSEG_x_?"  Part="1" 
AR Path="/6016F5EB/6013E194" Ref="DSEG_x_?"  Part="1" 
F 0 "DSEG_x_?" H 8700 4500 50  0000 C CNN
F 1 "LED" H 8693 4236 50  0001 C CNN
F 2 "" H 8700 4400 50  0001 C CNN
F 3 "~" H 8700 4400 50  0001 C CNN
	1    8700 4400
	1    0    0    -1  
$EndComp
$Comp
L Device:LED DSEG_x_?
U 1 1 6013E1B7
P 8700 4700
AR Path="/6013E1B7" Ref="DSEG_x_?"  Part="1" 
AR Path="/6014418F/6013E1B7" Ref="DSEG_x_?"  Part="1" 
AR Path="/6016F5EB/6013E1B7" Ref="DSEG_x_?"  Part="1" 
F 0 "DSEG_x_?" H 8700 4800 50  0000 C CNN
F 1 "LED" H 8693 4536 50  0001 C CNN
F 2 "" H 8700 4700 50  0001 C CNN
F 3 "~" H 8700 4700 50  0001 C CNN
	1    8700 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	8850 4400 9050 4400
Wire Wire Line
	9050 4400 9050 4550
Wire Wire Line
	9050 4700 8850 4700
Wire Wire Line
	8550 4400 8250 4400
Wire Wire Line
	8250 4400 8250 4550
Wire Wire Line
	8250 4700 8550 4700
Connection ~ 8250 4550
Wire Wire Line
	8250 4550 8250 4700
Text Label 7500 4550 2    50   ~ 0
GPIO
Wire Wire Line
	9200 4550 9050 4550
Connection ~ 9050 4550
Wire Wire Line
	9050 4550 9050 4700
Wire Notes Line
	7250 5000 9650 5000
Wire Notes Line
	9650 5000 9650 3850
Wire Notes Line
	9650 3850 7250 3850
Wire Notes Line
	7250 3850 7250 5000
$Comp
L Device:R_Small_US R_SEG?
U 1 1 6013E1CD
P 7900 4550
AR Path="/6013E1CD" Ref="R_SEG?"  Part="1" 
AR Path="/6014418F/6013E1CD" Ref="R_SEG?"  Part="1" 
AR Path="/6016F5EB/6013E1CD" Ref="R_SEG?"  Part="1" 
F 0 "R_SEG?" V 7800 4550 50  0000 C CNN
F 1 "470" V 8000 4550 50  0000 C CNN
F 2 "" H 7900 4550 50  0001 C CNN
F 3 "~" H 7900 4550 50  0001 C CNN
	1    7900 4550
	0    1    1    0   
$EndComp
Wire Wire Line
	8000 4550 8250 4550
Wire Wire Line
	7800 4550 7500 4550
$Comp
L Device:LED D_IND?
U 1 1 6013E1D6
P 8750 5850
AR Path="/6013E1D6" Ref="D_IND?"  Part="1" 
AR Path="/6014418F/6013E1D6" Ref="D_IND?"  Part="1" 
AR Path="/6016F5EB/6013E1D6" Ref="D_IND?"  Part="1" 
F 0 "D_IND?" H 8750 5950 50  0000 C CNN
F 1 "LED" H 8743 5686 50  0001 C CNN
F 2 "" H 8750 5850 50  0001 C CNN
F 3 "~" H 8750 5850 50  0001 C CNN
	1    8750 5850
	1    0    0    -1  
$EndComp
Text Label 7500 5850 2    50   ~ 0
GPIO
Wire Notes Line
	7250 6300 9650 6300
Wire Notes Line
	9650 6300 9650 5150
Wire Notes Line
	9650 5150 7250 5150
Wire Notes Line
	7250 5150 7250 6300
$Comp
L Device:R_Small_US R_IND?
U 1 1 6013E1E1
P 7900 5850
AR Path="/6013E1E1" Ref="R_IND?"  Part="1" 
AR Path="/6014418F/6013E1E1" Ref="R_IND?"  Part="1" 
AR Path="/6016F5EB/6013E1E1" Ref="R_IND?"  Part="1" 
F 0 "R_IND?" V 7800 5850 50  0000 C CNN
F 1 "1K" V 8000 5850 50  0000 C CNN
F 2 "" H 7900 5850 50  0001 C CNN
F 3 "~" H 7900 5850 50  0001 C CNN
	1    7900 5850
	0    1    1    0   
$EndComp
Wire Wire Line
	7800 5850 7500 5850
Wire Wire Line
	8000 5850 8600 5850
Wire Wire Line
	8900 5850 9200 5850
Text Notes 7250 3650 0    100  ~ 0
Display is wired up like that\nand there's nothing I can do\nbut deal with it. (A.k.a. resistors).
Wire Wire Line
	4300 5700 4600 5700
$Comp
L power:VDD #PWR?
U 1 1 6013E20B
P 9200 4550
F 0 "#PWR?" H 9200 4400 50  0001 C CNN
F 1 "VDD" V 9200 4700 50  0000 L CNN
F 2 "" H 9200 4550 50  0001 C CNN
F 3 "" H 9200 4550 50  0001 C CNN
	1    9200 4550
	0    1    1    0   
$EndComp
$Comp
L power:VDD #PWR?
U 1 1 6013E211
P 9200 5850
F 0 "#PWR?" H 9200 5700 50  0001 C CNN
F 1 "VDD" V 9200 6000 50  0000 L CNN
F 2 "" H 9200 5850 50  0001 C CNN
F 3 "" H 9200 5850 50  0001 C CNN
	1    9200 5850
	0    1    1    0   
$EndComp
Wire Wire Line
	4300 5600 4600 5600
Text Label 4300 5500 2    50   ~ 0
VCC
Wire Wire Line
	4300 5500 4600 5500
Text Notes 7350 4250 0    70   ~ 0
Every segment\n(GPA0 to GPA6)\n(GPB1, GPB2)
Text Notes 7350 5450 0    70   ~ 0
Every indicators (Dots)\nGPA7, GPB0, GPB3-GPB5, GPB7
$Comp
L power:+5V #PWR?
U 1 1 600DD874
P 2650 5000
AR Path="/600DD874" Ref="#PWR?"  Part="1" 
AR Path="/6014418F/600DD874" Ref="#PWR?"  Part="1" 
AR Path="/6016F5EB/600DD874" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 2650 4850 50  0001 C CNN
F 1 "+5V" V 2550 5000 50  0000 L CNN
F 2 "" H 2650 5000 50  0001 C CNN
F 3 "" H 2650 5000 50  0001 C CNN
	1    2650 5000
	0    1    1    0   
$EndComp
Text Label 1700 5000 2    50   ~ 0
VCC
Wire Wire Line
	1700 5600 2200 5600
$Comp
L power:GND #PWR?
U 1 1 600DD87D
P 2700 5650
AR Path="/600DD87D" Ref="#PWR?"  Part="1" 
AR Path="/6014418F/600DD87D" Ref="#PWR?"  Part="1" 
AR Path="/6016F5EB/600DD87D" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 2700 5400 50  0001 C CNN
F 1 "GND" H 2705 5477 50  0000 C CNN
F 2 "" H 2700 5650 50  0001 C CNN
F 3 "" H 2700 5650 50  0001 C CNN
	1    2700 5650
	1    0    0    -1  
$EndComp
Text Label 1700 5600 2    50   ~ 0
GND
$Comp
L Device:CP1 C?
U 1 1 600DD884
P 2200 5300
F 0 "C?" H 2250 5400 50  0000 L CNN
F 1 "220uF" H 1950 5200 50  0000 L CNN
F 2 "" H 2200 5300 50  0001 C CNN
F 3 "~" H 2200 5300 50  0001 C CNN
	1    2200 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 5150 2200 5000
Connection ~ 2200 5000
Wire Wire Line
	2200 5000 1700 5000
Wire Wire Line
	2200 5450 2200 5600
Connection ~ 2200 5600
Wire Wire Line
	2700 5600 2700 5650
Text Notes 800  1150 0    200  ~ 0
Display Board #1 (Digits 0-1)
Wire Wire Line
	2050 3350 2300 3350
Wire Wire Line
	2050 3450 2300 3450
Wire Wire Line
	2050 3550 2300 3550
Wire Wire Line
	2050 3650 2300 3650
Text Label 2300 3450 0    50   ~ 0
PWM
Wire Wire Line
	2050 4350 2350 4350
Wire Wire Line
	2050 4450 2350 4450
Wire Wire Line
	2050 4550 2350 4550
Text Label 2350 4350 0    50   ~ 0
GND
Text Label 2350 4450 0    50   ~ 0
SDA_5V
Text Label 2350 4550 0    50   ~ 0
SCL_5V
$Comp
L Connector:Conn_01x04_Male J_OUT?
U 1 1 600E0EBE
P 1850 4450
AR Path="/600E0EBE" Ref="J_OUT?"  Part="1" 
AR Path="/6014418F/600E0EBE" Ref="J_OUT?"  Part="1" 
AR Path="/6016F5EB/600E0EBE" Ref="J_OUT?"  Part="1" 
F 0 "J_OUT?" H 1550 4450 50  0000 C CNN
F 1 "Conn_01x04_Male" H 1958 4640 50  0001 C CNN
F 2 "" H 1850 4450 50  0001 C CNN
F 3 "~" H 1850 4450 50  0001 C CNN
	1    1850 4450
	1    0    0    1   
$EndComp
$Comp
L Connector:Conn_01x05_Male J_IN_D?
U 1 1 600E0EC4
P 1850 3450
AR Path="/600E0EC4" Ref="J_IN_D?"  Part="1" 
AR Path="/6014418F/600E0EC4" Ref="J_IN_D?"  Part="1" 
AR Path="/6016F5EB/600E0EC4" Ref="J_IN_D?"  Part="1" 
F 0 "J_IN_D?" H 1550 3450 50  0000 C CNN
F 1 "Conn_01x05_Male" H 1958 3740 50  0001 C CNN
F 2 "" H 1850 3450 50  0001 C CNN
F 3 "~" H 1850 3450 50  0001 C CNN
	1    1850 3450
	1    0    0    1   
$EndComp
Text Label 2300 3550 0    50   ~ 0
SDA_5V
Text Label 2300 3650 0    50   ~ 0
SCL_5V
Text Label 2300 3350 0    50   ~ 0
GND
Text Notes 1150 1550 0    138  ~ 0
- Display is Common Anode.
Text Notes 1150 1850 0    138  ~ 0
- P-FET is driven by N-FET on main PCB.
Text Notes 1150 2150 0    138  ~ 0
- 5V SCL/SDA downstream of the i²c level shifter.
Text Notes 1150 2450 0    138  ~ 0
- 5V SCL/SDA downstream of the i²c level shifter.
Wire Wire Line
	2200 7350 2650 7350
$Comp
L power:VDD #PWR?
U 1 1 602B758C
P 2650 7350
AR Path="/6016F5EB/602B758C" Ref="#PWR?"  Part="1" 
AR Path="/6014418F/602B758C" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 2650 7200 50  0001 C CNN
F 1 "VDD" V 2650 7500 50  0000 L CNN
F 2 "" H 2650 7350 50  0001 C CNN
F 3 "" H 2650 7350 50  0001 C CNN
	1    2650 7350
	0    1    1    0   
$EndComp
Wire Wire Line
	2700 6450 2200 6450
$Comp
L power:+5V #PWR?
U 1 1 602B7593
P 2700 6450
AR Path="/602B7593" Ref="#PWR?"  Part="1" 
AR Path="/6014418F/602B7593" Ref="#PWR?"  Part="1" 
AR Path="/6016F5EB/602B7593" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 2700 6300 50  0001 C CNN
F 1 "+5V" V 2700 6550 50  0000 L CNN
F 2 "" H 2700 6450 50  0001 C CNN
F 3 "" H 2700 6450 50  0001 C CNN
	1    2700 6450
	0    1    1    0   
$EndComp
Wire Wire Line
	2200 7150 2200 7350
Text Label 1200 6950 2    50   ~ 0
PWM
Wire Wire Line
	1700 6950 1200 6950
Wire Wire Line
	1700 6950 1900 6950
Connection ~ 1700 6950
Wire Wire Line
	1700 6850 1700 6950
Wire Wire Line
	2200 6450 2200 6650
Wire Wire Line
	2200 6650 2200 6750
Connection ~ 2200 6650
Wire Wire Line
	1700 6650 2200 6650
$Comp
L Device:R_Small_US R?
U 1 1 602B75A3
P 1700 6750
AR Path="/602B75A3" Ref="R?"  Part="1" 
AR Path="/6014418F/602B75A3" Ref="R?"  Part="1" 
AR Path="/6016F5EB/602B75A3" Ref="R?"  Part="1" 
F 0 "R?" H 1850 6650 50  0000 C CNN
F 1 "10K" H 1850 6750 50  0000 C CNN
F 2 "" H 1700 6750 50  0001 C CNN
F 3 "~" H 1700 6750 50  0001 C CNN
	1    1700 6750
	-1   0    0    1   
$EndComp
$Comp
L Transistor_FET:AO3401A Q?
U 1 1 602B75A9
P 2100 6950
AR Path="/602B75A9" Ref="Q?"  Part="1" 
AR Path="/6014418F/602B75A9" Ref="Q?"  Part="1" 
AR Path="/6016F5EB/602B75A9" Ref="Q?"  Part="1" 
F 0 "Q?" H 1950 7100 50  0000 L CNN
F 1 "AO3401A" H 2250 6850 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 2300 6875 50  0001 L CIN
F 3 "http://www.aosmd.com/pdfs/datasheet/AO3401A.pdf" H 2100 6950 50  0001 L CNN
	1    2100 6950
	1    0    0    1   
$EndComp
Text Notes 1500 3100 0    100  ~ 0
From main PCB
Text Notes 1450 4100 0    100  ~ 0
To Display #2 board
Wire Wire Line
	2050 4250 2350 4250
Wire Wire Line
	2050 3250 2300 3250
Text Label 2350 4250 0    50   ~ 0
VCC
Text Label 2300 3250 0    50   ~ 0
VCC
Wire Wire Line
	2200 5000 2650 5000
Wire Wire Line
	2200 5600 2700 5600
$EndSCHEMATC
