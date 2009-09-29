EESchema Schematic File Version 2
LIBS:power,device,conn,linear,regul,74xx,cmos4000,adc-dac,memory,xilinx,special,microcontrollers,dsp,microchip,analog_switches,motorola,texas,intel,audio,interface,digital-audio,philips,display,cypress,siliconi,contrib,valves,./Teclado6botones.cache
EELAYER 23  0
EELAYER END
$Descr A3 16535 11700
Sheet 1 1
Title ""
Date "17 aug 2009"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	5950 4300 9700 4300
Wire Wire Line
	5950 4100 7500 4100
Wire Wire Line
	5950 3900 6900 3900
Wire Wire Line
	6300 7400 6300 7300
Connection ~ 10000 6800
Connection ~ 9400 6800
Connection ~ 8200 5150
Connection ~ 9800 5700
Connection ~ 9200 5700
Connection ~ 7200 5700
Connection ~ 7800 5700
Connection ~ 8200 6300
Connection ~ 8800 6300
Connection ~ 8800 5700
Connection ~ 8800 5150
Connection ~ 8200 5700
Connection ~ 8100 4200
Wire Wire Line
	8100 4500 8100 4200
Connection ~ 7800 5100
Wire Wire Line
	7800 5000 7800 5100
Connection ~ 10000 5950
Wire Wire Line
	10000 5950 7800 5950
Wire Wire Line
	7800 5950 7800 5700
Wire Wire Line
	10000 6800 10000 5050
Wire Wire Line
	10000 5050 9700 5050
Wire Wire Line
	9700 5050 9700 4900
Wire Wire Line
	9800 5150 8800 5150
Wire Wire Line
	9800 5150 9800 5700
Connection ~ 9350 5150
Wire Wire Line
	9350 4900 9350 5150
Wire Wire Line
	9350 4500 9350 4200
Wire Wire Line
	7500 5300 9200 5300
Wire Wire Line
	7500 5300 7500 5000
Wire Wire Line
	8200 6300 8200 5400
Wire Wire Line
	7200 4500 7200 4000
Wire Wire Line
	8200 5150 6900 5150
Wire Wire Line
	6900 3900 6900 4500
Wire Wire Line
	6900 5000 6900 5700
Wire Wire Line
	6900 5700 7200 5700
Connection ~ 6900 5150
Wire Wire Line
	7200 5000 7200 5400
Wire Wire Line
	7200 5400 8200 5400
Wire Wire Line
	7500 4100 7500 4500
Wire Wire Line
	9400 6800 9200 6800
Wire Wire Line
	9200 6800 9200 5300
Wire Wire Line
	8800 5150 8800 5700
Wire Wire Line
	9700 4300 9700 4500
Wire Wire Line
	10000 6300 8800 6300
Connection ~ 10000 6300
Wire Wire Line
	6600 5100 6600 4400
Wire Wire Line
	6600 5100 8100 5100
Wire Wire Line
	8100 5100 8100 5000
Wire Wire Line
	7800 4500 7800 4300
Connection ~ 7800 4300
Wire Wire Line
	5800 7350 5900 7350
Wire Wire Line
	5900 7350 5900 7300
Wire Wire Line
	7200 4000 5950 4000
Wire Wire Line
	9350 4200 5950 4200
Wire Wire Line
	6600 4400 5950 4400
Text Label 6100 4400 0    60   ~
VDD
Text Label 6100 4300 0    60   ~
TECLADO_I2
Text Label 6100 4200 0    60   ~
TECLADO_I1
Text Label 6100 4100 0    60   ~
TECLADO_O3
Text Label 6100 4000 0    60   ~
TECLADO_O2
Text Label 6100 3900 0    60   ~
TECLADO_O1
$Comp
L +3.3V #PWR01
U 1 1 4A6660E0
P 5800 7350
F 0 "#PWR01" H 5800 7310 30  0001 C C
F 1 "+3.3V" H 5800 7460 30  0000 C C
	1    5800 7350
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG02
U 1 1 4A6660D8
P 5900 7300
F 0 "#FLG02" H 5900 7570 30  0001 C C
F 1 "PWR_FLAG" H 5900 7530 30  0000 C C
	1    5900 7300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 4A6660D2
P 6300 7400
F 0 "#PWR03" H 6300 7400 30  0001 C C
F 1 "GND" H 6300 7330 30  0001 C C
	1    6300 7400
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG04
U 1 1 4A6660B3
P 6300 7300
F 0 "#FLG04" H 6300 7570 30  0001 C C
F 1 "PWR_FLAG" H 6300 7530 30  0000 C C
	1    6300 7300
	1    0    0    -1  
$EndComp
$Comp
L R R20
U 1 1 4A650791
P 8100 4750
F 0 "R20" V 8180 4750 50  0000 C C
F 1 "47k" V 8100 4750 50  0000 C C
	1    8100 4750
	1    0    0    -1  
$EndComp
$Comp
L R R19
U 1 1 4A650790
P 7800 4750
F 0 "R19" V 7880 4750 50  0000 C C
F 1 "47k" V 7800 4750 50  0000 C C
	1    7800 4750
	1    0    0    -1  
$EndComp
$Comp
L DIODE D5
U 1 1 4A4EA23A
P 9700 4700
F 0 "D5" H 9700 4800 40  0000 C C
F 1 "1N4148" H 9700 4600 40  0000 C C
	1    9700 4700
	0    -1   -1   0   
$EndComp
$Comp
L SW_PUSH SW7
U 1 1 4A4EA1FC
P 9700 6800
F 0 "SW7" H 9850 6910 50  0000 C C
F 1 "-" H 9700 6720 50  0000 C C
	1    9700 6800
	1    0    0    -1  
$EndComp
$Comp
L DIODE D4
U 1 1 4A4EA1C1
P 9350 4700
F 0 "D4" H 9350 4800 40  0000 C C
F 1 "1N4148" H 9350 4600 40  0000 C C
	1    9350 4700
	0    -1   -1   0   
$EndComp
$Comp
L SW_PUSH SW4
U 1 1 4A4EA151
P 8500 5700
F 0 "SW4" H 8650 5810 50  0000 C C
F 1 "OK" H 8500 5620 50  0000 C C
	1    8500 5700
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW5
U 1 1 4A4EA14D
P 8500 6300
F 0 "SW5" H 8650 6410 50  0000 C C
F 1 "ABAJO" H 8500 6220 50  0000 C C
	1    8500 6300
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW2
U 1 1 4A4EA14B
P 7500 5700
F 0 "SW2" H 7650 5810 50  0000 C C
F 1 "<---" H 7500 5620 50  0000 C C
	1    7500 5700
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW6
U 1 1 4A4EA149
P 9500 5700
F 0 "SW6" H 9650 5810 50  0000 C C
F 1 "--->" H 9500 5620 50  0000 C C
	1    9500 5700
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW3
U 1 1 4A4EA11D
P 8500 5150
F 0 "SW3" H 8650 5260 50  0000 C C
F 1 "ARRIBA" H 8500 5070 50  0000 C C
	1    8500 5150
	1    0    0    -1  
$EndComp
$Comp
L CONN_6 P7
U 1 1 4A4EA0F2
P 5600 4150
F 0 "P7" V 5550 4150 60  0000 C C
F 1 "TECLADO" V 5650 4150 60  0000 C C
	1    5600 4150
	-1   0    0    -1  
$EndComp
$Comp
L R R18
U 1 1 48B99251
P 7500 4750
F 0 "R18" V 7580 4750 50  0000 C C
F 1 "10k" V 7500 4750 50  0000 C C
	1    7500 4750
	1    0    0    -1  
$EndComp
$Comp
L R R15
U 1 1 48B9924D
P 6900 4750
F 0 "R15" V 6980 4750 50  0000 C C
F 1 "10k" V 6900 4750 50  0000 C C
	1    6900 4750
	1    0    0    -1  
$EndComp
$Comp
L R R16
U 1 1 48A9E1BF
P 7200 4750
F 0 "R16" V 7280 4750 50  0000 C C
F 1 "10k" V 7200 4750 50  0000 C C
	1    7200 4750
	1    0    0    -1  
$EndComp
$EndSCHEMATC
