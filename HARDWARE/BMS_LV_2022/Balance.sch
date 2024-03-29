EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 13
Title "Balance part of LTC6810"
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	5650 3850 5650 3950
Wire Wire Line
	6100 3850 6100 3950
Connection ~ 6100 3850
Wire Wire Line
	6100 3850 6350 3850
$Comp
L Device:R_Small R21
U 1 1 6199E2E8
P 5650 4050
AR Path="/61996AA1/6199D637/6199E2E8" Ref="R21"  Part="1" 
AR Path="/61996AA1/61A346F1/6199E2E8" Ref="R26"  Part="1" 
AR Path="/61996AA1/61A395F7/6199E2E8" Ref="R31"  Part="1" 
AR Path="/61996AA1/61A3A424/6199E2E8" Ref="R36"  Part="1" 
AR Path="/61996AA1/61A3B341/6199E2E8" Ref="R41"  Part="1" 
AR Path="/61996AA1/61A3CF51/6199E2E8" Ref="R46"  Part="1" 
F 0 "R26" H 5592 4004 50  0000 R CNN
F 1 "10" H 5592 4095 50  0000 R CNN
F 2 "Resistor_SMD:R_2512_6332Metric" H 5650 4050 50  0001 C CNN
F 3 "~" H 5650 4050 50  0001 C CNN
F 4 "CHP2512AFX-10R0ELF" H 5650 4050 50  0001 C CNN "Part Number"
	1    5650 4050
	1    0    0    1   
$EndComp
$Comp
L Device:R_Small R22
U 1 1 6199F863
P 6100 4050
AR Path="/61996AA1/6199D637/6199F863" Ref="R22"  Part="1" 
AR Path="/61996AA1/61A346F1/6199F863" Ref="R27"  Part="1" 
AR Path="/61996AA1/61A395F7/6199F863" Ref="R32"  Part="1" 
AR Path="/61996AA1/61A3A424/6199F863" Ref="R37"  Part="1" 
AR Path="/61996AA1/61A3B341/6199F863" Ref="R42"  Part="1" 
AR Path="/61996AA1/61A3CF51/6199F863" Ref="R47"  Part="1" 
F 0 "R27" H 6042 4004 50  0000 R CNN
F 1 "10" H 6042 4095 50  0000 R CNN
F 2 "Resistor_SMD:R_2512_6332Metric" H 6100 4050 50  0001 C CNN
F 3 "~" H 6100 4050 50  0001 C CNN
F 4 "CHP2512AFX-10R0ELF" H 6100 4050 50  0001 C CNN "Part Number"
	1    6100 4050
	1    0    0    1   
$EndComp
Wire Wire Line
	5650 3850 6100 3850
$Comp
L Device:R_Small R23
U 1 1 619A21A9
P 6450 3850
AR Path="/61996AA1/6199D637/619A21A9" Ref="R23"  Part="1" 
AR Path="/61996AA1/61A346F1/619A21A9" Ref="R28"  Part="1" 
AR Path="/61996AA1/61A395F7/619A21A9" Ref="R33"  Part="1" 
AR Path="/61996AA1/61A3A424/619A21A9" Ref="R38"  Part="1" 
AR Path="/61996AA1/61A3B341/619A21A9" Ref="R43"  Part="1" 
AR Path="/61996AA1/61A3CF51/619A21A9" Ref="R48"  Part="1" 
F 0 "R28" V 6254 3850 50  0000 C CNN
F 1 "330" V 6345 3850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 6450 3850 50  0001 C CNN
F 3 "~" H 6450 3850 50  0001 C CNN
	1    6450 3850
	0    1    1    0   
$EndComp
Wire Wire Line
	6550 3850 6700 3850
Wire Wire Line
	6700 3850 6700 4300
Wire Wire Line
	6700 4300 6550 4300
$Comp
L Device:LED_Small D6
U 1 1 619A6565
P 6450 4300
AR Path="/61996AA1/6199D637/619A6565" Ref="D6"  Part="1" 
AR Path="/61996AA1/61A346F1/619A6565" Ref="D8"  Part="1" 
AR Path="/61996AA1/61A395F7/619A6565" Ref="D10"  Part="1" 
AR Path="/61996AA1/61A3A424/619A6565" Ref="D12"  Part="1" 
AR Path="/61996AA1/61A3B341/619A6565" Ref="D14"  Part="1" 
AR Path="/61996AA1/61A3CF51/619A6565" Ref="D16"  Part="1" 
F 0 "D8" H 6450 4535 50  0000 C CNN
F 1 "LED_RED" H 6450 4444 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric" V 6450 4300 50  0001 C CNN
F 3 "~" V 6450 4300 50  0001 C CNN
	1    6450 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 4300 6100 4300
Wire Wire Line
	6100 4300 6100 4150
Wire Wire Line
	6100 4300 5650 4300
Wire Wire Line
	5650 4300 5650 4150
Connection ~ 6100 4300
Wire Wire Line
	6100 4450 6100 4300
Wire Wire Line
	6100 4850 6100 4950
Wire Wire Line
	6100 4950 6350 4950
Wire Wire Line
	6100 4950 5150 4950
Connection ~ 6100 4950
$Comp
L Device:R_Small R24
U 1 1 619B0D16
P 6450 4950
AR Path="/61996AA1/6199D637/619B0D16" Ref="R24"  Part="1" 
AR Path="/61996AA1/61A346F1/619B0D16" Ref="R29"  Part="1" 
AR Path="/61996AA1/61A395F7/619B0D16" Ref="R34"  Part="1" 
AR Path="/61996AA1/61A3A424/619B0D16" Ref="R39"  Part="1" 
AR Path="/61996AA1/61A3B341/619B0D16" Ref="R44"  Part="1" 
AR Path="/61996AA1/61A3CF51/619B0D16" Ref="R49"  Part="1" 
F 0 "R29" V 6254 4950 50  0000 C CNN
F 1 "1k" V 6345 4950 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 6450 4950 50  0001 C CNN
F 3 "~" H 6450 4950 50  0001 C CNN
	1    6450 4950
	0    1    1    0   
$EndComp
Wire Wire Line
	6750 4950 6750 4650
Wire Wire Line
	6750 4950 6750 5250
Connection ~ 6750 4950
$Comp
L Device:D_Zener_Small D7
U 1 1 619B293B
P 6450 5250
AR Path="/61996AA1/6199D637/619B293B" Ref="D7"  Part="1" 
AR Path="/61996AA1/61A346F1/619B293B" Ref="D9"  Part="1" 
AR Path="/61996AA1/61A395F7/619B293B" Ref="D11"  Part="1" 
AR Path="/61996AA1/61A3A424/619B293B" Ref="D13"  Part="1" 
AR Path="/61996AA1/61A3B341/619B293B" Ref="D15"  Part="1" 
AR Path="/61996AA1/61A3CF51/619B293B" Ref="D17"  Part="1" 
F 0 "D9" H 6450 5043 50  0000 C CNN
F 1 "D_Zener 9.1V" H 6450 5134 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-323" V 6450 5250 50  0001 C CNN
F 3 "~" V 6450 5250 50  0001 C CNN
F 4 "BZX384-C9V1.115" H 6450 5250 50  0001 C CNN "Part Number"
	1    6450 5250
	-1   0    0    1   
$EndComp
Wire Wire Line
	6350 5250 6100 5250
Wire Wire Line
	6100 5250 6100 4950
Wire Wire Line
	6100 5250 6100 5450
Connection ~ 6100 5250
Connection ~ 6750 4650
Wire Wire Line
	6750 4650 6850 4650
Wire Wire Line
	6400 4650 6750 4650
Wire Wire Line
	6550 4950 6750 4950
Wire Wire Line
	6550 5250 6750 5250
Text HLabel 6850 4650 2    50   Input ~ 0
Sx
Connection ~ 5150 3600
Text HLabel 5050 3600 0    50   Input ~ 0
Cell
$Comp
L Device:R_Small R25
U 1 1 619B7EAD
P 6950 3600
AR Path="/61996AA1/6199D637/619B7EAD" Ref="R25"  Part="1" 
AR Path="/61996AA1/61A346F1/619B7EAD" Ref="R30"  Part="1" 
AR Path="/61996AA1/61A395F7/619B7EAD" Ref="R35"  Part="1" 
AR Path="/61996AA1/61A3A424/619B7EAD" Ref="R40"  Part="1" 
AR Path="/61996AA1/61A3B341/619B7EAD" Ref="R45"  Part="1" 
AR Path="/61996AA1/61A3CF51/619B7EAD" Ref="R50"  Part="1" 
F 0 "R30" V 6754 3600 50  0000 C CNN
F 1 "100" V 6845 3600 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 6950 3600 50  0001 C CNN
F 3 "~" H 6950 3600 50  0001 C CNN
	1    6950 3600
	0    1    1    0   
$EndComp
Wire Wire Line
	5150 3600 6850 3600
Wire Wire Line
	5150 4950 5150 3600
Text HLabel 6100 3700 0    50   Input ~ 0
PreviousBalance
Wire Wire Line
	7050 3600 7150 3600
Wire Wire Line
	7150 3600 7150 3700
Wire Wire Line
	7150 3600 7300 3600
Connection ~ 7150 3600
Text HLabel 7300 3600 2    50   Input ~ 0
Cx
$Comp
L Device:C_Small C19
U 1 1 619BEE0A
P 7150 3800
AR Path="/61996AA1/6199D637/619BEE0A" Ref="C19"  Part="1" 
AR Path="/61996AA1/61A346F1/619BEE0A" Ref="C20"  Part="1" 
AR Path="/61996AA1/61A395F7/619BEE0A" Ref="C21"  Part="1" 
AR Path="/61996AA1/61A3A424/619BEE0A" Ref="C22"  Part="1" 
AR Path="/61996AA1/61A3B341/619BEE0A" Ref="C23"  Part="1" 
AR Path="/61996AA1/61A3CF51/619BEE0A" Ref="C24"  Part="1" 
F 0 "C20" H 7242 3846 50  0000 L CNN
F 1 "10nF" H 7242 3755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7150 3800 50  0001 C CNN
F 3 "~" H 7150 3800 50  0001 C CNN
	1    7150 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 3900 7150 3950
Text HLabel 6100 5450 2    50   Input ~ 0
NextBalance
$Comp
L Device:Q_NMOS_GSD Q2
U 1 1 619A7C3D
P 6200 4650
AR Path="/61996AA1/6199D637/619A7C3D" Ref="Q2"  Part="1" 
AR Path="/61996AA1/61A346F1/619A7C3D" Ref="Q3"  Part="1" 
AR Path="/61996AA1/61A395F7/619A7C3D" Ref="Q4"  Part="1" 
AR Path="/61996AA1/61A3A424/619A7C3D" Ref="Q5"  Part="1" 
AR Path="/61996AA1/61A3B341/619A7C3D" Ref="Q6"  Part="1" 
AR Path="/61996AA1/61A3CF51/619A7C3D" Ref="Q7"  Part="1" 
F 0 "Q3" H 6405 4604 50  0000 L CNN
F 1 "ZXMN3F30FHTA" H 6405 4695 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 6400 4750 50  0001 C CNN
F 3 "https://html.alldatasheet.com/html-pdf/1229711/VBSEMI/PMV213SN/252/1/PMV213SN.html" H 6200 4650 50  0001 C CNN
	1    6200 4650
	-1   0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR?
U 1 1 61F1BB4A
P 7150 3950
AR Path="/61996AA1/61F1BB4A" Ref="#PWR?"  Part="1" 
AR Path="/61996AA1/61A346F1/61F1BB4A" Ref="#PWR0113"  Part="1" 
AR Path="/61996AA1/6199D637/61F1BB4A" Ref="#PWR0112"  Part="1" 
AR Path="/61996AA1/61A395F7/61F1BB4A" Ref="#PWR0114"  Part="1" 
AR Path="/61996AA1/61A3A424/61F1BB4A" Ref="#PWR0115"  Part="1" 
AR Path="/61996AA1/61A3B341/61F1BB4A" Ref="#PWR0116"  Part="1" 
AR Path="/61996AA1/61A3CF51/61F1BB4A" Ref="#PWR0117"  Part="1" 
F 0 "#PWR0113" H 7150 3750 50  0001 C CNN
F 1 "GNDPWR" H 7154 3796 50  0000 C CNN
F 2 "" H 7150 3900 50  0001 C CNN
F 3 "" H 7150 3900 50  0001 C CNN
	1    7150 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 3850 6100 3700
Wire Wire Line
	5050 3600 5150 3600
$EndSCHEMATC
