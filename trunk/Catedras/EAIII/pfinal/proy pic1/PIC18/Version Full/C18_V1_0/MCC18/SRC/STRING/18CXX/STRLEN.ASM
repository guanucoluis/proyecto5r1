; $Id: strlen.asm,v 1.3 2000/01/31 21:53:52 ConnerJ Exp $

#include "..\..\INC\P18CXXX.INC"
#include "..\..\INC\P18MACRO.INC"

; @name strlen
;``The {\bf strlen} function computes the length of the string pointed
;to by {\bf s}.''
;Stack usage: 2 bytes. Re-entrant.
;@param s pointer to the string
;@return ``The {\bf strlen} function returns the number of characters
;that precede the terminating null character.''
;
; size_t strlen (const char *s);


STRING CODE
strlen
  global strlen

; Proceedure: Use FSR0 for 's' and create 'n' on stack.  Return with FSR0
;         pointing to 'n'.

  ; Load FSR0 by POPing 's' off stack into FSR0.

          Stk2PopToReg FSR0L

  ; Push 2 bytes of 0 onto stack. This is initial value of 'n'.
          clrf      POSTINC1,ACCESS
          clrf      POSTINC1,ACCESS

  ; Scan for '\0' while counting.
jLoop:

  ; Test for '\0'
          movf      POSTINC0,F,ACCESS   ; set Z flag
          bz        jEnd

  ; Count it 

          Stk2Inc   -2
          bra       jLoop

jEnd

  ; Set FSR0 = FSR1 - 2 ( location of 'n')

          StkSetPtrToOffset FSR0L,-2
          return
  end
