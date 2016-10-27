.intel_syntax noprefix

.text
.global reverse_asm

reverse_asm:
	# Put ebx on the stack so we can use it
	push ebx
    push edi
	
	# All registers zero'd out
    xor eax, eax
    xor ebx, ebx # headptr
    xor ecx, ecx # nextptr
    xor edx, edx # new_headptr
    xor edi, edi

	# So if (head == NULL) return NULL;
	mov eax, [esp + 12]
    cmp eax, ebx # Compare eax to a 0'd register
	je null_ret
	
	# Move the ptr into eax, then set ebx as our headptr
	add eax, [esp + 16]
	mov ebx, eax
	
while_start:
	# While (headptr) is not null
	cmp ebx, edi
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
	sub eax, [esp + 16]
	
null_ret:
    pop edi
	pop ebx
	ret
