#Projet Arimaa � CR1 : Mercredi 17 Septembre
Pr�sents : Toute l'�quipe, Christian Raymond et un intervenant ext�rieur inconnu

##Ordre du jour :
- D�finition du projet et des objectifs
- Choix du jeu
- D�couverte des diff�rents outils/langages possibles

##Information �chang�es :

- Sur quel jeu allons-nous travailler ? Proposition d'Arimaa, les dames et le morpion �tant r�solus, et les �checs trop strat�gique, trop complexe et d�j� trop �tudi�.
- Codage du jeu par *Gabriel* en C++
- Jouer au jeu pour m�moriser les r�gles et pouvoir faire des strat�gies
- Quel langage utiliser ? Proposition du C++ car les applications seraient plus facile � coder, et compatible avec les cours de C++ du moment. Il sera toujours possible d'utiliser d'autres langages plus adapt�s et impl�menter des interfaces entre ces derniers.
- Quel logiciel utiliser pour la parall�lisation ? OpenMP mais v�rifier la compatibilit�. *T�che � effectuer par Baptiste et Mikail*
- Quel machine utiliser ? On prendra Grid5000, un cluster de machines virtuelles parall�les de l'IRISA pour avoir une puissance de calcul plus �lev�e. *V�rifier de m�me la compatibilit� par Dan*
- Utilisation de Microsoft Project pour g�rer les t�ches du projet. La pr�sentation du logiciel sera effectu�e un peu plus tard dans l'ann�e.
- Choix de la forge : Github priv�. Refus d'utiliser la forge de l'INSA pour des raisons de manque de stabilit� de l'ENT, utilisation du Git priv� de Benoit.
- Planification de t�ches � court terme : �tablir le cahier des charges pour le premier compte-rendu en Octobre. Le probl�me est que le groupe ne contient que 5 �l�ments avec 3 partants au deuxi�me semestre. Ainsi, commencer le code avant Janvier pourrait �tre une bonne chose. Alternative : ajout d'une sixi�me personne.
- Choix de l'environnement Linux
- �tablir la r�partition des t�ches. Trouver un coordinateur. 
- But du projet : effectuer des comparaisons d'algorithmes de chercheurs pour Arimaa (Gameplaying : d�velopper des strat�gies IA)
- Techniques pour calculer le meilleur chemin pour gagner une partie :
- Technique du boulet de canon : on tente tout et n'importe quoi et on finit par avoir une trame du meilleur chemin
Montecarlo : d�rouler une partie au hasard jusqu'� la fin et en tirer des statistiques en le r�p�tant, pour pouvoir explorer en fonction des statistiques.
- Tirer profit de la parall�lisation avec une heuristique
- Prix de 10000 � si l'ordinateur (un seul) peut gagner sur un ensemble de 6 parties contre un �tre humain.
- Technologies additionnelles � �tudier : Java Scala, Akka
- �tat de l'art (�tude de th�ses faites sur le jeu Arimaa) pour partir sur des bonnes bases. *T�che � effectuer par Beno�t.*

##Planification

T�che  | Responsable | Deadline
------------ | ------------- | --------
Initiation au jeu Arimaa | Tout le monde | aucune
Compatibilit� OpenMP | Baptiste, Mikail | 24/9
Compatibilit� Grid5000 | Dan | 24/9
�tat de l'art, th�ses |  Beno�t  | 24/9 extendable
�tablir le cahier des charges | Chef de projet | Octobre

##Date de la prochaine r�union : 24/09

##Documents additionnels :
- Adresse du GitHub du projet : https://github.com/ildyria/Arimaa