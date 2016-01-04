;;; loader.s
;;; Copyrights (C) 2016 KAWASAKI Yasukazu
;;; MIT License


;;; GRUBを通して起動した場合、protected modeで起動してくる
;;; そのため、32bit codeを利用する。
BITS 32

MB2_MAGIC		equ	0xe85250d6			; Multiboot2のマジック
MB2_ARCH		equ	0x00000000			; x86_64
STACK_SIZE	equ	0x4000

GLOBAL	start
EXTERN kmain

ALIGN	8
section .boot_text
_mb2_header_start:
				;; Header
				dd	MB2_MAGIC
				dd	MB2_ARCH
				dd	_mb2_header_end - _mb2_header_start
				dd	- (MB2_MAGIC + MB2_ARCH + (_mb2_header_end - _mb2_header_start))
				;; End Tag
				dw	0
				dw	0
				dd	8
_mb2_header_end:
start:

				;; GRUBから渡された情報を退避する
				mov	edi, eax
				mov	esi, ebx

				mov	esp, _stack + STACK_SIZE

				;; 仮のGDTを設定する
				lgdt	[gdt_toc]

				jmp 	0x08:flush
flush:
				nop
				mov 	ax, 0x10
				mov 	ds, ax
				mov 	es, ax
				mov 	ss, ax


				mov eax, _pdp_low
				or	eax, 1
				mov	[_pml4], eax

				mov	eax, _pdp_high
				or	eax, 1
				mov [_pml4 + 0x08 * (((0xFFFFFFFF80000000) >> (21 + 9 + 9)) & 0x1FF)], eax

				mov	eax, _pd
				or	eax, 1
				mov	[_pdp_low], eax
				mov	[_pdp_high + 0x08 * (((0xFFFFFFFF80000000) >> (21 + 9)) & 0x1FF)], eax

				xor	eax, eax
				or eax, 131
				mov [_pd], eax
				mov	[_pd + 0x08 * (((0xFFFFFFFF80000000) >> (21)) & 0x1FF)], eax

				mov eax, _pml4
				mov	cr3, eax

				mov eax, cr4
				or eax, 48
				mov cr4, eax

				mov	ecx, 0xC0000080
				rdmsr
				bts	eax, 8
				wrmsr

				mov	eax, cr0
				or eax, 1 << 31
				mov	cr0, eax

				lgdt [GDT64.Pointer] ; Load the 64-bit global descriptor table.

;;; 				jmp	0x18:_64_enter

				jmp	0x08:_64_enter
BITS 64
_64_enter:
				mov	rax, 0xFFFFFFFF80000000
				add	rsp, rax

				mov eax, 0x10
				mov ds, ax
				mov es, ax
				mov ss, ax


				push rsi
				push rdi
				mov	rax, 0xFFFFFFFF80000000
				add rsi, rax

				call kmain

_loop:
				hlt
				jmp	_loop


section	.boot_data
gdt_toc:
				dw	8 * 5
				dd	_gdt

_gdt:
				;; NULL Descriptor
				dw	0x0000
				dw	0x0000
				dw	0x0000
				dw	0x0000

				;; Code Descriptor
				db	0xFF
				db	0xFF
				dw	0x0000
				db	0x00
				db	0b10011010
				db	0xCF
				db	0x00

				;; Data Descriptor
				db	0xFF
				db	0xFF
				dw	0x0000
				db	0x00
				db	0b10010010
				db	0xCF
				db	0x00

				;; Code Descriptor
				db	0xFF
				db	0xFF
				dw	0x0000
				db	0x00
				db	0b10011010
				db	0xAF
				db	0x00

				;; Data Descriptor
				db	0xFF
				db	0xFF
				dw	0x0000
				db	0x00
				db	0b10010010
				db	0xAF
				db	0x00


GDT64:
.null:  											; Global Descriptor Table (64-bit).
				dw 0								 ; Limit (low).
				dw 0								 ; Base (low).
				db 0								 ; Base (middle)
				db 0								 ; Access.
				db 0								 ; Granularity.
				db 0								 ; Base (high).
.Code:
				dw 0								 ; Limit (low).
				dw 0								 ; Base (low).
				db 0								 ; Base (middle)
				db 10011010b				 ; Access (exec/read).
				db 00100000b				 ; Granularity.
				db 0								 ; Base (high).
.data:
				dw 0								 ; Limit (low).
				dw 0								 ; Base (low).
				db 0								 ; Base (middle)
				db 10010010b				 ; Access (read/write).
				db 00000000b				 ; Granularity.
				db 0								 ; Base (high).
.Pointer:						 ; The GDT-pointer.
				dw $ - GDT64 - 1		 ; Limit.
				dq GDT64						 ; Base.

;;; Page table
align 4096
_pd:
				times 1024*4 db 0
_pdp_high:
				times 1024*4 db 0
_pdp_low:
				times 1024*4 db 0
_pml4:
				times 1024*4 db 0

_stack:
				resb	STACK_SIZE
