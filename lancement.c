#include <stdio.h>
#include <string.h>
int load_game() {
    int niveau, vies, coups, rows, cols;
    int plateau[20][20];
    char pseudo[50];      // <-- correction : tableau pour stocker un nom
    float temps;
    char filename[60];
    printf("Entrez le pseudo à charger : ");
    scanf("%s", pseudo);
    sprintf(filename, "%s.txt", pseudo);

    FILE *f = fopen(filename, "r");
    if (f == NULL){
        printf("nouvelle partie");
        return 0;
    }


    fscanf(f, "%s", pseudo);
    fscanf(f, "%d", &niveau);
    fscanf(f, "%d", &vies);
    fscanf(f, "%d", &coups);
    fscanf(f, "%f", &temps);

    fscanf(f, "%d %d", &rows, &cols);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            fscanf(f, "%d", &plateau[i][j]);

    fclose(f);
    return 0;
}
