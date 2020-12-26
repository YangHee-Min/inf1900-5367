# Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

# Grille de correction des programmes:

Identification:
+ Travail    : Panneau de controle - Code
+ Section #  : 2
+ Équipe #   : 5367
+ Correcteur : Ahmad Faour

# LISIBILITÉ
## En-têtes en début de programme   

| Pénalité par erreur                          | -1.5       |
| -------------------------------------------- | ---------- |
| Noms des auteurs                             |            |
| Description du programme                     |            |
| Identifications matérielles (Broches I/O)    |            |
| Table des états ou autres s'il y a lieu      |            |
| __Résultat partiel__                         | __(0/1.5)__ |

## Identificateurs significatifs (Autodocumentation)

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Absence de *chiffres magiques*               | (0.5/0.5)     |
| Noms de variables décrivent l'intention      | (0.5/0.5)     |
| Noms de fonctions décrivent l'intention      | (0.5/0.5)     |
| __Résultat partiel__                         | __(1.5/1.5)__ |

## Commentaires pertinents

Bonnes raisons d'un commentaire
 + Explication d'un algorithme 
 + Procédure peu évidente (ou *hack*)
 + Référence d'extraits de code copiés d'Internet
 + Détail du POURQUOI d'un extrait de code

| Pénalité par erreur                          | -0.5       |
| -------------------------------------------- | ---------- |
| __Résultat partiel__                         | __(0/1.0)__ |


## Indentation   

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Indentation structurée                       | (0.5/0.5)     |
| Indentation uniforme dans le programme       | (0.5/0.5)     |
| __Résultat partiel__                         | __(1/1.0)__ |


# MODULARITÉ ET COMPRÉHENSION
## Fonctions bien définies

| Pénalité par erreur                          | -0.5       |
| -------------------------------------------- | ---------- |
| Responsabilité unique d'une fonction         |            |
| Maximum de 4 paramètres                      |            |
| Absence de code dupliqué                     |            |
| etc                                          |            |
| __Résultat partiel__                         | __(1/1.0)__ |


## Bonne application des concepts de programmation et systèmes embarqués

| Pénalité par erreur                          | -1.0       |
| -------------------------------------------- | ---------- |
| Utilisation appropriée des registres         |            |
| Machine à états codée clairement             |            |
| Délais et minuteries utilisés judicieusement |            |
| PWM bien établi                              |            |
| Scrutation et interruptions bien utilisées   |            |
| etc                                          |            |
| __Résultat partiel__                         | __(1/4.0)__ |

# FONCTIONNALITÉS
## Git

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Fichiers aux bons endroits                   | (1.5/1.5)     |
| Absence de fichiers inutiles                 | (1.5/1.5)     |
| __Résultat partiel__                         | __(3/3.0)__ |


## Compilation    

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Absence de messages d'erreurs de compilation | (1.5/1.5)     |
| Absence de messages d'attention (*warning*)  | (0.5/0.5)     |
| __Résultat partiel__                         | __(2/2.0)__ |
   

## Évaluation boîte noire  

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Cas normal de fonctionnement                 | (2.5/2.5)     |
| Cas limites observables                      | (2.5/2.5)     |
| __Résultat partiel__                         | __(5/5.0)__ |

# Résultat

__Total des points: 14.5/20__

# Commentaires du correcteur:

## En-têtes en début de programme  
* Aucune en-tête dans le fichier main

## Identificateurs significatifs (Autodocumentation)
* déclaration d'enum c'est comme une classe DoorState et non doorState


## Commentaires pertinents
* commentaire inutile dans les .h


## Bonne application des concepts de programmation et systèmes embarqués
* Keyboard.cpp: Utilisation d'un double pour un delay de 10ms, un uint8_t aurait été plus approprié
* Sonar.cpp: Calculer le sonar dans une interruption n'est pas une très bonne idée. L'interruption doit être le plus court possible.
* LEDBar.cpp: L'utilisation d'un PWM et d'une interruption aurait été plus judicieux qu'un delay

# Basé sur le commit suivant
```
commit 3f6bc968603e7ec842355157c6c7bb0f1e648118
Author: Adam Halim <adam.halim@polymtl.ca>
Date:   Mon Dec 7 21:22:45 2020 -0500

    modification du fichier .simu
```

# Fichiers indésirables
```

```

# Sortie de make dans les sous-répertoires
```
======================= Sortie de make dans /projet =============================
make: Entering directory '/home/ahmad/Desktop/Repo/my-grader/inf1900-grader/correction_projet_final/5367/projet'
make: *** No targets specified and no makefile found.  Stop.
make: Leaving directory '/home/ahmad/Desktop/Repo/my-grader/inf1900-grader/correction_projet_final/5367/projet'


```