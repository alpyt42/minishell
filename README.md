# minishell

PBS : 
30/01 --> dans la strcuture du dico, il faut un node start qui ne bouge pas. sinon, si on rappelle al fonction, la recherche ne commence pas au debut de la structure

TO DO LIST :

Builtins : 420 lignes
--> Coder les fonctions
	Coder les builtins
		◦ echo et l’option -n
		◦ cd uniquement avec un chemin relatif ou absolu
		◦ pwd sans aucune option
		◦ export sans aucune option
		◦ unset sans aucune option
		◦ env sans aucune option ni argument
		◦ exit sans aucune option
Env : 340 lignes
--> Recuperer les variables globales dans une liste chainee 
Exec: 250 lignes
--> Execution des commandes
main: 230 lignes
--> 
parsing: 400 lignes
--> 
tools: 
--> 


Récupérer en boucle l’entrée de l’utilisateur

lexing de lq ligne 

parsing des tokens

Executer la commande



Gestion de l’environnement


Ref :
https://github.com/iciamyplant/Minishell
https://github.com/maxime-42/minishell/tree/master/src 
https://brennan.io/2015/01/16/write-a-shell-in-c/
https://git.chevro.fr/42-cestoliv/minishell/-/blob/main/include/minishell.h
https://github.com/cclaude42/minishell

super schema https://github.com/paulahemsi/minishell
bon tuto : https://github.com/vportens/minishell
tuto sur les signax : https://www.codequoi.com/envoyer-et-intercepter-un-signal-en-c/
dinguerie de tuto qui explique tout : https://www.notion.so/Minishell-e856e9af377f44b588e5fe120d4b6e2a