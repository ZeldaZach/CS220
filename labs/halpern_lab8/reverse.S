.intel_syntax noprefix

.text
.global reverse_asm

reverse_asm:
	# Put ebx on the stack so we can use it
	push ebx
	
	# All registers zero'd out
    mov eax, 0x0
    mov ebx, eax # headptr
    mov ecx, eax # nextptr
    mov edx, eax # new_headptr

	# So if (head == NULL) return NULL;
	mov eax, [esp + 8]
    cmp eax, 0 
	je null_ret
	
	# Move the ptr into eax, then set ebx as our headptr
	add eax, [esp + 12]
	mov ebx, eax
	
while_start:
	# While (headptr) is not null
	cmp ebx, 0x0
	je while_done

	# nextptr = (void *)*(unsigned long *)headptr
	mov ecx, [ebx]

	# *(unsigned long *)headptr = (unsigned long)new_headptr
	mov [ebx], edx

	# new_headptr = headptr
	mov edx, ebx

	# headptr = nextptr
	mov ebx, ecx

	# next iteration
	jmp while_start

while_done:
	mov eax, edx
	sub eax, [esp + 12]
	
null_ret:
	pop ebx
	ret
