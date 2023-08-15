.data
	binar: .space 101
	hexa : .space 401
	
	sf : .asciz "%s"
	pfs : .asciz "%s "
	pfd : .asciz "%d "
	
	indexB2: .long 0
	suma : .long 0
	
	let: .asciz "let"
	div: .asciz "div"
	add: .asciz "add"
	mul: .asciz "mul"
	sub: .asciz "sub"
	
	v1: .long 1
	v2: .long 2
	v4: .long 4
	v8: .long 8
	v16: .long 16
	v32: .long 32
	v64: .long 64
	v128: .long 128
	v11: .long 11
	v12: .long 12
	
	aux1: .long 0
	aux2: .long 0
	v0: .long 0
	v3: .long 3
	
	minus: .asciz "-"
	endl: .asciz "\n"

.text

.global main

main:
	pushl $hexa
	push $sf
	call scanf
	popl %ebx
	popl %ebx
	
	movl $hexa, %edi
	movl $binar, %esi
	movl $0, %ecx
	
et_for:
	movb (%edi, %ecx, 1), %al
	cmp $0, %al
	je part_2
	
		cmp $48, %al
		je cif0
	
		cmp $49, %al
		je cif1
		
		cmp $50, %al
		je cif2
		
		cmp $51, %al
		je cif3
		
		cmp $52, %al
		je cif4
		
		cmp $53, %al
		je cif5
		
		cmp $54, %al
		je cif6
		
		cmp $55, %al
		je cif7
		
		cmp $56, %al
		je cif8
		
		cmp $57, %al
		je cif9
		
		cmp $65, %al
		je cifA
		
		cmp $66, %al
		je cifB
		
		cmp $67, %al
		je cifC
		
		cmp $68, %al
		je cifD
		
		cmp $69, %al
		je cifE
		
		cmp $70, %al
		je cifF
		
cont: 
	incl %ecx
	jmp et_for
	

		cif0: 
			pushl %ecx
			movl indexB2, %ecx
				movb $48, (%esi, %ecx, 1)
					incl %ecx
				movb $48, (%esi, %ecx, 1)
					incl %ecx
				movb $48, (%esi, %ecx, 1)
					incl %ecx
				movb $48, (%esi, %ecx, 1)
					incl %ecx
			addl $4, indexB2
			
			popl %ecx
			jmp cont
			
		cif1: 
			pushl %ecx
			movl indexB2, %ecx
				movb $48, (%esi, %ecx, 1)
					incl %ecx
				movb $48, (%esi, %ecx, 1)
					incl %ecx
				movb $48, (%esi, %ecx, 1)
					incl %ecx
				movb $49, (%esi, %ecx, 1)
					incl %ecx
			addl $4, indexB2
			
			popl %ecx
			jmp cont
			
		cif2: 
			pushl %ecx
			movl indexB2, %ecx
				movb $48, (%esi, %ecx, 1)
					incl %ecx
				movb $48, (%esi, %ecx, 1)
					incl %ecx
				movb $49, (%esi, %ecx, 1)
					incl %ecx
				movb $48, (%esi, %ecx, 1)
					incl %ecx
			addl $4, indexB2
			
			popl %ecx
			jmp cont
			
		cif3: 
			pushl %ecx
			movl indexB2, %ecx
				movb $48, (%esi, %ecx, 1)
					incl %ecx
				movb $48, (%esi, %ecx, 1)
					incl %ecx
				movb $49, (%esi, %ecx, 1)
					incl %ecx
				movb $49, (%esi, %ecx, 1)
					incl %ecx
			addl $4, indexB2
			
			popl %ecx
			jmp cont
			
		cif4: 
			pushl %ecx
			movl indexB2, %ecx
				movb $48, (%esi, %ecx, 1)
					incl %ecx
				movb $49, (%esi, %ecx, 1)
					incl %ecx
				movb $48, (%esi, %ecx, 1)
					incl %ecx
				movb $48, (%esi, %ecx, 1)
					incl %ecx
			addl $4, indexB2
			
			popl %ecx
			jmp cont
			
		cif5: 
			pushl %ecx
			movl indexB2, %ecx
				movb $48, (%esi, %ecx, 1)
					incl %ecx
				movb $49, (%esi, %ecx, 1)
					incl %ecx
				movb $48, (%esi, %ecx, 1)
					incl %ecx
				movb $49, (%esi, %ecx, 1)
					incl %ecx
			addl $4, indexB2
			
			popl %ecx
			jmp cont
			
		cif6: 
			pushl %ecx
			movl indexB2, %ecx
				movb $48, (%esi, %ecx, 1)
					incl %ecx
				movb $49, (%esi, %ecx, 1)
					incl %ecx
				movb $49, (%esi, %ecx, 1)
					incl %ecx
				movb $48, (%esi, %ecx, 1)
					incl %ecx
			addl $4, indexB2
			
			popl %ecx
			jmp cont
			
		cif7: 
			pushl %ecx
			movl indexB2, %ecx
				movb $48, (%esi, %ecx, 1)
					incl %ecx
				movb $49, (%esi, %ecx, 1)
					incl %ecx
				movb $49, (%esi, %ecx, 1)
					incl %ecx
				movb $49, (%esi, %ecx, 1)
					incl %ecx
			addl $4, indexB2
			
			popl %ecx
			jmp cont
			
		cif8: 
			pushl %ecx
			movl indexB2, %ecx
				movb $49, (%esi, %ecx, 1)
					incl %ecx
				movb $48, (%esi, %ecx, 1)
					incl %ecx
				movb $48, (%esi, %ecx, 1)
					incl %ecx
				movb $48, (%esi, %ecx, 1)
					incl %ecx
			addl $4, indexB2
			
			popl %ecx
			jmp cont
			
		cif9: 
			pushl %ecx
			movl indexB2, %ecx
				movb $49, (%esi, %ecx, 1)
					incl %ecx
				movb $48, (%esi, %ecx, 1)
					incl %ecx
				movb $48, (%esi, %ecx, 1)
					incl %ecx
				movb $49, (%esi, %ecx, 1)
					incl %ecx
			addl $4, indexB2
			
			popl %ecx
			jmp cont
			
		cifA: 
			pushl %ecx
			movl indexB2, %ecx
				movb $49, (%esi, %ecx, 1)
					incl %ecx
				movb $48, (%esi, %ecx, 1)
					incl %ecx
				movb $49, (%esi, %ecx, 1)
					incl %ecx
				movb $48, (%esi, %ecx, 1)
					incl %ecx
			addl $4, indexB2
			
			popl %ecx
			jmp cont
			
		cifB: 
			pushl %ecx
			movl indexB2, %ecx
				movb $49, (%esi, %ecx, 1)
					incl %ecx
				movb $48, (%esi, %ecx, 1)
					incl %ecx
				movb $49, (%esi, %ecx, 1)
					incl %ecx
				movb $49, (%esi, %ecx, 1)
					incl %ecx
			addl $4, indexB2
			
			popl %ecx
			jmp cont
			
		cifC: 
			pushl %ecx
			movl indexB2, %ecx
				movb $49, (%esi, %ecx, 1)
					incl %ecx
				movb $49, (%esi, %ecx, 1)
					incl %ecx
				movb $48, (%esi, %ecx, 1)
					incl %ecx
				movb $48, (%esi, %ecx, 1)
					incl %ecx
			addl $4, indexB2
			
			popl %ecx
			jmp cont
			
		cifD: 
			pushl %ecx
			movl indexB2, %ecx
				movb $49, (%esi, %ecx, 1)
					incl %ecx
				movb $49, (%esi, %ecx, 1)
					incl %ecx
				movb $48, (%esi, %ecx, 1)
					incl %ecx
				movb $49, (%esi, %ecx, 1)
					incl %ecx
			addl $4, indexB2
			
			popl %ecx
			jmp cont
		cifE: 
			pushl %ecx
			movl indexB2, %ecx
				movb $49, (%esi, %ecx, 1)
					incl %ecx
				movb $49, (%esi, %ecx, 1)
					incl %ecx
				movb $49, (%esi, %ecx, 1)
					incl %ecx
				movb $48, (%esi, %ecx, 1)
					incl %ecx
			addl $4, indexB2
			
			popl %ecx
			jmp cont
			
		cifF: 
			pushl %ecx
			movl indexB2, %ecx
				movb $49, (%esi, %ecx, 1)
					incl %ecx
				movb $49, (%esi, %ecx, 1)
					incl %ecx
				movb $49, (%esi, %ecx, 1)
					incl %ecx
				movb $49, (%esi, %ecx, 1)
					incl %ecx
			addl $4, indexB2
			
			popl %ecx
			jmp cont
			
// am facut codul binar, urmeaza trecerea in cuvinte

// parcurb nr cu nr, incepand de la 1

part_2:


xorl %ecx, %ecx

et_loop:
	movb (%esi, %ecx, 1), %al
	cmp $0, %al 
	je exit1
	
	movl %ecx, aux1
  et_0:	
  	xorl %eax, %eax
	movl v11, %ebx
	addl %ebx, %ecx
	movb (%esi, %ecx, 1), %al
	cmp $49, %al
	je s0
  et_1:
	decl %ecx
	xorl %eax, %eax
	movb (%esi, %ecx, 1), %al
	cmp $49, %al
	je s1
  et_2:	
	decl %ecx
	xorl %eax, %eax
	movb (%esi, %ecx, 1), %al
	cmp $49, %al
	je s2
  et_3:
	decl %ecx
	xorl %eax, %eax
	movb (%esi, %ecx, 1), %al
	cmp $49, %al
	je s3
  et_4:
	decl %ecx
	xorl %eax, %eax
	movb (%esi, %ecx, 1), %al
	cmp $49, %al
	je s4
  et_5:
	decl %ecx
	xorl %eax, %eax
	movb (%esi, %ecx, 1), %al
	cmp $49, %al
	je s5
  et_6:
	decl %ecx
	xorl %eax, %eax
	movb (%esi, %ecx, 1), %al
	cmp $49, %al
	je s6
  et_7:
	decl %ecx
	xorl %eax, %eax
	movb (%esi, %ecx, 1), %al
	cmp $49, %al
	je s7
  et_n:
  	decl %ecx
  	xorl %eax, %eax
	movb (%esi, %ecx, 1), %al
	cmp $49, %al
	je negativ
	
	
  et_numar:
	movl aux1, %ecx
	
	pushl %ecx
	
	incl %ecx
	xorl %eax, %eax
	movb (%esi, %ecx, 1), %al
	cmp $49, %al
	je op
	
	xorl %eax, %eax
	movb (%esi, %ecx, 1), %al
	cmp $48, %al
	je nrv
	
  identificator_out:	
	popl %ecx
	xorl %eax, %eax
	movb (%esi, %ecx, 1), %al
	cmp $48, %al
	je contor

contor:
	movl v12, %ebx	
	addl %ebx, %ecx
	xorl %ebx, %ebx
	movl %ebx, suma
	jmp et_loop
	
s0:
	movl v1, %ebx
	addl %ebx, suma
	jmp et_1
s1:
	movl v2, %ebx
	addl %ebx, suma
	jmp et_2
s2:
	movl v4, %ebx
	addl %ebx, suma
	jmp et_3
s3:
	movl v8, %ebx
	addl %ebx, suma
	jmp et_4
s4:
	movl v16, %ebx
	addl %ebx, suma
	jmp et_5
s5:
	movl v32, %ebx
	addl %ebx, suma
	jmp et_6
s6:
	movl v64, %ebx
	addl %ebx, suma
	jmp et_7
s7:
	movl v128, %ebx
	addl %ebx, suma
	jmp et_n
negativ:
	pushl %ecx
	pushl $minus
	call printf
	popl %ebx
	popl %ecx
	
	jmp et_numar
	
op:
	movl v0, %ebx
	cmp suma, %ebx
	je lett
	movl v1, %ebx
	cmp suma, %ebx
	je addd
	movl v2, %ebx
	cmp suma, %ebx
	je subb
	movl v3, %ebx
	cmp suma, %ebx
	je mull
	movl v4, %ebx
	cmp suma, %ebx
	je divv
	
	lett:
		pushl %ecx
		pushl $let
		pushl $pfs
		call printf
		popl %ebx
		popl %ebx
		popl %ecx
		
		jmp identificator_out
	addd:
		pushl %ecx
		pushl $add
		pushl $pfs
		call printf
		popl %ebx
		popl %ebx
		popl %ecx
		
		jmp identificator_out
	subb:
		pushl %ecx
		pushl $sub
		pushl $pfs
		call printf
		popl %ebx
		popl %ebx
		popl %ecx
		
		jmp identificator_out
	mull:
		pushl %ecx
		pushl $mul
		pushl $pfs
		call printf
		popl %ebx
		popl %ebx
		popl %ecx
		
		
		jmp identificator_out
	divv:
		pushl %ecx
		pushl $div
		pushl $pfs
		call printf
		popl %ebx
		popl %ebx
		popl %ecx
		
		jmp identificator_out
	
nrv:
	incl %ecx
	movb (%esi, %ecx, 1), %al
	cmp $48, %al
	je nr
	
	movb (%esi, %ecx, 1), %al
	cmp $49, %al
	je var
	
	nr:
		pushl %ecx
		pushl suma
		pushl $pfd
		call printf
		popl %ebx
		popl %ebx
		popl %ecx
		
		jmp identificator_out
		
	var:
		pushl %ecx
		pushl $suma
		pushl $pfs
		call printf
		popl %ebx
		popl %ebx
		popl %ecx
		
		jmp identificator_out
	


exit:
	pushl $binar
	pushl $pfs
	call printf
	popl %ebx
	popl %ebx
	
	movl $1, %eax
	xorl %ebx, %ebx
	int $0x80
exit1:
	pushl $endl
	call printf
	popl %ebx
		
 	movl $1, %eax
	xorl %ebx, %ebx
	int $0x80
