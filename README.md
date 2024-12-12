# Compte rendu TP1 synthèse : 

Ce TP m'a permis d'acquérir différentes connaissances : 

La question 2 m'a permis de mieux appréhender la création d'un processus fils (qu'il soit exécuté, non exécuté ou que ce soit le processus parent qui soit exécuté).
Grace à ça j'ai pu créer la boucle qui m'as permis d'écrire des commandes dans mon shell.
![whatever](TPinfo_q2.png)

La question 4 m'a causé problème car je ne comprenais pas comment "tuer" le signal. 
Premièrement j'ai appris a utiliser des boucles sur la commande "WIFEXISTED" pour savoir si la commande existait "exit:0" ou n'existait pas "exit:1".
La boucle sur la commande "WIFSIGNALED" m'a donc permis de pouvoir tuer le signal lorsque je le voulais. Pour ça j'ai compris qu'il fallait recuperé l'adresse du PID afin de fermer le fils à l'aide d'un signal extérieur. Pour avoir ce signal il faut donc lancé un autre terminal car le notre est en "sleep".

![whatever](TPinfo_q4.png)
![whatever](termsig.png)
![whatever](sigkill.png)

Dans la question 5 j'ai pu utilisé la commande clock_gettime, notamment avec cette ligne : 
if (clock_gettime(CLOCK_MONOTONIC, start) == -1) 
qui permet d'obtenir l’heure actuelle et la stocker dans la variable start. On peut donc en déduire qu'il faudra faire la meme pour la variable de fin puis soustraire les deux.

Pour la 6ème question, on travaille sur l'utilisation de la fonction strtok. Pour envoyer notre commande complexe j'ai alors pensé à faire une fonction qui sépare une commande complexe comme "ls -l" en "ls" et "-l".
On remplace maintenant dans notre fonction : execlp(buf, buf,(char*) NULL) par execvp(argv[0], argv); qui permettra de alors de traiter les différents arguments de notre commande.
Avec cela, on arrive à traiter des commandes complexe.

J'ai essayé de résoudre la question 7, pendant un moment, cependant je n'ai pas réussi à trouver la solution. Le code que j'avais essayé est en commenté dans mon code.
