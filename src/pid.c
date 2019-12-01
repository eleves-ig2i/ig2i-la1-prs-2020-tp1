/**
 * Auteur : Nathan SALEZ
 * Description : Programme en C permettant d’afficher l’identificateur du processus courant et celui de son père.
 * Date : 12/11/2019
 * Compilation et exécution : gcc pid.c -o pid && ./pid
 */
 
#include <unistd.h>
#include <stdio.h>

int main()
{
	// Les fonctions getpid() et getppid() ne renvoyant jamais une erreur d'après le man, on n'effectue aucun test sur les valeurs de retour
	fprintf(stdout,"Identificateur du processus courant : %d\n",getpid());
	fprintf(stdout,"Identificateur du processus parent : %d\n",getppid());
	return 0;
}

