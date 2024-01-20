# Chapitre 6


## 6.1 Notion de tâche

Une tâche $T_{i}$ est un ensemble d'instructions réalisées sur un seul PE, entre 2 points de communication ou synchronisation.

Une tâche est caractérisée par ses données d'entrée $E_{i}$ et données de sortie $S_{i}$.


### Granularité
La granularité est une mesure de la taille de la tâche (nombre d'instructions réalisées pendant cette tâche...), à savoir le nombre d'instructions réalisée.

On parle de granularité fine, moyenne ou grossière en fonction de sa taille.


### Indépendance de deux tâches

$T_{i}$ et $T_{j}$ sont indépendants si

- $S_{i} \subset S_{j} = \null$ donc pas de données communes modifiées
- $S_{i} \subset E_{j} = \null$ donc pas de données lues par $T_{j}$ et modifiée par $T_{i}$
- $S_{i} \subset E_{i} = \null$ 
- $E_{i} \subset E_{j}$ -> pas de contrainte dessus....

Deux tâches qui sont indépendantes peuvent être exécutées dans un arbre quelconque.

Deux tâches qui ne sont pas indépendantes doivent être exécutées dans un ordre spécifié.
On notera par exemple:
$$T_{i} < T_{j}$$
pour indiquer que $T_{i}$ doit être fini avant que $T_{j}$ ne démarre.

__Deux tâches qui sont indépendantes peuvent s'exécuter en parallèle !__


Cela peut s'exprimer par une __relation de précédence__ et un __graphe de précédence__.

Notre question sera de voir comment on peut paralléliser une application sur la base de son graphe de précédence.

## 6.2 Partitionnement, placement et ordonnancement


### Partitionnement
C'est la division d'un problème en tâches

Souvent, le partitionnement concerne la division des données en sous-domaines de calcul.
(On peut faire des partitionnements en tranches verticales ou horizontales...)
(Partitionnement (décomposition) en blocs)
(Ou encore 'modulo' ou cyclique'... Utile pour répartir équitablement toutes les zones du domaine sur tous les processeurs, mais peu recommandé s'il y a des communications car on page la latence plusieurs fois...)

Le partitionnement est au choix de l'utilisateur, et il y a plusieurs contraintes:
    - si on choisit une granularité fine, il y aura un meilleur potentiel de parallélisme.
    Mais cela risque d'augmenter l'overhead de la gestion de ce parallélisme: (regarder schéma cours)

En général, on s'attend à ce que la granularité optimale requière la solution d'un problème d'optimisation.

### Placement
C'est le choix du processeur qui exécutera chacune des tâches résultant du partitionnement.

En général, cela peut aussi être un problème d'optimisation si on veut minimiser le temps d'exécution:

Exemple: On a des tâches indépendantes, mais de durée différente.
```text
T1: --------------
T2: -----
T3: ----------
```
La répartition de ces tâches sur plusieurs processeurs avec la contrainte qu'ils soient tous également chargé est un problème qui n'est pas simple (optimisation combinatoire)


### Ordonnancement
À quel moment chaque processeur peut commencer les tâches dont il a la charge, de sorte à ne pas violer des dépendances, tout en minimisant le temps d'exécution total.

__La méthode des temps au plus tôt et au plus tard__

C'est une technique de recherche opérationnelle qui s'applique à la résolution de ce type de problème.


On va considérer un exemple didactique, basé sur un graphe de précédence pour lequel on veut résoudre le problème du placement et de l'ordonnancement.

Soit le graphe de tâches suivant: (schéma du cours...) + (tableau du cours header: tache, earlest, latest)


Avec les marges obtenues dans le tableau, on va placer les tâches sur des processeurs. On voit que le processeur P2 est inactif pendant 3 unités de temps...

On constate que pour ce problème, 2 processeurs sont nécessaires et suffisants.
On voit que P2 est inactif pendant 3 unités de temps.

$T_{par} = 15$
$T_{seq} = 27$
$S = \frac{27}{15} = 1.8$
$\text{Efficacité} = \frac{1.8}{2} = 0.9 = 90% \text{des processeurs sont utilisés}$

Ce qui correspond au 3 secondes inactives sur les 30 secondes au total de 2 processeurs: $\frac{3}{30} = 0.1 = 1 - 0.9$

Si on voulait avoir un meilleur speedup, il faudrait repartitionner le problème en tâches différentes.
Par exemple $T_{7} \rightarrow T_{7}'\ et\ T_{7}''$


## 6.3 Équilibrage de charge

En anglais: __load balancing__

Le but est que tous les processeurs soient occupés pendant la même durée.

Le temps parallèle $T_{par}$ est le temps du processeur le plus lent.
On va donc essayer au mieux de répartir le travail de façon équilibrée à travers les processeurs.
C'est ce qu'on appelle le load balancing.

On va proposer ci-dessous des approches qui favorisent cet équilibrage...

### Métrique de déséquilibrage de charge

Soit $T_{i}$ le temps cpu du processeur $p_{i}$ mesuré entre 2 points de synchronisation (tous les processeurs doivent avoir fini leur travail pour passer le point de synchronisation...).

On définit le temps moyen $\mu = \frac{1}{p} \sum_{i=1}^{p} T_{i}$

Si tous les $T_{i}$ sont égaux, on a un équilibre parfait.
Le déséquilibre se mesurera sur la variation de ces $T_{i}$.

La déviation standard n'est pas forcément le meilleur critère....

Les exemples nous suggèrent que la déviation standard des $T_{i}$ n'est pas la meilleure valeur pour caractériser le déséquilibre.
Mieux vaut comparer le temps du processeur le plus lent à la moyenne.
$$m = max_{i} T_{i}$$
$$\Delta = m - \mu$$
$$\Delta \geq 0$$
$$\Delta = 0 \Rightarrow \text{équilibre parfait et plus}\ \Delta\ \text{ augrmente, plus le déséquilibre augmente}$$

On peut aussi le mesurer de façon relative
$$\Delta ' = \frac{\Delta}{\mu} = \frac{m}{\mu} - 1$$

Dans la littérature, il y a de nombreuses façon de mesurer le déséquilibrage de charge.

Si le déséquilibre est trop grand, on va vouloir redistribuer les données à travers les processeurs, et on souhaite que suite à ce répartitionnement, on ait:
$$m = \mu$$
mais cela n'est pas une garantie.

On verra qu'il existe des techniques de rééquilibrage qui n'assurent pas ceci.
