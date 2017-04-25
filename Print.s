; Print.s
; Student names: change this to your names or look very silly
; Last modification date: change this to the last modification date or look very silly
; Runs on LM4F120 or TM4C123
; EE319K lab 7 device driver for any LCD
;
; As part of Lab 7, students need to implement these LCD_OutDec and LCD_OutFix
; This driver assumes two low-level LCD functions
; ST7735_OutChar   outputs a single 8-bit ASCII character
; ST7735_OutString outputs a null-terminated string 
number equ 9999
thousand equ 12
hundred equ 8
ten equ 4
unit equ 0
    IMPORT   ST7735_OutChar
    IMPORT   ST7735_OutString
    EXPORT   LCD_OutDec
    EXPORT   LCD_OutFix

    AREA    |.text|, CODE, READONLY, ALIGN=2
    THUMB
	preserve8
  

;-----------------------LCD_OutDec-----------------------
; Output a 32-bit number in unsigned decimal format
; Input: R0 (call by value) 32-bit unsigned number
; Output: none
; Invariables: This function must not permanently modify registers R4 to R11
LCD_OutDec
	push {r4, lr}
	mov r2, #10				;divisor
	mov r4, #0				;counter
again	
	udiv r3, r0, r2 
	mul r1, r3, r2
	sub r1, r0, r1
	push {r1, r2}			;pushing a digit onto the stack
	add r4, r4, #1
	mov r0, r3
	cmp r0, #0				;if the quotient isn't yet zero, keep dividing
	bne again	
more	
	pop{r0, r2}
	add r0, r0, #0x30
	bl ST7735_OutChar		;outputs an ASCII character
	subs r4, r4, #1
	bne more
	pop{r4, lr}

      BX  LR
;* * * * * * * * End of LCD_OutDec * * * * * * * *

; -----------------------LCD _OutFix----------------------
; Output characters to LCD display in fixed-point format
; unsigned decimal, resolution 0.001, range 0.000 to 9.999
; Inputs:  R0 is an unsigned 32-bit number
; Outputs: none
; E.g., R0=0,    then output "0.000 "
;       R0=3,    then output "0.003 "
;       R0=89,   then output "0.089 "
;       R0=123,  then output "0.123 "
;       R0=9999, then output "9.999 "
;       R0>9999, then output "*.*** "
; Invariables: This function must not permanently modify registers R4 to R11
LCD_OutFix
	push{r4, lr}
	ldr r4, =number
	cmp r0, r4
	bhi stars
	sub sp, sp, #16
	mov r2, #10				;divisor
	mov r4, #4				;counter
	
	udiv r3, r0, r2 
	mul r1, r3, r2
	sub r1, r0, r1
	str r1, [sp, #thousand]	;store thousandth digit on stack			
	mov r0, r3
	udiv r3, r0, r2 
	mul r1, r3, r2
	sub r1, r0, r1
	str r1, [sp, #hundred]	;store hundredth digit on stack
	mov r0, r3
	udiv r3, r0, r2 
	mul r1, r3, r2
	sub r1, r0, r1
	str r1, [sp, #ten]		;store tenth digit on stack
	mov r0, r3
	udiv r3, r0, r2 
	mul r1, r3, r2
	sub r1, r0, r1
	str r1, [sp, #unit]		;store unit digit on stack
	mov r0, r3
	

	ldr r0, [sp]
	add r0, r0, #0x30
	bl ST7735_OutChar		;outputs an ASCII character
	add sp, sp, #4
	mov r0, #0x2e
	bl ST7735_OutChar
	ldr r0, [sp]
	add r0, r0, #0x30
	bl ST7735_OutChar
	add sp, sp, #4
	ldr r0, [sp]
	add r0, r0, #0x30
	bl ST7735_OutChar
	add sp, sp, #4
	ldr r0, [sp]
	add r0, r0, #0x30
	bl ST7735_OutChar
	add sp, sp, #4
	b exit
	
stars						;outputs *.*** if greater than 9999
	mov r0, #0x2a
	bl ST7735_OutChar
	mov r0, #0x2e
	bl ST7735_OutChar
	mov r0, #0x2a
	bl ST7735_OutChar
	mov r0, #0x2a
	bl ST7735_OutChar
	mov r0, #0x2a
	bl ST7735_OutChar
	 
	 
exit	 
	 pop{r4, pc}
     BX   LR
 
     ALIGN
;* * * * * * * * End of LCD_OutFix * * * * * * * *

     ALIGN                           ; make sure the end of this section is aligned
     END                             ; end of file
