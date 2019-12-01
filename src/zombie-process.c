/**
 * Auteur : Nathan SALEZ
 * Description : Programme en C permettant l'analyse d'un processus zombie
 * Date : 12/11/2019
 * Compilation et exécution : gcc zombie-process.c -o zombie-process && ./zombie-process
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> // pour la fonction exit()
#include <sys/wait.h> // pour la fonction wait()

#define CHECK(sts,msg) if ((sts) == -1 ) { perror(msg);exit(-1);}


int main()
{
	pid_t pid;
	
	CHECK(pid= fork(),"Ne peut pas créer un nouveau processus");
	/**
	 * fork() retourne les valeurs suivantes :
	 * => le pid du fils au processus père
	 * => 0 au processus fils
	 * => -1 en cas d'erreur
	 */
	if( pid == 0)
	{
		// processus fils
		fprintf(stdout,"Processus %d : fils de %d\n",getpid(),getppid());
		sleep(3);
		exit(10);
	}
	else
	{
		// processus père
		int wstatus;
		fprintf(stdout,"Processus %d : père de %d\n",getpid(),pid);
		waitpid(pid,&wstatus,0);
		fprintf(stdout,"Processus %d : processus %d fini avec wstatus = %d.\n",getpid(),pid,wstatus);
		sleep(2);
		if( WIFEXITED(wstatus) )
		{
			fprintf(stdout,"Processus %d : code de retour du processus fils = %d.\n",getpid(),WEXITSTATUS(wstatus));
		}
		exit(0);
	}

	pause();
	return 0;
}
