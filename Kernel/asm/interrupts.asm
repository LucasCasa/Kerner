
GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL _write_port

GLOBAL _int_timer_hand
GLOBAL _int_keyboard_hand
GLOBAL _int80_hand

GLOBAL haltcpu
GLOBAL _call_int80


EXTERN timer_handler
EXTERN keyboard_handler
EXTERN sys_manager

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

_int80_hand:
    call sys_manager
    iretq

_int_timer_hand:				; Handler de INT 8 ( Timer tick)
   	push rdi
	push rax                  ; Se salvan los registros
                            ; Carga de DS y ES con el valor del selector
    mov     ax, 10h			; a utilizar.
    mov     ds, ax
    mov     es, ax
   	call    timer_handler
    
    mov		al,20h			; Envio de EOI generico al PIC
	out		20h,al
	
	pop 	rax
	pop 	rdi
    iretq


_int_keyboard_hand:				; Handler de INT 9 ( Teclado )
    push   	rdi
    push   	rax                      ; Se salvan los registros
                          
    xor     rax,rax
	in 		al, 60h	              ;Leo el puerto del teclado
	and     rax,0x00000000000000FF
    xor     rdi,rdi
    mov     rdi,rax	            ;Le envio el SCAN CODE como parametro a la funcion int_09
	call 	keyboard_handler	;Llamo a la interrupcion que maneja el SCAN CODE en C
	

    mov		al,20h			; Envio de EOI generico al PIC
	out		20h,al

    pop     rax
    pop     rdi
    iretq

_call_int80:
    push    rbp
    mov     rbp, rsp
    int     80h
    leave
    ret

haltcpu:
	cli
	hlt
	ret

