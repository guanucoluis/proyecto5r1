; ..............................................................................
;    File   fir24_1_2.s
; ..............................................................................

		.equ fir24_1_2NumTaps, 31

; ..............................................................................
; Allocate and initialize filter taps

		.section .fir24_1_2const, "x"
		.align 64

fir24_1_2Taps:
.hword 	0xFFCC,	0x0000,	0x005D,	0x0000,	0xFF28,	0x0000,	0x01C9,	0x0000,	0xFC99
.hword 	0x0000,	0x0640,	0x0000,	0xF3A8,	0x0000,	0x2839,	0x3FD3,	0x2839,	0x0000
.hword 	0xF3A8,	0x0000,	0x0640,	0x0000,	0xFC99,	0x0000,	0x01C9,	0x0000,	0xFF28
.hword 	0x0000,	0x005D,	0x0000,	0xFFCC

; ..............................................................................
; Allocate delay line in (uninitialized) Y data space

		.section .ybss,  "b"
		.align 64

fir24_1_2Delay:
		.space fir24_1_2NumTaps*2

; ..............................................................................
; Allocate and intialize filter structure

		.section .data
		.global _fir24_1_2Filter

_fir24_1_2Filter:
.hword fir24_1_2NumTaps
.hword psvoffset(fir24_1_2Taps)
.hword psvoffset(fir24_1_2Taps)+fir24_1_2NumTaps*2-1
.hword psvpage(fir24_1_2Taps)
.hword fir24_1_2Delay
.hword fir24_1_2Delay+fir24_1_2NumTaps*2-1
.hword fir24_1_2Delay

; ..............................................................................
; ..............................................................................
; Sample assembly language calling program
;  The following declarations can be cut and pasted as needed into a program
;		.extern	_FIRFilterInit
;		.extern	_BlockFIRFilter
;		.extern	_fir24_1_2Filter
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
;		mov	#_fir24_1_2Filter, W0	; Initalize W0 to filter structure
;		call	_FIRFilterInit	; call this function once
;
; The next 4 instructions are required prior to each subroutine call
; to _BlockFIRFilter
;		mov	#_fir24_1_2Filter, W0	; Initalize W0 to filter structure
;		mov	#input, W1	; Initalize W1 to input buffer 
;		mov	#output, W2	; Initalize W2 to output buffer
;		mov	#20, W3	; Initialize W3 with number of required output samples
;		call	_BlockFIRFilter	; call as many times as needed
