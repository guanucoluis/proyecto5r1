EESchema Schematic File Version 2
LIBS:power,device,conn,linear,regul,74xx,cmos4000,adc-dac,memory,xilinx,special,microcontrollers,dsp,microchip,analog_switches,motorola,texas,intel,audio,interface,digital-audio,philips,display,cypress,siliconi,contrib,valves
EELAYER 43  0
EELAYER END
$Descr A4 11700 8267
Sheet 1 1
Title ""
Date "29 aug 2009"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	5000 3550 5000 3700
Wire Wire Line
	8950 4600 8950 4750
Connection ~ 8350 4950
Wire Wire Line
	9050 4950 9050 4600
Connection ~ 5100 4850
Wire Wire Line
	4350 4850 5200 4850
Wire Wire Line
	5200 4850 5200 4500
Connection ~ 2850 4000
Wire Wire Line
	2850 4000 2850 3250
Wire Wire Line
	2850 3250 3850 3250
Connection ~ 7050 4100
Wire Wire Line
	7050 4100 7050 3350
Wire Wire Line
	7050 3350 7800 3350
Wire Wire Line
	9550 4200 9900 4200
Connection ~ 8350 4100
Wire Wire Line
	8350 4350 8350 4100
Wire Wire Line
	7650 4100 7750 4100
Wire Wire Line
	5600 4100 5800 4100
Connection ~ 4350 4000
Wire Wire Line
	4350 4300 4350 4000
Wire Wire Line
	2700 4000 2950 4000
Wire Wire Line
	1350 4000 1550 4000
Wire Wire Line
	2050 4000 2200 4000
Wire Wire Line
	3450 4000 3650 4000
Wire Wire Line
	4150 4000 4600 4000
Wire Wire Line
	4350 4700 4350 4950
Wire Wire Line
	6300 4100 6450 4100
Wire Wire Line
	6950 4100 7150 4100
Wire Wire Line
	8250 4100 8550 4100
Wire Wire Line
	8350 4750 8350 5000
Wire Wire Line
	8550 4300 8450 4300
Wire Wire Line
	8450 4300 8450 3350
Wire Wire Line
	8450 3350 8200 3350
Wire Wire Line
	4600 4200 4450 4200
Wire Wire Line
	4450 4200 4450 3250
Wire Wire Line
	4450 3250 4250 3250
Wire Wire Line
	5100 4850 5100 4500
Connection ~ 4350 4850
Wire Wire Line
	5000 4500 5000 4650
Wire Wire Line
	9150 4600 9150 4950
Wire Wire Line
	9150 4950 8350 4950
Connection ~ 9050 4950
Wire Wire Line
	8950 3800 8950 3650
$Comp
L -5V #PWR?
U 1 1 4A99C951
P 5000 4650
F 0 "#PWR?" H 5000 4790 20  0001 C C
F 1 "-5V" H 5000 4760 30  0000 C C
	1    5000 4650
	-1   0    0    1   
$EndComp
$Comp
L -5V #PWR?
U 1 1 4A99C93E
P 8950 4750
F 0 "#PWR?" H 8950 4890 20  0001 C C
F 1 "-5V" H 8950 4860 30  0000 C C
	1    8950 4750
	-1   0    0    1   
$EndComp
$Comp
L +5V #PWR?
U 1 1 4A99C925
P 8950 3650
F 0 "#PWR?" H 8950 3740 20  0001 C C
F 1 "+5V" H 8950 3740 30  0000 C C
	1    8950 3650
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 4A99C8DA
P 5000 3550
F 0 "#PWR?" H 5000 3640 20  0001 C C
F 1 "+5V" H 5000 3640 30  0000 C C
	1    5000 3550
	1    0    0    -1  
$EndComp
$Comp
L LM741 U?
U 1 1 4A99C13E
P 5100 4100
F 0 "U?" H 5250 4250 60  0000 C C
F 1 "LM741" H 5250 4350 60  0000 C C
	1    5100 4100
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 4A99C529
P 8000 3350
F 0 "C?" H 8050 3450 50  0000 L C
F 1 "3.3 nF" H 8050 3250 50  0000 L C
	1    8000 3350
	0    1    1    0   
$EndComp
$Comp
L C C?
U 1 1 4A99C522
P 8350 4550
F 0 "C?" H 8400 4650 50  0000 L C
F 1 "2.7 nF" H 8400 4450 50  0000 L C
	1    8350 4550
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 4A99C475
P 8000 4100
F 0 "R?" V 8080 4100 50  0000 C C
F 1 "12000" V 8000 4100 50  0000 C C
	1    8000 4100
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 4A99C46F
P 7400 4100
F 0 "R?" V 7480 4100 50  0000 C C
F 1 "4700" V 7400 4100 50  0000 C C
	1    7400 4100
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 4A99C466
P 6700 4100
F 0 "R?" V 6780 4100 50  0000 C C
F 1 "10000" V 6700 4100 50  0000 C C
	1    6700 4100
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 4A99C462
P 6050 4100
F 0 "R?" V 6130 4100 50  0000 C C
F 1 "820" V 6050 4100 50  0000 C C
	1    6050 4100
	0    1    1    0   
$EndComp
$Comp
L C C?
U 1 1 4A99C437
P 4050 3250
F 0 "C?" H 4100 3350 50  0000 L C
F 1 "22 nF" H 4100 3150 50  0000 L C
	1    4050 3250
	0    1    1    0   
$EndComp
$Comp
L C C?
U 1 1 4A99C40C
P 4350 4500
F 0 "C?" H 4400 4600 50  0000 L C
F 1 "2.7 nF" H 4400 4400 50  0000 L C
	1    4350 4500
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 4A99C3B9
P 3900 4000
F 0 "R?" V 3980 4000 50  0000 C C
F 1 "6800" V 3900 4000 50  0000 C C
	1    3900 4000
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 4A99C3B6
P 3200 4000
F 0 "R?" V 3280 4000 50  0000 C C
F 1 "1200" V 3200 4000 50  0000 C C
	1    3200 4000
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 4A99C375
P 2450 4000
F 0 "R?" V 2530 4000 50  0000 C C
F 1 "3300" V 2450 4000 50  0000 C C
	1    2450 4000
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 4A99C35A
P 1800 4000
F 0 "R?" V 1880 4000 50  0000 C C
F 1 "150" V 1800 4000 50  0000 C C
	1    1800 4000
	0    1    1    0   
$EndComp
$Comp
L CONN_1 P?
U 1 1 4A99C312
P 10050 4200
F 0 "P?" H 10130 4200 40  0000 L C
F 1 "CONN_1" H 10050 4255 30  0001 C C
	1    10050 4200
	1    0    0    -1  
$EndComp
$Comp
L CONN_1 P?
U 1 1 4A99C258
P 1200 4000
F 0 "P?" H 1280 4000 40  0000 L C
F 1 "CONN_1" H 1200 4055 30  0001 C C
	1    1200 4000
	-1   0    0    1   
$EndComp
$Comp
L LM741 U?
U 1 1 4A99C145
P 9050 4200
F 0 "U?" H 9200 4350 60  0000 C C
F 1 "LM741" H 9200 4450 60  0000 C C
	1    9050 4200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 4A99C0FB
P 8350 5000
F 0 "#PWR?" H 8350 5000 30  0001 C C
F 1 "GND" H 8350 4930 30  0001 C C
	1    8350 5000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 4A99C0E5
P 4350 4950
F 0 "#PWR?" H 4350 4950 30  0001 C C
F 1 "GND" H 4350 4880 30  0001 C C
	1    4350 4950
	1    0    0    -1  
$EndComp
$EndSCHEMATC
