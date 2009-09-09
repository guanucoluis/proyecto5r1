EESchema Schematic File Version 2  date 09/09/2009 12:52:27
LIBS:power,device,transistors,conn,linear,regul,74xx,cmos4000,adc-dac,memory,xilinx,special,microcontrollers,dsp,microchip,analog_switches,motorola,texas,intel,audio,interface,digital-audio,philips,display,cypress,siliconi,opto,atmel,contrib,valves,.\esquematico.cache
EELAYER 24  0
EELAYER END
$Descr A4 11700 8267
Sheet 1 1
Title ""
Date "9 sep 2009"
Rev "1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L SG3525A U?
U 1 1 4AA7CB0A
P 4300 5200
F 0 "U?" H 4300 6050 70  0000 C CNN
F 1 "SG3525A" H 4300 4350 70  0000 C CNN
	1    4300 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	9750 1050 9000 1050
Connection ~ 7550 1450
Connection ~ 8250 1050
Wire Wire Line
	8250 1050 8250 1850
Wire Wire Line
	8250 1850 8050 1850
Wire Wire Line
	7650 1050 7550 1050
Wire Wire Line
	7550 1350 7550 1550
Wire Wire Line
	6750 1650 6650 1650
Connection ~ 4900 1250
Wire Wire Line
	6750 1250 4900 1250
Wire Wire Line
	5000 700  4900 700 
Connection ~ 4900 2800
Wire Wire Line
	4900 2900 4900 2150
Wire Wire Line
	4900 2150 5000 2150
Wire Wire Line
	5000 1100 4900 1100
Connection ~ 4200 2800
Wire Wire Line
	4200 2450 4200 2800
Wire Wire Line
	4600 1950 3100 1950
Wire Wire Line
	4900 1100 4900 1750
Wire Wire Line
	4600 900  3100 900 
Wire Wire Line
	3100 2250 3100 2800
Wire Wire Line
	3850 1300 3850 1350
Wire Wire Line
	1700 2500 2000 2500
Wire Wire Line
	1700 1150 2000 1150
Wire Wire Line
	2000 1550 2000 2100
Connection ~ 1700 1650
Wire Wire Line
	2300 1650 1700 1650
Wire Wire Line
	2300 2050 2000 2050
Connection ~ 2000 2050
Wire Wire Line
	1700 1550 1700 2100
Wire Wire Line
	1850 1050 1850 1150
Connection ~ 1850 1150
Wire Wire Line
	1850 2600 1850 2500
Connection ~ 1850 2500
Wire Wire Line
	3850 2350 3850 2400
Wire Wire Line
	3100 900  3100 1450
Wire Wire Line
	3100 2800 4900 2800
Wire Wire Line
	5000 1750 3100 1750
Connection ~ 4900 1750
Wire Wire Line
	6250 1650 6200 1650
Wire Wire Line
	7550 1850 7650 1850
Wire Wire Line
	8050 1050 8400 1050
Wire Wire Line
	9450 1450 9450 1550
Wire Wire Line
	9750 1450 7550 1450
Connection ~ 9450 1450
Wire Wire Line
	4150 1400 4150 1750
Connection ~ 4150 1750
Text Notes 9100 1300 0    60   ~ 0
HFC
$Comp
L CONN_1 P4
U 1 1 4AA7B812
P 9900 1450
F 0 "P4" H 9980 1450 40  0000 L CNN
F 1 "Vout_gnd" H 9900 1505 30  0000 C CNN
	1    9900 1450
	1    0    0    -1  
$EndComp
$Comp
L CONN_1 P3
U 1 1 4AA7B80E
P 9900 1050
F 0 "P3" H 9980 1050 40  0000 L CNN
F 1 "+Vout" H 9900 1105 30  0000 C CNN
	1    9900 1050
	1    0    0    -1  
$EndComp
$Comp
L VSS #PWR4
U 1 1 4AA7B7D6
P 9450 1550
F 0 "#PWR4" H 9450 1550 30  0001 C CNN
F 1 "VSS" H 9450 1480 30  0000 C CNN
	1    9450 1550
	1    0    0    -1  
$EndComp
$Comp
L CAPAPOL C2
U 1 1 4AA7B797
P 9450 1250
F 0 "C2" H 9500 1350 50  0000 L CNN
F 1 "100uF/63v" H 9550 1250 50  0000 L CNN
	1    9450 1250
	1    0    0    -1  
$EndComp
$Comp
L INDUCTOR L1
U 1 1 4AA7B76A
P 8700 1050
F 0 "L1" V 8650 1050 40  0000 C CNN
F 1 "INDUCTOR" V 8800 1050 40  0000 C CNN
	1    8700 1050
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D12
U 1 1 4AA7B724
P 7850 1850
F 0 "D12" H 7850 1950 40  0000 C CNN
F 1 "MUR820" H 7850 1750 40  0000 C CNN
	1    7850 1850
	1    0    0    -1  
$EndComp
$Comp
L DIODE D11
U 1 1 4AA7B71C
P 7850 1050
F 0 "D11" H 7850 1150 40  0000 C CNN
F 1 "MUR420" H 7850 950 40  0000 C CNN
	1    7850 1050
	1    0    0    -1  
$EndComp
$Comp
L CONN_1 P2
U 1 1 4AA7B68B
P 6050 1650
F 0 "P2" H 6000 1550 40  0000 L CNN
F 1 "V_Power in/2" H 6050 1705 30  0000 C CNN
	1    6050 1650
	-1   0    0    1   
$EndComp
$Comp
L CAPAPOL C1
U 1 1 4AA7B669
P 6450 1650
F 0 "C1" H 6500 1750 50  0000 L CNN
F 1 "470nF / 250v" V 6250 1600 50  0000 L CNN
	1    6450 1650
	0    -1   -1   0   
$EndComp
$Comp
L TRANSFO2 T2
U 1 1 4AA7B63D
P 7150 1450
F 0 "T2" H 7150 1950 70  0000 C CNN
F 1 "T_POWER" H 7150 950 70  0000 C CNN
	1    7150 1450
	1    0    0    -1  
$EndComp
$Comp
L CONN_1 P1
U 1 1 4AA7B50D
P 4950 550
F 0 "P1" V 4950 300 40  0000 L CNN
F 1 "V_Power in" V 4900 350 30  0000 C CNN
	1    4950 550 
	0    -1   -1   0   
$EndComp
$Comp
L VSS #PWR3
U 1 1 4AA7B45E
P 4900 2900
F 0 "#PWR3" H 4900 2900 30  0001 C CNN
F 1 "VSS" H 4900 2830 30  0000 C CNN
	1    4900 2900
	1    0    0    -1  
$EndComp
$Comp
L DIODE D10
U 1 1 4AA7B3B7
P 5000 1950
F 0 "D10" V 5200 1850 40  0000 C CNN
F 1 "DIODE" H 4750 1900 40  0000 C CNN
	1    5000 1950
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D9
U 1 1 4AA7B3AB
P 5000 900
F 0 "D9" V 5150 800 40  0000 C CNN
F 1 "DIODE" H 4800 850 40  0000 C CNN
	1    5000 900 
	0    -1   -1   0   
$EndComp
$Comp
L R R2
U 1 1 4AA7B33F
P 4200 2200
F 0 "R2" V 4280 2200 50  0000 C CNN
F 1 "1K" V 4200 2200 50  0000 C CNN
	1    4200 2200
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 4AA7B337
P 4150 1150
F 0 "R1" V 4230 1150 50  0000 C CNN
F 1 "1K" V 4150 1150 50  0000 C CNN
	1    4150 1150
	1    0    0    -1  
$EndComp
$Comp
L MOSFET_N Q2
U 1 1 4AA7B31F
P 4800 1950
F 0 "Q2" H 4800 1750 60  0000 R CNN
F 1 "IRF820" H 5550 1950 60  0000 R CNN
	1    4800 1950
	1    0    0    -1  
$EndComp
$Comp
L MOSFET_N Q1
U 1 1 4AA7B313
P 4800 900
F 0 "Q1" H 4810 1070 60  0000 R CNN
F 1 "IRF820" H 5550 950 60  0000 R CNN
	1    4800 900 
	1    0    0    -1  
$EndComp
$Comp
L ZENER D5
U 1 1 4AA7B19A
P 3850 1100
F 0 "D5" H 3850 1200 50  0000 C CNN
F 1 "15v/0.5w" H 3850 1000 40  0000 C CNN
	1    3850 1100
	0    -1   -1   0   
$EndComp
$Comp
L ZENER D6
U 1 1 4AA7B191
P 3850 1550
F 0 "D6" H 3850 1650 50  0000 C CNN
F 1 "15v/0.5w" H 3850 1450 40  0000 C CNN
	1    3850 1550
	0    1    1    0   
$EndComp
$Comp
L ZENER D8
U 1 1 4AA7B166
P 3850 2600
F 0 "D8" H 3850 2700 50  0000 C CNN
F 1 "15v/0.5w" H 3850 2500 40  0000 C CNN
	1    3850 2600
	0    1    1    0   
$EndComp
$Comp
L ZENER D7
U 1 1 4AA7B151
P 3850 2150
F 0 "D7" H 3850 2250 50  0000 C CNN
F 1 "15v/0.5w" H 3850 2050 40  0000 C CNN
	1    3850 2150
	0    -1   -1   0   
$EndComp
$Comp
L VSS #PWR2
U 1 1 4AA7B021
P 1850 2600
F 0 "#PWR2" H 1850 2600 30  0001 C CNN
F 1 "VSS" H 1850 2530 30  0000 C CNN
	1    1850 2600
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR1
U 1 1 4AA7AFC8
P 1850 1050
F 0 "#PWR1" H 1850 1000 20  0001 C CNN
F 1 "+12V" H 1850 1150 30  0000 C CNN
	1    1850 1050
	1    0    0    -1  
$EndComp
$Comp
L DIODE D1
U 1 1 4AA7AF52
P 1700 1350
F 0 "D1" H 1700 1450 40  0000 C CNN
F 1 "DIODE" H 1700 1250 40  0000 C CNN
	1    1700 1350
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D2
U 1 1 4AA7AF34
P 1700 2300
F 0 "D2" H 1700 2400 40  0000 C CNN
F 1 "DIODE" H 1700 2200 40  0000 C CNN
	1    1700 2300
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D3
U 1 1 4AA7AF26
P 2000 1350
F 0 "D3" H 2000 1450 40  0000 C CNN
F 1 "DIODE" H 2000 1250 40  0000 C CNN
	1    2000 1350
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D4
U 1 1 4AA7AF19
P 2000 2300
F 0 "D4" H 2000 2400 40  0000 C CNN
F 1 "DIODE" H 2000 2200 40  0000 C CNN
	1    2000 2300
	0    -1   -1   0   
$EndComp
$Comp
L TRANSFO2 T1
U 1 1 4AA7AEFE
P 2700 1850
F 0 "T1" H 2700 2350 70  0000 C CNN
F 1 "TRANSFO2" H 2700 1350 70  0000 C CNN
	1    2700 1850
	1    0    0    -1  
$EndComp
$EndSCHEMATC
