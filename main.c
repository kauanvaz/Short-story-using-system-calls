#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

/*
fork		OK
exec		
clone		OK
pipe		
waitpid		OK
exit		OK
sigaction	
kill		
*/

/*

Ymir era uma escrava do rei Fritz, de Eldia, um antigo reino que sofria com as guerras
constantes. Como qualquer escrava, Ymir era bastante maltratada e, certo dia, após uma
fuga mortal pela floresta, foi agraciada com os poderes de um titã. Mas Ymir possuia
um complexo que não a permitia abandonar o rei e mesmo com os grandes poderes 
que possuia continuou a servi-lo fielmente.

********* fork, clone, waitpid **********
O rei teve três filhas com ela: Maria, Rose e Sina

Ymir, já bastante desgastada após ser usada como instrumento de guerra, estava próxima
de sua morte e para que os poderes pudessem ser passados adiantes, o rei Fritz
ordenou que as filhas se alimentassem da própria mãe em um ritual canibalesco.

Ligação com o Eren (futuro). Ymir realmente só descanda após Eren realizar o seu desejo.

********* exec **********
Após várias gerações, um garoto chamado Eren nasceu.

********* pipe **********
Em uma das guerras travadas entre humanos e titãs, sua mãe foi fatalmente ferida e, antes
de morrer, falou para que Eren sobrevivesse e não fizesse nada imprudente.

********* kill **********
No entanto, Eren não se conformou e seu desejo de vida passou a ser exterminar todos
os titãs que existem.

********* sigaction, kill  e exit **********
Ymir tem seu desejo de se libertar daquela maldição realizado por Eren e, finalmente, foi
capaz descansar.
*/

static int rose(void* arg) {
    char* buffer = (char*)arg;
    printf("%s\n", buffer);
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
	free(stack);
	return 0;
}

int main() {

	pid_t pid[2];
	int status;

	printf("Sou Ymir, uma escrava do rei Fritz, de Eldia, um antigo reino que\n"
			"sofria com guerras constantes.\n\n");
	printf("Como qualquer escrava, fui bastante maltratada e, certo dia,\n"
			"após uma fuga mortal pela floresta, fui agraciada com os poderes\n"
			"de um titã.\n\n");
	printf("Mas eu possuia um complexo que não me permitia abandonar o rei e\n"
			"mesmo com os grandes poderes que obtive continuei a servi-lo\n"
			"fielmente.\n\n");

	printf("Eu e o rei Fritz tivemos duas filhas:\n\n");

	pid_t maria, sina;

	maria = fork();
	pid[0] = maria;

	if (maria == 0) {
		printf("Maria, a preferida do rei.\n");
	} else {
		sina = fork();
		pid[1] = sina;
		if (sina == 0) {
			printf("E Sina, a caçula até então.\n\n");
		} else if (sina) {
			waitpid(pid[0], &status, 0);
			waitpid(pid[1], &status, 0);

			printf("Eu, já bastante desgastada após ser usada como instrumento de\n"
					"guerra por causa de meus poderes, estava próxima da morte, mas\n" 
					"meses antes ainda tive outra filha, Rose.\n\n");

			printf("No momento de seu nascimento, ciente de meu destido, cochichei,\n"
					"como se ela pudesse me endender:\n\n");
			
			nascimento_rose();
		}
	}
	return 0;
}