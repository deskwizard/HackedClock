EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 1 4
Title "Hacked Clock"
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 9350 1650 2    200  ~ 0
Display Boards
$Sheet
S 7450 2200 1750 850 
U 6014418F
F0 "Display Board 1" 100
F1 "display board 1.sch" 100
$EndSheet
$Sheet
S 7450 3850 1750 850 
U 6016F5EB
F0 "display board 2" 100
F1 "display board 2.sch" 100
$EndSheet
$Sheet
S 1850 1350 1750 850 
U 6004B0A4
F0 "Power Input/Supply" 100
F1 "power.sch" 100
$EndSheet
$Comp
L Connector:Conn_01x05_Male J_DISP?
U 1 1 600947A0
P 1900 5100
AR Path="/6004B0A4/600947A0" Ref="J_DISP?"  Part="1" 
AR Path="/600947A0" Ref="J_DISP?"  Part="1" 
F 0 "J_DISP?" H 2000 5450 50  0000 C CNN
F 1 "Conn_01x05_Male" H 2008 5390 50  0001 C CNN
F 2 "" H 1900 5100 50  0001 C CNN
F 3 "~" H 1900 5100 50  0001 C CNN
	1    1900 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 4900 2550 4900
Wire Wire Line
	2100 5000 2550 5000
Wire Wire Line
	2100 5100 2550 5100
Wire Wire Line
	2100 5200 2550 5200
Text Label 2550 5200 0    50   ~ 0
GND
Text Label 2550 4900 0    50   ~ 0
SCL
Text Label 2550 5000 0    50   ~ 0
SDA
$Comp
L Connector:Conn_01x05_Male J_KP?
U 1 1 600947AF
P 1900 3500
AR Path="/6004B0A4/600947AF" Ref="J_KP?"  Part="1" 
AR Path="/600947AF" Ref="J_KP?"  Part="1" 
F 0 "J_KP?" H 1950 3850 50  0000 C CNN
F 1 "Conn_01x05_Male" H 2008 3790 50  0001 C CNN
F 2 "" H 1900 3500 50  0001 C CNN
F 3 "~" H 1900 3500 50  0001 C CNN
	1    1900 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 3300 2550 3300
Wire Wire Line
	2100 3400 2550 3400
Wire Wire Line
	2100 3500 2550 3500
Wire Wire Line
	2100 3600 2550 3600
Wire Wire Line
	2100 3700 2550 3700
Text Label 2550 3500 0    50   ~ 0
VCC
Text Label 2550 3600 0    50   ~ 0
GND
Text Label 2550 3300 0    50   ~ 0
SCL
Text Label 2550 3400 0    50   ~ 0
SDA
Text Label 2550 3700 0    50   ~ 0
GPIO_18
Text Label 2550 5100 0    50   ~ 0
GPIO_21
Wire Wire Line
	2100 4200 2550 4200
Wire Wire Line
	2100 4400 2550 4400
Wire Wire Line
	2100 4500 2550 4500
Text Label 2550 4400 0    50   ~ 0
VCC
Text Label 2550 4500 0    50   ~ 0
GND
Text Label 2550 4200 0    50   ~ 0
SCL
Text Label 2550 4300 0    50   ~ 0
SDA
Wire Wire Line
	2100 4300 2550 4300
$Comp
L Connector:Conn_01x04_Male J_RTC?
U 1 1 600947C8
P 1900 4300
AR Path="/6004B0A4/600947C8" Ref="J_RTC?"  Part="1" 
AR Path="/600947C8" Ref="J_RTC?"  Part="1" 
F 0 "J_RTC?" H 2000 4550 50  0000 C CNN
F 1 "Conn_01x04_Male" H 2008 4490 50  0001 C CNN
F 2 "" H 1900 4300 50  0001 C CNN
F 3 "~" H 1900 4300 50  0001 C CNN
	1    1900 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 5300 2450 5300
$Comp
L power:+5V #PWR?
U 1 1 601C1AD7
P 2450 5300
F 0 "#PWR?" H 2450 5150 50  0001 C CNN
F 1 "+5V" V 2450 5400 50  0000 L CNN
F 2 "" H 2450 5300 50  0001 C CNN
F 3 "" H 2450 5300 50  0001 C CNN
	1    2450 5300
	0    1    1    0   
$EndComp
$EndSCHEMATC
