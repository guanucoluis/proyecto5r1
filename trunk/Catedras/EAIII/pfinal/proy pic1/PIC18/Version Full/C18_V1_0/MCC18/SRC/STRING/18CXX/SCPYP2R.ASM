; $Id: scpyp2r.asm,v 1.3 2000/01/31 21:53:52 ConnerJ Exp $

#include "..\..\INC\P18CXXX.INC"
#include "..\..\INC\P18MACRO.INC"

; @name strcpypgm2ram
;The {\bf strcpypgm2ram} function performs a {\bf strcpy} where
;{\bf s1} points to data memory and {\bf s2} points to program
;memory.
;@param s1 pointer to destination in data memory
;@param s2 pointer to source in program memory
;
; char *strcpypgm2ram (char *s1, const rom char *s2);

STRING CODE
strcpypgm2ram
  global strcpypgm2ram


#ifdef __SMALL__
 messg "strcpypgm2ram - SMALL"


; Proceedure: Use FSR0 for 'dest' and TBLPTR for 'src' 
;         Assumes TBLPTRU = 0.

  ; Load TBLPTR with the 'src' pointer

          Stk2CpyToReg -4,TBLPTRL

  ; Load FSR0 with the 'dest' pointer

          Stk2CpyToReg -2,FSR0L

jLoop:
          tblrd     *+                  ; read & increment
          movff     TABLAT, INDF0

  ; Test for '\0'
          tstfsz    POSTINC0,ACCESS
          bra       jLoop

jEnd

  ; Return value: Set FSR0 to 'dest'.
          StkSetPtrToOffset FSR0L,-2

          return

#else
#ifdef __LARGE__
 messg "strcpypgm2ram - LARGE"


; Proceedure: Three byte rom pointer.
;         Use FSR0 for 'dest' and TBLPTR for 'src' 

  ; Load TBLPTR with the 'src' pointer

          Stk3CpyToReg -5,TBLPTRL

  ; Load FSR0 with the 'dest' pointer

          Stk2CpyToReg -2,FSR0L

jLoop:
          tblrd     *+                  ; read & increment
          movff     TABLAT, INDF0

  ; Test for '\0'
          tstfsz    POSTINC0,ACCESS
          bra       jLoop

jEnd

  ; Return value: Set FSR0 to 'dest'.
          StkSetPtrToOffset FSR0L,-2

          return

#else
 error "No Model Specified"
#endif
#endif
  end
