; $Id: strlwr.asm,v 1.3 2000/01/31 21:53:52 ConnerJ Exp $

#include "..\..\INC\P18CXXX.INC"
#include "..\..\INC\P18MACRO.INC"

; @name strlwr
;The {\bf strlwr} function converts each upper case character in the
;string pointed to by {\bf s} to the corresponding lower case character.
;Stack usage: 2 bytes. Re-entrant.
;@param s pointer to string
;@return The {\bf strlwr} function returns the value of {\bf s}.
;
; char *strlwr (char *s);

STRING CODE
strlwr
  global strlwr

; Proceedure: Use FSR0 for 's'.

  ; Load FSR0 with the 's' pointer

          Stk2CpyToReg -2,FSR0L

  ; Scan for '\0' while converting case
jLoop:
          movlw     'A'
          subwf     INDF0,W,ACCESS
          bn        jSkip

          movlw     'Z'+1
          subwf     INDF0,W,ACCESS
          bnn       jSkip

  ; Convert to lowercase

          movlw     0x20
          iorwf     INDF0,F,ACCESS

jSkip

  ; Test for '\0'
          movf      POSTINC0,F,ACCESS   ; set Z flag
          bnz       jLoop

jEnd

  ; Set FSR0 = 's'.

          StkSetPtrToOffset FSR0L,-2
          return
  end
