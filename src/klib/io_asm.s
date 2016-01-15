GLOBAL io_out8
io_out8:
				push rbp
				mov	rbp, rsp
				mov edx, edi
				mov eax, esi

				out dx, al

				pop rbp
				ret

GLOBAL io_in8
io_in8:
				push rbp
				mov	rbp, rsp
				mov edx, edi

				in al, dx

				pop rbp
				ret
