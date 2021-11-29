EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr User 7087 5906
encoding utf-8
Sheet 12 13
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
P 2550 1450
AR Path="/626B571F" Ref="#PWR?"  Part="1" 
AR Path="/6269845F/626B571F" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 2550 1300 50  0001 C CNN
F 1 "+24V" H 2565 1623 50  0000 C CNN
F 2 "" H 2550 1450 50  0001 C CNN
F 3 "" H 2550 1450 50  0001 C CNN
	1    2550 1450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 626B572C
P 3600 3850
AR Path="/626B572C" Ref="#PWR?"  Part="1" 
AR Path="/6269845F/626B572C" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 3600 3600 50  0001 C CNN
F 1 "GND" H 3605 3677 50  0000 C CNN
F 2 "" H 3600 3850 50  0001 C CNN
F 3 "" H 3600 3850 50  0001 C CNN
	1    3600 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 3550 2800 3550
Wire Wire Line
	3600 3750 3600 3800
Wire Wire Line
	3600 3200 3600 3350
Wire Wire Line
	4200 2300 4200 2450
Wire Wire Line
	3000 2450 3000 2300
Wire Wire Line
	3600 3000 3600 2450
Wire Wire Line
	3500 2000 3500 2100
Wire Wire Line
	3500 2300 3500 2450
Wire Wire Line
	3700 2000 3700 2100
Connection ~ 3700 2000
Wire Wire Line
	3700 2000 4000 2000
Wire Wire Line
	3700 2300 3700 2450
Connection ~ 3700 2450
Wire Wire Line
	3700 2450 4200 2450
Connection ~ 3600 2450
Wire Wire Line
	3600 2450 3700 2450
Wire Wire Line
	3500 2450 3600 2450
Text Label 3600 2650 3    50   ~ 0
Gate
Text Label 4200 1200 3    50   ~ 0
Gate
Wire Wire Line
	3600 900  4000 900 
Wire Wire Line
	3500 2000 3600 2000
Wire Wire Line
	2750 2000 2750 1450
Wire Wire Line
	3600 2000 3600 900 
Connection ~ 3600 2000
Wire Wire Line
	3600 2000 3700 2000
Connection ~ 2750 1450
Wire Wire Line
	2750 1450 2750 900 
$Comp
L Transistor_FET:BSS138 Q?
U 1 1 626B577C
P 3500 3550
AR Path="/626B577C" Ref="Q?"  Part="1" 
AR Path="/6269845F/626B577C" Ref="Q?"  Part="1" 
F 0 "Q?" H 3704 3596 50  0000 L CNN
F 1 "BSS138" H 3704 3505 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 3700 3475 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/BSS138-D.PDF" H 3500 3550 50  0001 L CNN
	1    3500 3550
	1    0    0    -1  
$EndComp
Connection ~ 3600 3800
Wire Wire Line
	3600 3800 3600 3850
$Comp
L Device:R_Small R?
U 1 1 626B5786
P 3050 3550
AR Path="/626B5786" Ref="R?"  Part="1" 
AR Path="/6269845F/626B5786" Ref="R?"  Part="1" 
F 0 "R?" V 2854 3550 50  0000 C CNN
F 1 "100" V 2945 3550 50  0000 C CNN
F 2 "" H 3050 3550 50  0001 C CNN
F 3 "~" H 3050 3550 50  0001 C CNN
	1    3050 3550
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 626B578C
P 3350 3800
AR Path="/626B578C" Ref="R?"  Part="1" 
AR Path="/6269845F/626B578C" Ref="R?"  Part="1" 
F 0 "R?" V 3546 3800 50  0000 C CNN
F 1 "10k" V 3455 3800 50  0000 C CNN
F 2 "" H 3350 3800 50  0001 C CNN
F 3 "~" H 3350 3800 50  0001 C CNN
	1    3350 3800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3200 3550 3200 3800
Wire Wire Line
	3200 3800 3250 3800
Wire Wire Line
	3200 3550 3300 3550
Wire Wire Line
	3450 3800 3600 3800
Wire Wire Line
	3200 3550 3150 3550
Connection ~ 3200 3550
$Comp
L Device:C_Small C?
U 1 1 62872278
P 3500 2200
F 0 "C?" H 3408 2154 50  0000 R CNN
F 1 "C_Small" H 3408 2245 50  0000 R CNN
F 2 "" H 3500 2200 50  0001 C CNN
F 3 "~" H 3500 2200 50  0001 C CNN
	1    3500 2200
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 62874194
P 3700 2200
F 0 "R?" H 3759 2246 50  0000 L CNN
F 1 "R_Small" H 3759 2155 50  0000 L CNN
F 2 "" H 3700 2200 50  0001 C CNN
F 3 "~" H 3700 2200 50  0001 C CNN
	1    3700 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 900  3600 900 
Connection ~ 3600 900 
Wire Wire Line
	3000 2450 3500 2450
Connection ~ 3500 2450
Wire Wire Line
	3200 2000 3500 2000
Connection ~ 3500 2000
Wire Wire Line
	2800 2000 2750 2000
Wire Wire Line
	2800 900  2750 900 
Wire Wire Line
	4950 1450 4850 1450
Wire Wire Line
	4450 1450 4550 1450
Wire Wire Line
	4450 1450 4450 900 
Connection ~ 4450 1450
Wire Wire Line
	4450 2000 4450 1450
Wire Wire Line
	4400 900  4450 900 
Wire Wire Line
	4450 2000 4400 2000
Wire Wire Line
	2550 1450 2750 1450
$Comp
L Device:Fuse F?
U 1 1 6287D375
P 4700 1450
F 0 "F?" V 4503 1450 50  0000 C CNN
F 1 "Fuse" V 4594 1450 50  0000 C CNN
F 2 "" V 4630 1450 50  0001 C CNN
F 3 "~" H 4700 1450 50  0001 C CNN
	1    4700 1450
	0    1    1    0   
$EndComp
$Comp
L Device:Q_PMOS_GDS Q?
U 1 1 6287F1CD
P 3000 2100
F 0 "Q?" V 3342 2100 50  0000 C CNN
F 1 "Q_PMOS_GDS" V 3251 2100 50  0000 C CNN
F 2 "" H 3200 2200 50  0001 C CNN
F 3 "~" H 3000 2100 50  0001 C CNN
	1    3000 2100
	0    -1   -1   0   
$EndComp
$Comp
L Device:Q_PMOS_GDS Q?
U 1 1 62882C0C
P 3000 1000
F 0 "Q?" V 3342 1000 50  0000 C CNN
F 1 "Q_PMOS_GDS" V 3251 1000 50  0000 C CNN
F 2 "" H 3200 1100 50  0001 C CNN
F 3 "~" H 3000 1000 50  0001 C CNN
	1    3000 1000
	0    -1   -1   0   
$EndComp
$Comp
L Device:Q_PMOS_GDS Q?
U 1 1 62883BEA
P 4200 2100
F 0 "Q?" V 4542 2100 50  0000 C CNN
F 1 "Q_PMOS_GDS" V 4451 2100 50  0000 C CNN
F 2 "" H 4400 2200 50  0001 C CNN
F 3 "~" H 4200 2100 50  0001 C CNN
	1    4200 2100
	0    1    -1   0   
$EndComp
$Comp
L Device:Q_PMOS_GDS Q?
U 1 1 62886B18
P 4200 1000
F 0 "Q?" V 4542 1000 50  0000 C CNN
F 1 "Q_PMOS_GDS" V 4451 1000 50  0000 C CNN
F 2 "" H 4400 1100 50  0001 C CNN
F 3 "~" H 4200 1000 50  0001 C CNN
	1    4200 1000
	0    -1   -1   0   
$EndComp
Text HLabel 2800 3550 0    50   Input ~ 0
Switch_Signal
$Comp
L Device:R_Small R?
U 1 1 62887CEF
P 3600 3100
F 0 "R?" H 3659 3146 50  0000 L CNN
F 1 "R_Small" H 3659 3055 50  0000 L CNN
F 2 "" H 3600 3100 50  0001 C CNN
F 3 "~" H 3600 3100 50  0001 C CNN
	1    3600 3100
	1    0    0    -1  
$EndComp
Text Label 3000 1200 3    50   ~ 0
Gate
Text HLabel 4950 1450 2    50   Output ~ 0
CurrentSensor_IP+
$EndSCHEMATC
