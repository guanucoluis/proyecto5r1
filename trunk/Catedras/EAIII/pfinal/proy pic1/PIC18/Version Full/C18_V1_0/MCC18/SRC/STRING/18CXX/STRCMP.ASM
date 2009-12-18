; $Id: strcmp.asm,v 1.3 2000/01/31 21:53:52 ConnerJ Exp $

#include "..\..\INC\P18CXXX.INC"
#include "..\..\INC\P18MACRO.INC"

; @name strcmp
;``The {\bf strcmp} function compares the string pointed to by {\bf s1} to
;the string pointed to by {\bf s2}.''
;Stack usage: 6 bytes. Re-entrant.
;@param s1 pointer to string one
;@param s2 pointer to string two
;@return ``The {\bf strcmp} function returns a signed char greater than, equal
;to, or less than zero, accordingly as the string pointed to by {\bf s1} is
;greater than, equal to, or less than the string pointed to by {\bf s2}.''
;
; signed char strcmp (const char *s1, const char *s2);


STRING CODE
strcmp
  global strcmp

; Proceedure: Use FSR0 for 's1' and FSR2 for 's2'.

  ; Save FSR2 on the stack. 

          Stk2PushFromReg FSR2L

  ; Load FSR2 with the 's2' pointer

          Stk2CpyToReg -6,FSR2L

  ; Load FSR0 with the 's1' pointer

          Stk2CpyToReg -4,FSR0L

  ; Compare s1 to s2
jLoop:
          movf      POSTINC2, W, ACCESS
          subwf     INDF0, W, ACCESS
          bnz       jEnd                ; unequal - diff in WREG 

  ; Here only if bytes are equal. Need to test for '\0' on only one byte.
          tstfsz    POSTINC0,ACCESS
          bra       jLoop


  ; Falls through with WREG = 0

jEnd
  ; Setup to put WREG on Stack and set FSR0 equal to it.

  ; Set FSR0 = FSR1
          movff     FSR1L,FSR0L
          movff     FSR1H,FSR0H

  ; Put WREG on Stack and set FSR0 equal to it.
          movf      POSTDEC0, F, ACCESS           ; decrement FSR0
          movf      POSTDEC0, F, ACCESS           ; decrement FSR0
          movf      POSTDEC0, F, ACCESS           ; decrement FSR0
          movwf     INDF0, ACCESS

  ; Restore FSR2.  Doesn't change WREG.
          Stk2PopToReg FSR2L
          return
  end
