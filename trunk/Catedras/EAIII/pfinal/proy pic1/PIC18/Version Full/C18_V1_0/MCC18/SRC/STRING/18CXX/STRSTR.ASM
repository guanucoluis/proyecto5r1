; $Id: strstr.asm,v 1.3 2000/01/31 21:53:52 ConnerJ Exp $

#include "..\..\INC\P18CXXX.INC"
#include "..\..\INC\P18MACRO.INC"

; @name strstr
;``The {\bf strstr} function locates the first occurrence in the string 
;pointed to by {\bf s1} of the sequence of characters (excluding the
;null terminator) in the string pointed to by {\bf s2}.''
;Stack usage: 8 bytes. Re-entrant.
;@param s1 pointer to the string to search
;@param s2 pointer to sequence to search for
;@return ``The {\bf strstr} function returns a pointer to the located
;string, or a null pointer if the string is not found. If {\bf s2}
;points to a string with zero length, the function returns {\bf s1}.''
;
; char *strstr (const char *s1, const char *SubStr)

STRING CODE
strstr
  global strstr

; Proceedure: Use FSR0 as 's1' pointer and FSR2 as 'SubStr' pointer.
;         Allocate on stack temporary pointer to hold location of beginning
;         of match. 

  ; Save FSR2 on the stack. 

          Stk2PushFromReg FSR2L

  ; Load FSR0 with the 's1' pointer

          Stk2CpyToReg -4,FSR0L


  ; Allocate and store 's1' on stack
          Stk2PushFromReg FSR0L

jOuterLoop:

  ; Test for '\0' in 's1'
          movf      INDF0, W, ACCESS
          bz        jNull               ; found end of 's1'

  ; Load FSR2 with the 's2' pointer

          Stk2CpyToReg -8,FSR2L

  ; Put start of next comparision on stack
          Stk2CpyFromReg FSR0L,-2

jInnerLoop:

  ; Test for '\0' in 's2'
          movf      POSTINC2, W, ACCESS
          bz        jMatch               ; found end of 's2'

  ; Compare 'SubStr' character with 's1' character at FSR0
          subwf     INDF0, W, ACCESS
          bz        jInnerLoop           ; match

  ; No match. Increment 's1' pointer
          movf      POSTINC0, W, ACCESS
          bra       jOuterLoop

jNull:
  ; discard temporary pointer and load FSR2 with NULL 
          Stk2PopToReg FSR2L
          clrf      FSR2L, ACCESS
          clrf      FSR2H, ACCESS
          bra       jReturn

jMatch:
  ; Found match.  Load FSR2 with temporary pointer from stack

          Stk2PopToReg FSR2L


jReturn:
  ; Put FSR2 into location of 'SubStr' and set FSR0 to point to it

          Stk2CpyFromReg FSR2L,-8
  
  ; Set FSR0 to point to 'SubStr' for return
          StkSetPtrToOffset FSR0L,-8

  ; Restore stack frame for return: restore FSR2
          Stk2PopToReg FSR2L

          return
  end


