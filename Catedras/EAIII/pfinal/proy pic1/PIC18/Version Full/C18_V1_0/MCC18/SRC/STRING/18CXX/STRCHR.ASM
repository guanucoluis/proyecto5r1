; $Id: strchr.asm,v 1.3 2000/01/31 21:53:52 ConnerJ Exp $

#include "..\..\INC\P18CXXX.INC"
#include "..\..\INC\P18MACRO.INC"

; @name strchr
;``The {\bf strchr} function locates the first occurence of {\bf c} [...]
;in the string pointed to by {\bf s}. The terminating null character is
;considered to be part of the string.''
; * The MPLAB-C18 version of the {\bf strchr} function differs from the ANSI
;specified function in that {\bf c} is defined as an {\bf unsigned char}
;parameter rather than an {\bf int} parameter.
;Stack usage: 3 bytes. Re-entrant.
;@param s pointer to string to search
;@param c character to search for
;@return ``The {\bf strchr} function returns a pointer to the located character,
;or a null pointer if the character does not occur in the string.''
;
; char *strchr (const char *s, unsigned char c);

STRING CODE
strchr
  global strchr

; Proceedure: Use FSR0 for 's'.


  ; Load FSR0 with the 's' pointer

          Stk2CpyToReg -2,FSR0L

jLoop:

  ; get 'c'
          movlw     -3
          movf      PLUSW1, W, ACCESS

  ; Compare with character in 's'
          subwf     INDF0, W, ACCESS
          bz        jMatch               ; match

  ; Test for '\0'
          tstfsz    POSTINC0,ACCESS
          bra       jLoop


  ; No match - Load NULL to 's'
          movlw     -2
          clrf      PLUSW1,ACCESS
          movlw     -1
          clrf      PLUSW1,ACCESS
          bra       jEnd

jMatch
  ; Found match - Load 's' with current value of FSR0 which points to
  ; match character.  
  
          Stk2CpyFromReg FSR0L,-2
  
jEnd

  ; Set FSR0 to point to 's' for return
          StkSetPtrToOffset FSR0L,-2

          return
  end

