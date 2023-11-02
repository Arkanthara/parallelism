## 2.5 Architectures hybrides

Mémoire partagée combinée avec mémoire distribuée
(Multicoeurs interconnectés entre eux...)
On peut aussi voir des GPU comme noeud de calcul.
On peut alors combiner MPI et openMP (ou C++17)

#### GPU
C'est un modèle mixte entre SIMD et MIMD. On a une collection de processeurs SIMD, chacun pouvant exécuter un autre code, de façon asynchrone.
Les processeurs SIMD sont à mémoire partagée.

## 2.6 Architecture vectorielle

Actuellement, les processeurs modernes ont des unités dites vectorielles qui permettent de traîter quelques éléments d'un vecteur en même temps.
(Pour nous, c'est plutôt une approche SIMD...)
Nous on parlerait plutôt d'unités SIMD avec un faible degré de parallélisme.

Du point de vue historique, les architectures vectorielles se distinguent par:
- Registres vectoriels
- Exécution en pipeline
- Unités d'exécution multiples
(C'était pour les supers ordinateurs des années 1980 à 2000)

#### Registre vectoriel
On peut accéder en même temps à plusieurs données en mémoire et les avoir dans le CPU dans des registres vectoriels. (Soucis: vitesse de chargement de la mémoire vers le cpu...)
Dans les machines haut de gamme, ces registres avaient des tailles de 128, 256 ou 512 mots.

Exemple du gain dû à ces registres:
$T_{seq} = NT_{fetch} + NT_{cpu} + NT_{store}$ avec N le nombre de données et $T_{fetch}$ le temspde lecture mémoire
$T_{vector} = T_{fetch} + NT_{cpu} + T_{store}$
Gain:
$$\frac{T_{seq}}{T_{vector}} = \frac{NT_{fetch} + \dots +}{T_{fetch} + \dots + } ~= \frac{N(T_fetch + T_cpu + T_store)}{NT_cpu} ~= T_fetch + T_store/T_cpu \Rightarrow >> 1$$ T_fetch >> T_cpu

#### Exécution en pipeline
Toutes les unités de calcul sont divisées en q étages
$T_{seq} = Nq\tau$
$T_{vector} = q\tau + (N - 1)\tau$ ($q\tau$ : première donnée... $(N - 1) \tau$: données suivantes)
Si $N$ est grand, on a un speedup de $q$.

#### Parallélisme grâce à plusieurs unités de calcul
(voir figure polycopié)


## 2.7 Architecture Data-Flow

Habituellement, les ordinateurs sont "control-driven" ou "instructions-driven".
On peut aussi avoir un modèle "Data-driven".

On a une donnée a, une donnée b. Une fois qu'elles sont disponibles, on active une opération.
La disponibilité des opérandes active l'exécution de l'instruction qui les combine.

##### Variante: Demand-driven
?c = a + b
On va aller chercher les instructions a et b pour les exécuter
C'est le besoin du résultat (c en l'occurence) qui déclenche le calcul des opérandes.

L'intérêt du data-flow est que le parallélisme présent dans les calculs est automatiquement exploité.

## 2.8 Parallélisme interne

On parle aussi de ILP: instruction level parallelism
Dans les processeurs modernes, il y a plusieurs instructions qui sont exécutées en même temps.
Cela prend plusieurs formes:
- Pipeline d'exécution:
fetch (prend l'instruction en mémoire) -> decode -> execute -> write-bach (résultat dans les registres)

Avec ce pipeline, plusieurs instructions sont traitées en même temps, bien qu'à des stades différents.
On dit alors que le CPI = 1 (Cycle Per Instruction)
