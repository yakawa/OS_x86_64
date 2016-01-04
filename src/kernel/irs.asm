GLOBAL
irs_ignore:
				push rax
				push rbx
				push rcx
				push rdx
				push rsi
				push rdi
				push rbp

				pop  rbp
				pop  rdi
				pop  rsi
				pop  rdx
				pop  rcx
				pop  rbx
				pop  rax

				iretq
