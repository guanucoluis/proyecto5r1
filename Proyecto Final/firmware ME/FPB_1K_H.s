; ..............................................................................
;    File   FPB_1K_H.s
; ..............................................................................

		.equ FPB_1K_HNumTaps, 31

; ..............................................................................
; Allocate and initialize filter taps

		.section .FPB_1K_Hconst, "x"
		.align 64

FPB_1K_HTaps:
.hword 	0xFFDB,	0xFFC0,	0xFFBF,	0x0000,	0x0099,	0x0140,	0x0143,	0x0000,	0xFD99
.hword 	0xFB64,	0xFB95,	0x0000,	0x08BC,	0x1382,	0x1C72,	0x1FEA,	0x1C72,	0x1382
.hword 	0x08BC,	0x0000,	0xFB95,	0xFB64,	0xFD99,	0x0000,	0x0143,	0x0140,	0x0099
.hword 	0x0000,	0xFFBF,	0xFFC0,	0xFFDB

; ..............................................................................
; Allocate delay line in (uninitialized) Y data space

		.section .ybss,  "b"
		.align 64

FPB_1K_HDelay:
		.space FPB_1K_HNumTaps*2

; ..............................................................................
; Allocate and intialize filter structure

		.section .data
		.global _FPB_1K_HFilter

_FPB_1K_HFilter:
.hword FPB_1K_HNumTaps
.hword psvoffset(FPB_1K_HTaps)
.hword psvoffset(FPB_1K_HTaps)+FPB_1K_HNumTaps*2-1
.hword psvpage(FPB_1K_HTaps)
.hword FPB_1K_HDelay
.hword FPB_1K_HDelay+FPB_1K_HNumTaps*2-1
.hword FPB_1K_HDelay

; ..............................................................................
; ..............................................................................
; Sample assembly language calling program
;  The following declarations can be cut and pasted as needed into a program
;		.extern	_FIRFilterInit
;		.extern	_BlockFIRFilter
;		.extern	_FPB_1K_HFilter
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
;		mov	#_FPB_1K_HFilter, W0	; Initalize W0 to filter structure
;		call	_FIRFilterInit	; call this function once
;
; The next 4 instructions are required prior to each subroutine call
; to _BlockFIRFilter
;		mov	#_FPB_1K_HFilter, W0	; Initalize W0 to filter structure
;		mov	#input, W1	; Initalize W1 to input buffer 
;		mov	#output, W2	; Initalize W2 to output buffer
;		mov	#20, W3	; Initialize W3 with number of required output samples
;		call	_BlockFIRFilter	; call as many times as needed
