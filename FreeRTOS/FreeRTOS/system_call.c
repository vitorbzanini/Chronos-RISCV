#include "system_call.h"

#include "chronos.h"
#include <errno.h>

/* Receives a message */
int sys_Receive(unsigned int addr, unsigned int from){
	prints("1 testando receive!\n");
    printsv("SYS_RECV_MSG ", SYS_RECV_MSG);
    printsv("addr ", addr);
    printsv("from ", from);
	__internal_syscall(SYS_RECV_MSG, addr, from, 0, 0, 0, 0);
	prints("2 testando receive!\n");
	return 1;
}

/* Sends a message */
int sys_Send(unsigned int addr, unsigned int to){
	__internal_syscall(SYS_SEND_MSG, addr, to, 0, 0, 0, 0);
	return 1;
}

/* Finishes a task */
int sys_Exit(){
	__internal_syscall(SYS_END_TASK, 0, 0, 0, 0, 0, 0);
	return 1;
}

/* Prints one value using the printer peripheral */
int sys_Printi(unsigned int value){
	__internal_syscall(SYS_PRINTI, value, 0, 0, 0, 0, 0);
	return 1;	
}

/* Prints a string using the printer peripheral */
int sys_Prints(unsigned int addr){
	__internal_syscall(SYS_PRINTS, addr, 0, 0, 0, 0, 0);
	return 1;
}

int sys_Testing(unsigned int arg0, unsigned int arg1, unsigned int arg2, unsigned int arg3, unsigned int arg4, unsigned int arg5){
	__internal_syscall(SYS_TESTING, arg0, arg1, arg2, arg3, arg4, arg5);
	return 1;
}

/* Syscall Handler */
unsigned int handle_syscall(){
	unsigned int arg0, arg1, arg2, arg3, arg4, arg5, type;
	unsigned int *pointer;
	register long temp asm("s2") = 0;
	asm("addi	s2, sp, 0");
	
	pointer = (unsigned int *)(temp + (29*4));
	arg0 =  *pointer;

	pointer = (unsigned int *)(temp + (30*4));
	arg1 = *pointer;
	
	pointer = (unsigned int *)(temp + (31*4));
	arg2 = *pointer;

	pointer = (unsigned int *)(temp + (32*4));
	arg3 = *pointer;

	pointer = (unsigned int *)(temp + (33*4));
	arg4 = *pointer;

	pointer = (unsigned int *)(temp + (34*4));
	arg4 = *pointer;

	pointer = (unsigned int *)(temp + (36*4));
	type = *pointer;
	
	switch (type){

		case SYS_TESTING:
			prints("Detectei uma chamada TESTE de sistema!\n");
			printsv("arg0 ", arg0);
			printsv("arg1 ", arg1);
			printsv("arg2 ", arg2);
			printsv("arg3 ", arg3);
			printsv("arg4 ", arg4);
			printsv("type ", type);
			break;

		default:
			prints("Systemcall não identificada!\n");
			printsv("arg0 ", arg0);
			printsv("arg1 ", arg1);
			printsv("arg2 ", arg2);
			printsv("arg3 ", arg3);
			printsv("arg4 ", arg4);
			printsv("type ", type);
			break;
	}
	return 87;
	////////////////////////////////////////////////////
	// Utilize para encontrar os argumentos na pilha!!!
	// int i;
	// unsigned int *p;
	// unsigned int value;
	// register long temp asm("t4") = 0;
	// asm("addi	t4, sp, 0");
	// for (i = 0; i < 64; i++){
	// 	p = (temp + (i*4));
	// 	value = *p;
	// 	printsvsv("i: ", i, " value: ", value);
	// }
    // prints("Cheguei aqui!!!!!!! sucessooo :D\n");
	////////////////////////////////////////////////////
}