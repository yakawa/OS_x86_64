
GLOBAL irs_ignore
EXTERN irs_ignore_func
irs_ignore:
				call irs_ignore_func
				jmp	hlt
				iretq

GLOBAL irs_div_by_0
EXTERN div_by_0_func
irs_div_by_0:
				call div_by_0_func
				jmp hlt
				iretq


GLOBAL irs_timer
EXTERN timer_func
irs_timer:
				cli
				push rdi
				push rsi
				push rdx
				push rcx
				push rax
				push r8
				push r9
				push r10
				push r11
				push rbp
				mov rbp, rsp
				push rbp

				call timer_func

				pop rbp
				mov rsp, rbp
				pop rbp
				pop r11
				pop r10
				pop r9
				pop r8
				pop rax
				pop rcx
				pop rdx
				pop rsi
				pop rdi
				sti
				iretq

hlt:
				hlt
				jmp	hlt
