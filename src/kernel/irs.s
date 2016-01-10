
GLOBAL irs_ignore
EXTERN irs_ignore_func
irs_ignore:
				call irs_ignore_func
				jmp	hlt
				iretq

GLOBAL irs_DE
EXTERN DE_func
irs_DE:
				call DE_func
				jmp hlt
				iretq

GLOBAL	irs_DB
EXTERN	DB_func
irs_DB:
				call DB_func
				jmp hlt
				iretq

GLOBAL	irs_NMI
EXTERN	NMI_func
irs_NMI:
				call NMI_func
				jmp hlt
				iretq

GLOBAL	irs_BP
EXTERN	BP_func
irs_BP:
				call BP_func
				jmp hlt
				iretq


GLOBAL	irs_OF
EXTERN  OF_func
irs_OF:
				call OF_func
				jmp hlt
				iretq

GLOBAL	irs_BR
EXTERN	BR_func
irs_BR:
				call BR_func
				jmp	hlt
				iretq

GLOBAL	irs_UD
EXTERN	UD_func
irs_UD:
				call UD_func
				jmp hlt
				iretq

GLOBAL	irs_NM
EXTERN	NM_func
irs_NM:
				call NM_func
				jmp hlt
				iretq

GLOBAL	irs_DF
EXTERN	DF_func
irs_DF:
				call DF_func
				jmp hlt
				iretq

GLOBAL	irs_coprocessor
EXTERN	coprocessor_func
irs_coprocessor:
				call coprocessor_func
				jmp hlt
				iretq

GLOBAL	irs_TS
EXTERN	TS_func
irs_TS:
				call TS_func
				jmp hlt
				iretq

GLOBAL	irs_NP
EXTERN	NP_func
irs_NP:
				call NP_func
				jmp hlt
				iretq

GLOBAL	irs_SS
EXTERN	SS_func
irs_SS:
				call SS_func
				jmp hlt
				iretq

GLOBAL irs_GP
EXTERN GP_func
irs_GP:
				call GP_func
				jmp hlt
				iretq

GLOBAL	irs_PF
EXTERN	PF_func
irs_PF:
				call PF_func
				jmp hlt
				iretq

GLOBAL	irs_MF
EXTERN	MF_func
irs_MF:
				call MF_func
				jmp hlt
				iretq

GLOBAL	irs_AC
EXTERN 	AC_func
irs_AC:
				call AC_func
				jmp hlt
				iretq

GLOBAL	irs_MC
EXTERN 	MC_func
irs_MC:
				call MC_func
				jmp hlt
				iretq

GLOBAL	irs_XF
EXTERN	XF_func
irs_XF:
				call XF_func
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
