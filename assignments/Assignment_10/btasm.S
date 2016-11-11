.intel_syntax noprefix

.text
.global getBasePointer

getBasePointer:
	mov eax, ebp
	ret
