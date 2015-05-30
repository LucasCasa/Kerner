;
; interrups.asm
;
; Created on: Apr 18, 2010
;      Author: anizzomc
;

GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL _write_port
GLOBAL picSlaveMask
GLOBAL _int_timer_hand
GLOBAL _int_keyboard_hand
GLOBAL _lidt
GLOBAL haltcpu

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler


EXTERN irqDispatcher
EXTERN int_08
EXTERN int_09


SECTION .text

_cli:
	cli
	ret


_sti:
	sti
	ret

_write_port:
    push rbp
    mov rbp, rsp
    mov edx, edi    
    mov rax, rsi
    and rax, 0FFFFh  
    out dx, al
    mov rsp,rbp
    pop rbp  
    ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, [rbp+8]
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, [rbp+8]  ; ax = mascara de 16 bits
    out		0A1h,al
    pop     rbp
    retn

_lidt:				; Carga el IDTR
    push    rbp
    mov     rbp, rsp
    push    rbx
    mov     rbx, [rbp + 6] ; ds:bx = puntero a IDTR
	rol		rbx,16
	lidt    [ds: rbx]          ; carga IDTR
    pop     rbx
    pop     rbp
    retn


;8254 Timer (Timer Tick)
_irq00Handler:
	jmp _int_timer_hand
	
;Keyboard
_irq01Handler:
	jmp _int_keyboard_hand

;Cascade pic never called
_irq02Handler:
	iretq

;Serial Port 2 and 4
_irq03Handler:
	iretq
	
;Serial Port 1 and 3	
_irq04Handler:
	iretq
	
;USB
_irq05Handler:
	iretq


_int_timer_hand:				; Handler de INT 8 ( Timer tick)
   	push rdi
	push rax                  ; Se salvan los registros
                            ; Carga de DS y ES con el valor del selector
    mov     ax, 10h			; a utilizar.
    mov     ds, ax
    mov     es, ax
   	call    int_08
    mov		al,20h			; Envio de EOI generico al PIC
	out		20h,al
	
	pop 	rax
	pop 	rdi
    iretq


_int_keyboard_hand:				; Handler de INT 9 ( Teclado )
    push   	rdi
    push   	rax                      ; Se salvan los registros
                            ; Carga de DS y ES con el valor del selector

    xor     rax,rax
	in 		al, 60h	;Leo el puerto del teclado
	and     rax,0x00000000000000FF
    xor     rdi,rdi
    mov     rdi,rax	;Le envio el SCAN CODE como parametro a la funcion int_09
	call 	int_09	;Llamo a la interrupcion que maneja el SCAN CODE en C
	

    mov		al,20h			; Envio de EOI generico al PIC
	out		20h,al

    pop     rax
    pop     rdi
    iretq

haltcpu:
	cli
	hlt
	ret

