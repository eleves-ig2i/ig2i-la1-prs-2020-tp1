/**
 * Auteur : Nathan SALEZ
 * Description : Programme en C effectuant un traitement lorsque qu'on appuie sur CTRL+C
 * Date : 12/11/2019
 * Compilation et exécution : gcc ctrlc-handler-v2.c -o ctrlc-handler-v2; ./ctrlc-handler-v2
 */
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void callback(int numSignal)
{
	fprintf(stdout,"Le contrôle-C est désactivé.\n");
}


int main()
{
	fprintf(stdout,"PID du processus : %d\n",getpid());
	
	struct sigaction preparationSignal;
	
	// Association du callback au gestionnaire de signaux.
	preparationSignal.sa_handler=&callback;
	
	// On ne souhaite pas bloquer de signal.
	sigemptyset(&preparationSignal.sa_mask);
	
	//Installation du gestionnaire d'actions
	sigaction(SIGINT,&preparationSignal,NULL);
	
	while(1);
	// Pour fermer le programme, utiliser la commande "kill -SIGHUP <pid>"

	return 0;
}
