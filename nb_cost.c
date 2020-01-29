#include <stdio.h>
#include <stdlib.h>
int main()
{
	int taille_chemin;
	int nb_chemin;
	int nb_ants;
	int somme;
	int i;

	i = 0;
	somme = 0;
	printf("Combien de chemins ? :\n");
	scanf("%d", &nb_chemin);
	printf("Combien de fourmis ? :\n");
	scanf("%d", &nb_ants);
	printf("%d chemins, %d fourmis\n", nb_chemin, nb_ants);
	while (i < nb_chemin)
	{
		printf("Taille chemins [%d] ? :\n", i);
		
		scanf("%d", &taille_chemin);
		somme += ((nb_ants / nb_chemin) + taille_chemin);
		i++;
	}
	somme = somme / nb_chemin;
	printf("Nombre de coups = %d\n", somme);
	return (1);
}
