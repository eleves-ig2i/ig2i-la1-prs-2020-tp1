/**
 * Auteur : Nathan SALEZ
 * Description : Programme en C permettant l'analyse de la macro check et de la fonction fork()
 * Date : 12/11/2019
 * Compilation et exécution : gcc check-fork.c -o check-fork && ./check-fork
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> // pour la fonction exit()

#define CHECK(sts,msg) if ((sts) == -1 ) { perror(msg);exit(-1);}


int main()
{
	
	CHECK(fork(),"Ne peut pas créer un nouveau processus");
	CHECK(fork(),"Ne peut pas créer un nouveau processus");
	printf("Je suis le processus %d, mon pere est le %d.\n",getpid(),getppid());

	return 0;
}
