# Convertisseur infixe vers notation polonaise inversée (RPN)

Programme en C++ qui convertit une expression mathématique écrite en notation **infixe** (`a+b*c`) en notation **postfixe**, aussi appelée **notation polonaise inversée** ou **RPN** (`a b c * +`).

La pile utilisée pour la conversion est **implémentée à la main** avec une liste chaînée, sans passer par `std::stack`. Le projet suit l'algorithme *Shunting-yard* de Dijkstra.

## Fonctionnalités

- Conversion d'expressions infixes en notation postfixe
- Opérateurs supportés : `+`, `-`, `*`, `/`, `^`
- Gestion des parenthèses, y compris imbriquées
- Respect des priorités et de l'associativité des opérateurs
- Pile codée avec des noeuds chaînés (`empiler`, `depiler`) et allocation dynamique
- Journalisation des caractères traités dans un fichier `valeurs.in`

## Priorité et associativité des opérateurs

| Opérateur | Priorité | Associativité     |
|-----------|----------|-------------------|
| `^`       | 3        | De droite à gauche |
| `*`, `/`  | 2        | De gauche à droite |
| `+`, `-`  | 1        | De gauche à droite |

Exemples :
- `a-b-c` devient `a b - c -` (de gauche à droite)
- `a^b^c` devient `a b c ^ ^` (de droite à gauche)

## Compilation et exécution

Un compilateur C++ (g++, clang++ ou MSVC) est requis.

```bash
g++ -Wall -Wextra -o rpn rpn.cpp
./rpn
```

Sous Windows :

```bash
g++ -Wall -Wextra -o rpn.exe rpn.cpp
rpn.exe
```

## Utilisation

Entrez une expression **sans espaces**, puis appuyez sur Entrée. Le programme affiche l'expression en notation postfixe. Tapez `exit` pour quitter.

```
Veuillez entrer l'operation a effectuer : a+b*c
a b c * +
Veuillez entrer l'operation a effectuer : (a+b)*c
a b + c *
Veuillez entrer l'operation a effectuer : a^b^c
a b c ^ ^
Veuillez entrer l'operation a effectuer : ((a+b)*(c-d))/e
a b + c d - * e /
Veuillez entrer l'operation a effectuer : exit
```

## Fonctionnement

L'expression est lue caractère par caractère :

1. **Opérande** (lettre ou chiffre) : affiché directement.
2. **Parenthèse ouvrante `(`** : empilée.
3. **Opérateur** : on dépile et on affiche les opérateurs du sommet qui ont une priorité plus élevée (ou égale, sauf pour `^`), puis on empile l'opérateur courant.
4. **Parenthèse fermante `)`** : on dépile et on affiche jusqu'à la parenthèse ouvrante, qui est retirée sans être affichée.
5. **Fin de l'expression** : on dépile et on affiche tous les opérateurs restants.

## Structure du code

| Élément            | Rôle                                                                 |
|--------------------|----------------------------------------------------------------------|
| `NoeudPile`        | Noeud de la liste chaînée (valeur et pointeur vers le noeud suivant) |
| `Pile`             | Pile avec un pointeur vers le sommet et une taille                   |
| `empiler()`        | Ajoute un élément au sommet de la pile                               |
| `depiler()`        | Retire et retourne l'élément du sommet, puis libère le noeud         |
| `priorite()`       | Retourne la priorité d'un opérateur                                  |
| `enregistrement()` | Ajoute un caractère traité au fichier `valeurs.in`                   |
| `lecture()`        | Affiche le contenu de `valeurs.in` (utile pour le débogage)          |

## Limites connues

- L'expression doit être saisie **sans espaces** (la lecture se fait avec `cin >>`).
- Chaque **opérande ne contient qu'un seul caractère** : `12+3` est traité comme `1`, `2` et `3`.
- Aucune validation de l'expression (par exemple `a++b` ou des parenthèses mal appariées).
- Le fichier `valeurs.in` grossit à chaque exécution, car il est ouvert en mode ajout.

## Pistes d'amélioration

- Utiliser un *tokenizer* pour supporter les nombres à plusieurs chiffres et les variables à plusieurs lettres
- Accepter les espaces dans l'expression
- Valider l'expression et signaler les erreurs de syntaxe
- Évaluer le résultat de l'expression postfixe

## Auteur

Jonathan Balezi, étudiant au baccalauréat en informatique appliquée (régime coop) à l'Université de Moncton.

- Portfolio : https://jigo29.github.io/portfolio/
- GitHub : https://github.com/JiGo29
- LinkedIn : https://www.linkedin.com/in/balezi-jonathan-a991a6386/
