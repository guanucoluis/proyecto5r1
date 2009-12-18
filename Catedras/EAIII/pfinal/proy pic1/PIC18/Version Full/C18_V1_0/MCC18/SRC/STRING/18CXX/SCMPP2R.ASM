; $Id: scmpp2r.asm,v 1.3 2000/01/31 21:53:52 ConnerJ Exp $

#include "..\..\INC\P18CXXX.INC"
#include "..\..\INC\P18MACRO.INC"

; @name strcmppgm2ram
;The {\bf strcmppgm2ram} function performs a {\bf strcmp} where
;{\bf s1} points to data memory and {\bf s2} points to program
;memory.
;@param s1 pointer to string in data memory
;@param s2 pointer to string in program memory
;
; signed char strcmppgm2ram (const char *s1, const rom char *s2);

STRING CODE
strcmppgm2ram
  global strcmppgm2ram


#ifdef __SMALL__
 messg "strcmppgm2ram - SMALL"


; Proceedure: Use FSR0 for 'dest' and TBLPTR for 'src' 
;         Assumes TBLPTRU = 0.

  ; Load TBLPTR with the 'src' pointer

          Stk2CpyToReg -4,TBLPTRL

  ; Load FSR0 with the 'dest' pointer

          Stk2CpyToReg -2,FSR0L

jLoop:
          tblrd     *+                  ; read & increment
          movf      TABLAT, W, ACCESS

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
          movwf     INDF0, ACCESS
          return

#else
#ifdef __LARGE__
 messg "strcmppgm2ram - LARGE"


; Proceedure: Three byte rom pointer.
;         Use FSR0 for 'dest' and TBLPTR for 'src' 

  ; Load TBLPTR with the 'src' pointer

          Stk3CpyToReg -5,TBLPTRL

  ; Load FSR0 with the 'dest' pointer

          Stk2CpyToReg -2,FSR0L

jLoop:
          tblrd     *+                  ; read & increment
          movf      TABLAT, W, ACCESS

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
          movwf     INDF0, ACCESS
          return

#else
 error "No Model Specified"
#endif
#endif
  end
