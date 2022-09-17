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
#define MSGSIZE 305
#define TEMPO_MIN 2

/*
fork		OK
exec		OK
clone		OK
pipe		OK
waitpid		OK
exit		OK
sigaction	OK
kill		OK
*/

static int rose(void* arg) {
    char* buffer = (char*)arg;
    printf("%s\n", buffer);
	sleep(2*TEMPO_MIN);

    strcpy(buffer, "Rose: ...\n"); // Filho escreve no buffer
    return 0;
}

static int nascimento_rose(void) {
    const int STACK_SIZE = 65536;
    char* stack = malloc(STACK_SIZE);
    if (!stack) {
        perror("malloc");
        exit(1);
    }

    // Se CLONE_VM for definido, os processos pai e filho executam
	// no mesmo espaço de memória
    unsigned long flags = 0;
    flags |= CLONE_VM;

    char buffer[100];
    strcpy(buffer, "\"Rose, você será diferente de suas irmãs. Não se sinta\n"
					"culpada pelo o que acontecer.\"\n"); // Pai escreve no buffer
				
    if (clone(rose, stack + STACK_SIZE, flags | SIGCHLD, buffer) == -1) {
        perror("clone");
        exit(1);
    }

    int status;
    if (wait(&status) == -1) {
        perror("wait");
        exit(1);
    }

    printf("%s\n", buffer);
	sleep(TEMPO_MIN);

	free(stack);
	return 0;
}

int main() {

	pid_t pid[2];
	int status;
	char inbuf[MSGSIZE];
	int p[2];

	printf("\n                  CONFLITO DA LINHAGEM ELDIANA                   \n\n");
	sleep(TEMPO_MIN);
	printf("Sou Ymir, uma escrava do rei Fritz, de Eldia, um antigo reino que\n"
			"sofria com guerras constantes.\n\n");
	sleep(2*TEMPO_MIN+1);

	printf("Como qualquer escrava, fui bastante maltratada e, certo dia,\n"
			"após uma fuga mortal pela floresta, fui agraciada com os poderes\n"
			"de um titã.\n\n");
	sleep(3*TEMPO_MIN);

	printf("Mas eu possuia um complexo que não me permitia abandonar o rei e\n"
			"mesmo com os grandes poderes que obtive continuei a servi-lo\n"
			"fielmente como um instrumento de guerra.\n\n");
	sleep(3*TEMPO_MIN);

	printf("Eu e o rei Fritz tivemos duas filhas:\n\n");
	sleep(TEMPO_MIN+1);

	if (pipe(p) < 0)
        exit(1);

	char* msg1 = "\"Sina,\n\n"
				 "Há verdades as quais você desconhece. Venha me encontrar\n"
				 "no porão do castelo meia noite. Assim você poderá ter um\n"
				 "futuro diferente do meu.\n\n"
				 "Com carinho,\n"
				 "Sua mãe, Ymir.\"\n\n";

	write(p[1], msg1, MSGSIZE);

	pid_t maria, sina;
	maria = fork();
	pid[0] = maria;

	if (maria == 0) {
		printf("Maria, a preferida do rei.\n\n");
		sleep(TEMPO_MIN+1);
	} else {
		sleep(TEMPO_MIN);
		sina = fork();
		pid[1] = sina;
		if (sina == 0) {
			printf("E Sina, a caçula até então. Tentei, assim como tentei com\n" 
					"Maria, fazer com que ela não seguisse os princípos do\n"
					"próprio pai, mas foi inútil, o rei Fritz sempre teve\n"
					"mais influência.\n\n");
			sleep(4*TEMPO_MIN);

			printf("Cheguei mesmo a colocar uma carta em seu quarto, já que eu não\n"
					"podia interagir muito com elas. A carta dizia: \n\n");
			sleep(2*TEMPO_MIN);

			read(p[0], inbuf, MSGSIZE);
			printf("%s", inbuf);
			sleep(5*TEMPO_MIN);

			printf("Inútil. Sina nunca apareceu.\n\n");
			sleep(TEMPO_MIN);
		} else {
			waitpid(pid[0], &status, 0);
			waitpid(pid[1], &status, 0);

			printf("Eu, já bastante desgastada, estava próxima da morte, mas\n" 
					"ainda tive outra filha, Rose.\n\n");
			sleep(2*TEMPO_MIN);

			printf("No momento de seu nascimento, ciente de meu destido, cochichei,\n"
					"como se ela pudesse me endender:\n\n");
			sleep(2*TEMPO_MIN);

			nascimento_rose();

			printf("Comigo cada vez mais fraca, o rei Fritz ordenou que nossas\n"
					"filhas me consumissem em um ritual canibalesco para que os\n" 
					"poderes pudessem ser passados adiante.\n\n");
			sleep(3*TEMPO_MIN);

			printf("Mas ninguém percebeu que também dei origem a um outro filho que não se\n"
					"materializou como uma nova criança, mas sim como o rancor que guardei\n"
					"por tudo que sofri e que, assim como meus poderes, transitou entre\n"
					"diversas gerações.\n\n");
			sleep(4*TEMPO_MIN+1);

			static char *args[] = { "./geracaoEren", "1", "10", NULL };
            execv(args[0], args);
		}
	}
	return 0;
}