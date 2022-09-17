#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#define TEMPO_MIN 2

void handler(int num) {
	write(STDOUT_FILENO, "\nMuito bem, Eren treinou vigorosamente durante os anos seguintes,\n"
						 "no entanto, nesse mundo não existe o poder superior do personagem\n"
						 "principal e, em uma das batalhas mais importantes, acabou morrendo.\n\n", 203);


	sleep(3*TEMPO_MIN+1);
	write(STDOUT_FILENO, "FIM\n", 5);

	kill(getpid(), SIGKILL);
}

void handler2(int num) {
	write(STDOUT_FILENO, "\nEren decidiu viver uma vida pacata, sabia de seu prósito,\n"
						 "mas também tinha conhecimento de suas fraquezas. Viveu muito,\n"
						 "mas com remorsos.\n\n", 143);


	sleep(3*TEMPO_MIN+1);
	write(STDOUT_FILENO, "FIM\n", 5);

	exit(0);
}

int main(int argc, char **argv) {

	struct sigaction sa;
	sa.sa_handler = handler;
	sigaction(SIGINT, &sa, NULL);

	struct sigaction sa2;
	sa2.sa_handler = handler2;
	sigaction(SIGTSTP, &sa2, NULL);

	printf("Assim o tempo passou. Minhas filhas foram vítimas do mesmo\n"
			"tipo de ritual, o poder sempre concentrado na linhagem da família\n"
			"real.\n\n");
	sleep(2*TEMPO_MIN+1);

	printf("Todas as nações nos odiavam, afinal o massacre que os titãs causavam\n"	
			"nas guerras eram enormes e nada podiam pará-los.\n\n");
	sleep(2*TEMPO_MIN+1);

	printf("Em uma certa geração tudo mudou. Uma mulher de nome Carla\n"
			"deu luz a Eren, a personificação do meu ódio.\n\n");
	sleep(2*TEMPO_MIN+1);

	printf("Eren era um bom menino, mas em uma das guerras travadas entre\n"
			"humanos e titãs, sua mãe foi morta.\n\n");
	sleep(2*TEMPO_MIN+1);

	printf("Ele ficou muito triste vendo sua mãe desfalacer na sua frente.\n"
			"Este é um momento da história que cabe a você decidir o que acontecerá:\n\n");
	sleep(2*TEMPO_MIN+1);

	printf("1. Permitir que ele siga com o objetivo herdado de Ymir.\n"
		   "(Pressione Ctrl + C);\n\n"
		   "2. Deixá-lo seguir a vida como está, já que é fraco demais para lutar\n"
		   "(Pressione Ctrl + Z).\n\n");
	sleep(4*TEMPO_MIN);

	while(1) {
		printf("...\n");
		sleep(2*TEMPO_MIN);
	}

	//char SHELLSCRIPT[60];
  	//int num, i=4, j=2;
  	//num = sprintf(SHELLSCRIPT, "#/bin/bash\npgrep -P %d", getpgrp());

	//kill(getpgrp(), SIGSEGV);

	//system(SHELLSCRIPT);

	return 0;
}