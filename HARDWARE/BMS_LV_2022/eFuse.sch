EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 13 13
Title "eFuse"
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:+24V #PWR?
U 1 1 626B571F
P 4250 2800
AR Path="/626B571F" Ref="#PWR?"  Part="1" 
AR Path="/6269845F/626B571F" Ref="#PWR047"  Part="1" 
F 0 "#PWR047" H 4250 2650 50  0001 C CNN
F 1 "+24V" H 4265 2973 50  0000 C CNN
F 2 "" H 4250 2800 50  0001 C CNN
F 3 "" H 4250 2800 50  0001 C CNN
	1    4250 2800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 626B572C
P 5950 5200
AR Path="/626B572C" Ref="#PWR?"  Part="1" 
AR Path="/6269845F/626B572C" Ref="#PWR048"  Part="1" 
F 0 "#PWR048" H 5950 4950 50  0001 C CNN
F 1 "GND" H 5955 5027 50  0000 C CNN
F 2 "" H 5950 5200 50  0001 C CNN
F 3 "" H 5950 5200 50  0001 C CNN
	1    5950 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 4900 5150 4900
Wire Wire Line
	5950 5100 5950 5150
Wire Wire Line
	5950 4550 5950 4700
Wire Wire Line
	6550 3650 6550 3800
Wire Wire Line
	5350 3800 5350 3650
Wire Wire Line
	5950 4350 5950 3800
Wire Wire Line
	5850 3350 5850 3450
Wire Wire Line
	5850 3650 5850 3800
Wire Wire Line
	6050 3650 6050 3800
Connection ~ 6050 3800
Wire Wire Line
	6050 3800 6550 3800
Connection ~ 5950 3800
Wire Wire Line
	5950 3800 6050 3800
Wire Wire Line
	5850 3800 5950 3800
Text Label 5950 4000 3    50   ~ 0
Gate
Text Label 6550 2550 3    50   ~ 0
Gate
Wire Wire Line
	5950 2250 6350 2250
Wire Wire Line
	5850 3350 5950 3350
Wire Wire Line
	5950 3350 5950 2250
Connection ~ 5950 3350
Connection ~ 5950 5150
Wire Wire Line
	5950 5150 5950 5200
$Comp
L Device:R_Small R?
U 1 1 626B5786
P 5400 4900
AR Path="/626B5786" Ref="R?"  Part="1" 
AR Path="/6269845F/626B5786" Ref="R59"  Part="1" 
F 0 "R59" V 5204 4900 50  0000 C CNN
F 1 "100" V 5295 4900 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 5400 4900 50  0001 C CNN
F 3 "~" H 5400 4900 50  0001 C CNN
	1    5400 4900
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 626B578C
P 5700 5150
AR Path="/626B578C" Ref="R?"  Part="1" 
AR Path="/6269845F/626B578C" Ref="R60"  Part="1" 
F 0 "R60" V 5896 5150 50  0000 C CNN
F 1 "10k" V 5805 5150 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 5700 5150 50  0001 C CNN
F 3 "~" H 5700 5150 50  0001 C CNN
	1    5700 5150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5550 4900 5550 5150
Wire Wire Line
	5550 5150 5600 5150
Wire Wire Line
	5550 4900 5650 4900
Wire Wire Line
	5800 5150 5950 5150
Wire Wire Line
	5550 4900 5500 4900
Connection ~ 5550 4900
$Comp
L Device:C_Small C41
U 1 1 62872278
P 5850 3550
F 0 "C41" H 5758 3504 50  0000 R CNN
F 1 "0*" H 5758 3595 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5850 3550 50  0001 C CNN
F 3 "~" H 5850 3550 50  0001 C CNN
	1    5850 3550
	1    0    0    1   
$EndComp
$Comp
L Device:R_Small R62
U 1 1 62874194
P 6050 3550
F 0 "R62" H 6109 3596 50  0000 L CNN
F 1 "10k" H 6109 3505 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 6050 3550 50  0001 C CNN
F 3 "~" H 6050 3550 50  0001 C CNN
	1    6050 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 2250 5950 2250
Connection ~ 5950 2250
Wire Wire Line
	5350 3800 5850 3800
Connection ~ 5850 3800
Wire Wire Line
	5550 3350 5850 3350
Connection ~ 5850 3350
Wire Wire Line
	5150 3350 5100 3350
Wire Wire Line
	5150 2250 5100 2250
Wire Wire Line
	6800 2800 6900 2800
Wire Wire Line
	6800 2800 6800 2250
Connection ~ 6800 2800
Wire Wire Line
	6800 3350 6800 2800
Wire Wire Line
	6750 2250 6800 2250
Wire Wire Line
	6800 3350 6750 3350
$Comp
L Device:Fuse F2
U 1 1 6287D375
P 7050 2800
F 0 "F2" V 6853 2800 50  0000 C CNN
F 1 "Fuse" V 6944 2800 50  0000 C CNN
F 2 "footprints:3557-2" V 6980 2800 50  0001 C CNN
F 3 "~" H 7050 2800 50  0001 C CNN
F 4 "3557-2" H 7050 2800 50  0001 C CNN "Part Number"
	1    7050 2800
	0    1    1    0   
$EndComp
Text HLabel 5150 4900 0    50   Input ~ 0
Switch_Signal
$Comp
L Device:R_Small R61
U 1 1 62887CEF
P 5950 4450
F 0 "R61" H 6009 4496 50  0000 L CNN
F 1 "100" H 6009 4405 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 5950 4450 50  0001 C CNN
F 3 "~" H 5950 4450 50  0001 C CNN
	1    5950 4450
	1    0    0    -1  
$EndComp
Text Label 5350 2550 3    50   ~ 0
Gate
Text HLabel 7800 2800 2    50   Output ~ 0
CurrentSensor_IP+
Wire Wire Line
	5100 2250 5100 2800
Connection ~ 5100 2800
Wire Wire Line
	5100 2800 5100 3350
Wire Wire Line
	4850 2800 4850 2650
Connection ~ 4850 2800
Wire Wire Line
	4850 2800 5100 2800
Text HLabel 4850 2250 1    50   Output ~ 0
VCC_Pin
Wire Wire Line
	4850 2350 4850 2250
$Comp
L Device:Polyfuse F1
U 1 1 61C9E38A
P 4850 2500
F 0 "F1" H 4938 2546 50  0000 L CNN
F 1 "Polyfuse" H 4938 2455 50  0000 L CNN
F 2 "Fuse:Fuse_1206_3216Metric" H 4900 2300 50  0001 L CNN
F 3 "https://pl.mouser.com/datasheet/2/643/ds_CP_0zcj_series-1664160.pdf" H 4850 2500 50  0001 C CNN
F 4 "0ZCJ0020FF2E" H 5200 2650 50  0001 C CNN "Part Number"
	1    4850 2500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4250 2800 4850 2800
$Comp
L Transistor_FET:BSS138 Q?
U 1 1 626B577C
P 5850 4900
AR Path="/626B577C" Ref="Q?"  Part="1" 
AR Path="/6269845F/626B577C" Ref="Q10"  Part="1" 
F 0 "Q10" H 6054 4946 50  0000 L CNN
F 1 "BSS138" H 6054 4855 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 6050 4825 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/BSS138-D.PDF" H 5850 4900 50  0001 L CNN
	1    5850 4900
	1    0    0    -1  
$EndComp
$Comp
L BMS_LV_2022-rescue:SiSS27DN-Transistor_FET Q8
U 1 1 61EA3DB0
P 5350 2350
AR Path="/61EA3DB0" Ref="Q8"  Part="1" 
AR Path="/6269845F/61EA3DB0" Ref="Q8"  Part="1" 
F 0 "Q8" V 5692 2350 50  0000 C CNN
F 1 "SiSS05DN" V 5601 2350 50  0000 C CNN
F 2 "Package_SO:Vishay_PowerPAK_1212-8_Single" H 5550 2275 50  0001 L CIN
F 3 "https://www.farnell.com/datasheets/2818743.pdf" V 5350 2350 50  0001 L CNN
F 4 "SISS05DN-T1-GE3" V 5601 2350 50  0001 C CNN "Part Number"
	1    5350 2350
	0    -1   -1   0   
$EndComp
$Comp
L BMS_LV_2022-rescue:SiSS27DN-Transistor_FET Q9
U 1 1 61EA59E3
P 5350 3450
AR Path="/61EA59E3" Ref="Q9"  Part="1" 
AR Path="/6269845F/61EA59E3" Ref="Q9"  Part="1" 
F 0 "Q9" V 5692 3450 50  0000 C CNN
F 1 "SiSS05DN" V 5601 3450 50  0000 C CNN
F 2 "Package_SO:Vishay_PowerPAK_1212-8_Single" H 5550 3375 50  0001 L CIN
F 3 "https://www.farnell.com/datasheets/2818743.pdf" V 5350 3450 50  0001 L CNN
F 4 "SISS05DN-T1-GE3" H 5350 3450 50  0001 C CNN "Part Number"
	1    5350 3450
	0    -1   -1   0   
$EndComp
$Comp
L BMS_LV_2022-rescue:SiSS27DN-Transistor_FET Q11
U 1 1 61EA704A
P 6550 2350
AR Path="/61EA704A" Ref="Q11"  Part="1" 
AR Path="/6269845F/61EA704A" Ref="Q11"  Part="1" 
F 0 "Q11" V 6892 2350 50  0000 C CNN
F 1 "SiSS05DN" V 6801 2350 50  0000 C CNN
F 2 "Package_SO:Vishay_PowerPAK_1212-8_Single" H 6750 2275 50  0001 L CIN
F 3 "https://www.farnell.com/datasheets/2818743.pdf" V 6550 2350 50  0001 L CNN
F 4 "SISS05DN-T1-GE3" H 6550 2350 50  0001 C CNN "Part Number"
	1    6550 2350
	0    1    -1   0   
$EndComp
$Comp
L BMS_LV_2022-rescue:SiSS27DN-Transistor_FET Q12
U 1 1 61EA8267
P 6550 3450
AR Path="/61EA8267" Ref="Q12"  Part="1" 
AR Path="/6269845F/61EA8267" Ref="Q12"  Part="1" 
F 0 "Q12" V 6892 3450 50  0000 C CNN
F 1 "SiSS05DN" V 6801 3450 50  0000 C CNN
F 2 "Package_SO:Vishay_PowerPAK_1212-8_Single" H 6750 3375 50  0001 L CIN
F 3 "https://www.farnell.com/datasheets/2818743.pdf" V 6550 3450 50  0001 L CNN
F 4 "SISS05DN-T1-GE3" H 6550 3450 50  0001 C CNN "Part Number"
	1    6550 3450
	0    1    -1   0   
$EndComp
Wire Wire Line
	5950 3350 6050 3350
Wire Wire Line
	6050 3350 6350 3350
Connection ~ 6050 3350
Wire Wire Line
	6050 3350 6050 3450
$Comp
L power:PWR_FLAG #FLG0106
U 1 1 61ECFB96
P 3950 2800
F 0 "#FLG0106" H 3950 2875 50  0001 C CNN
F 1 "PWR_FLAG" H 3950 2973 50  0000 C CNN
F 2 "" H 3950 2800 50  0001 C CNN
F 3 "~" H 3950 2800 50  0001 C CNN
	1    3950 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 2800 3950 2800
Connection ~ 4250 2800
$Comp
L Device:R_Small R65
U 1 1 61EF9D80
P 7400 3000
F 0 "R65" H 7459 3046 50  0000 L CNN
F 1 "20k" H 7459 2955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 7400 3000 50  0001 C CNN
F 3 "~" H 7400 3000 50  0001 C CNN
	1    7400 3000
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R66
U 1 1 61EFA7A0
P 7400 3400
F 0 "R66" H 7459 3446 50  0000 L CNN
F 1 "2,7k" H 7459 3355 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 7400 3400 50  0001 C CNN
F 3 "~" H 7400 3400 50  0001 C CNN
	1    7400 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 2900 7400 2800
Wire Wire Line
	7200 2800 7400 2800
Wire Wire Line
	7400 3100 7400 3200
Wire Wire Line
	7400 3500 7400 3600
$Comp
L power:GND #PWR?
U 1 1 61EFD62C
P 7400 3600
AR Path="/61EFD62C" Ref="#PWR?"  Part="1" 
AR Path="/6269845F/61EFD62C" Ref="#PWR0101"  Part="1" 
F 0 "#PWR0101" H 7400 3350 50  0001 C CNN
F 1 "GND" H 7405 3427 50  0000 C CNN
F 2 "" H 7400 3600 50  0001 C CNN
F 3 "" H 7400 3600 50  0001 C CNN
	1    7400 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 2800 7800 2800
Connection ~ 7400 2800
Wire Wire Line
	7400 3200 7800 3200
Connection ~ 7400 3200
Wire Wire Line
	7400 3200 7400 3300
Text HLabel 7800 3200 2    50   Output ~ 0
VoltageFuseMeasure
$EndSCHEMATC
