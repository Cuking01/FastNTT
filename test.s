	.file	"test.cpp"
	.text
	.section	.text.startup,"x"
	.align 2
	.p2align 4
	.def	_ZN3ymmC1Ev.isra.0;	.scl	3;	.type	32;	.endef
	.seh_proc	_ZN3ymmC1Ev.isra.0
_ZN3ymmC1Ev.isra.0:
.LFB10817:
	.seh_endprologue
	ret
	.seh_endproc
	.section	.text$_Z6printfPKcz,"x"
	.linkonce discard
	.p2align 4
	.globl	_Z6printfPKcz
	.def	_Z6printfPKcz;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z6printfPKcz
_Z6printfPKcz:
.LFB9:
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$56, %rsp
	.seh_stackalloc	56
	.seh_endprologue
	leaq	88(%rsp), %rsi
	movq	%rdx, 88(%rsp)
	movq	%rcx, %rbx
	movl	$1, %ecx
	movq	%r8, 96(%rsp)
	movq	%r9, 104(%rsp)
	movq	%rsi, 40(%rsp)
	call	*__imp___acrt_iob_func(%rip)
	movq	%rsi, %r8
	movq	%rbx, %rdx
	movq	%rax, %rcx
	call	__mingw_vfprintf
	addq	$56, %rsp
	popq	%rbx
	popq	%rsi
	ret
	.seh_endproc
	.section	.text$_ZN3ymmC1Ej,"x"
	.linkonce discard
	.align 2
	.p2align 4
	.globl	_ZN3ymmC1Ej
	.def	_ZN3ymmC1Ej;	.scl	2;	.type	32;	.endef
	.seh_proc	_ZN3ymmC1Ej
_ZN3ymmC1Ej:
.LFB10029:
	.seh_endprologue
	vmovd	%edx, %xmm0
	vpbroadcastd	%xmm0, %ymm0
	vmovdqu	%ymm0, (%rcx)
	vzeroupper
	ret
	.seh_endproc
	.text
	.p2align 4
	.globl	_Z2moj
	.def	_Z2moj;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z2moj
_Z2moj:
.LFB10053:
	.seh_endprologue
	movl	%ecx, %eax
	leal	-998244353(%rcx), %edx
	cmpl	$998244352, %ecx
	cmova	%edx, %eax
	ret
	.seh_endproc
	.p2align 4
	.globl	_Z5exgcdxxRxS_
	.def	_Z5exgcdxxRxS_;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z5exgcdxxRxS_
_Z5exgcdxxRxS_:
.LFB10055:
	pushq	%r13
	.seh_pushreg	%r13
	pushq	%r12
	.seh_pushreg	%r12
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movq	%rdx, %rbx
	movq	%r8, %rdi
	testq	%rdx, %rdx
	jne	.L9
	movq	%rcx, %rax
	movq	$1, (%r8)
	movq	%rbx, (%r9)
	addq	$32, %rsp
	popq	%rbx
	popq	%rdi
	popq	%rbp
	popq	%r12
	popq	%r13
	ret
	.p2align 4,,10
	.p2align 3
.L9:
	movq	%rcx, %rax
	cqto
	idivq	%rbx
	movq	%rdx, %r13
	movq	%rax, %rbp
	testq	%rdx, %rdx
	jne	.L11
	movq	$1, (%r9)
	xorl	%ecx, %ecx
	movq	%rbx, %rax
.L12:
	movq	%rcx, (%rdi)
	movq	(%r9), %rbx
	subq	%rdx, %rbx
	movq	%rbx, (%r9)
	addq	$32, %rsp
	popq	%rbx
	popq	%rdi
	popq	%rbp
	popq	%r12
	popq	%r13
	ret
	.p2align 4,,10
	.p2align 3
.L11:
	movq	%rbx, %rax
	cqto
	idivq	%r13
	movq	%rdx, %r12
	movq	%rax, %rbx
	testq	%rdx, %rdx
	jne	.L13
	movq	$1, (%r8)
	movq	%r13, %rax
	xorl	%r8d, %r8d
.L14:
	movq	%r8, (%r9)
	movq	(%rdi), %rcx
	subq	%rdx, %rcx
	movq	%rbp, %rdx
	imulq	%rcx, %rdx
	jmp	.L12
	.p2align 4,,10
	.p2align 3
.L13:
	movq	%r13, %rax
	cqto
	idivq	%r12
	movq	%rdx, %rcx
	movq	%rax, %r13
	testq	%rdx, %rdx
	jne	.L15
	movq	$1, (%r9)
	xorl	%edx, %edx
	movq	%r12, %rax
.L16:
	movq	%rdx, (%rdi)
	movq	(%r9), %r8
	subq	%rcx, %r8
	imulq	%r8, %rbx
	movq	%rbx, %rdx
	jmp	.L14
	.p2align 4,,10
	.p2align 3
.L15:
	movq	%r12, %rax
	movq	%r9, 104(%rsp)
	cqto
	idivq	%rcx
	movq	%rax, %r12
	call	_Z5exgcdxxRxS_
	movq	104(%rsp), %r9
	movq	%r12, %r8
	movq	(%rdi), %rdx
	movq	%r13, %rcx
	imulq	(%r9), %r8
	subq	%r8, %rdx
	imulq	%rdx, %rcx
	jmp	.L16
	.seh_endproc
	.p2align 4
	.globl	_Z7to_mogo3ymm
	.def	_Z7to_mogo3ymm;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z7to_mogo3ymm
_Z7to_mogo3ymm:
.LFB10057:
	.seh_endprologue
	vmovdqu	(%rdx), %ymm0
	movq	%rcx, %rax
	vmovdqu	%ymm0, (%rcx)
	vzeroupper
	ret
	.seh_endproc
	.p2align 4
	.globl	_Z7mogo_to3ymm
	.def	_Z7mogo_to3ymm;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z7mogo_to3ymm
_Z7mogo_to3ymm:
.LFB10058:
	.seh_endprologue
	vmovdqu	mogo_np(%rip), %ymm2
	vmovdqu	(%rdx), %ymm0
	vpsrlq	$32, %ymm0, %ymm1
	vpmuludq	%ymm2, %ymm0, %ymm0
	vpmuludq	%ymm2, %ymm1, %ymm1
	vmovdqu	mogo_n(%rip), %ymm2
	movq	%rcx, %rax
	vpmuludq	%ymm2, %ymm0, %ymm0
	vpmuludq	%ymm2, %ymm1, %ymm1
	vpsrlq	$32, %ymm0, %ymm0
	vpblendd	$170, %ymm1, %ymm0, %ymm0
	vmovdqu	mod_vec(%rip), %ymm1
	vpsubd	%ymm0, %ymm1, %ymm0
	vpcmpgtd	mod1_vec(%rip), %ymm0, %ymm2
	vpand	%ymm2, %ymm1, %ymm1
	vpsubd	%ymm1, %ymm0, %ymm0
	vmovdqu	%ymm0, (%rcx)
	vzeroupper
	ret
	.seh_endproc
	.p2align 4
	.globl	_Z3powjj
	.def	_Z3powjj;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z3powjj
_Z3powjj:
.LFB10059:
	.seh_endprologue
	movl	%edx, %r8d
	testl	%edx, %edx
	je	.L24
	movabsq	$-8525806094425994177, %r10
	movl	$1, %r9d
	.p2align 6
	.p2align 4
	.p2align 3
.L22:
	movl	%ecx, %ecx
	testb	$1, %r8b
	je	.L21
	imulq	%rcx, %r9
	imulq	%rcx, %rcx
	movq	%r9, %rax
	mulq	%r10
	movq	%rcx, %rax
	shrq	$29, %rdx
	imulq	$998244353, %rdx, %rdx
	subl	%edx, %r9d
	mulq	%r10
	shrq	$29, %rdx
	imulq	$998244353, %rdx, %rdx
	subl	%edx, %ecx
	shrl	%r8d
	jne	.L22
	movl	%r9d, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L21:
	imulq	%rcx, %rcx
	shrl	%r8d
	movq	%rcx, %rax
	mulq	%r10
	shrq	$29, %rdx
	imulq	$998244353, %rdx, %rdx
	subl	%edx, %ecx
	jmp	.L22
	.p2align 4,,10
	.p2align 3
.L24:
	movl	$1, %r9d
	movl	%r9d, %eax
	ret
	.seh_endproc
	.p2align 4
	.globl	_Z3mulRjj
	.def	_Z3mulRjj;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z3mulRjj
_Z3mulRjj:
.LFB10060:
	.seh_endprologue
	movabsq	$-8525806094425994177, %rax
	movl	(%rcx), %r8d
	movl	%edx, %edx
	imulq	%rdx, %r8
	mulq	%r8
	movq	%rcx, %rax
	shrq	$29, %rdx
	imulq	$998244353, %rdx, %rdx
	subq	%rdx, %r8
	movl	%r8d, (%rcx)
	ret
	.seh_endproc
	.p2align 4
	.globl	_Z2upi
	.def	_Z2upi;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z2upi
_Z2upi:
.LFB10061:
	.seh_endprologue
	movl	$1, %eax
	cmpl	$1, %ecx
	jle	.L29
	.p2align 3
	.p2align 4
	.p2align 3
.L31:
	addl	%eax, %eax
	cmpl	%eax, %ecx
	jg	.L31
.L29:
	ret
	.seh_endproc
	.p2align 4
	.globl	_Z4initi
	.def	_Z4initi;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z4initi
_Z4initi:
.LFB10062:
	pushq	%r15
	.seh_pushreg	%r15
	pushq	%r14
	.seh_pushreg	%r14
	pushq	%r13
	.seh_pushreg	%r13
	pushq	%r12
	.seh_pushreg	%r12
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$152, %rsp
	.seh_stackalloc	152
	vmovups	%xmm6, 16(%rsp)
	.seh_savexmm	%xmm6, 16
	vmovups	%xmm7, 32(%rsp)
	.seh_savexmm	%xmm7, 32
	vmovups	%xmm8, 48(%rsp)
	.seh_savexmm	%xmm8, 48
	vmovups	%xmm9, 64(%rsp)
	.seh_savexmm	%xmm9, 64
	vmovups	%xmm10, 80(%rsp)
	.seh_savexmm	%xmm10, 80
	vmovups	%xmm11, 96(%rsp)
	.seh_savexmm	%xmm11, 96
	vmovups	%xmm12, 112(%rsp)
	.seh_savexmm	%xmm12, 112
	vmovups	%xmm13, 128(%rsp)
	.seh_savexmm	%xmm13, 128
	.seh_endprologue
	movl	%ecx, 224(%rsp)
	cmpl	$1, %ecx
	jle	.L71
	vmovdqu	mod_vec(%rip), %ymm5
	movl	$1, %ebp
	vmovdqu	mogo_np(%rip), %ymm4
	leaq	wr(%rip), %r15
	vmovdqu	mogo_n(%rip), %ymm3
	movl	%ebp, %r14d
	vmovdqu	mod1_vec(%rip), %ymm6
	leaq	wi(%rip), %r12
	movabsq	$-8525806094425994177, %r9
	vmovdqa	%ymm5, %ymm7
	.p2align 4
	.p2align 3
.L54:
	leal	(%r14,%r14), %esi
	movl	$998244352, %eax
	xorl	%edx, %edx
	divl	%esi
	movl	%esi, 12(%rsp)
	movl	%eax, %r11d
	cmpl	$998244352, %esi
	ja	.L36
	movl	%eax, %esi
	movl	$3, %r10d
	movl	$1, %r8d
	.p2align 4
	.p2align 3
.L39:
	movl	%esi, %ecx
	andl	$1, %ecx
	je	.L37
	imulq	%r10, %r8
	imulq	%r10, %r10
	movq	%r8, %rax
	mulq	%r9
	movq	%rdx, %rbx
	shrq	$29, %rbx
	imulq	$998244353, %rbx, %rax
	movq	%r8, %rbx
	subq	%rax, %rbx
	movq	%r10, %rax
	mulq	%r9
	movl	%ebx, %r8d
	shrq	$29, %rdx
	imulq	$998244353, %rdx, %rdx
	subl	%edx, %r10d
	shrl	%esi
	jne	.L39
	movl	$332748118, %r10d
	.p2align 4
	.p2align 3
.L38:
	movl	%r11d, %edi
	andl	$1, %edi
	je	.L42
	movl	%ecx, %ecx
	imulq	%r10, %rcx
	imulq	%r10, %r10
	movq	%rcx, %rax
	mulq	%r9
	movq	%rdx, %rsi
	shrq	$29, %rsi
	imulq	$998244353, %rsi, %rax
	movq	%rcx, %rsi
	subq	%rax, %rsi
	movq	%r10, %rax
	mulq	%r9
	movl	%esi, %ecx
	shrq	$29, %rdx
	imulq	$998244353, %rdx, %rdx
	subl	%edx, %r10d
	shrl	%r11d
	jne	.L38
	cmpl	$7, %r14d
	jg	.L41
	testl	%r14d, %r14d
	jle	.L40
	movslq	%r14d, %r10
	movl	%edi, %ecx
	leaq	0(,%r10,4), %r8
	salq	$3, %r10
	.p2align 4
	.p2align 3
.L46:
	movl	%edi, (%r15,%r8)
	movl	%edi, %edi
	imulq	%rbx, %rdi
	movl	%ecx, (%r12,%r8)
	addq	$4, %r8
	imulq	%rsi, %rcx
	movq	%rdi, %rax
	mulq	%r9
	movq	%rcx, %rax
	shrq	$29, %rdx
	imulq	$998244353, %rdx, %rdx
	subl	%edx, %edi
	mulq	%r9
	shrq	$29, %rdx
	imulq	$998244353, %rdx, %rdx
	subl	%edx, %ecx
	cmpq	%r8, %r10
	jne	.L46
.L40:
	movl	12(%rsp), %r14d
	cmpl	%r14d, 224(%rsp)
	jg	.L54
.L72:
	vzeroupper
.L71:
	vmovups	16(%rsp), %xmm6
	vmovups	32(%rsp), %xmm7
	vmovups	48(%rsp), %xmm8
	vmovups	64(%rsp), %xmm9
	vmovups	80(%rsp), %xmm10
	vmovups	96(%rsp), %xmm11
	vmovups	128(%rsp), %xmm13
	vmovups	112(%rsp), %xmm12
	addq	$152, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	popq	%rbp
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	ret
	.p2align 4,,10
	.p2align 3
.L42:
	imulq	%r10, %r10
	shrl	%r11d
	movq	%r10, %rax
	mulq	%r9
	shrq	$29, %rdx
	imulq	$998244353, %rdx, %rdx
	subl	%edx, %r10d
	jmp	.L38
	.p2align 4,,10
	.p2align 3
.L37:
	imulq	%r10, %r10
	shrl	%esi
	movq	%r10, %rax
	mulq	%r9
	shrq	$29, %rdx
	imulq	$998244353, %rdx, %rdx
	subl	%edx, %r10d
	jmp	.L39
	.p2align 4,,10
	.p2align 3
.L36:
	cmpl	$7, %r14d
	jle	.L40
	movl	$1, %ebx
	movl	$1, %esi
	movl	$1, %ecx
	movl	$1, %r8d
	.p2align 4
	.p2align 3
.L41:
	movslq	%r14d, %rbp
	xorl	%edi, %edi
	movl	$1, %r11d
	movl	$1, %r10d
	salq	$2, %rbp
	leaq	(%r15,%rbp), %r13
	addq	%r12, %rbp
	.p2align 4
	.p2align 3
.L45:
	movl	%r10d, 0(%r13,%rdi)
	imulq	%rbx, %r10
	movl	%r11d, 0(%rbp,%rdi)
	imulq	%rsi, %r11
	addq	$4, %rdi
	movq	%r10, %rax
	mulq	%r9
	movq	%r11, %rax
	shrq	$29, %rdx
	imulq	$998244353, %rdx, %rdx
	subl	%edx, %r10d
	mulq	%r9
	shrq	$29, %rdx
	imulq	$998244353, %rdx, %rdx
	subl	%edx, %r11d
	cmpq	$32, %rdi
	jne	.L45
	vmovdqu	0(%r13), %ymm2
	vmovdqu	0(%rbp), %ymm0
	movl	$1, %ebx
	movl	$4, %r11d
	movl	$8, %r10d
	.p2align 6
	.p2align 4
	.p2align 3
.L48:
	testb	$1, %r10b
	je	.L47
	imulq	%r8, %rbx
	movq	%rbx, %rax
	mulq	%r9
	shrq	$29, %rdx
	imulq	$998244353, %rdx, %rdx
	subl	%edx, %ebx
.L47:
	imulq	%r8, %r8
	shrl	%r10d
	movq	%r8, %rax
	mulq	%r9
	shrq	$29, %rdx
	imulq	$998244353, %rdx, %rdx
	subl	%edx, %r8d
	subl	$1, %r11d
	jne	.L48
	vmovd	%ebx, %xmm9
	movl	$4, %r10d
	movl	$1, %r11d
	movl	$8, %r8d
	vpbroadcastd	%xmm9, %ymm9
	.p2align 6
	.p2align 4
	.p2align 3
.L50:
	testb	$1, %r8b
	je	.L49
	imulq	%rcx, %r11
	movq	%r11, %rax
	mulq	%r9
	shrq	$29, %rdx
	imulq	$998244353, %rdx, %rdx
	subl	%edx, %r11d
.L49:
	imulq	%rcx, %rcx
	shrl	%r8d
	movq	%rcx, %rax
	mulq	%r9
	shrq	$29, %rdx
	imulq	$998244353, %rdx, %rdx
	subl	%edx, %ecx
	subl	$1, %r10d
	jne	.L50
	vmovd	%r11d, %xmm8
	vpsrlq	$32, %ymm9, %ymm11
	movl	$8, %eax
	vpbroadcastd	%xmm8, %ymm8
	vpsrlq	$32, %ymm8, %ymm10
	cmpl	$8, %r14d
	je	.L40
	.p2align 4
	.p2align 3
.L52:
	vpmuludq	%ymm2, %ymm9, %ymm1
	vpsrlq	$32, %ymm2, %ymm12
	vpmuludq	%ymm12, %ymm11, %ymm12
	vpmuludq	%ymm4, %ymm1, %ymm2
	vpsrlq	$32, %ymm1, %ymm1
	vpmuludq	%ymm4, %ymm12, %ymm13
	vpblendd	$170, %ymm12, %ymm1, %ymm1
	vpaddd	%ymm7, %ymm1, %ymm1
	vpsrlq	$32, %ymm0, %ymm12
	vpmuludq	%ymm12, %ymm10, %ymm12
	vpmuludq	%ymm3, %ymm2, %ymm2
	vpmuludq	%ymm3, %ymm13, %ymm13
	vpsrlq	$32, %ymm2, %ymm2
	vpblendd	$170, %ymm13, %ymm2, %ymm2
	vpmuludq	%ymm4, %ymm12, %ymm13
	vpsubd	%ymm2, %ymm1, %ymm1
	vpcmpgtd	%ymm6, %ymm1, %ymm2
	vpand	%ymm2, %ymm5, %ymm2
	vpmuludq	%ymm3, %ymm13, %ymm13
	vpsubd	%ymm2, %ymm1, %ymm1
	vmovdqu	%ymm1, 0(%r13,%rax,4)
	vmovdqa	%ymm1, %ymm2
	vpmuludq	%ymm0, %ymm8, %ymm1
	vpmuludq	%ymm4, %ymm1, %ymm0
	vpsrlq	$32, %ymm1, %ymm1
	vpblendd	$170, %ymm12, %ymm1, %ymm1
	vpaddd	%ymm7, %ymm1, %ymm1
	vpmuludq	%ymm3, %ymm0, %ymm0
	vpsrlq	$32, %ymm0, %ymm0
	vpblendd	$170, %ymm13, %ymm0, %ymm0
	vpsubd	%ymm0, %ymm1, %ymm1
	vpcmpgtd	%ymm6, %ymm1, %ymm0
	vpand	%ymm0, %ymm5, %ymm0
	vpsubd	%ymm0, %ymm1, %ymm1
	vmovdqu	%ymm1, 0(%rbp,%rax,4)
	addq	$8, %rax
	vmovdqa	%ymm1, %ymm0
	cmpl	%eax, %r14d
	jg	.L52
	movl	12(%rsp), %r14d
	cmpl	%r14d, 224(%rsp)
	jg	.L54
	jmp	.L72
	.seh_endproc
	.p2align 4
	.globl	_Z5NTTfaPji
	.def	_Z5NTTfaPji;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z5NTTfaPji
_Z5NTTfaPji:
.LFB10063:
	pushq	%r15
	.seh_pushreg	%r15
	pushq	%r14
	.seh_pushreg	%r14
	pushq	%r13
	.seh_pushreg	%r13
	pushq	%r12
	.seh_pushreg	%r12
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$104, %rsp
	.seh_stackalloc	104
	vmovups	%xmm6, 32(%rsp)
	.seh_savexmm	%xmm6, 32
	vmovups	%xmm7, 48(%rsp)
	.seh_savexmm	%xmm7, 48
	vmovups	%xmm8, 64(%rsp)
	.seh_savexmm	%xmm8, 64
	vmovups	%xmm9, 80(%rsp)
	.seh_savexmm	%xmm9, 80
	.seh_endprologue
	leaq	.L89(%rip), %r15
	movl	%edx, %r13d
	movq	%rcx, %r8
	sarl	%edx
	.p2align 4
	.p2align 3
.L74:
	cmpl	$8, %edx
	ja	.L87
	movl	%edx, %eax
	movslq	(%r15,%rax,4), %rax
	addq	%r15, %rax
	jmp	*%rax
	.section .rdata,"dr"
	.align 4
.L89:
	.long	.L104-.L89
	.long	.L90-.L89
	.long	.L77-.L89
	.long	.L87-.L89
	.long	.L81-.L89
	.long	.L87-.L89
	.long	.L87-.L89
	.long	.L87-.L89
	.long	.L88-.L89
	.text
	.p2align 4,,10
	.p2align 3
.L87:
	testl	%r13d, %r13d
	jle	.L76
	movslq	%edx, %rax
	leal	(%rdx,%rdx), %r12d
	leaq	64(%r8), %rbp
	xorl	%edi, %edi
	salq	$2, %rax
	movslq	%r12d, %r12
	movq	%rax, %rsi
	movq	%rax, 8(%rsp)
	leaq	wr(%rip), %rax
	leaq	0(,%r12,4), %r14
	addq	%rsi, %rax
	movq	%rax, 16(%rsp)
	leal	-1(%rdx), %eax
	shrl	$4, %eax
	salq	$4, %rax
.L92:
	testl	%edx, %edx
	jg	.L105
	addq	%r12, %rdi
	addq	%r14, %rbp
	cmpl	%edi, %r13d
	jg	.L92
.L76:
	sarl	%edx
	jmp	.L74
.L88:
	testl	%r13d, %r13d
	jle	.L76
	leal	-1(%r13), %ecx
	leaq	64(%r8), %rax
	shrl	$4, %ecx
	leaq	mod1_vec(%rip), %r9
	leaq	mogo_np(%rip), %rbx
	salq	$6, %rcx
	leaq	mogo_n(%rip), %r11
	leaq	128(%r8,%rcx), %rcx
	.p2align 4
	.p2align 3
.L83:
	vmovdqu	-32(%rax), %ymm4
	vmovdqu	-64(%rax), %ymm0
	prefetcht0	(%rax)
	addq	$64, %rax
	vmovdqu	32+wr(%rip), %ymm5
	vpaddd	%ymm4, %ymm0, %ymm1
	vpcmpgtd	(%r9), %ymm1, %ymm2
	vpand	mod_vec(%rip), %ymm2, %ymm2
	vpsubd	%ymm2, %ymm1, %ymm1
	vmovdqu	%ymm1, -128(%rax)
	vpsrlq	$32, %ymm5, %ymm1
	vmovdqu	(%rbx), %ymm2
	vmovdqu	mod_vec(%rip), %ymm3
	vpaddd	%ymm3, %ymm0, %ymm0
	vpsubd	%ymm4, %ymm0, %ymm0
	vpsrlq	$32, %ymm0, %ymm4
	vpmuludq	%ymm5, %ymm0, %ymm0
	vmovdqu	(%r11), %ymm5
	vpmuludq	%ymm1, %ymm4, %ymm4
	vpmuludq	%ymm2, %ymm0, %ymm1
	vpsrlq	$32, %ymm0, %ymm0
	vpmuludq	%ymm2, %ymm4, %ymm2
	vpblendd	$170, %ymm4, %ymm0, %ymm0
	vpaddd	%ymm3, %ymm0, %ymm0
	vpmuludq	%ymm5, %ymm1, %ymm1
	vpmuludq	%ymm5, %ymm2, %ymm2
	vpsrlq	$32, %ymm1, %ymm1
	vpblendd	$170, %ymm2, %ymm1, %ymm1
	vpsubd	%ymm1, %ymm0, %ymm0
	vpcmpgtd	(%r9), %ymm0, %ymm1
	vpand	%ymm1, %ymm3, %ymm3
	vpsubd	%ymm3, %ymm0, %ymm0
	vmovdqu	%ymm0, -96(%rax)
	cmpq	%rax, %rcx
	jne	.L83
	sarl	%edx
	jmp	.L74
.L81:
	vbroadcasti128	16+wr(%rip), %ymm5
	testl	%r13d, %r13d
	jle	.L76
	leal	-1(%r13), %ecx
	leaq	64(%r8), %rax
	vpsrlq	$32, %ymm5, %ymm4
	shrl	$4, %ecx
	leaq	mod1_vec(%rip), %r9
	leaq	mogo_np(%rip), %rbx
	salq	$6, %rcx
	leaq	mogo_n(%rip), %r11
	leaq	128(%r8,%rcx), %rcx
	.p2align 4
	.p2align 3
.L82:
	vmovdqu	-32(%rax), %ymm1
	vmovdqu	-64(%rax), %ymm2
	prefetcht0	(%rax)
	addq	$64, %rax
	vmovdqu	mod_vec(%rip), %ymm3
	vmovdqu	(%r9), %ymm6
	vperm2i128	$32, %ymm1, %ymm2, %ymm0
	vperm2i128	$49, %ymm1, %ymm2, %ymm2
	vmovdqu	(%r11), %ymm9
	vpaddd	%ymm0, %ymm2, %ymm1
	vpaddd	%ymm0, %ymm3, %ymm0
	vpcmpgtd	%ymm6, %ymm1, %ymm7
	vpsubd	%ymm2, %ymm0, %ymm0
	vpsrlq	$32, %ymm0, %ymm8
	vpmuludq	%ymm5, %ymm0, %ymm0
	vpmuludq	%ymm4, %ymm8, %ymm8
	vpand	%ymm7, %ymm3, %ymm7
	vpsubd	%ymm7, %ymm1, %ymm1
	vmovdqu	(%rbx), %ymm7
	vpmuludq	%ymm7, %ymm0, %ymm2
	vpsrlq	$32, %ymm0, %ymm0
	vpmuludq	%ymm7, %ymm8, %ymm7
	vpblendd	$170, %ymm8, %ymm0, %ymm0
	vpaddd	%ymm3, %ymm0, %ymm0
	vpmuludq	%ymm9, %ymm2, %ymm2
	vpmuludq	%ymm9, %ymm7, %ymm7
	vpsrlq	$32, %ymm2, %ymm2
	vpblendd	$170, %ymm7, %ymm2, %ymm2
	vpsubd	%ymm2, %ymm0, %ymm0
	vpcmpgtd	%ymm6, %ymm0, %ymm6
	vpand	%ymm6, %ymm3, %ymm3
	vpsubd	%ymm3, %ymm0, %ymm0
	vperm2i128	$32, %ymm0, %ymm1, %ymm2
	vperm2i128	$49, %ymm0, %ymm1, %ymm1
	vmovdqu	%ymm2, -128(%rax)
	vmovdqu	%ymm1, -96(%rax)
	cmpq	%rax, %rcx
	jne	.L82
	sarl	%edx
	jmp	.L74
.L77:
	vmovd	8+wr(%rip), %xmm6
	vpinsrd	$1, 12+wr(%rip), %xmm6, %xmm3
	vpunpcklqdq	%xmm3, %xmm3, %xmm3
	vinserti128	$1, %xmm3, %ymm3, %ymm3
	testl	%r13d, %r13d
	jle	.L76
	leal	-1(%r13), %ecx
	leaq	64(%r8), %rax
	vpsrlq	$32, %ymm3, %ymm4
	shrl	$4, %ecx
	leaq	mod1_vec(%rip), %r9
	leaq	mogo_np(%rip), %rbx
	salq	$6, %rcx
	leaq	mogo_n(%rip), %r11
	leaq	128(%r8,%rcx), %rcx
	.p2align 4
	.p2align 3
.L79:
	vmovdqu	-32(%rax), %ymm2
	vmovdqu	-64(%rax), %ymm1
	prefetcht0	(%rax)
	addq	$64, %rax
	vmovdqu	mod_vec(%rip), %ymm5
	vmovdqu	(%r9), %ymm6
	vpslldq	$8, %ymm2, %ymm0
	vmovdqu	(%r11), %ymm9
	vpblendd	$204, %ymm0, %ymm1, %ymm0
	vpsrldq	$8, %ymm1, %ymm1
	vpblendd	$51, %ymm1, %ymm2, %ymm2
	vpaddd	%ymm2, %ymm0, %ymm1
	vpaddd	%ymm5, %ymm0, %ymm0
	vpcmpgtd	%ymm6, %ymm1, %ymm7
	vpsubd	%ymm2, %ymm0, %ymm0
	vpsrlq	$32, %ymm0, %ymm8
	vpmuludq	%ymm3, %ymm0, %ymm0
	vpmuludq	%ymm4, %ymm8, %ymm8
	vpand	%ymm7, %ymm5, %ymm7
	vpsubd	%ymm7, %ymm1, %ymm1
	vmovdqu	(%rbx), %ymm7
	vpmuludq	%ymm7, %ymm0, %ymm2
	vpsrlq	$32, %ymm0, %ymm0
	vpmuludq	%ymm7, %ymm8, %ymm7
	vpblendd	$170, %ymm8, %ymm0, %ymm0
	vpaddd	%ymm5, %ymm0, %ymm0
	vpmuludq	%ymm9, %ymm2, %ymm2
	vpmuludq	%ymm9, %ymm7, %ymm7
	vpsrlq	$32, %ymm2, %ymm2
	vpblendd	$170, %ymm7, %ymm2, %ymm2
	vpsubd	%ymm2, %ymm0, %ymm0
	vpcmpgtd	%ymm6, %ymm0, %ymm6
	vpand	%ymm6, %ymm5, %ymm5
	vpsubd	%ymm5, %ymm0, %ymm0
	vpslldq	$8, %ymm0, %ymm2
	vpblendd	$204, %ymm2, %ymm1, %ymm2
	vpsrldq	$8, %ymm1, %ymm1
	vpblendd	$51, %ymm1, %ymm0, %ymm0
	vmovdqu	%ymm2, -128(%rax)
	vmovdqu	%ymm0, -96(%rax)
	cmpq	%rax, %rcx
	jne	.L79
	sarl	%edx
	jmp	.L74
.L90:
	testl	%r13d, %r13d
	jle	.L76
	leal	-1(%r13), %ecx
	leaq	64(%r8), %rax
	shrl	$4, %ecx
	leaq	mod1_vec(%rip), %r9
	salq	$6, %rcx
	leaq	128(%r8,%rcx), %rcx
	.p2align 4
	.p2align 3
.L75:
	vmovdqu	-64(%rax), %ymm3
	vmovdqu	mod_vec(%rip), %ymm2
	prefetcht0	(%rax)
	addq	$64, %rax
	vpsllq	$32, %ymm3, %ymm1
	vpsrlq	$32, %ymm3, %ymm0
	vpaddd	%ymm2, %ymm1, %ymm1
	vpaddd	%ymm0, %ymm3, %ymm0
	vpsubd	%ymm3, %ymm1, %ymm1
	vmovdqu	-96(%rax), %ymm3
	vpblendd	$170, %ymm1, %ymm0, %ymm0
	vpcmpgtd	(%r9), %ymm0, %ymm1
	vpand	%ymm1, %ymm2, %ymm2
	vpsllq	$32, %ymm3, %ymm1
	vpsubd	%ymm2, %ymm0, %ymm0
	vmovdqu	%ymm0, -128(%rax)
	vmovdqu	mod_vec(%rip), %ymm2
	vpsrlq	$32, %ymm3, %ymm0
	vpaddd	%ymm0, %ymm3, %ymm0
	vpaddd	%ymm2, %ymm1, %ymm1
	vpsubd	%ymm3, %ymm1, %ymm1
	vpblendd	$170, %ymm1, %ymm0, %ymm0
	vpcmpgtd	(%r9), %ymm0, %ymm1
	vpand	%ymm1, %ymm2, %ymm2
	vpsubd	%ymm2, %ymm0, %ymm0
	vmovdqu	%ymm0, -96(%rax)
	cmpq	%rcx, %rax
	jne	.L75
	sarl	%edx
	jmp	.L74
.L104:
	vzeroupper
	vmovups	32(%rsp), %xmm6
	vmovups	48(%rsp), %xmm7
	vmovups	64(%rsp), %xmm8
	vmovups	80(%rsp), %xmm9
	addq	$104, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	popq	%rbp
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	ret
	.p2align 4,,10
	.p2align 3
.L105:
	movl	%edx, 28(%rsp)
	leaq	128(%r8), %rsi
	leaq	mod1_vec(%rip), %r9
	movq	%rax, %r10
	movq	%r8, 176(%rsp)
	leaq	mogo_np(%rip), %rbx
	leaq	mogo_n(%rip), %r11
	.p2align 4
	.p2align 3
.L85:
	movq	8(%rsp), %rax
	movq	16(%rsp), %rcx
	leaq	0(%rbp,%rax), %rdx
	leaq	(%rdi,%r10), %rax
	leaq	(%rsi,%rax,4), %r8
	movq	%rbp, %rax
	.p2align 4
	.p2align 3
.L84:
	vmovdqu	-64(%rdx), %ymm4
	vmovdqu	-64(%rax), %ymm0
	prefetcht0	(%rax)
	prefetcht0	(%rdx)
	vmovdqu	(%rcx), %ymm5
	addq	$64, %rax
	addq	$64, %rcx
	addq	$64, %rdx
	vpaddd	%ymm4, %ymm0, %ymm1
	vpcmpgtd	(%r9), %ymm1, %ymm2
	vpand	mod_vec(%rip), %ymm2, %ymm2
	vpsubd	%ymm2, %ymm1, %ymm1
	vmovdqu	%ymm1, -128(%rax)
	vpsrlq	$32, %ymm5, %ymm1
	vmovdqu	(%rbx), %ymm2
	vmovdqu	mod_vec(%rip), %ymm3
	vpaddd	%ymm3, %ymm0, %ymm0
	vpsubd	%ymm4, %ymm0, %ymm0
	vpsrlq	$32, %ymm0, %ymm4
	vpmuludq	%ymm5, %ymm0, %ymm0
	vmovdqu	(%r11), %ymm5
	vpmuludq	%ymm1, %ymm4, %ymm4
	vpmuludq	%ymm2, %ymm0, %ymm1
	vpsrlq	$32, %ymm0, %ymm0
	vpmuludq	%ymm2, %ymm4, %ymm2
	vpblendd	$170, %ymm4, %ymm0, %ymm0
	vmovdqu	-96(%rdx), %ymm4
	vpaddd	%ymm3, %ymm0, %ymm0
	vpmuludq	%ymm5, %ymm1, %ymm1
	vpmuludq	%ymm5, %ymm2, %ymm2
	vpsrlq	$32, %ymm1, %ymm1
	vpblendd	$170, %ymm2, %ymm1, %ymm1
	vpsubd	%ymm1, %ymm0, %ymm0
	vpcmpgtd	(%r9), %ymm0, %ymm1
	vpand	%ymm1, %ymm3, %ymm3
	vpsubd	%ymm3, %ymm0, %ymm0
	vmovdqu	%ymm0, -128(%rdx)
	vmovdqu	-96(%rax), %ymm0
	vmovdqu	-32(%rcx), %ymm5
	vpaddd	%ymm4, %ymm0, %ymm1
	vpcmpgtd	(%r9), %ymm1, %ymm2
	vpand	mod_vec(%rip), %ymm2, %ymm2
	vpsubd	%ymm2, %ymm1, %ymm1
	vmovdqu	%ymm1, -96(%rax)
	vpsrlq	$32, %ymm5, %ymm1
	vmovdqu	(%rbx), %ymm2
	vmovdqu	mod_vec(%rip), %ymm3
	vpaddd	%ymm3, %ymm0, %ymm0
	vpsubd	%ymm4, %ymm0, %ymm0
	vpsrlq	$32, %ymm0, %ymm4
	vpmuludq	%ymm5, %ymm0, %ymm0
	vmovdqu	(%r11), %ymm5
	vpmuludq	%ymm1, %ymm4, %ymm4
	vpmuludq	%ymm2, %ymm0, %ymm1
	vpsrlq	$32, %ymm0, %ymm0
	vpmuludq	%ymm2, %ymm4, %ymm2
	vpblendd	$170, %ymm4, %ymm0, %ymm0
	vpaddd	%ymm3, %ymm0, %ymm0
	vpmuludq	%ymm5, %ymm1, %ymm1
	vpmuludq	%ymm5, %ymm2, %ymm2
	vpsrlq	$32, %ymm1, %ymm1
	vpblendd	$170, %ymm2, %ymm1, %ymm1
	vpsubd	%ymm1, %ymm0, %ymm0
	vpcmpgtd	(%r9), %ymm0, %ymm1
	vpand	%ymm1, %ymm3, %ymm3
	vpsubd	%ymm3, %ymm0, %ymm0
	vmovdqu	%ymm0, -96(%rdx)
	cmpq	%r8, %rax
	jne	.L84
	addq	%r12, %rdi
	addq	%r14, %rbp
	cmpl	%edi, %r13d
	jg	.L85
	movl	28(%rsp), %edx
	movq	176(%rsp), %r8
	sarl	%edx
	jmp	.L74
	.seh_endproc
	.p2align 4
	.globl	_Z6NTTifaPji
	.def	_Z6NTTifaPji;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z6NTTifaPji
_Z6NTTifaPji:
.LFB10076:
	pushq	%r15
	.seh_pushreg	%r15
	pushq	%r14
	.seh_pushreg	%r14
	pushq	%r13
	.seh_pushreg	%r13
	pushq	%r12
	.seh_pushreg	%r12
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$120, %rsp
	.seh_stackalloc	120
	vmovups	%xmm6, 48(%rsp)
	.seh_savexmm	%xmm6, 48
	vmovups	%xmm7, 64(%rsp)
	.seh_savexmm	%xmm7, 64
	vmovups	%xmm8, 80(%rsp)
	.seh_savexmm	%xmm8, 80
	vmovups	%xmm9, 96(%rsp)
	.seh_savexmm	%xmm9, 96
	.seh_endprologue
	movq	%rcx, 192(%rsp)
	movl	%edx, %r15d
	cmpl	$1, %edx
	jle	.L142
	leal	-1(%rdx), %r10d
	movq	192(%rsp), %rax
	leaq	mod1_vec(%rip), %rcx
	movl	%r10d, %edx
	shrl	$4, %edx
	leaq	128(%rax), %r14
	addq	$64, %rax
	salq	$6, %rdx
	leaq	(%r14,%rdx), %r8
	leaq	(%rax,%rdx), %r11
	movq	%rax, %rdx
	.p2align 4
	.p2align 3
.L110:
	vmovdqu	-64(%rdx), %ymm3
	vmovdqu	mod_vec(%rip), %ymm2
	prefetcht0	(%rdx)
	addq	$64, %rdx
	vpsllq	$32, %ymm3, %ymm1
	vpsrlq	$32, %ymm3, %ymm0
	vpaddd	%ymm2, %ymm1, %ymm1
	vpaddd	%ymm0, %ymm3, %ymm0
	vpsubd	%ymm3, %ymm1, %ymm1
	vmovdqu	-96(%rdx), %ymm3
	vpblendd	$170, %ymm1, %ymm0, %ymm0
	vpcmpgtd	(%rcx), %ymm0, %ymm1
	vpand	%ymm1, %ymm2, %ymm2
	vpsllq	$32, %ymm3, %ymm1
	vpsubd	%ymm2, %ymm0, %ymm0
	vmovdqu	%ymm0, -128(%rdx)
	vmovdqu	mod_vec(%rip), %ymm2
	vpsrlq	$32, %ymm3, %ymm0
	vpaddd	%ymm0, %ymm3, %ymm0
	vpaddd	%ymm2, %ymm1, %ymm1
	vpsubd	%ymm3, %ymm1, %ymm1
	vpblendd	$170, %ymm1, %ymm0, %ymm0
	vpcmpgtd	(%rcx), %ymm0, %ymm1
	vpand	%ymm1, %ymm2, %ymm2
	vpsubd	%ymm2, %ymm0, %ymm0
	vmovdqu	%ymm0, -96(%rdx)
	cmpq	%rdx, %r8
	jne	.L110
	movq	%rax, %rdx
	movl	$2, %r9d
	movl	%r10d, %eax
.L111:
	cmpl	%r9d, %r15d
	jle	.L140
.L146:
	cmpl	$2, %r9d
	je	.L143
	cmpl	$4, %r9d
	je	.L144
	cmpl	$8, %r9d
	je	.L116
	leal	(%r9,%r9), %edi
	movslq	%r9d, %rbp
	movq	%rdx, %rsi
	xorl	%ebx, %ebx
	movslq	%edi, %r12
	movl	%edi, 44(%rsp)
	salq	$2, %rbp
	leaq	wi(%rip), %rdi
	addq	%rbp, %rdi
	leaq	0(,%r12,4), %r13
	movq	%rdi, 8(%rsp)
	leal	-1(%r9), %edi
	shrl	$4, %edi
	salq	$4, %rdi
	testl	%r9d, %r9d
	jg	.L145
.L137:
	addq	%r12, %rbx
	addq	%r13, %rsi
	cmpl	%ebx, %r15d
	jle	.L121
	testl	%r9d, %r9d
	jle	.L137
.L145:
	movq	%r8, 16(%rsp)
	leaq	mogo_np(%rip), %r10
	leaq	mogo_n(%rip), %r9
	movq	%r11, 24(%rsp)
	movl	%eax, 40(%rsp)
	movq	%rdx, 32(%rsp)
	.p2align 4
	.p2align 3
.L120:
	leaq	(%rdi,%rbx), %rax
	movq	8(%rsp), %r8
	leaq	0(%rbp,%rsi), %rdx
	leaq	(%r14,%rax,4), %r11
	movq	%rsi, %rax
	.p2align 4
	.p2align 3
.L119:
	vmovdqu	(%r8), %ymm1
	vmovdqu	-64(%rdx), %ymm0
	prefetcht0	(%rax)
	prefetcht0	(%rdx)
	vmovdqu	(%rcx), %ymm6
	addq	$64, %rax
	addq	$64, %r8
	addq	$64, %rdx
	vpsrlq	$32, %ymm1, %ymm2
	vpsrlq	$32, %ymm0, %ymm3
	vmovdqu	(%r9), %ymm4
	vpmuludq	%ymm1, %ymm0, %ymm0
	vpmuludq	%ymm2, %ymm3, %ymm3
	vmovdqu	(%r10), %ymm2
	vpmuludq	%ymm2, %ymm0, %ymm1
	vpmuludq	%ymm2, %ymm3, %ymm2
	vpsrlq	$32, %ymm0, %ymm0
	vpblendd	$170, %ymm3, %ymm0, %ymm0
	vmovdqu	mod_vec(%rip), %ymm3
	vpaddd	%ymm3, %ymm0, %ymm0
	vpmuludq	%ymm4, %ymm1, %ymm1
	vpmuludq	%ymm4, %ymm2, %ymm2
	vmovdqu	-128(%rax), %ymm4
	vpsrlq	$32, %ymm1, %ymm1
	vpblendd	$170, %ymm2, %ymm1, %ymm1
	vpsubd	%ymm1, %ymm0, %ymm2
	vpcmpgtd	%ymm6, %ymm2, %ymm5
	vpaddd	%ymm2, %ymm4, %ymm2
	vpsubd	%ymm0, %ymm4, %ymm4
	vpand	%ymm5, %ymm3, %ymm5
	vpsubd	%ymm5, %ymm2, %ymm2
	vpcmpgtd	%ymm6, %ymm2, %ymm6
	vpand	%ymm6, %ymm3, %ymm3
	vpsubd	%ymm3, %ymm2, %ymm2
	vmovdqu	%ymm2, -128(%rax)
	vmovdqu	mod_vec(%rip), %ymm2
	vpaddd	%ymm2, %ymm1, %ymm1
	vpaddd	%ymm5, %ymm1, %ymm1
	vpaddd	%ymm4, %ymm1, %ymm0
	vpcmpgtd	(%rcx), %ymm0, %ymm1
	vpand	%ymm1, %ymm2, %ymm2
	vpsubd	%ymm2, %ymm0, %ymm0
	vmovdqu	%ymm0, -128(%rdx)
	vmovdqu	-96(%rdx), %ymm0
	vmovdqu	-32(%r8), %ymm1
	vmovdqu	(%r9), %ymm4
	vmovdqu	(%rcx), %ymm6
	vpsrlq	$32, %ymm1, %ymm2
	vpsrlq	$32, %ymm0, %ymm3
	vpmuludq	%ymm1, %ymm0, %ymm0
	vpmuludq	%ymm2, %ymm3, %ymm3
	vmovdqu	(%r10), %ymm2
	vpmuludq	%ymm2, %ymm0, %ymm1
	vpmuludq	%ymm2, %ymm3, %ymm2
	vpsrlq	$32, %ymm0, %ymm0
	vpblendd	$170, %ymm3, %ymm0, %ymm0
	vmovdqu	mod_vec(%rip), %ymm3
	vpaddd	%ymm3, %ymm0, %ymm0
	vpmuludq	%ymm4, %ymm1, %ymm1
	vpmuludq	%ymm4, %ymm2, %ymm2
	vmovdqu	-96(%rax), %ymm4
	vpsrlq	$32, %ymm1, %ymm1
	vpblendd	$170, %ymm2, %ymm1, %ymm1
	vpsubd	%ymm1, %ymm0, %ymm2
	vpcmpgtd	%ymm6, %ymm2, %ymm5
	vpaddd	%ymm2, %ymm4, %ymm2
	vpsubd	%ymm0, %ymm4, %ymm4
	vpand	%ymm5, %ymm3, %ymm5
	vpsubd	%ymm5, %ymm2, %ymm2
	vpcmpgtd	%ymm6, %ymm2, %ymm6
	vpand	%ymm6, %ymm3, %ymm3
	vpsubd	%ymm3, %ymm2, %ymm2
	vmovdqu	%ymm2, -96(%rax)
	vmovdqu	mod_vec(%rip), %ymm2
	vpaddd	%ymm2, %ymm1, %ymm1
	vpaddd	%ymm5, %ymm1, %ymm1
	vpaddd	%ymm4, %ymm1, %ymm0
	vpcmpgtd	(%rcx), %ymm0, %ymm1
	vpand	%ymm1, %ymm2, %ymm2
	vpsubd	%ymm2, %ymm0, %ymm0
	vmovdqu	%ymm0, -96(%rdx)
	cmpq	%rax, %r11
	jne	.L119
	addq	%r12, %rbx
	addq	%r13, %rsi
	cmpl	%ebx, %r15d
	jg	.L120
	movq	16(%rsp), %r8
	movq	24(%rsp), %r11
	movl	40(%rsp), %eax
	movq	32(%rsp), %rdx
.L121:
	movl	44(%rsp), %r9d
	cmpl	%r9d, %r15d
	jg	.L146
.L140:
	movl	%eax, %r10d
	jmp	.L108
.L116:
	movq	%rdx, %rbx
	leaq	mogo_np(%rip), %r10
	leaq	mogo_n(%rip), %r9
	.p2align 4
	.p2align 3
.L118:
	vmovdqu	32+wi(%rip), %ymm1
	vmovdqu	-32(%rbx), %ymm0
	prefetcht0	(%rbx)
	addq	$64, %rbx
	vmovdqu	(%r9), %ymm4
	vmovdqu	(%rcx), %ymm6
	vpsrlq	$32, %ymm1, %ymm2
	vpsrlq	$32, %ymm0, %ymm3
	vpmuludq	%ymm1, %ymm0, %ymm0
	vpmuludq	%ymm2, %ymm3, %ymm3
	vmovdqu	(%r10), %ymm2
	vpmuludq	%ymm2, %ymm0, %ymm1
	vpmuludq	%ymm2, %ymm3, %ymm2
	vpsrlq	$32, %ymm0, %ymm0
	vpblendd	$170, %ymm3, %ymm0, %ymm0
	vmovdqu	mod_vec(%rip), %ymm3
	vpaddd	%ymm3, %ymm0, %ymm0
	vpmuludq	%ymm4, %ymm1, %ymm1
	vpmuludq	%ymm4, %ymm2, %ymm2
	vmovdqu	-128(%rbx), %ymm4
	vpsrlq	$32, %ymm1, %ymm1
	vpblendd	$170, %ymm2, %ymm1, %ymm1
	vpsubd	%ymm1, %ymm0, %ymm2
	vpcmpgtd	%ymm6, %ymm2, %ymm5
	vpaddd	%ymm2, %ymm4, %ymm2
	vpsubd	%ymm0, %ymm4, %ymm4
	vpand	%ymm5, %ymm3, %ymm5
	vpsubd	%ymm5, %ymm2, %ymm2
	vpcmpgtd	%ymm6, %ymm2, %ymm6
	vpand	%ymm6, %ymm3, %ymm3
	vpsubd	%ymm3, %ymm2, %ymm2
	vmovdqu	%ymm2, -128(%rbx)
	vmovdqu	mod_vec(%rip), %ymm2
	vpaddd	%ymm2, %ymm1, %ymm1
	vpaddd	%ymm5, %ymm1, %ymm1
	vpaddd	%ymm4, %ymm1, %ymm0
	vpcmpgtd	(%rcx), %ymm0, %ymm1
	vpand	%ymm1, %ymm2, %ymm2
	vpsubd	%ymm2, %ymm0, %ymm0
	vmovdqu	%ymm0, -96(%rbx)
	cmpq	%rbx, %r8
	jne	.L118
	movl	$16, %r9d
	jmp	.L111
.L143:
	vmovd	8+wi(%rip), %xmm7
	movq	192(%rsp), %rbx
	leaq	mogo_np(%rip), %r10
	leaq	mogo_n(%rip), %r9
	vpinsrd	$1, 12+wi(%rip), %xmm7, %xmm3
	vpunpcklqdq	%xmm3, %xmm3, %xmm3
	vinserti128	$1, %xmm3, %ymm3, %ymm3
	vpsrlq	$32, %ymm3, %ymm4
	.p2align 4
	.p2align 3
.L112:
	vmovdqu	32(%rbx), %ymm1
	vmovdqu	(%rbx), %ymm2
	addq	$64, %rbx
	vmovdqu	(%r9), %ymm7
	vpslldq	$8, %ymm1, %ymm0
	vpblendd	$204, %ymm0, %ymm2, %ymm0
	vpsrldq	$8, %ymm2, %ymm2
	vpblendd	$51, %ymm2, %ymm1, %ymm1
	vmovdqu	(%r10), %ymm2
	vpsrlq	$32, %ymm1, %ymm6
	vpmuludq	%ymm3, %ymm1, %ymm1
	vpmuludq	%ymm4, %ymm6, %ymm6
	vpmuludq	%ymm2, %ymm1, %ymm5
	vpsrlq	$32, %ymm1, %ymm1
	vpmuludq	%ymm2, %ymm6, %ymm2
	vpblendd	$170, %ymm6, %ymm1, %ymm1
	vmovdqu	(%rcx), %ymm6
	vpmuludq	%ymm7, %ymm5, %ymm5
	vpmuludq	%ymm7, %ymm2, %ymm2
	vmovdqu	mod_vec(%rip), %ymm7
	vpsrlq	$32, %ymm5, %ymm5
	vpblendd	$170, %ymm2, %ymm5, %ymm5
	vpaddd	%ymm7, %ymm1, %ymm2
	vpsubd	%ymm5, %ymm2, %ymm2
	vpcmpgtd	%ymm6, %ymm2, %ymm8
	vpaddd	%ymm2, %ymm0, %ymm2
	vpaddd	%ymm5, %ymm0, %ymm0
	vpand	%ymm8, %ymm7, %ymm8
	vpaddd	%ymm8, %ymm0, %ymm0
	vpsubd	%ymm8, %ymm2, %ymm2
	vpsubd	%ymm1, %ymm0, %ymm0
	vpcmpgtd	%ymm6, %ymm2, %ymm9
	vpcmpgtd	%ymm6, %ymm0, %ymm5
	vpand	%ymm9, %ymm7, %ymm9
	vpand	%ymm5, %ymm7, %ymm1
	vpsubd	%ymm9, %ymm2, %ymm2
	vpsubd	%ymm1, %ymm0, %ymm0
	vpslldq	$8, %ymm0, %ymm1
	vpblendd	$204, %ymm1, %ymm2, %ymm1
	vpsrldq	$8, %ymm2, %ymm2
	vpblendd	$51, %ymm2, %ymm0, %ymm0
	vmovdqu	%ymm1, -64(%rbx)
	vmovdqu	%ymm0, -32(%rbx)
	cmpq	%rbx, %r11
	jne	.L112
	movl	$4, %r9d
	jmp	.L111
.L144:
	vbroadcasti128	16+wi(%rip), %ymm3
	movq	192(%rsp), %rbx
	leaq	mogo_np(%rip), %r10
	leaq	mogo_n(%rip), %r9
	vpsrlq	$32, %ymm3, %ymm4
	.p2align 4
	.p2align 3
.L115:
	vmovdqu	32(%rbx), %ymm0
	vmovdqu	(%rbx), %ymm1
	addq	$64, %rbx
	vmovdqu	(%r9), %ymm7
	vperm2i128	$32, %ymm0, %ymm1, %ymm5
	vperm2i128	$49, %ymm0, %ymm1, %ymm1
	vmovdqu	(%r10), %ymm0
	vpsrlq	$32, %ymm1, %ymm6
	vpmuludq	%ymm3, %ymm1, %ymm1
	vpmuludq	%ymm4, %ymm6, %ymm6
	vpmuludq	%ymm0, %ymm1, %ymm2
	vpsrlq	$32, %ymm1, %ymm1
	vpmuludq	%ymm0, %ymm6, %ymm0
	vpblendd	$170, %ymm6, %ymm1, %ymm1
	vmovdqu	(%rcx), %ymm6
	vpmuludq	%ymm7, %ymm2, %ymm2
	vpmuludq	%ymm7, %ymm0, %ymm0
	vmovdqu	mod_vec(%rip), %ymm7
	vpsrlq	$32, %ymm2, %ymm2
	vpblendd	$170, %ymm0, %ymm2, %ymm2
	vpaddd	%ymm7, %ymm1, %ymm0
	vpsubd	%ymm2, %ymm0, %ymm0
	vpaddd	%ymm5, %ymm2, %ymm2
	vpcmpgtd	%ymm6, %ymm0, %ymm8
	vpaddd	%ymm5, %ymm0, %ymm0
	vpand	%ymm8, %ymm7, %ymm8
	vpaddd	%ymm8, %ymm2, %ymm2
	vpsubd	%ymm8, %ymm0, %ymm0
	vpsubd	%ymm1, %ymm2, %ymm1
	vpcmpgtd	%ymm6, %ymm0, %ymm9
	vpcmpgtd	%ymm6, %ymm1, %ymm6
	vpand	%ymm9, %ymm7, %ymm9
	vpand	%ymm6, %ymm7, %ymm2
	vpsubd	%ymm9, %ymm0, %ymm0
	vpsubd	%ymm2, %ymm1, %ymm1
	vperm2i128	$32, %ymm1, %ymm0, %ymm2
	vperm2i128	$49, %ymm1, %ymm0, %ymm0
	vmovdqu	%ymm2, -64(%rbx)
	vmovdqu	%ymm0, -32(%rbx)
	cmpq	%rbx, %r11
	jne	.L115
	movl	$8, %r9d
	jmp	.L111
.L142:
	movl	$0, %r10d
	leaq	mod1_vec(%rip), %rcx
	jne	.L141
.L108:
	shrl	$3, %r10d
	movq	192(%rsp), %rax
	movl	%r10d, %edx
	salq	$5, %rdx
	leaq	32(%rax,%rdx), %rdx
	.p2align 6
	.p2align 4
	.p2align 3
.L125:
	vmovdqu	mod_vec(%rip), %ymm0
	addq	$32, %rax
	vpcmpgtd	(%rcx), %ymm0, %ymm1
	vpand	%ymm1, %ymm0, %ymm1
	vpsubd	%ymm1, %ymm0, %ymm0
	vmovdqu	%ymm0, -32(%rax)
	cmpq	%rdx, %rax
	jne	.L125
	vzeroupper
.L141:
	vmovups	48(%rsp), %xmm6
	vmovups	64(%rsp), %xmm7
	vmovups	80(%rsp), %xmm8
	vmovups	96(%rsp), %xmm9
	addq	$120, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	popq	%rbp
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	ret
	.seh_endproc
	.p2align 4
	.globl	_Z8div_fastILj1EEjj
	.def	_Z8div_fastILj1EEjj;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z8div_fastILj1EEjj
_Z8div_fastILj1EEjj:
.LFB10090:
	.seh_endprologue
	movl	%ecx, %eax
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC0:
	.ascii "error.\0"
.LC1:
	.ascii "%u %u %u\12\0"
.LC2:
	.ascii "OK\0"
	.text
	.p2align 4
	.globl	_Z4testv
	.def	_Z4testv;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z4testv
_Z4testv:
.LFB10091:
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$40, %rsp
	.seh_stackalloc	40
	.seh_endprologue
	xorl	%ebx, %ebx
	movabsq	$4619796751, %rdx
	movq	%rdx, %r8
	.p2align 6
	.p2align 4
	.p2align 3
.L149:
	addl	$1, %ebx
	cmpl	$998244354, %ebx
	je	.L152
	movslq	%ebx, %rax
	movl	%ebx, %ecx
	movq	%rdx, %rsi
	addq	%r8, %rdx
	imulq	$288737297, %rax, %rax
	sarl	$31, %ecx
	shrq	$62, %rsi
	sarq	$58, %rax
	subl	%ecx, %eax
	cmpl	%esi, %eax
	je	.L149
	leaq	.LC0(%rip), %rcx
	call	puts
	movl	%esi, %r9d
	movl	$998244353, %r8d
	movl	%ebx, %edx
	leaq	.LC1(%rip), %rcx
	call	_Z6printfPKcz
	xorl	%ecx, %ecx
	call	exit
	.p2align 4,,10
	.p2align 3
.L152:
	leaq	.LC2(%rip), %rcx
	addq	$40, %rsp
	popq	%rbx
	popq	%rsi
	jmp	puts
	.seh_endproc
	.p2align 4
	.globl	_Z13poly_multiplyPjiS_iS_
	.def	_Z13poly_multiplyPjiS_iS_;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z13poly_multiplyPjiS_iS_
_Z13poly_multiplyPjiS_iS_:
.LFB10092:
	pushq	%r15
	.seh_pushreg	%r15
	pushq	%r14
	.seh_pushreg	%r14
	pushq	%r13
	.seh_pushreg	%r13
	pushq	%r12
	.seh_pushreg	%r12
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$120, %rsp
	.seh_stackalloc	120
	vmovups	%xmm6, 64(%rsp)
	.seh_savexmm	%xmm6, 64
	vmovups	%xmm7, 80(%rsp)
	.seh_savexmm	%xmm7, 80
	vmovups	%xmm8, 96(%rsp)
	.seh_savexmm	%xmm8, 96
	.seh_endprologue
	leaq	a(%rip), %r14
	leaq	b(%rip), %rbp
	movq	224(%rsp), %rax
	movq	%rcx, %rdi
	movl	%edx, %r15d
	movl	%r9d, %r12d
	movq	%r8, %rbx
	movq	%rax, 40(%rsp)
	leal	4(,%r12,4), %r13d
	call	_Z4testv
	leaq	48(%rsp), %r9
	leaq	56(%rsp), %r8
	movslq	%r13d, %r13
	movl	$8388423, %edx
	movl	$16777358, %ecx
	call	_Z5exgcdxxRxS_
	movq	48(%rsp), %rdx
	movq	56(%rsp), %rax
	leal	4(,%r15,4), %r9d
	movslq	%r9d, %rsi
	subq	%rdx, %rax
	movq	%rsi, %r8
	leaq	(%rax,%rax,2), %rcx
	subq	%rcx, %rdx
	leaq	(%rdx,%rdx,2), %rcx
	subq	%rcx, %rax
	leaq	(%rax,%rax,2), %rcx
	subq	%rcx, %rdx
	movq	%r14, %rcx
	movq	%rdx, 48(%rsp)
	salq	$2, %rdx
	subl	%edx, %eax
	movq	%rdi, %rdx
	leal	1(%r15,%r12), %edi
	movq	%rax, 56(%rsp)
	vzeroupper
	call	memcpy
	movq	%r13, %r8
	movq	%rbx, %rdx
	movq	%rbp, %rcx
	call	memcpy
	testl	%r15d, %r15d
	js	.L154
	movslq	%r15d, %rax
	leaq	4(%r14), %rdx
	movq	%r14, %r8
	movabsq	$-8525806094425994177, %r10
	leaq	(%rdx,%rax,4), %r11
	.p2align 6
	.p2align 4
	.p2align 3
.L155:
	movl	(%r8), %ecx
	addq	$4, %r8
	salq	$32, %rcx
	movq	%rcx, %rax
	mulq	%r10
	shrq	$29, %rdx
	imulq	$998244353, %rdx, %rdx
	subq	%rdx, %rcx
	movl	%ecx, -4(%r8)
	cmpq	%r8, %r11
	jne	.L155
	testl	%r12d, %r12d
	js	.L162
.L157:
	movabsq	$-8525806094425994177, %r10
	xorl	%r8d, %r8d
	.p2align 6
	.p2align 4
	.p2align 3
.L159:
	movl	0(%rbp,%r8,4), %ecx
	salq	$32, %rcx
	movq	%rcx, %rax
	mulq	%r10
	shrq	$29, %rdx
	imulq	$998244353, %rdx, %rdx
	subq	%rdx, %rcx
	movl	%ecx, 0(%rbp,%r8,4)
	addq	$1, %r8
	cmpl	%r8d, %r12d
	jge	.L159
.L162:
	movl	$32, %ebx
	cmpl	$32, %edi
	jle	.L161
	.p2align 3
	.p2align 4
	.p2align 3
.L160:
	addl	%ebx, %ebx
	cmpl	%edi, %ebx
	jl	.L160
.L158:
	movl	%ebx, %eax
	leaq	(%r14,%rsi), %rcx
	xorl	%edx, %edx
	subl	%r15d, %eax
	leal	-4(,%rax,4), %r8d
	movslq	%r8d, %r8
	call	memset
	movl	%ebx, %eax
	xorl	%edx, %edx
	leaq	0(%rbp,%r13), %rcx
	subl	%r12d, %eax
	leaq	c(%rip), %r12
	leal	-4(,%rax,4), %r8d
	movslq	%r8d, %r8
	call	memset
	movl	%ebx, %ecx
	call	_Z4initi
	movl	%ebx, %edx
	movq	%r14, %rcx
	call	_Z5NTTfaPji
	movl	%ebx, %edx
	movq	%rbp, %rcx
	call	_Z5NTTfaPji
	vmovdqu	mod_vec(%rip), %ymm4
	xorl	%eax, %eax
	vmovdqu	mogo_np(%rip), %ymm3
	vmovdqu	mogo_n(%rip), %ymm2
	vmovdqu	mod1_vec(%rip), %ymm5
	vmovdqa	%ymm4, %ymm6
	.p2align 4
	.p2align 3
.L163:
	vmovdqu	0(%rbp,%rax,4), %ymm1
	vmovdqu	(%r14,%rax,4), %ymm0
	vpsrlq	$32, %ymm1, %ymm8
	vpsrlq	$32, %ymm0, %ymm7
	vpmuludq	%ymm1, %ymm0, %ymm0
	vpmuludq	%ymm8, %ymm7, %ymm7
	vpmuludq	%ymm3, %ymm0, %ymm1
	vpmuludq	%ymm3, %ymm7, %ymm8
	vpsrlq	$32, %ymm0, %ymm0
	vpblendd	$170, %ymm7, %ymm0, %ymm0
	vpaddd	%ymm6, %ymm0, %ymm0
	vpmuludq	%ymm2, %ymm1, %ymm1
	vpmuludq	%ymm2, %ymm8, %ymm8
	vpsrlq	$32, %ymm1, %ymm1
	vpblendd	$170, %ymm8, %ymm1, %ymm1
	vpsubd	%ymm1, %ymm0, %ymm0
	vpcmpgtd	%ymm5, %ymm0, %ymm1
	vpand	%ymm1, %ymm4, %ymm1
	vpsubd	%ymm1, %ymm0, %ymm0
	vmovdqu	%ymm0, (%r12,%rax,4)
	addq	$8, %rax
	cmpl	%eax, %ebx
	jg	.L163
	movl	%ebx, %edx
	movq	%r12, %rcx
	vzeroupper
	call	_Z6NTTifaPji
	leal	-1(%rbx), %eax
	vmovdqu	mod_vec(%rip), %ymm4
	leaq	c(%rip), %rdx
	shrl	$3, %eax
	leaq	32(%rdx), %rcx
	vmovdqu	mogo_np(%rip), %ymm3
	vmovdqu	mogo_n(%rip), %ymm2
	salq	$5, %rax
	vmovdqu	mod1_vec(%rip), %ymm5
	vmovdqa	%ymm4, %ymm6
	addq	%rcx, %rax
	.p2align 4
	.p2align 3
.L164:
	vmovdqu	(%rdx), %ymm0
	addq	$32, %rdx
	vpsrlq	$32, %ymm0, %ymm1
	vpmuludq	%ymm3, %ymm0, %ymm0
	vpmuludq	%ymm3, %ymm1, %ymm1
	vpmuludq	%ymm2, %ymm0, %ymm0
	vpmuludq	%ymm2, %ymm1, %ymm1
	vpsrlq	$32, %ymm0, %ymm0
	vpblendd	$170, %ymm1, %ymm0, %ymm0
	vpsubd	%ymm0, %ymm6, %ymm0
	vpcmpgtd	%ymm5, %ymm0, %ymm1
	vpand	%ymm1, %ymm4, %ymm1
	vpsubd	%ymm1, %ymm0, %ymm0
	vmovdqu	%ymm0, -32(%rdx)
	cmpq	%rdx, %rax
	jne	.L164
	movq	40(%rsp), %rcx
	leal	0(,%rdi,4), %r8d
	vzeroupper
	movq	%r12, %rdx
	vmovups	64(%rsp), %xmm6
	vmovups	80(%rsp), %xmm7
	movslq	%r8d, %r8
	vmovups	96(%rsp), %xmm8
	addq	$120, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	popq	%rbp
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	jmp	memcpy
	.p2align 4,,10
	.p2align 3
.L154:
	testl	%r12d, %r12d
	jns	.L157
	.p2align 4
	.p2align 3
.L161:
	movl	$32, %ebx
	jmp	.L158
	.seh_endproc
	.p2align 4
	.globl	_Z5writev
	.def	_Z5writev;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z5writev
_Z5writev:
.LFB10094:
	.seh_endprologue
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC3:
	.ascii "%u \0"
.LC4:
	.ascii "\0"
	.text
	.p2align 4
	.globl	_Z5printPji
	.def	_Z5printPji;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z5printPji
_Z5printPji:
.LFB10098:
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	testl	%edx, %edx
	jle	.L175
	movslq	%edx, %rdx
	movq	%rcx, %rbx
	leaq	.LC3(%rip), %rsi
	leaq	(%rcx,%rdx,4), %rdi
	.p2align 4
	.p2align 3
.L176:
	movl	(%rbx), %edx
	movq	%rsi, %rcx
	addq	$4, %rbx
	call	_Z6printfPKcz
	cmpq	%rdi, %rbx
	jne	.L176
.L175:
	leaq	.LC4(%rip), %rcx
	addq	$32, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	jmp	puts
	.seh_endproc
	.section	.text$_ZNSt23mersenne_twister_engineIjLy32ELy624ELy397ELy31ELj2567483615ELy11ELj4294967295ELy7ELj2636928640ELy15ELj4022730752ELy18ELj1812433253EE11_M_gen_randEv,"x"
	.linkonce discard
	.align 2
	.p2align 4
	.globl	_ZNSt23mersenne_twister_engineIjLy32ELy624ELy397ELy31ELj2567483615ELy11ELj4294967295ELy7ELj2636928640ELy15ELj4022730752ELy18ELj1812433253EE11_M_gen_randEv
	.def	_ZNSt23mersenne_twister_engineIjLy32ELy624ELy397ELy31ELj2567483615ELy11ELj4294967295ELy7ELj2636928640ELy15ELj4022730752ELy18ELj1812433253EE11_M_gen_randEv;	.scl	2;	.type	32;	.endef
	.seh_proc	_ZNSt23mersenne_twister_engineIjLy32ELy624ELy397ELy31ELj2567483615ELy11ELj4294967295ELy7ELj2636928640ELy15ELj4022730752ELy18ELj1812433253EE11_M_gen_randEv
_ZNSt23mersenne_twister_engineIjLy32ELy624ELy397ELy31ELj2567483615ELy11ELj4294967295ELy7ELj2636928640ELy15ELj4022730752ELy18ELj1812433253EE11_M_gen_randEv:
.LFB10616:
	subq	$24, %rsp
	.seh_stackalloc	24
	movups	%xmm6, (%rsp)
	.seh_savexmm	%xmm6, 0
	.seh_endprologue
	movl	(%rcx), %r8d
	movq	%rcx, %r10
	leaq	908(%rcx), %r9
	movq	%rcx, %rax
	.p2align 6
	.p2align 4
	.p2align 3
.L179:
	movl	%r8d, %ecx
	movl	4(%rax), %r8d
	addq	$4, %rax
	andl	$-2147483648, %ecx
	movl	%r8d, %edx
	andl	$2147483647, %edx
	orl	%ecx, %edx
	movl	%edx, %ecx
	andl	$1, %edx
	negl	%edx
	shrl	%ecx
	xorl	1584(%rax), %ecx
	andl	$-1727483681, %edx
	xorl	%ecx, %edx
	movl	%edx, -4(%rax)
	cmpq	%r9, %rax
	jne	.L179
	movl	$-2147483648, %ecx
	leaq	2492(%r10), %rdx
	movd	%ecx, %xmm5
	movl	$2147483647, %ecx
	movd	%ecx, %xmm4
	movl	$1, %ecx
	pshufd	$0, %xmm5, %xmm5
	movd	%ecx, %xmm3
	pshufd	$0, %xmm4, %xmm4
	pshufd	$0, %xmm3, %xmm3
	.p2align 4
	.p2align 3
.L180:
	movdqu	(%rax), %xmm1
	movdqu	4(%rax), %xmm0
	addq	$16, %rax
	movdqu	-924(%rax), %xmm2
	pand	%xmm4, %xmm0
	pand	%xmm5, %xmm1
	por	%xmm0, %xmm1
	movdqa	%xmm1, %xmm0
	pand	%xmm3, %xmm1
	psrld	$1, %xmm0
	pxor	%xmm0, %xmm2
	movdqa	%xmm1, %xmm0
	pslld	$3, %xmm0
	paddd	%xmm1, %xmm0
	pslld	$9, %xmm0
	paddd	%xmm1, %xmm0
	pslld	$5, %xmm0
	paddd	%xmm1, %xmm0
	pslld	$2, %xmm0
	psubd	%xmm1, %xmm0
	pslld	$3, %xmm0
	psubd	%xmm1, %xmm0
	movdqa	%xmm0, %xmm6
	pslld	$4, %xmm6
	paddd	%xmm6, %xmm0
	pslld	$5, %xmm0
	psubd	%xmm1, %xmm0
	pxor	%xmm0, %xmm2
	movups	%xmm2, -16(%rax)
	cmpq	%rdx, %rax
	jne	.L180
	movl	2492(%r10), %eax
	movl	(%r10), %edx
	movq	$0, 2496(%r10)
	movups	(%rsp), %xmm6
	andl	$2147483647, %edx
	andl	$-2147483648, %eax
	orl	%edx, %eax
	movl	%eax, %edx
	andl	$1, %eax
	negl	%eax
	shrl	%edx
	xorl	1584(%r10), %edx
	andl	$-1727483681, %eax
	xorl	%edx, %eax
	movl	%eax, 2492(%r10)
	addq	$24, %rsp
	ret
	.seh_endproc
	.text
	.p2align 4
	.globl	_Z4readv
	.def	_Z4readv;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z4readv
_Z4readv:
.LFB10093:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$2552, %rsp
	.seh_stackalloc	2552
	.seh_endprologue
	movl	$300100, %ecx
	movl	$1, %edx
	movl	$300100, 32(%rsp)
	leaq	32(%rsp), %rbx
	.p2align 5
	.p2align 4
	.p2align 3
.L184:
	movl	%ecx, %eax
	shrl	$30, %eax
	xorl	%ecx, %eax
	imull	$1812433253, %eax, %eax
	leal	(%rax,%rdx), %ecx
	movl	%ecx, (%rbx,%rdx,4)
	addq	$1, %rdx
	cmpq	$624, %rdx
	jne	.L184
	leaq	a(%rip), %rsi
	movl	$3435973837, %edi
	movq	$624, 2528(%rsp)
	movl	$1000000, n(%rip)
	leaq	4000004(%rsi), %rbp
	movl	$1000000, m(%rip)
	jmp	.L186
	.p2align 4,,10
	.p2align 3
.L185:
	leaq	1(%rax), %rdx
	movl	32(%rsp,%rax,4), %eax
	addq	$4, %rsi
	movq	%rdx, 2528(%rsp)
	movl	%eax, %ecx
	shrl	$11, %ecx
	xorl	%ecx, %eax
	movl	%eax, %ecx
	sall	$7, %ecx
	andl	$-1658038656, %ecx
	xorl	%ecx, %eax
	movl	%eax, %ecx
	sall	$15, %ecx
	andl	$-272236544, %ecx
	xorl	%ecx, %eax
	movl	%eax, %ecx
	shrl	$18, %ecx
	xorl	%ecx, %eax
	movl	%eax, %ecx
	imulq	%rdi, %rcx
	shrq	$35, %rcx
	leal	(%rcx,%rcx,4), %ecx
	addl	%ecx, %ecx
	subl	%ecx, %eax
	movl	%eax, -4(%rsi)
	cmpq	%rbp, %rsi
	je	.L194
.L186:
	movq	%rdx, %rax
	cmpq	$623, %rdx
	jbe	.L185
	movq	%rbx, %rcx
	call	_ZNSt23mersenne_twister_engineIjLy32ELy624ELy397ELy31ELj2567483615ELy11ELj4294967295ELy7ELj2636928640ELy15ELj4022730752ELy18ELj1812433253EE11_M_gen_randEv
	movq	2528(%rsp), %rax
	jmp	.L185
.L194:
	leaq	b(%rip), %rsi
	movl	$3435973837, %edi
	leaq	4000004(%rsi), %rbp
	jmp	.L188
	.p2align 4,,10
	.p2align 3
.L187:
	leaq	1(%rax), %rdx
	movl	32(%rsp,%rax,4), %eax
	addq	$4, %rsi
	movq	%rdx, 2528(%rsp)
	movl	%eax, %ecx
	shrl	$11, %ecx
	xorl	%ecx, %eax
	movl	%eax, %ecx
	sall	$7, %ecx
	andl	$-1658038656, %ecx
	xorl	%ecx, %eax
	movl	%eax, %ecx
	sall	$15, %ecx
	andl	$-272236544, %ecx
	xorl	%ecx, %eax
	movl	%eax, %ecx
	shrl	$18, %ecx
	xorl	%ecx, %eax
	movl	%eax, %ecx
	imulq	%rdi, %rcx
	shrq	$35, %rcx
	leal	(%rcx,%rcx,4), %ecx
	addl	%ecx, %ecx
	subl	%ecx, %eax
	movl	%eax, -4(%rsi)
	cmpq	%rbp, %rsi
	je	.L195
.L188:
	movq	%rdx, %rax
	cmpq	$623, %rdx
	jbe	.L187
	movq	%rbx, %rcx
	call	_ZNSt23mersenne_twister_engineIjLy32ELy624ELy397ELy31ELj2567483615ELy11ELj4294967295ELy7ELj2636928640ELy15ELj4022730752ELy18ELj1812433253EE11_M_gen_randEv
	movq	2528(%rsp), %rax
	jmp	.L187
.L195:
	addq	$2552, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC8:
	.ascii "%dx%d %d\12\0"
.LC9:
	.ascii "err\0"
	.text
	.p2align 4
	.globl	_Z4testi
	.def	_Z4testi;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z4testi
_Z4testi:
.LFB10099:
	pushq	%r15
	.seh_pushreg	%r15
	pushq	%r14
	.seh_pushreg	%r14
	pushq	%r13
	.seh_pushreg	%r13
	pushq	%r12
	.seh_pushreg	%r12
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$2584, %rsp
	.seh_stackalloc	2584
	.seh_endprologue
	movl	$1, %edx
	movl	$10, 64(%rsp)
	leaq	64(%rsp), %r13
	movl	%ecx, 60(%rsp)
	movl	$10, %ecx
	.p2align 6
	.p2align 4
	.p2align 3
.L197:
	movl	%ecx, %eax
	shrl	$30, %eax
	xorl	%ecx, %eax
	imull	$1812433253, %eax, %eax
	leal	(%rax,%rdx), %ecx
	movl	%ecx, 0(%r13,%rdx,4)
	addq	$1, %rdx
	cmpq	$624, %rdx
	jne	.L197
	movq	$624, 2560(%rsp)
	movl	60(%rsp), %eax
	testl	%eax, %eax
	jle	.L198
	movslq	%eax, %rdi
	leaq	_ZZ4testiE1b(%rip), %rbp
	movl	$3435973837, %ebx
	leaq	_ZZ4testiE1a(%rip), %rsi
	salq	$2, %rdi
	movq	%rbp, %r14
	movq	%rsi, %r15
	leaq	0(%rbp,%rdi), %r12
	jmp	.L201
	.p2align 4,,10
	.p2align 3
.L199:
	movl	64(%rsp,%rdx,4), %eax
	leaq	1(%rdx), %rcx
	movq	%rcx, 2560(%rsp)
	movl	%eax, %edx
	shrl	$11, %edx
	xorl	%edx, %eax
	movl	%eax, %edx
	sall	$7, %edx
	andl	$-1658038656, %edx
	xorl	%edx, %eax
	movl	%eax, %edx
	sall	$15, %edx
	andl	$-272236544, %edx
	xorl	%edx, %eax
	movl	%eax, %edx
	shrl	$18, %edx
	xorl	%edx, %eax
	movl	%eax, %edx
	imulq	%rbx, %rdx
	shrq	$35, %rdx
	leal	(%rdx,%rdx,4), %edx
	addl	%edx, %edx
	subl	%edx, %eax
	movl	%eax, (%r15)
	cmpq	$623, %rcx
	ja	.L216
.L200:
	movl	64(%rsp,%rcx,4), %eax
	leaq	1(%rcx), %rdx
	addq	$4, %r14
	addq	$4, %r15
	movq	%rdx, 2560(%rsp)
	movl	%eax, %ecx
	shrl	$11, %ecx
	xorl	%ecx, %eax
	movl	%eax, %ecx
	sall	$7, %ecx
	andl	$-1658038656, %ecx
	xorl	%ecx, %eax
	movl	%eax, %ecx
	sall	$15, %ecx
	andl	$-272236544, %ecx
	xorl	%ecx, %eax
	movl	%eax, %ecx
	shrl	$18, %ecx
	xorl	%ecx, %eax
	movl	%eax, %ecx
	imulq	%rbx, %rcx
	shrq	$35, %rcx
	leal	(%rcx,%rcx,4), %ecx
	addl	%ecx, %ecx
	subl	%ecx, %eax
	movl	%eax, -4(%r14)
	cmpq	%r14, %r12
	je	.L217
.L201:
	cmpq	$623, %rdx
	jbe	.L199
	movq	%r13, %rcx
	call	_ZNSt23mersenne_twister_engineIjLy32ELy624ELy397ELy31ELj2567483615ELy11ELj4294967295ELy7ELj2636928640ELy15ELj4022730752ELy18ELj1812433253EE11_M_gen_randEv
	movq	2560(%rsp), %rdx
	jmp	.L199
	.p2align 4,,10
	.p2align 3
.L216:
	movq	%r13, %rcx
	call	_ZNSt23mersenne_twister_engineIjLy32ELy624ELy397ELy31ELj2567483615ELy11ELj4294967295ELy7ELj2636928640ELy15ELj4022730752ELy18ELj1812433253EE11_M_gen_randEv
	movq	2560(%rsp), %rcx
	jmp	.L200
.L217:
	movl	$16777216, %eax
	xorl	%edx, %edx
	idivl	60(%rsp)
	movl	%eax, %r12d
	call	clock
	movl	%eax, %ebx
	testl	%r12d, %r12d
	je	.L206
	movl	60(%rsp), %eax
	xorl	%r13d, %r13d
	leaq	_ZZ4testiE1c(%rip), %r15
	leal	-1(%rax), %r14d
	.p2align 4
	.p2align 3
.L205:
	movq	%r15, 32(%rsp)
	movl	%r14d, %r9d
	movl	%r14d, %edx
	movq	%rsi, %rcx
	leaq	_ZZ4testiE1b(%rip), %r8
	addl	$1, %r13d
	call	_Z13poly_multiplyPjiS_iS_
	cmpl	%r13d, %r12d
	jne	.L205
.L206:
	call	clock
	xorl	%r15d, %r15d
	xorl	%r10d, %r10d
	movl	$1, %ecx
	movabsq	$-8525806094425994177, %r11
	movl	%eax, %r9d
	xorl	%r14d, %r14d
	.p2align 4
	.p2align 3
.L204:
	movl	(%rsi,%r10), %r8d
	imulq	%rcx, %r8
	addq	%r14, %r8
	movq	%r8, %rax
	movq	%r8, %r14
	movl	0(%rbp,%r10), %r8d
	addq	$4, %r10
	mulq	%r11
	imulq	%rcx, %r8
	shrq	$29, %rdx
	imulq	$998244353, %rdx, %rax
	addq	%r15, %r8
	movq	%r8, %r15
	subq	%rax, %r14
	movq	%r8, %rax
	movq	%rcx, %r8
	mulq	%r11
	salq	$4, %r8
	addq	%rcx, %r8
	movq	%r8, %rcx
	shrq	$29, %rdx
	imulq	$998244353, %rdx, %rax
	subq	%rax, %r15
	movq	%r8, %rax
	mulq	%r11
	shrq	$29, %rdx
	imulq	$998244353, %rdx, %rax
	subq	%rax, %rcx
	cmpq	%rdi, %r10
	jne	.L204
	movl	60(%rsp), %eax
	leaq	_ZZ4testiE1c(%rip), %r10
	movl	$1, %r8d
	xorl	%esi, %esi
	movabsq	$-8525806094425994177, %rdi
	leaq	4(%r10), %rdx
	leal	-1(%rax,%rax), %eax
	leaq	(%rdx,%rax,4), %r11
	.p2align 4
	.p2align 3
.L207:
	movl	(%r10), %ecx
	addq	$4, %r10
	imulq	%r8, %rcx
	addq	%rsi, %rcx
	movq	%rcx, %rax
	mulq	%rdi
	movq	%rdx, %rsi
	shrq	$29, %rsi
	imulq	$998244353, %rsi, %rax
	movq	%rcx, %rsi
	movq	%r8, %rcx
	salq	$4, %rcx
	addq	%r8, %rcx
	subq	%rax, %rsi
	movq	%rcx, %rax
	mulq	%rdi
	shrq	$29, %rdx
	imulq	$998244353, %rdx, %rax
	subq	%rax, %rcx
	movq	%rcx, %r8
	cmpq	%r11, %r10
	jne	.L207
	imulq	%r15, %r14
	movl	60(%rsp), %r8d
	movl	%r12d, %edx
	subl	%ebx, %r9d
	leaq	.LC8(%rip), %rcx
	call	_Z6printfPKcz
	movq	%r14, %rax
	mulq	%rdi
	shrq	$29, %rdx
	imulq	$998244353, %rdx, %rax
	subq	%rax, %r14
	cmpq	%rsi, %r14
	je	.L215
	leaq	.LC9(%rip), %rcx
	addq	$2584, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	popq	%rbp
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	jmp	puts
.L215:
	addq	$2584, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	popq	%rbp
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	ret
.L198:
	movl	60(%rsp), %ebx
	xorl	%edx, %edx
	movl	$16777216, %eax
	idivl	%ebx
	movl	%eax, %edi
	call	clock
	movl	%eax, %esi
	call	clock
	movl	%ebx, %r8d
	movl	%edi, %edx
	leaq	.LC8(%rip), %rcx
	subl	%esi, %eax
	movl	%eax, %r9d
	addq	$2584, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	popq	%rbp
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	jmp	_Z6printfPKcz
	.seh_endproc
	.section	.text.startup,"x"
	.p2align 4
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
.LFB10100:
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$40, %rsp
	.seh_stackalloc	40
	.seh_endprologue
	movl	$12, %esi
	movl	$256, %ebx
	call	__main
	.p2align 4
	.p2align 3
.L219:
	movl	%ebx, %ecx
	addl	%ebx, %ebx
	call	_Z4testi
	subl	$1, %esi
	jne	.L219
	xorl	%eax, %eax
	addq	$40, %rsp
	popq	%rbx
	popq	%rsi
	ret
	.seh_endproc
	.p2align 4
	.def	_GLOBAL__sub_I_p1_vec;	.scl	3;	.type	32;	.endef
	.seh_proc	_GLOBAL__sub_I_p1_vec
_GLOBAL__sub_I_p1_vec:
.LFB10814:
	subq	$40, %rsp
	.seh_stackalloc	40
	.seh_endprologue
	movl	$-1, %edx
	leaq	p1_vec(%rip), %rcx
	call	_ZN3ymmC1Ej
	xorl	%edx, %edx
	leaq	p0_vec(%rip), %rcx
	call	_ZN3ymmC1Ej
	movl	$998244352, %edx
	leaq	mod1_vec(%rip), %rcx
	call	_ZN3ymmC1Ej
	movl	$998244353, %edx
	leaq	mod_vec(%rip), %rcx
	call	_ZN3ymmC1Ej
	movl	$-770891610, %edx
	leaq	mod_inv_vec(%rip), %rcx
	addq	$40, %rsp
	jmp	_ZN3ymmC1Ej
	.seh_endproc
	.section	.ctors,"w"
	.align 8
	.quad	_GLOBAL__sub_I_p1_vec
.lcomm _ZZ4testiE1c,67108864,32
.lcomm _ZZ4testiE1b,67108864,32
.lcomm _ZZ4testiE1a,67108864,32
	.globl	c
	.bss
	.align 64
c:
	.space 67108928
	.globl	b
	.align 64
b:
	.space 67108928
	.globl	a
	.align 64
a:
	.space 67108928
	.globl	wbuf
	.align 32
wbuf:
	.space 2000000
	.globl	buf
	.align 32
buf:
	.space 500000
	.globl	m
	.align 4
m:
	.space 4
	.globl	n
	.align 4
n:
	.space 4
	.globl	wi
	.align 64
wi:
	.space 67108928
	.globl	wr
	.align 64
wr:
	.space 67108928
	.globl	mogo_np
	.align 32
mogo_np:
	.space 32
	.globl	mogo_n
	.align 32
mogo_n:
	.space 32
	.globl	mod_inv_vec
	.align 32
mod_inv_vec:
	.space 32
	.globl	mod_vec
	.align 32
mod_vec:
	.space 32
	.globl	mod1_vec
	.align 32
mod1_vec:
	.space 32
	.globl	p0_vec
	.align 32
p0_vec:
	.space 32
	.globl	p1_vec
	.align 32
p1_vec:
	.space 32
	.def	__main;	.scl	2;	.type	32;	.endef
	.ident	"GCC: (Rev1, Built by MSYS2 project) 14.2.0"
	.def	__mingw_vfprintf;	.scl	2;	.type	32;	.endef
	.def	puts;	.scl	2;	.type	32;	.endef
	.def	exit;	.scl	2;	.type	32;	.endef
	.def	memcpy;	.scl	2;	.type	32;	.endef
	.def	memset;	.scl	2;	.type	32;	.endef
	.def	clock;	.scl	2;	.type	32;	.endef
