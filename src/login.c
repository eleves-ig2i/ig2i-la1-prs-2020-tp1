/**
 * Auteur : Nathan SALEZ
 * Description : Programme en C simulant un login, avec la mise en place d'une alarme, et d'un limiteur de tentatives
 * Date : 12/11/2019
 * Compilation et exécution : gcc login.c -o login; ./login
 */
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h> // pour la fonction exit()
#include <sys/wait.h> // pour la fonction wait()

#define CHECK(sts,msg) if ((sts) == -1 ) { perror(msg);exit(-1);}

/**
 * Définit le délai en secondes, pendant lequel l'utilisateur peut saisir le mot de passe.
 */
#define DELAI_ALARME 20


/**
 * Définit le mot de passe de l'application, ne doit pas être constitué de tabulations, d'espaces ou de sauts de ligne.
 */
#define MOT_DE_PASSE "Hellothere"


/**
 * Définit le nombre de tentatives de connexion autorisé.
 */
#define NOMBRE_TENTATIVES 5


/**
 * Callback utilisé par le gestionnaire de signaux.
 */
void deroute(int numSignal)
{
	switch(numSignal)
	{
		case SIGINT :
			fprintf(stderr,"Le contrôle-C est désactivé.\n");
			break;
		
		case SIGALRM :
			exit(2);
			break;
			
		default :
			fprintf(stderr,"Signal %d non pris en compte.\n",numSignal);
	}
}


/**
 * Permet de faire saisir le mot de passe à l'utilisateur.
 * Nombre de tentatives limités par NOMBRE_TENTATIVES.
 * Cette fonction renvoie un signal au processus père : 0 pour succès et -1 pour trop de tentatives.
 * On n'effectue pas de vérification pour le buffer overflow.
 */
void saisirMotDePasse()
{
	char mdpUtilisateur[30];
	int nbTentatives = 0;
	while( nbTentatives < NOMBRE_TENTATIVES)
	{
		fprintf(stdout,"Veuillez saisir le mot de passe :");
		fscanf(stdin,"%s",mdpUtilisateur);
		if( strcmp(MOT_DE_PASSE,mdpUtilisateur) == 0 )
		{
			exit(0);
		} 
		else
		{
			++nbTentatives;
		}
	}
	exit(1);
}


/**
 *	Analyse le code de retour du processus fils et affiche le message correspondant.
 */
void traiterReponseProcessusFils(int wstatus)
{
	// fprintf(stdout,"Debug - pid %d - wstatus = %d\n",getpid(),wstatus);
	if( WIFEXITED(wstatus) )
	{
		int exitStatus = WEXITSTATUS(wstatus);
		// fprintf(stdout,"Debug - pid %d - WEXITSTATUS = %d\n",getpid(),exitStatus);
		switch( exitStatus )
		{
			case 0 : 
				fprintf(stdout,"Mot de passe trouvé !\n");
				break;
				
			case 1 :
				fprintf(stderr,"Trop de tentatives, arrêt du programme.\n");
				break;
				
			case 2 :
				fprintf(stderr,"Temps écoulé, arrêt du programme.\n");
				break;
				
			default:
				fprintf(stderr,"Code statut non pris en compte.\n");
		}
	}
}


/**
 * Associe le callback void deroute(int) à la saisie de CTRL+C pour le processus fils.
 * doit réagir au signal d'alarme avec la fonction void deroute(int)
 */
void initGestionnaireSignauxFils()
{
	struct sigaction preparationSignalFils;		
	preparationSignalFils.sa_handler=&deroute;
	preparationSignalFils.sa_flags=0;
	sigemptyset(&preparationSignalFils.sa_mask);
	CHECK( sigaction(SIGINT,&preparationSignalFils,NULL),"Impossible d'installer l'action SIGINT pour le processus fils.\n");
	CHECK( sigaction(SIGALRM,&preparationSignalFils,NULL),"Impossible d'installer l'action SIGALRM pour le processus fils.\n");
}


/**
 * Permet de ne pas prendre en compte la saisie de CTRL+C pour le processus père.
 * doit réagir au signal d'alarme avec la fonction void deroute(int)
 */
void initGestionnaireSignauxPere()
{
	sigset_t sigSet;
	sigemptyset(&sigSet);
	sigaddset(&sigSet,SIGINT);	// le signal correspondant au CTRL+C est SIGINT
	CHECK( sigprocmask(SIG_BLOCK,&sigSet,NULL), "Impossible d'installer le masque pour le processus père");
}


int main()
{
	pid_t pid;
	
	initGestionnaireSignauxPere();
	CHECK(pid = fork(),"CHECK - Impossible de créer le processus fils, arrêt du programme.\n");
	
	if(pid == 0)
	{
		alarm(DELAI_ALARME);
		initGestionnaireSignauxFils();
		saisirMotDePasse();
	}
	
	int wstatus;
	CHECK(waitpid(pid,&wstatus,0),"CHECK - Le processus fils n'existe pas ou n'est pas un fils du processus parent.\n");
	
	traiterReponseProcessusFils(wstatus);
	
	return 0;
}
