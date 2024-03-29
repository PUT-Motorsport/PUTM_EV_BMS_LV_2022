EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 11 13
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
P 5400 3700
AR Path="/62C41044" Ref="U?"  Part="1" 
AR Path="/62C2DD72/62C41044" Ref="U5"  Part="1" 
F 0 "U5" H 5400 4281 50  0000 C CNN
F 1 "ACHS-7123" H 5400 4190 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 5500 3350 50  0001 L CIN
F 3 "https://download.kamami.pl/p586603-ACHS-712x-DS101_2018-02-28.pdf" H 5400 3700 50  0001 C CNN
	1    5400 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 3500 4850 3500
Wire Wire Line
	5000 3900 4850 3900
$Comp
L Device:C_Small C?
U 1 1 62C4104D
P 5900 3950
AR Path="/62C4104D" Ref="C?"  Part="1" 
AR Path="/62C2DD72/62C4104D" Ref="C42"  Part="1" 
F 0 "C42" H 5992 3996 50  0000 L CNN
F 1 "1nF" H 5992 3905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5900 3950 50  0001 C CNN
F 3 "~" H 5900 3950 50  0001 C CNN
	1    5900 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 3800 5900 3800
Wire Wire Line
	5900 3800 5900 3850
Wire Wire Line
	5400 4600 5900 4600
$Comp
L Device:C_Small C?
U 1 1 62C4105A
P 7300 3700
AR Path="/62C4105A" Ref="C?"  Part="1" 
AR Path="/62C2DD72/62C4105A" Ref="C43"  Part="1" 
F 0 "C43" H 7392 3746 50  0000 L CNN
F 1 "1uF" H 7392 3655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7300 3700 50  0001 C CNN
F 3 "~" H 7300 3700 50  0001 C CNN
	1    7300 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 3600 7300 3300
$Comp
L power:GND #PWR?
U 1 1 62C41064
P 7300 4650
AR Path="/62C41064" Ref="#PWR?"  Part="1" 
AR Path="/62C2DD72/62C41064" Ref="#PWR050"  Part="1" 
F 0 "#PWR050" H 7300 4400 50  0001 C CNN
F 1 "GND" H 7305 4477 50  0000 C CNN
F 2 "" H 7300 4650 50  0001 C CNN
F 3 "" H 7300 4650 50  0001 C CNN
	1    7300 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 4600 7300 4650
Connection ~ 7300 4600
$Comp
L power:+5V #PWR?
U 1 1 62C4106C
P 7300 3250
AR Path="/62C4106C" Ref="#PWR?"  Part="1" 
AR Path="/62C2DD72/62C4106C" Ref="#PWR049"  Part="1" 
F 0 "#PWR049" H 7300 3100 50  0001 C CNN
F 1 "+5V" H 7315 3423 50  0000 C CNN
F 2 "" H 7300 3250 50  0001 C CNN
F 3 "" H 7300 3250 50  0001 C CNN
	1    7300 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 3250 7300 3300
Connection ~ 7300 3300
Text HLabel 4850 3500 0    50   Input ~ 0
CS_IP+
Text HLabel 4850 3900 0    50   Output ~ 0
V_Out
Text HLabel 6650 4100 2    50   Output ~ 0
CurrentSensor
Wire Wire Line
	5400 4100 5400 4600
Wire Wire Line
	5900 4050 5900 4600
Wire Wire Line
	7300 3800 7300 4600
Wire Wire Line
	5900 4600 6400 4600
Connection ~ 5900 4600
Wire Wire Line
	5400 3300 7300 3300
$Comp
L Device:R_Small R67
U 1 1 62BB2CC9
P 6400 3900
F 0 "R67" H 6459 3946 50  0000 L CNN
F 1 "1k" H 6459 3855 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 6400 3900 50  0001 C CNN
F 3 "~" H 6400 3900 50  0001 C CNN
	1    6400 3900
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R68
U 1 1 62BB3BF9
P 6400 4300
F 0 "R68" H 6459 4346 50  0000 L CNN
F 1 "2k" H 6459 4255 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 6400 4300 50  0001 C CNN
F 3 "~" H 6400 4300 50  0001 C CNN
	1    6400 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 3700 6400 3800
Wire Wire Line
	5800 3700 6400 3700
Wire Wire Line
	6400 4000 6400 4100
Connection ~ 6400 4600
Wire Wire Line
	6400 4600 7300 4600
Wire Wire Line
	6650 4100 6400 4100
Wire Wire Line
	6400 4100 6400 4200
Connection ~ 6400 4100
Wire Wire Line
	6400 4400 6400 4600
$EndSCHEMATC
