EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr User 5906 4725
encoding utf-8
Sheet 13 13
Title "ACHS-7123 Current Sensor"
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Sensor_Current:ACS712xLCTR-30A U?
U 1 1 62C41044
P 2600 1800
AR Path="/62C41044" Ref="U?"  Part="1" 
AR Path="/62C2DD72/62C41044" Ref="U?"  Part="1" 
F 0 "U?" H 2600 2381 50  0000 C CNN
F 1 "ACHS-7123" H 2600 2290 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 2700 1450 50  0001 L CIN
F 3 "https://download.kamami.pl/p586603-ACHS-712x-DS101_2018-02-28.pdf" H 2600 1800 50  0001 C CNN
	1    2600 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 1600 2050 1600
Wire Wire Line
	2200 2000 2050 2000
Wire Wire Line
	2600 2200 2600 2250
$Comp
L Device:C_Small C?
U 1 1 62C4104D
P 3100 2050
AR Path="/62C4104D" Ref="C?"  Part="1" 
AR Path="/62C2DD72/62C4104D" Ref="C?"  Part="1" 
F 0 "C?" H 3192 2096 50  0000 L CNN
F 1 "1n" H 3192 2005 50  0000 L CNN
F 2 "" H 3100 2050 50  0001 C CNN
F 3 "~" H 3100 2050 50  0001 C CNN
	1    3100 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 1900 3100 1900
Wire Wire Line
	3100 1900 3100 1950
Wire Wire Line
	3100 2150 3100 2250
Wire Wire Line
	2600 2250 3100 2250
Wire Wire Line
	3000 1800 3050 1800
$Comp
L Device:C_Small C?
U 1 1 62C4105A
P 3750 1800
AR Path="/62C4105A" Ref="C?"  Part="1" 
AR Path="/62C2DD72/62C4105A" Ref="C?"  Part="1" 
F 0 "C?" H 3842 1846 50  0000 L CNN
F 1 "1u" H 3842 1755 50  0000 L CNN
F 2 "" H 3750 1800 50  0001 C CNN
F 3 "~" H 3750 1800 50  0001 C CNN
	1    3750 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 2250 3750 1900
Wire Wire Line
	3750 1700 3750 1400
$Comp
L power:GND #PWR?
U 1 1 62C41064
P 3750 2300
AR Path="/62C41064" Ref="#PWR?"  Part="1" 
AR Path="/62C2DD72/62C41064" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 3750 2050 50  0001 C CNN
F 1 "GND" H 3755 2127 50  0000 C CNN
F 2 "" H 3750 2300 50  0001 C CNN
F 3 "" H 3750 2300 50  0001 C CNN
	1    3750 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 2250 3750 2300
Connection ~ 3750 2250
$Comp
L power:+5V #PWR?
U 1 1 62C4106C
P 3750 1350
AR Path="/62C4106C" Ref="#PWR?"  Part="1" 
AR Path="/62C2DD72/62C4106C" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 3750 1200 50  0001 C CNN
F 1 "+5V" H 3765 1523 50  0000 C CNN
F 2 "" H 3750 1350 50  0001 C CNN
F 3 "" H 3750 1350 50  0001 C CNN
	1    3750 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 1350 3750 1400
Connection ~ 3750 1400
Text HLabel 2050 1600 0    50   Input ~ 0
CS_IP+
Text HLabel 2050 2000 0    50   Output ~ 0
V_Out
Text HLabel 3050 1800 2    50   Output ~ 0
CurrentSensor
Wire Wire Line
	3100 2250 3750 2250
Connection ~ 3100 2250
Wire Wire Line
	2600 1400 3750 1400
$EndSCHEMATC
