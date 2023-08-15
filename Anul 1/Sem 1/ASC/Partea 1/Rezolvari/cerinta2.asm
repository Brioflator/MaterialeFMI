.data

	expresie: .space 10001
	delim: .asciz " "
	sf: .asciz "%10000[^\n]"
	pfs: .asciz "%s\n"
	pfd: .asciz "%d\n"
	rez: .space 8
	aux: .space 8
	atoi_aux: .space 8

.text

.global main

main:
	// citire expresie
	pushl $expresie
	pushl $sf
	call scanf
	popl %ebx
	popl %ebx
	
	// punem primul numar in auxiliar
	pushl $delim
	pushl $expresie
	call strtok
	popl %ebx
	popl %ebx
	
	movl %eax, aux
	
	//tin in atoi_aux atoi-ul primului numar
		pushl aux
		call atoi
		popl %ebx
	
		movl %eax, atoi_aux
	// pun primul nr pe stiva
		pushl atoi_aux
	
loop:
	pushl $delim
	pushl $0
	call strtok
	popl %ebx
	popl %ebx
	
	cmp $0, %eax
	je exit
	
	movl %eax, aux
	
	pushl aux
	call atoi 
	popl %ebx
	
	movl %eax, atoi_aux
	//verific daca atoi_aux este operatie
	cmp $0, atoi_aux 
	je ASMD
	
	//daca e numar, sare de cmp precedent si e adaugat ca numar in stiva
	pushl atoi_aux
	
	jmp loop
	
//AddSubMulDiv
ASMD:

	//verific prima litera, iar in fct de ea stabilesc operatia
		//tratez auxiliarul ca pe un vector
		movl aux, %edi
		xorl %ecx, %ecx
		
		movb (%edi, %ecx, 1), %al
	//add
	cmp $97, %al
	   je addd
	//sub
	cmp $115, %al
	   je subb
	//mul
	cmp $109, %al
	   je mull
	//div
	cmp $100, %al
	   je divv
	   
addd:
	xorl %eax, %eax
	xorl %ecx, %ecx
	
		popl %ecx
		popl %eax
		addl %ecx, %eax
	
	pushl %eax
	
	jmp loop
subb:
	xorl %eax, %eax
	xorl %ecx, %ecx
	
		popl %ecx
		popl %eax
		subl %ecx, %eax
	
	pushl %eax
	
	jmp loop

divv:
	xorl %eax, %eax
	xorl %ecx, %ecx
	xorl %edx, %edx
	
		popl %ecx
		popl %eax
		divl %ecx
	
	pushl %eax
	
	jmp loop


mull:
	xorl %eax, %eax
	xorl %ecx, %ecx
	xorl %edx, %edx
	
		popl %ecx
		popl %eax
		mull %ecx
	
	pushl %eax
	
	jmp loop


exit:
	//scot de pe stiva rezultatul
	popl %ebx
	movl %ebx, rez
	
	//afisez rezultatul
	pushl rez
	pushl $pfd
	call printf
	popl %ebx
	popl %ebx
	
	//inchid programul
	movl $1, %eax
	xorl %ebx, %ebx
	int $0x80
