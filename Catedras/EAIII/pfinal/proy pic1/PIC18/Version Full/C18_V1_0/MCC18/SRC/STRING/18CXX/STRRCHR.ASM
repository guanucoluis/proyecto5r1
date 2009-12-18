; $Id: strrchr.asm,v 1.3 2000/01/31 21:53:52 ConnerJ Exp $

#include "..\..\INC\P18CXXX.INC"
#include "..\..\INC\P18MACRO.INC"

; @name strrchr
;``The {\bf strrchr} function locates the last occurrence of {\bf c} [...]
;in the string pointed to by {\bf s}. The terminating null character is 
;considered to be part of the string.''
; * The MPLAB-C18 version of the {\bf strrchr} function differs from the ANSI
;specified function in that {\bf c} is defined as an {\bf unsigned char}
;parameter rather than an {\bf int} parameter.
;Stack usage: 3 bytes. Re-entrant.
;@param s pointer to string to search
;@param c character to search for
;@return ``The {\bf strrchr} function returns a pointer to the character,
;or a null pointer if {\bf c} does not occur in the string.''
;
; char *strrchr (const char *s, unsigned char c);

STRING CODE
strrchr
  global strrchr

; Proceedure: Use FSR0 for 's'.


  ; Load FSR0 with the 's' pointer

          Stk2CpyToReg -2,FSR0L

  ; Preload NULL to 's' in case there is no match.
          movlw     -2
          clrf      PLUSW1,ACCESS
          movlw     -1
          clrf      PLUSW1,ACCESS
jLoop:

  ; get 'c'
          movlw     -3
          movf      PLUSW1, W, ACCESS

  ; Compare with character in 's'
          subwf     INDF0, W, ACCESS
          bnz       jLoop1

  ; Match: save ponter in 's'

          Stk2CpyFromReg FSR0L,-2

jLoop1:
  ; Test for '\0'
          tstfsz    POSTINC0,ACCESS
          bra       jLoop


  ; Done.  The last match is in 's' or, if no match, then 's' contains NULL.

  ; Set FSR0 to point to 's' for return
          StkSetPtrToOffset FSR0L,-2

          return
  end

