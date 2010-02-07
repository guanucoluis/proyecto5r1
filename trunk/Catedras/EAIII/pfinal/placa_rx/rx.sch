EESchema Schematic File Version 2  date 07/02/2010 17:49:07
LIBS:power,./holtek,./o_analog,device,conn,linear,regul,74xx,cmos4000,adc-dac,memory,xilinx,special,microcontrollers,dsp,microchip,analog_switches,motorola,texas,intel,audio,interface,digital-audio,philips,display,cypress,siliconi,contrib,valves,.\rx.cache
EELAYER 24  0
EELAYER END
$Descr A4 11700 8267
Sheet 1 1
Title ""
Date "7 feb 2010"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 2650 550  0    60   ~ 0
Recepcion correcta
Wire Wire Line
	3650 750  3650 650 
Wire Wire Line
	3650 650  3500 650 
Wire Wire Line
	3350 1850 3350 1300
Wire Wire Line
	3350 1300 3100 1300
Wire Wire Line
	8800 1750 8450 1750
Wire Wire Line
	8450 1750 8450 2300
Wire Wire Line
	8450 2300 8050 2300
Wire Wire Line
	8050 2300 8050 3350
Wire Wire Line
	8050 3350 4250 3350
Wire Wire Line
	4250 3350 4250 2650
Wire Wire Line
	4250 2650 4600 2650
Wire Wire Line
	5200 2350 3350 2350
Wire Wire Line
	5200 2150 4050 2150
Wire Wire Line
	4050 2150 4050 2550
Wire Wire Line
	4050 2550 3350 2550
Wire Wire Line
	5500 2950 5500 3100
Wire Wire Line
	8500 2800 8750 2800
Wire Wire Line
	8750 2000 8750 1950
Connection ~ 8100 1850
Wire Wire Line
	8800 1850 8050 1850
Wire Wire Line
	7450 2150 7450 2200
Wire Wire Line
	8100 1850 8100 1100
Wire Wire Line
	8100 1100 7750 1100
Wire Wire Line
	7050 1950 7000 1950
Wire Wire Line
	7000 1950 7000 2000
Wire Wire Line
	4600 2850 4500 2850
Wire Wire Line
	4500 2850 4500 2900
Wire Wire Line
	6700 2050 6750 2050
Wire Wire Line
	6750 2050 6750 2150
Wire Wire Line
	6700 2450 6800 2450
Wire Wire Line
	6800 2450 6800 2550
Wire Wire Line
	5500 1500 5500 1650
Connection ~ 5150 1900
Wire Wire Line
	5150 1900 5000 1900
Connection ~ 5150 1950
Wire Wire Line
	5200 2050 5150 2050
Wire Wire Line
	5150 2050 5150 1750
Wire Wire Line
	5150 1850 5200 1850
Wire Wire Line
	5150 1750 5200 1750
Wire Wire Line
	4450 1550 4450 1600
Wire Wire Line
	4450 1600 4850 1600
Wire Wire Line
	4850 1600 4850 1300
Wire Wire Line
	4250 1550 4250 1600
Wire Wire Line
	4250 1600 4350 1600
Wire Wire Line
	4350 1600 4350 1550
Wire Wire Line
	3850 1650 3850 1550
Wire Wire Line
	3350 2050 3650 2050
Wire Wire Line
	3650 2050 3650 1550
Wire Wire Line
	3050 3350 3050 3150
Connection ~ 1900 1950
Wire Wire Line
	1950 1950 1900 1950
Connection ~ 1900 2150
Wire Wire Line
	1950 2150 1900 2150
Connection ~ 1900 2350
Wire Wire Line
	1950 2350 1900 2350
Wire Wire Line
	1900 2550 1950 2550
Wire Wire Line
	1950 1850 1900 1850
Wire Wire Line
	1950 2450 1900 2450
Connection ~ 1900 2450
Wire Wire Line
	1950 2250 1900 2250
Connection ~ 1900 2250
Wire Wire Line
	1950 2050 1900 2050
Connection ~ 1900 2050
Wire Wire Line
	2650 1150 2650 1250
Wire Wire Line
	1900 1850 1900 2650
Connection ~ 1900 2550
Wire Wire Line
	2550 3350 2550 3150
Wire Wire Line
	3550 1550 3550 1600
Wire Wire Line
	3850 1600 4150 1600
Wire Wire Line
	4150 1600 4150 1550
Connection ~ 3850 1600
Wire Wire Line
	4300 1650 4300 1600
Connection ~ 4300 1600
Wire Wire Line
	5150 1950 5200 1950
Connection ~ 5150 1850
Wire Wire Line
	5000 1900 5000 1950
Wire Wire Line
	6800 2950 6800 3050
Wire Wire Line
	5200 2850 5100 2850
Wire Wire Line
	7050 1750 6700 1750
Wire Wire Line
	7250 1100 6900 1100
Wire Wire Line
	6900 1100 6900 1750
Connection ~ 6900 1750
Wire Wire Line
	7450 1450 7450 1550
Wire Wire Line
	5100 2650 5200 2650
Wire Wire Line
	8750 1950 8800 1950
Wire Wire Line
	8750 3100 8700 3100
Wire Wire Line
	8700 3100 8700 3150
Wire Wire Line
	8500 3000 8750 3000
Wire Wire Line
	8500 2900 8750 2900
Wire Wire Line
	3350 2450 4200 2450
Wire Wire Line
	4200 2450 4200 2250
Wire Wire Line
	4200 2250 5200 2250
Wire Wire Line
	3350 2250 3800 2250
Wire Wire Line
	3800 2250 3800 2400
Wire Wire Line
	3800 2400 4450 2400
Wire Wire Line
	4450 2400 4450 2450
Wire Wire Line
	4450 2450 5200 2450
Wire Wire Line
	2250 3150 2250 3300
Wire Wire Line
	3100 800  3100 650 
$Comp
L GND #PWR01
U 1 1 4B6F23CE
P 3650 750
F 0 "#PWR01" H 3650 750 30  0001 C CNN
F 1 "GND" H 3650 680 30  0001 C CNN
	1    3650 750 
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 4B6F23AC
P 3100 1050
F 0 "R5" V 3180 1050 50  0000 C CNN
F 1 "470" V 3100 1050 50  0000 C CNN
	1    3100 1050
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 4B6F23A4
P 3300 650
F 0 "D1" H 3300 750 50  0000 C CNN
F 1 "LED" H 3300 550 50  0000 C CNN
	1    3300 650 
	1    0    0    -1  
$EndComp
Kmarq B 5500 3100 "Warning Pin power_in not driven (Net 15)" F=1
Kmarq B 8500 2800 "Warning Pin power_in not driven (Net 14)" F=1
Kmarq B 2250 3150 "Error: Pin power_out conectado a Pin output (net 4)" F=2
Kmarq B 2650 1250 "Warning Pin power_in not driven (Net 3)" F=1
$Comp
L HT12D IC1
U 1 1 4B2B19E8
P 2650 2250
F 0 "IC1" H 2450 2350 50  0000 L BNN
F 1 "HT12D" H 2450 2350 50  0000 C CNN
F 2 "holtek-18-DIP-A" H 2650 2400 50  0001 C CNN
	1    2650 2250
	1    0    0    -1  
$EndComp
$Comp
L -12V #PWR02
U 1 1 4B2B20D6
P 5500 3100
F 0 "#PWR02" H 5500 3230 20  0001 C CNN
F 1 "-12V" H 5500 3200 30  0000 C CNN
	1    5500 3100
	-1   0    0    1   
$EndComp
$Comp
L -12V #PWR03
U 1 1 4B2B1FF1
P 8500 2900
F 0 "#PWR03" H 8500 3030 20  0001 C CNN
F 1 "-12V" H 8500 3000 30  0000 C CNN
	1    8500 2900
	0    -1   -1   0   
$EndComp
$Comp
L +12V #PWR04
U 1 1 4B2B1FE8
P 8500 2800
F 0 "#PWR04" H 8500 2750 20  0001 C CNN
F 1 "+12V" H 8500 2900 30  0000 C CNN
	1    8500 2800
	0    -1   -1   0   
$EndComp
$Comp
L VCC #PWR05
U 1 1 4B2B1FDA
P 8500 3000
F 0 "#PWR05" H 8500 3100 30  0001 C CNN
F 1 "VCC" H 8500 3100 30  0000 C CNN
	1    8500 3000
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR06
U 1 1 4B2B1FCC
P 8700 3150
F 0 "#PWR06" H 8700 3150 30  0001 C CNN
F 1 "GND" H 8700 3080 30  0001 C CNN
	1    8700 3150
	1    0    0    -1  
$EndComp
$Comp
L CONN_4 P4
U 1 1 4B2B1FB3
P 9100 2950
F 0 "P4" V 9050 2950 50  0000 C CNN
F 1 "fuente" V 9150 2950 50  0000 C CNN
	1    9100 2950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 4B2B1F6E
P 8750 2000
F 0 "#PWR07" H 8750 2000 30  0001 C CNN
F 1 "GND" H 8750 1930 30  0001 C CNN
	1    8750 2000
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 4B2B1F2F
P 4850 2650
F 0 "R2" V 4930 2650 50  0000 C CNN
F 1 "5k" V 4850 2650 50  0000 C CNN
	1    4850 2650
	0    1    1    0   
$EndComp
$Comp
L CONN_3 K1
U 1 1 4B2B1F1B
P 9150 1850
F 0 "K1" V 9100 1850 50  0000 C CNN
F 1 "DAC" V 9200 1850 40  0000 C CNN
	1    9150 1850
	1    0    0    -1  
$EndComp
$Comp
L -12V #PWR08
U 1 1 4B2B1EFF
P 7450 2200
F 0 "#PWR08" H 7450 2330 20  0001 C CNN
F 1 "-12V" H 7450 2300 30  0000 C CNN
	1    7450 2200
	-1   0    0    1   
$EndComp
$Comp
L +12V #PWR09
U 1 1 4B2B1EF1
P 7450 1450
F 0 "#PWR09" H 7450 1400 20  0001 C CNN
F 1 "+12V" H 7450 1550 30  0000 C CNN
	1    7450 1450
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 4B2B1EC6
P 7500 1100
F 0 "R4" V 7580 1100 50  0000 C CNN
F 1 "5k" V 7500 1100 50  0000 C CNN
	1    7500 1100
	0    1    1    0   
$EndComp
$Comp
L GND #PWR010
U 1 1 4B2B1EB7
P 7000 2000
F 0 "#PWR010" H 7000 2000 30  0001 C CNN
F 1 "GND" H 7000 1930 30  0001 C CNN
	1    7000 2000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR011
U 1 1 4B2B1E91
P 4500 2900
F 0 "#PWR011" H 4500 2900 30  0001 C CNN
F 1 "GND" H 4500 2830 30  0001 C CNN
	1    4500 2900
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 4B2B1E8A
P 4850 2850
F 0 "R3" V 4930 2850 50  0000 C CNN
F 1 "5k" V 4850 2850 50  0000 C CNN
	1    4850 2850
	0    1    1    0   
$EndComp
$Comp
L GND #PWR012
U 1 1 4B2B1E78
P 6750 2150
F 0 "#PWR012" H 6750 2150 30  0001 C CNN
F 1 "GND" H 6750 2080 30  0001 C CNN
	1    6750 2150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR013
U 1 1 4B2B1E3E
P 6800 3050
F 0 "#PWR013" H 6800 3050 30  0001 C CNN
F 1 "GND" H 6800 2980 30  0001 C CNN
	1    6800 3050
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 4B2B1E34
P 6800 2750
F 0 "C1" H 6850 2850 50  0000 L CNN
F 1 "100n" H 6850 2650 50  0000 L CNN
	1    6800 2750
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR014
U 1 1 4B2B1E15
P 5500 1500
F 0 "#PWR014" H 5500 1600 30  0001 C CNN
F 1 "VCC" H 5500 1600 30  0000 C CNN
	1    5500 1500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR015
U 1 1 4B2B1BE7
P 5000 1950
F 0 "#PWR015" H 5000 1950 30  0001 C CNN
F 1 "GND" H 5000 1880 30  0001 C CNN
	1    5000 1950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR016
U 1 1 4B2B1B5E
P 4300 1650
F 0 "#PWR016" H 4300 1650 30  0001 C CNN
F 1 "GND" H 4300 1580 30  0001 C CNN
	1    4300 1650
	1    0    0    -1  
$EndComp
$Comp
L CONN_1 ant1
U 1 1 4B2B1B6F
P 4850 1150
F 0 "ant1" H 4930 1150 40  0000 L CNN
F 1 "CONN_1" H 4850 1205 30  0001 C CNN
	1    4850 1150
	0    -1   -1   0   
$EndComp
$Comp
L CONN_4 P2
U 1 1 4B2B1993
P 4300 1200
F 0 "P2" V 4250 1200 50  0000 C CNN
F 1 "rx_der" V 4350 1200 50  0000 C CNN
	1    4300 1200
	0    -1   -1   0   
$EndComp
$Comp
L VCC #PWR017
U 1 1 4B2B1B36
P 3850 1650
F 0 "#PWR017" H 3850 1750 30  0001 C CNN
F 1 "VCC" H 3850 1750 30  0000 C CNN
	1    3850 1650
	-1   0    0    1   
$EndComp
NoConn ~ 3750 1550
$Comp
L GND #PWR018
U 1 1 4B2B1B20
P 3550 1600
F 0 "#PWR018" H 3550 1600 30  0001 C CNN
F 1 "GND" H 3550 1530 30  0001 C CNN
	1    3550 1600
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 4B2B1AB1
P 2800 3350
F 0 "R1" V 2880 3350 50  0000 C CNN
F 1 "47k" V 2800 3350 50  0000 C CNN
	1    2800 3350
	0    1    1    0   
$EndComp
$Comp
L GND #PWR019
U 1 1 4B2B1A9E
P 2250 3300
F 0 "#PWR019" H 2250 3300 30  0001 C CNN
F 1 "GND" H 2250 3230 30  0001 C CNN
	1    2250 3300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR020
U 1 1 4B2B1A92
P 1900 2650
F 0 "#PWR020" H 1900 2650 30  0001 C CNN
F 1 "GND" H 1900 2580 30  0001 C CNN
	1    1900 2650
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR021
U 1 1 4B2B1A79
P 2650 1150
F 0 "#PWR021" H 2650 1250 30  0001 C CNN
F 1 "VCC" H 2650 1250 30  0000 C CNN
	1    2650 1150
	1    0    0    -1  
$EndComp
$Comp
L CONN_4 P1
U 1 1 4B2B198F
P 3700 1200
F 0 "P1" V 3650 1200 50  0000 C CNN
F 1 "rx_izq" V 3750 1200 50  0000 C CNN
	1    3700 1200
	0    -1   -1   0   
$EndComp
$Comp
L TL082 U2
U 1 1 4B2B1902
P 7550 1850
F 0 "U2" H 7670 2100 60  0000 C CNN
F 1 "TL082" H 7700 1600 60  0000 C CNN
F 11 "7911" H 7550 1850 60  0000 C CNN "Campo8"
	1    7550 1850
	1    0    0    -1  
$EndComp
$Comp
L DAC0808 U1
U 1 1 4B2B18EE
P 5950 2300
F 0 "U1" H 5950 3000 60  0000 C CNN
F 1 "DAC0808" H 5950 1600 60  0000 C CNN
	1    5950 2300
	1    0    0    -1  
$EndComp
$EndSCHEMATC
