; ..............................................................................
;    File   CoefFiltro01.s
; ..............................................................................

		.equ CoefFiltro01NumTaps, 27

; ..............................................................................
; Allocate and initialize filter taps

		.section .CoefFiltro01const, "x"
		.align 64

CoefFiltro01Taps:
.hword 	0x003D,	0x0000,	0xFF86,	0x0000,	0x013F,	0x0000,	0xFD34,	0x0000,	0x05B4
.hword 	0x0000,	0xF409,	0x0000,	0x2814,	0x3FCF,	0x2814,	0x0000,	0xF409,	0x0000
.hword 	0x05B4,	0x0000,	0xFD34,	0x0000,	0x013F,	0x0000,	0xFF86,	0x0000,	0x003D

; ..............................................................................
; Allocate delay line in (uninitialized) Y data space

		.section .ybss,  "b"
		.align 64

CoefFiltro01Delay:
		.space CoefFiltro01NumTaps*2

; ..............................................................................
; Allocate and intialize filter structure

		.section .data
		.global _CoefFiltro01Filter

_CoefFiltro01Filter:
.hword CoefFiltro01NumTaps
.hword psvoffset(CoefFiltro01Taps)
.hword psvoffset(CoefFiltro01Taps)+CoefFiltro01NumTaps*2-1
.hword psvpage(CoefFiltro01Taps)
.hword CoefFiltro01Delay
.hword CoefFiltro01Delay+CoefFiltro01NumTaps*2-1
.hword CoefFiltro01Delay

; ..............................................................................
; ..............................................................................
; Sample assembly language calling program
;  The following declarations can be cut and pasted as needed into a program
;		.extern	_FIRFilterInit
;		.extern	_BlockFIRFilter
;		.extern	_CoefFiltro01Filter
;
;		.section	.bss
;
;	 The input and output buffers can be made any desired size
;	   the value 40 is just an example - however, one must ensure
;	   that the output buffer is at least as long as the number of samples
;	   to be filtered (parameter 4)
;input:		.space	40
;output:	.space	40
;		.text
;
;
;  This code can be copied and pasted as needed into a program
;
;
; Set up pointers to access input samples, filter taps, delay line and
; output samples.
;		mov	#_CoefFiltro01Filter, W0	; Initalize W0 to filter structure
;		call	_FIRFilterInit	; call this function once
;
; The next 4 instructions are required prior to each subroutine call
; to _BlockFIRFilter
;		mov	#_CoefFiltro01Filter, W0	; Initalize W0 to filter structure
;		mov	#input, W1	; Initalize W1 to input buffer 
;		mov	#output, W2	; Initalize W2 to output buffer
;		mov	#20, W3	; Initialize W3 with number of required output samples
;		call	_BlockFIRFilter	; call as many times as needed
