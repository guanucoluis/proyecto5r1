EESchema Schematic File Version 2
LIBS:power,./holtek,./o_analog,device,conn,linear,regul,74xx,cmos4000,adc-dac,memory,xilinx,special,microcontrollers,dsp,microchip,analog_switches,motorola,texas,intel,audio,interface,digital-audio,philips,display,cypress,siliconi,contrib,valves
EELAYER 43  0
EELAYER END
$Descr A4 11700 8267
Sheet 1 1
Title ""
Date "18 dec 2009"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	3800 3400 3800 3550
Wire Wire Line
	6750 2700 6000 2700
Wire Wire Line
	6000 2700 6000 2650
Wire Wire Line
	6000 2650 5350 2650
Wire Wire Line
	5350 2650 5350 2500
Wire Wire Line
	5350 2500 4900 2500
Wire Wire Line
	6750 2500 5750 2500
Wire Wire Line
	5750 2500 5750 2700
Wire Wire Line
	5750 2700 4900 2700
Wire Wire Line
	10050 3150 10300 3150
Wire Wire Line
	10050 3250 10300 3250
Wire Wire Line
	10250 3400 10250 3350
Wire Wire Line
	10250 3350 10300 3350
Wire Wire Line
	10350 2200 10300 2200
Wire Wire Line
	6650 2900 6750 2900
Wire Wire Line
	9000 1700 9000 1800
Connection ~ 8450 2000
Wire Wire Line
	8450 2000 8450 1350
Wire Wire Line
	8450 1350 8800 1350
Wire Wire Line
	8600 2000 8250 2000
Wire Wire Line
	6750 3100 6650 3100
Wire Wire Line
	8350 3200 8350 3300
Wire Wire Line
	6550 2200 6550 2150
Connection ~ 6700 2100
Wire Wire Line
	6700 2200 6750 2200
Connection ~ 5850 1850
Wire Wire Line
	5850 1900 5850 1850
Connection ~ 5400 1850
Wire Wire Line
	5700 1800 5700 1850
Wire Wire Line
	5700 1850 5400 1850
Wire Wire Line
	5100 1800 5100 1850
Wire Wire Line
	4100 3600 4100 3400
Connection ~ 3450 2800
Wire Wire Line
	3450 2900 3450 2100
Wire Wire Line
	4200 1400 4200 1500
Connection ~ 3450 2300
Wire Wire Line
	3500 2300 3450 2300
Connection ~ 3450 2500
Wire Wire Line
	3500 2500 3450 2500
Connection ~ 3450 2700
Wire Wire Line
	3500 2700 3450 2700
Wire Wire Line
	3450 2100 3500 2100
Wire Wire Line
	3450 2800 3500 2800
Wire Wire Line
	3500 2600 3450 2600
Connection ~ 3450 2600
Wire Wire Line
	3500 2400 3450 2400
Connection ~ 3450 2400
Wire Wire Line
	3500 2200 3450 2200
Connection ~ 3450 2200
Wire Wire Line
	4600 3600 4600 3400
Wire Wire Line
	5200 1800 5200 2300
Wire Wire Line
	5200 2300 4900 2300
Wire Wire Line
	5400 1900 5400 1800
Wire Wire Line
	5900 1800 5900 1850
Wire Wire Line
	5900 1850 5800 1850
Wire Wire Line
	5800 1850 5800 1800
Wire Wire Line
	6400 1550 6400 1850
Wire Wire Line
	6400 1850 6000 1850
Wire Wire Line
	6000 1850 6000 1800
Wire Wire Line
	6750 2000 6700 2000
Wire Wire Line
	6700 2100 6750 2100
Wire Wire Line
	6700 2000 6700 2300
Wire Wire Line
	6700 2300 6750 2300
Connection ~ 6700 2200
Wire Wire Line
	6550 2150 6700 2150
Connection ~ 6700 2150
Wire Wire Line
	7050 1750 7050 1900
Wire Wire Line
	8350 2800 8350 2700
Wire Wire Line
	8350 2700 8250 2700
Wire Wire Line
	8300 2400 8300 2300
Wire Wire Line
	8300 2300 8250 2300
Wire Wire Line
	6050 3150 6050 3100
Wire Wire Line
	6050 3100 6150 3100
Wire Wire Line
	8550 2250 8550 2200
Wire Wire Line
	8550 2200 8600 2200
Wire Wire Line
	9300 1350 9650 1350
Wire Wire Line
	9650 1350 9650 2100
Wire Wire Line
	9000 2400 9000 2450
Wire Wire Line
	10350 2100 9600 2100
Connection ~ 9650 2100
Wire Wire Line
	10300 2200 10300 2250
Wire Wire Line
	10050 3050 10300 3050
Wire Wire Line
	7050 3200 7050 3350
Wire Wire Line
	4900 2800 5600 2800
Wire Wire Line
	5600 2800 5600 2400
Wire Wire Line
	5600 2400 6750 2400
Wire Wire Line
	6750 2600 4900 2600
Wire Wire Line
	6150 2900 5800 2900
Wire Wire Line
	5800 2900 5800 3600
Wire Wire Line
	5800 3600 9600 3600
Wire Wire Line
	9600 3600 9600 2550
Wire Wire Line
	9600 2550 10000 2550
Wire Wire Line
	10000 2550 10000 2000
Wire Wire Line
	10000 2000 10350 2000
Kmarq B 7050 3350 "Warning Pin power_in not driven (Net 15)" F=1
Kmarq B 10050 3050 "Warning Pin power_in not driven (Net 14)" F=1
Kmarq B 3800 3400 "Error: Pin power_out conectado a Pin output (net 4)" F=2
Kmarq B 4200 1500 "Warning Pin power_in not driven (Net 3)" F=1
$Comp
L HT12D IC1
U 1 1 4B2B19E8
P 4200 2500
F 0 "IC1" H 4000 2600 50  0000 L B
F 1 "HT12D" H 4000 2600 50  0000 C C
F 2 "holtek-18-DIP-A" H 4200 2650 50  0001 C C
	1    4200 2500
	1    0    0    -1  
$EndComp
$Comp
L -12V #PWR01
U 1 1 4B2B20D6
P 7050 3350
F 0 "#PWR01" H 7050 3480 20  0001 C C
F 1 "-12V" H 7050 3450 30  0000 C C
	1    7050 3350
	-1   0    0    1   
$EndComp
$Comp
L -12V #PWR02
U 1 1 4B2B1FF1
P 10050 3150
F 0 "#PWR02" H 10050 3280 20  0001 C C
F 1 "-12V" H 10050 3250 30  0000 C C
	1    10050 3150
	0    -1   -1   0   
$EndComp
$Comp
L +12V #PWR03
U 1 1 4B2B1FE8
P 10050 3050
F 0 "#PWR03" H 10050 3000 20  0001 C C
F 1 "+12V" H 10050 3150 30  0000 C C
	1    10050 3050
	0    -1   -1   0   
$EndComp
$Comp
L VCC #PWR04
U 1 1 4B2B1FDA
P 10050 3250
F 0 "#PWR04" H 10050 3350 30  0001 C C
F 1 "VCC" H 10050 3350 30  0000 C C
	1    10050 3250
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR05
U 1 1 4B2B1FCC
P 10250 3400
F 0 "#PWR05" H 10250 3400 30  0001 C C
F 1 "GND" H 10250 3330 30  0001 C C
	1    10250 3400
	1    0    0    -1  
$EndComp
$Comp
L CONN_4 P4
U 1 1 4B2B1FB3
P 10650 3200
F 0 "P4" V 10600 3200 50  0000 C C
F 1 "fuente" V 10700 3200 50  0000 C C
	1    10650 3200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 4B2B1F6E
P 10300 2250
F 0 "#PWR06" H 10300 2250 30  0001 C C
F 1 "GND" H 10300 2180 30  0001 C C
	1    10300 2250
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 4B2B1F2F
P 6400 2900
F 0 "R2" V 6480 2900 50  0000 C C
F 1 "5k" V 6400 2900 50  0000 C C
	1    6400 2900
	0    1    1    0   
$EndComp
$Comp
L CONN_3 K1
U 1 1 4B2B1F1B
P 10700 2100
F 0 "K1" V 10650 2100 50  0000 C C
F 1 "DAC" V 10750 2100 40  0000 C C
	1    10700 2100
	1    0    0    -1  
$EndComp
$Comp
L -12V #PWR07
U 1 1 4B2B1EFF
P 9000 2450
F 0 "#PWR07" H 9000 2580 20  0001 C C
F 1 "-12V" H 9000 2550 30  0000 C C
	1    9000 2450
	-1   0    0    1   
$EndComp
$Comp
L +12V #PWR08
U 1 1 4B2B1EF1
P 9000 1700
F 0 "#PWR08" H 9000 1650 20  0001 C C
F 1 "+12V" H 9000 1800 30  0000 C C
	1    9000 1700
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 4B2B1EC6
P 9050 1350
F 0 "R4" V 9130 1350 50  0000 C C
F 1 "5k" V 9050 1350 50  0000 C C
	1    9050 1350
	0    1    1    0   
$EndComp
$Comp
L GND #PWR09
U 1 1 4B2B1EB7
P 8550 2250
F 0 "#PWR09" H 8550 2250 30  0001 C C
F 1 "GND" H 8550 2180 30  0001 C C
	1    8550 2250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 4B2B1E91
P 6050 3150
F 0 "#PWR010" H 6050 3150 30  0001 C C
F 1 "GND" H 6050 3080 30  0001 C C
	1    6050 3150
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 4B2B1E8A
P 6400 3100
F 0 "R3" V 6480 3100 50  0000 C C
F 1 "5k" V 6400 3100 50  0000 C C
	1    6400 3100
	0    1    1    0   
$EndComp
$Comp
L GND #PWR011
U 1 1 4B2B1E78
P 8300 2400
F 0 "#PWR011" H 8300 2400 30  0001 C C
F 1 "GND" H 8300 2330 30  0001 C C
	1    8300 2400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 4B2B1E3E
P 8350 3300
F 0 "#PWR012" H 8350 3300 30  0001 C C
F 1 "GND" H 8350 3230 30  0001 C C
	1    8350 3300
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 4B2B1E34
P 8350 3000
F 0 "C1" H 8400 3100 50  0000 L C
F 1 "100n" H 8400 2900 50  0000 L C
	1    8350 3000
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR013
U 1 1 4B2B1E15
P 7050 1750
F 0 "#PWR013" H 7050 1850 30  0001 C C
F 1 "VCC" H 7050 1850 30  0000 C C
	1    7050 1750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 4B2B1BE7
P 6550 2200
F 0 "#PWR014" H 6550 2200 30  0001 C C
F 1 "GND" H 6550 2130 30  0001 C C
	1    6550 2200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR015
U 1 1 4B2B1B5E
P 5850 1900
F 0 "#PWR015" H 5850 1900 30  0001 C C
F 1 "GND" H 5850 1830 30  0001 C C
	1    5850 1900
	1    0    0    -1  
$EndComp
$Comp
L CONN_1 ant1
U 1 1 4B2B1B6F
P 6400 1400
F 0 "ant1" H 6480 1400 40  0000 L C
F 1 "CONN_1" H 6400 1455 30  0001 C C
	1    6400 1400
	0    -1   -1   0   
$EndComp
$Comp
L CONN_4 P2
U 1 1 4B2B1993
P 5850 1450
F 0 "P2" V 5800 1450 50  0000 C C
F 1 "rx_der" V 5900 1450 50  0000 C C
	1    5850 1450
	0    -1   -1   0   
$EndComp
$Comp
L VCC #PWR016
U 1 1 4B2B1B36
P 5400 1900
F 0 "#PWR016" H 5400 2000 30  0001 C C
F 1 "VCC" H 5400 2000 30  0000 C C
	1    5400 1900
	-1   0    0    1   
$EndComp
NoConn ~ 5300 1800
$Comp
L GND #PWR017
U 1 1 4B2B1B20
P 5100 1850
F 0 "#PWR017" H 5100 1850 30  0001 C C
F 1 "GND" H 5100 1780 30  0001 C C
	1    5100 1850
	1    0    0    -1  
$EndComp
NoConn ~ 4900 2100
$Comp
L R R1
U 1 1 4B2B1AB1
P 4350 3600
F 0 "R1" V 4430 3600 50  0000 C C
F 1 "47k" V 4350 3600 50  0000 C C
	1    4350 3600
	0    1    1    0   
$EndComp
$Comp
L GND #PWR018
U 1 1 4B2B1A9E
P 3800 3550
F 0 "#PWR018" H 3800 3550 30  0001 C C
F 1 "GND" H 3800 3480 30  0001 C C
	1    3800 3550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR019
U 1 1 4B2B1A92
P 3450 2900
F 0 "#PWR019" H 3450 2900 30  0001 C C
F 1 "GND" H 3450 2830 30  0001 C C
	1    3450 2900
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR020
U 1 1 4B2B1A79
P 4200 1400
F 0 "#PWR020" H 4200 1500 30  0001 C C
F 1 "VCC" H 4200 1500 30  0000 C C
	1    4200 1400
	1    0    0    -1  
$EndComp
$Comp
L CONN_4 P1
U 1 1 4B2B198F
P 5250 1450
F 0 "P1" V 5200 1450 50  0000 C C
F 1 "rx_izq" V 5300 1450 50  0000 C C
	1    5250 1450
	0    -1   -1   0   
$EndComp
$Comp
L TL082 U2
U 1 1 4B2B1902
P 9100 2100
F 0 "U2" H 9220 2350 60  0000 C C
F 1 "TL082" H 9250 1850 60  0000 C C
F 11 "7911" H 9100 2100 60  0000 C C
	1    9100 2100
	1    0    0    -1  
$EndComp
$Comp
L DAC0808 U1
U 1 1 4B2B18EE
P 7500 2550
F 0 "U1" H 7500 3250 60  0000 C C
F 1 "DAC0808" H 7500 1850 60  0000 C C
	1    7500 2550
	1    0    0    -1  
$EndComp
$EndSCHEMATC
