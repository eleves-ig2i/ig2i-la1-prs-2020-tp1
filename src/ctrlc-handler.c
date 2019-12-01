/**
 * Auteur : Nathan SALEZ
 * Description : Programme en C effectuant un traitement lorsque qu'on appuie sur CTRL+C
 * Date : 12/11/2019
 * Compilation et exécution : gcc ctrlc-handler.c -o ctrlc-handler && ./ctrlc-handler
 */
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int main()
{
	fprintf(stdout,"PID du processus : %d\n",getpid());
	sigset_t sigSet;
	sigemptyset(&sigSet);
	sigaddset(&sigSet,SIGINT);	// le signal correspondant au CTRL+C est SIGINT
	
	// Le mode SIG_BLOCK correspond 
	if( sigprocmask(SIG_BLOCK,&sigSet,NULL) == 0)
	{
		while(1);
	}
	else
	{
		fprintf(stderr,"Impossible de mettre en place le masque.\n");
	}
	return 0;
}
