EESchema Schematic File Version 2
LIBS:./MC1496,/home/leo/Escritorio/MC1496,power,device,conn,linear,regul,74xx,cmos4000,adc-dac,memory,xilinx,special,microcontrollers,dsp,microchip,analog_switches,motorola,texas,intel,audio,interface,digital-audio,philips,display,cypress,siliconi,contrib,valves
EELAYER 24  0
EELAYER END
$Descr A4 11700 8267
Sheet 1 1
Title ""
Date "5 sep 2009"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Connection ~ 6350 5700
Wire Wire Line
	6350 5700 4300 5700
Wire Wire Line
	4300 5700 4300 5500
Wire Wire Line
	3150 3850 5550 3850
Connection ~ 5000 3850
Wire Wire Line
	5000 4700 5000 3850
Connection ~ 4050 3400
Wire Wire Line
	4050 2150 4050 3400
Wire Wire Line
	7350 4850 7350 5200
Connection ~ 8550 2150
Wire Wire Line
	5750 2150 8550 2150
Wire Wire Line
	7350 2450 7350 2300
Wire Wire Line
	7350 2300 7250 2300
Wire Wire Line
	8150 4100 9100 4100
Wire Wire Line
	4550 5200 4550 5350
Wire Wire Line
	5000 5200 5300 5200
Wire Wire Line
	4800 2400 4800 2300
Wire Wire Line
	8700 2550 8700 2450
Wire Wire Line
	8700 2450 8400 2450
Wire Wire Line
	8400 2450 8400 2550
Connection ~ 8400 3200
Wire Wire Line
	8200 3200 9100 3200
Wire Wire Line
	8400 3050 8400 3200
Wire Wire Line
	8550 1950 8550 2450
Connection ~ 8550 2450
Wire Wire Line
	4550 2150 5250 2150
Wire Wire Line
	5100 2450 5100 2300
Connection ~ 4950 2150
Wire Wire Line
	3150 3400 3350 3400
Wire Wire Line
	4950 2900 4950 3000
Wire Wire Line
	5100 2850 5100 2900
Wire Wire Line
	5100 2900 4800 2900
Connection ~ 4950 2900
Wire Wire Line
	4950 2150 4950 2300
Wire Wire Line
	5100 2300 4800 2300
Connection ~ 4950 2300
Wire Wire Line
	5150 5400 5150 5200
Connection ~ 5150 5200
Wire Wire Line
	4050 5200 4050 5350
Wire Wire Line
	7350 5700 7350 5950
Wire Wire Line
	8700 4100 8700 3050
Connection ~ 8700 4100
Wire Wire Line
	6750 2300 6650 2300
Wire Wire Line
	6650 2300 6650 2450
Wire Wire Line
	4950 2300 5550 2300
Wire Wire Line
	5550 2300 5550 2950
Wire Wire Line
	6350 5900 6350 4850
Wire Wire Line
	3750 3400 5550 3400
Wire Wire Line
	5550 4300 4550 4300
Wire Wire Line
	4550 4300 4550 4700
Wire Wire Line
	5300 4700 5300 4300
Connection ~ 5300 4300
Wire Wire Line
	4050 4700 4050 3850
Connection ~ 4050 3850
$Comp
L MC1496 U?
U 1 1 4AA27D4D
P 6850 3650
F 0 "U?" H 6850 3650 60  0000 C C
F 1 "MC1496" H 6850 3650 60  0000 C C
	1    6850 3650
	1    0    0    -1  
$EndComp
$Comp
L POT RV?
U 1 1 4AA1F9EB
P 4300 5350
F 0 "RV?" H 4300 5250 50  0000 C C
F 1 "50K" H 4300 5350 50  0000 C C
	1    4300 5350
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR?
U 1 1 4AA1F847
P 5150 5400
F 0 "#PWR?" H 5150 5400 30  0001 C C
F 1 "GND" H 5150 5330 30  0001 C C
	1    5150 5400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 4AA1F83B
P 7350 5950
F 0 "#PWR?" H 7350 5950 30  0001 C C
F 1 "GND" H 7350 5880 30  0001 C C
	1    7350 5950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 4AA1F834
P 4950 3000
F 0 "#PWR?" H 4950 3000 30  0001 C C
F 1 "GND" H 4950 2930 30  0001 C C
	1    4950 3000
	1    0    0    -1  
$EndComp
$Comp
L CONN_1 Vs
U 1 1 4AA1F7C4
P 3000 3850
F 0 "Vs" H 3080 3850 40  0000 L C
F 1 "CONN_1" H 3000 3905 30  0001 C C
	1    3000 3850
	-1   0    0    1   
$EndComp
$Comp
L CONN_1 Vc
U 1 1 4AA1F7B1
P 3000 3400
F 0 "Vc" H 3080 3400 40  0000 L C
F 1 "CONN_1" H 3000 3455 30  0001 C C
	1    3000 3400
	-1   0    0    1   
$EndComp
$Comp
L CONN_1 -Vo
U 1 1 4AA1F7A4
P 9250 4100
F 0 "-Vo" H 9330 4100 40  0000 L C
F 1 "CONN_1" H 9250 4155 30  0001 C C
	1    9250 4100
	1    0    0    -1  
$EndComp
$Comp
L CONN_1 +Vo
U 1 1 4AA1F799
P 9250 3200
F 0 "+Vo" H 9330 3200 40  0000 L C
F 1 "CONN_1" H 9250 3255 30  0001 C C
	1    9250 3200
	1    0    0    -1  
$EndComp
$Comp
L -8V #PWR?
U 1 1 4AA1F777
P 6350 5900
F 0 "#PWR?" H 6350 6030 20  0001 C C
F 1 "-8V" H 6350 6000 30  0000 C C
	1    6350 5900
	-1   0    0    1   
$EndComp
$Comp
L +12V #PWR?
U 1 1 4AA1F766
P 8550 1950
F 0 "#PWR?" H 8550 1900 20  0001 C C
F 1 "+12V" H 8550 2050 30  0000 C C
	1    8550 1950
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 4AA1F741
P 3550 3400
F 0 "C?" H 3600 3500 50  0000 L C
F 1 "100nF" H 3600 3300 50  0000 L C
	1    3550 3400
	0    1    1    0   
$EndComp
$Comp
L C C?
U 1 1 4AA1F71C
P 5100 2650
F 0 "C?" H 5150 2750 50  0000 L C
F 1 "100nF" H 5150 2550 50  0000 L C
	1    5100 2650
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 4AA1F6FF
P 4800 2650
F 0 "R?" V 4880 2650 50  0000 C C
F 1 "1K" V 4800 2650 50  0000 C C
	1    4800 2650
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 4AA1F6C4
P 4300 2150
F 0 "R?" V 4380 2150 50  0000 C C
F 1 "51" V 4300 2150 50  0000 C C
	1    4300 2150
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 4AA1F6AC
P 4050 4950
F 0 "R?" V 4130 4950 50  0000 C C
F 1 "10K" V 4050 4950 50  0000 C C
	1    4050 4950
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 4AA1F6A4
P 4550 4950
F 0 "R?" V 4630 4950 50  0000 C C
F 1 "10K" V 4550 4950 50  0000 C C
	1    4550 4950
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 4AA1F69A
P 5000 4950
F 0 "R?" V 5080 4950 50  0000 C C
F 1 "51" V 5000 4950 50  0000 C C
	1    5000 4950
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 4AA1F68F
P 5300 4950
F 0 "R?" V 5380 4950 50  0000 C C
F 1 "51" V 5300 4950 50  0000 C C
	1    5300 4950
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 4AA1F67E
P 7350 5450
F 0 "R?" V 7430 5450 50  0000 C C
F 1 "6.8K" V 7350 5450 50  0000 C C
	1    7350 5450
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 4AA1F674
P 5500 2150
F 0 "R?" V 5580 2150 50  0000 C C
F 1 "1K" V 5500 2150 50  0000 C C
	1    5500 2150
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 4AA1F663
P 8700 2800
F 0 "R?" V 8780 2800 50  0000 C C
F 1 "3.9K" V 8700 2800 50  0000 C C
	1    8700 2800
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 4AA1F65E
P 8400 2800
F 0 "R?" V 8480 2800 50  0000 C C
F 1 "3.9K" V 8400 2800 50  0000 C C
	1    8400 2800
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 4AA1F649
P 7000 2300
F 0 "R?" V 7080 2300 50  0000 C C
F 1 "1K" V 7000 2300 50  0000 C C
	1    7000 2300
	0    1    1    0   
$EndComp
$EndSCHEMATC
