.386
.model flat,stdcall
option casemap:none
include E:\masm32\include\windows.inc
include E:\masm32\include\user32.inc
includelib E:\masm32\lib\user32.lib
include E:\masm32\include\kernel32.inc
includelib E:\masm32\lib\kernel32.lib
include E:\masm32\include\masm32.inc
includelib E:\masm32\lib\masm32.lib
include E:\masm32\include\msvcrt.inc
includelib E:\masm32\lib\msvcrt.lib
.data
	id1 dd 20
	@Fmt db "%d",10,0
	i dd ?
	@Temp_0 dd ?
.code
start:
@line_1:
	mov eax,1
	cmp eax,0
	jne @line_3
@line_2:
	jmp @line_7
@line_3:
	mov eax,i
	add eax,1
	mov @Temp_0,eax
@line_4:
	mov eax,@Temp_0
	mov i,eax
@line_5:
	jmp @line_7
@line_7:
	mov eax,i
	invoke crt_printf,addr @Fmt,eax
@line_8:
	jmp @line_9
@line_9:
	invoke ExitProcess,NULL
end start
