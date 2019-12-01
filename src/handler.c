/**
 * Auteur : Nathan SALEZ
 * Description : Programme en C permettant d'étudier le comportement obtenu lors d'envoi de signal avec la commande kill
 * Date : 12/11/2019
 * Compilation et exécution : gcc handler.c -o handler && ./handler
 */
#include <unistd.h>
#include <stdio.h>

int main()
{
	fprintf(stdout,"PID du processus : %d\n",getpid());
	alarm(20) ; pause() ;
	return 0;
}
