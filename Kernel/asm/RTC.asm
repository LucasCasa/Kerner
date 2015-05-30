
GLOBAL getSeconds
GLOBAL getMonth
GLOBAL getHour
GLOBAL getDay
GLOBAL getMinutes
GLOBAL getYear
GLOBAL setHour


getSeconds:
		cli
		push rbp
		mov rbp, rsp
		xor eax, eax
		mov al, 0x00
		jmp calc

getMinutes:
		push rbp
		mov rbp, rsp
		xor eax, eax
		mov al, 2
		jmp calc

getHour:
		push rbp
		mov rbp, rsp
		xor eax, eax
		mov al, 4
		jmp calc

getDay:
		push rbp
		mov rbp, rsp
		xor eax, eax
		mov al, 7
		jmp calc

getMonth:
		push rbp
		mov rbp, rsp
		xor eax, eax
		mov al, 8
		jmp calc

getYear:
		push rbp
		mov rbp, rsp
		mov al, 9
		jmp calc

calc:
		out 70h, al
		xor al,al
		in	al,71h
		mov rsp, rbp 
       	pop rbp 
       	sti
		ret

setHour:
		cli
		push rbp
		mov rbp, rsp
		mov al,4
		out 70h,al
		mov rax,rdi
		out 71h,al
		sti
		leave
		ret