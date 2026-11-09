#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

// Enregistrement des opérations dans un fichier
void enregistrement(char m) 
{
    if(m == '(' || m == ')') // Si le caractère est une parenthèse, on ne l'enregistre pas
        return;
    ofstream fichier("valeurs.in", ios::app); // On crée le fichiers'il n'existe pas et on l'ouvre en mode app pour conserver les anciennes données
    fichier << m << endl; // On y écrit les différents caractères
}
// Lecture du fichier
void lecture()
{
    ifstream fichier("valeurs.in"); // Ouverture du fichier
    if(!fichier.is_open()) // Si le fichier n'a pas été ouvert on sort de la fonction
        return;
    string m; // On crée une variable char qui va contenir chaque ligne qui sera une variable
    while(getline(fichier, m)) // On lit le fichier ligne par ligne en s'assurant que la ligne n'est pas vide
    {
        cout<<m<<" "; // On l'affiche à l'écran
    }
    fichier.close(); // Fermer le fichier par sécurité
}

// Noued qui va pointer sur les différents éléments à ajouter
struct NoeudPile
{
    char v;
    NoeudPile* suivant; // Pointeur vers le noeud suivant

    NoeudPile(char p) : v(p), suivant(nullptr) {} // Constructeur
};

// Notre pile avec une taille = 0 et le sommet qui pointe vers rien, donc la pile est vide
struct Pile
{
    NoeudPile* sommet; // Pointeur vers l"élément du sommet
    int taille;

    Pile() : sommet(nullptr), taille(0) {} // Constructeur
};

// Fonction pour empiler dans notre pile :: push
void empiler(Pile* pile, char m)
{
    NoeudPile* nouveau = new NoeudPile(m); // On crée un nouveau noeud qui contient l'élément à ajouter à la pile
    nouveau->suivant = pile->sommet; // L'élément pointe vers le prochain élément du sommet
    pile->sommet = nouveau; // Le sommet pointe alors vers ce nouveau élément
    pile->taille++; // La taille augmente de 1
    // enregistrement(m);  // On enregistre la valeur dans un fichier
}
// Fonction qui permet de défiler :: pop
char depiler(Pile* pile)
{
    // assert(pile->sommet == nullptr && "La pile est vide"); // Vérifie si la pile est vide

    NoeudPile* asupprimer = pile->sommet; // L'élément à supprimer est le sommet
    char valeur = asupprimer->v; // On sauvegarde l'élément
    pile->sommet = asupprimer->suivant; // Le sommet pointe vers le prochain élément
    delete asupprimer; // On supprime le sommet
    pile->taille--; // La taille diminue de 1
    enregistrement(valeur); // On enregistre la valeur dans un fichier
    return valeur; // On retourne la valeur 
}
// Priorité d'un opérateur : plus le nombre est grand, plus l'opérateur est prioritaire
int priorite(char op)
{
    if(op == '^') return 3;
    if(op == '*' || op == '/') return 2;
    if(op == '+' || op == '-') return 1;
    return 0; // Parenthèse ouvrante ou autre
}

int main()
{
    Pile valeurs; // On crée une pile qui va contenir les valeurs de l'expression
    string operation; // Variable de chaines de caractères qui va prendre l'entrée à l'écran de l'utilisateur
    while(true)
    {
        cout << "Veuillez entrer l'operation a effectuer : ";
        if(!(cin>>operation)) // Si la lecture échoue (fin de l'entrée), on sort
            break;
        if(operation == "exit")
            break;
        for (auto& s : operation) // On parcourt toute la chaine de caractères caractère après caractère
        {
            /*if(s == ' ') //Si c'est un espace on continue la lecture
                continue;*/
            if(s == '(') // Si le caractère est une parenthèse, on l'mempile
                empiler(&valeurs, s); //empiler()
            else if(isdigit(s) || isalpha(s)) // Si le caractère est un chiffre, une consonne ou une voyelle
            {
                // On l'affiche et on l'enregistre dans notre fichier de valeurs
                cout << s << " "; 
               enregistrement(s); 
            }
            else if (s == '+' || s == '-' || s == '*' || s == '/'|| s == '^') // Si le caractère est un signe d'opération
            {
                // La taille est vide ou l'élément qui est au sommet est une parenthèse oiuvrante
                if(valeurs.taille == 0 || valeurs.sommet->v == '(')
                    empiler(&valeurs, s); // On empile la valeur
                else
                {
                    // On dépile tant que l'opérateur au sommet est plus prioritaire,
                    // ou de même priorité (sauf pour ^ qui s'évalue de droite à gauche)
                    while(valeurs.taille > 0 && valeurs.sommet->v != '(' &&
                         (priorite(valeurs.sommet->v) > priorite(s) ||
                         (priorite(valeurs.sommet->v) == priorite(s) && s != '^'))) 
                    {
                        {
                        // On dépile la pile en l'affichant à l'écran
                        cout <<  depiler(&valeurs) << " ";
                        }
                    }
                    empiler(&valeurs, s); // Puis on empile l'opérateur courant
                }
            }
            else if (s == ')') // Le caractère est une parenthèse fermante
            {
                while(valeurs.sommet != nullptr && valeurs.sommet->v != '(') // Tant que la pile n'est pas vide et que la valeur de l'élément se trouvant au sommet n'est pas une parenthèse ouvrante
                {
                    char st = depiler(&valeurs);
                    // Dépiler toute la pile jusqu'à la parenthèse ouvrante, mais on l'aura déjà dépiler
                    if(st == '(') continue;
                    cout<< st << " ";
                }
                if(valeurs.sommet != nullptr) // On retire la parenthèse ouvrante de la pile sans l'afficher
                    depiler(&valeurs);  
            }
        } // Fin de la boucle for

        // On a parcouru toute la chaine, on va faire sur dépiler la pile pour les valeurs restantes
        while(valeurs.taille != 0) // Tant que le pile n'est pas vide
        {
            if(valeurs.sommet->v == '(' || valeurs.sommet->v == ')') // Si le sommet est l'une des parenthèses
            {
                // On la dépile et mais on ne va pas l'afficher à l'écran et on repart au début de la boucle while
                depiler(&valeurs);
                continue;
            }
            // On dépile et on affiche l'élément à l'ecran
            cout<< depiler(&valeurs) << " ";
        }
        cout<<endl;
        // On essaie d'aaficher tout ce qu'on a enregistrer dans le fichier pour voir si les opérations correspondent
        // lecture();
    }

    return 0;
}