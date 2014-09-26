#Projet Arimaa � CR2 : Mercredi 24 Septembre
Pr�sents : Toute l'�quipe, Christian Raymond, et Nikos Parlavantzas

##Ordre du jour :
- Validation des technologies choisies
- �tude de l'�tat de l'art
- Orientation du cahier des charges

##Information �chang�es :

- Pr�sentation de th�ses et travaux sur la parall�lisation du jeu Arimaa par Beno�t:
  - Tout raisonnement trop li� au jeu ne pourra pas se g�n�raliser. Cela ne sert � rien de commencer � �tudier des cas qui ne sont relatifs qu'� Arimaa
  - Graphique tr�s int�ressant montrant la baisse de l'efficacit� de l'algorithme utilis� par un th�sard, g�r� par 4 threads quand le temps augmente. "Additionnal time for thinking worths the less the time engine has".
- Travail sur Arimaa simplifi�, pour commencer, on sauvegardera des algorithmes de m�moire avec des tableaux simples en 2D remplis de 0 et 1.
- Validation du C++, de Grid5000, et de OpenMP.
- Ordre du jour des prochaines s�ances�:
  - s'int�resser au contenu du prochain rapport (pr�sentation algorithme, st�r�otype de parall�lisation)
  - continuer � s'int�resser � l'�tat de l'art, faire une �tude plus pouss�e de la bibliographie, l'impl�mentation de la m�thode de Montecarlo � Algo Min-Max
- Discuter des 3 strat�gies de la parall�lisation�: (d�finitions � approfondir)
  - Root parallel�: 1 thread, 1 arbre, fusion des statistiques de la premi�re ligne et continue. Ne calcule qu'un n�ud � la fois, puis recommence le calcul sur toutes les branches
  - Leaf parallel�: plus simple pour les communications machines, on fusionne les r�sultats trouv�s pour cr�er un nouveau n�ud "moyen"
  - Tree parallel�: d�veloppe les feuilles de fa�on parall�les (autant de thread que de feuilles)
- Probl�me dans un certain cas. Lors d'une surcharge de statistiques, il est possible de perdre quelques unes de ces statistiques. On utiliserait un mutex pour prot�ger et enregistrer ces statistiques. Le probl�me de cette m�thode est le co�t qui para�trait trop �lev�. Ainsi, on ignorera le probl�me au vu de toutes les autres statistiques que nous avons.
- Faire une pr�-�tude des probl�mes dans le premier rapport, d�crire le projet, et les r�soudre dans le deuxi�me rapport.
- Dans tous les cas, l'�tude se fait sur plusieurs postes d�s le d�part.
- R�partition des r�les faite (temporaire avec rotations toutes les deux semaines � priori en fonction des charges de travail � les noms des postes ne sont pas d�finitifs)�:
  - R�dacteur en chef�: il g�re et oriente le groupe, recherche des axes pour le compte-rendu d'octobre *(Dan pour le moment)*
  - Responsable r�union�: il g�re les r�unions, le mat�riel, la relation avec les enseignants, il oriente le debriefing, et sait de quoi tout parle. *(Dan pour le moment)*
  - Responsable parall�lisation�: il approfondit les notions des 3 parall�lismes de Christian Raymond (Tree/Leaf/Root), recherche de bibliographe et comparatifs des diff�rentes m�thodes *(Beno�t et Mika�l pour le moment)*
  - Responsable utilitaires: il g�re l'UML (si le temps le permet) et Microsoft Project, travail sur le suivi des t�ches, les deadlines et la r�partition des ressources *(Baptiste pour le moment)*
  - Responsable application�: il compl�te la version du jeu d'Arimaa et cherche � savoir si la nouvelle version de C++ 2011 est stable pour l'utiliser dans le projet. *(Gabriel pour le moment)*
- �criture des compte-rendus en Latex pour la forme et se familiariser avec le format.

##Planification

T�che  | Responsable | Deadline
------------ | ------------- | --------
�tat de l'art, th�ses, comparatifs,bibliographie | Beno�t,Mika�l | 01/10 extendable
�tablir le cahier des charges/compte-rendu | Dan | 01/10 Octobre
Compl�ter le jeu, et la compatibilit� C++ 2011 | Gabriel | 01/10 extendable
Tutoriel MS Project + UML si possible | Baptiste | 01/10 extendable

##Date de la prochaine r�union : 01/10