#include <stdio.h>
#define WIDTH 20
#define HEIGHT 10

/* Initialisation du monde */
void initialize_world(int world[HEIGHT][WIDTH])
{
    int i;
    int j;

    /* Toutes les cellules sont mortes au départ */
    for (i = 0; i < HEIGHT; i++)
    {
        for (j = 0; j < WIDTH; j++)
        {
            world[i][j] = 0;
        }
    }

    /* Structure stable : bloc */
    world[1][1] = 1;
    world[1][2] = 1;
    world[2][1] = 1;
    world[2][2] = 1;

    /* Oscillateur : clignotant */
    world[4][5] = 1;
    world[4][6] = 1;
    world[4][7] = 1;

    /* Vaisseau : planeur */
    world[7][12] = 1;
    world[8][13] = 1;
    world[9][11] = 1;
    world[9][12] = 1;
    world[9][13] = 1;
}

/* Affichage du monde */
void display_world(int world[HEIGHT][WIDTH])
{
    int i;
    int j;

    for (i = 0; i < HEIGHT; i++)
    {
        for (j = 0; j < WIDTH; j++)
        {
            if (cellule(world, i, j))
            {
                printf("X ");
            }
            else
            {
                printf(". ");
            }
        }

        printf("\n");
    }
}

/* Retourne l'état actuel : chiffre des unités */
int cell_cur_state(int world[HEIGHT][WIDTH], int i, int j)
{
    return world[i][j] % 10;
}

/* Retourne l'état futur : chiffre des dizaines */
int cell_next_state(int world[HEIGHT][WIDTH], int i, int j)
{
    return world[i][j] / 10;
}

/* Calcule l'état futur d'une cellule */
void cell_compute_next_state(int world[HEIGHT][WIDTH], int i, int j)
{
    int di;
    int dj;
    int ni;
    int nj;
    int neighbors;
    int current;
    int next;

    neighbors = 0;

    /* Parcourir les huit voisines */
    for (di = -1; di <= 1; di++)
    {
        for (dj = -1; dj <= 1; dj++)
        {
            /* Ignorer la cellule étudiée */
            if (di == 0 && dj == 0)
            {
                continue;
            }

            ni = i + di;
            nj = j + dj;

            /* Vérifier que la voisine appartient au monde */
            if (ni >= 0 && ni < HEIGHT &&
                nj >= 0 && nj < WIDTH)
            {
                neighbors += cell_cur_state(world, ni, nj);
            }
        }
    }

    current = cell_cur_state(world, i, j);

    /* Appliquer les règles du jeu de la vie */
    if (current == 1)
    {
        if (neighbors == 2 || neighbors == 3)
        {
            next = 1;
        }
        else
        {
            next = 0;
        }
    }
    else
    {
        if (neighbors == 3)
        {
            next = 1;
        }
        else
        {
            next = 0;
        }
    }

    /* Stocker l'état actuel et l'état futur */
    world[i][j] = current + 10 * next;
}

/* Phase 1 : calculer les états futurs */
void compute_generation(int world[HEIGHT][WIDTH])
{
    int i;
    int j;

    for (i = 0; i < HEIGHT; i++)
    {
        for (j = 0; j < WIDTH; j++)
        {
            cell_compute_next_state(world, i, j);
        }
    }
}

/* Phase 2 : appliquer les états futurs */
void apply_generation(int world[HEIGHT][WIDTH])
{
    int i;
    int j;

    for (i = 0; i < HEIGHT; i++)
    {
        for (j = 0; j < WIDTH; j++)
        {
            world[i][j] = cell_next_state(world, i, j);
        }
    }
}

/* Faire évoluer le monde d'une génération */
void next_generation(int world[HEIGHT][WIDTH])
{
    compute_generation(world);
    apply_generation(world);
}

/* Programme principal */
int main(void)
{
    int world[HEIGHT][WIDTH] = {0};
    int generation;
    int total_generations;

    initialize_world(world);

    printf("=== Jeu de la vie ===\n");
    printf("Generation initiale :\n\n");

    display_world(world);

    printf("\nNombre de generations a calculer : ");
    if (scanf("%d", &total_generations) != 1 ||
        total_generations < 0)
    {
        printf("Nombre de generations invalide.\n");
        return 1;
    }

    for (generation = 1;
         generation <= total_generations;
         generation++)
    {
        next_generation(world);

        printf("\nGeneration %d :\n\n", generation);
        display_world(world);
    }

    return 0;
}