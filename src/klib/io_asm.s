GLOBAL io_out8
io_out8:
				push rbp
				mov	rbp, rsp
				mov edx, edi
				mov eax, esi
				mov [rbp - 4], dx
				mov [rbp - 8], al

				out dx, al

				pop rbp
				ret
