#define MAX_SIZE_ARBORE 128
#define STRING_SIZE 512

#include <stdio.h>
#include <stdlib.h>

typedef struct masina_t{
    int id, usi;
    float pret;
    char *brand;
} masina_t;

typedef struct arbore_t{
    masina_t vector[MAX_SIZE_ARBORE];
    int dimensiune;
} arbore_t;

masina_t make_masina(){
    masina_t masina;
    masina.brand = (char *)malloc(sizeof(char)*STRING_SIZE);
    return masina;
}

arbore_t make_arbore(){
    arbore_t arbore;
    arbore.dimensiune = 0;

}

void filtrare(arbore_t *arbore, int poz){
    int poz_stanga = 2*poz+1, poz_dreapta = poz_stanga+1;
    masina_t aux;
    if(poz_stanga < arbore->dimensiune && arbore->vector[poz].pret < arbore->vector[poz_stanga].pret && arbore->vector[poz_dreapta].pret <= arbore->vector[poz_stanga].pret){
        aux = arbore->vector[poz];
        arbore->vector[poz] = arbore->vector[poz_stanga];
        arbore->vector[poz_stanga] = aux;
        filtrare(arbore, poz_stanga);
    } else if(poz_dreapta < arbore->dimensiune && arbore->vector[poz].pret < arbore->vector[poz_dreapta].pret && arbore->vector[poz_dreapta].pret >= arbore->vector[poz_stanga].pret){
        aux = arbore->vector[poz];
        arbore->vector[poz] = arbore->vector[poz_dreapta];
        arbore->vector[poz_dreapta] = aux;
        filtrare(arbore, poz_dreapta);
    }
}

void adauga(arbore_t *arbore, masina_t masina){
    arbore->vector[arbore->dimensiune++] = masina;
    filtrare(arbore, (arbore->dimensiune-2)/2);
}

void afiseaza(arbore_t arbore){
    for(int i = 0; i < arbore.dimensiune; i++)
        printf("ID %d: usi %d, pret %.2f, brand %s\n", arbore.vector[i].id, arbore.vector[i].usi, arbore.vector[i].pret, arbore.vector[i].brand);
}

int main(){
    arbore_t arbore = make_arbore();

    
    return 0;
}