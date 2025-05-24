#define STRING_SIZE 512
#define SEPARATOR_FISIER ","

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct masina_t{
    int id, usi;
    float pret;
    char *brand;
} masina_t;

typedef struct nod_t{
    masina_t *masina;
    struct nod_t *copil_stanga, *copil_dreapta;
} nod_t;

masina_t *aloca_masina(){
    masina_t *masina = (masina_t *)malloc(sizeof(masina_t));
    masina->brand = (char *)malloc(sizeof(char)*STRING_SIZE);
    return masina;
}

void dezaloca_masina(masina_t *masina){
    free(masina->brand);
    free(masina);
}

nod_t *adauga_r(nod_t *nod, nod_t **adresa_din_parinte, masina_t *masina){
    if(!nod){
        nod = (nod_t*)malloc(sizeof(nod_t));
        nod->masina = masina;
        nod->copil_dreapta = NULL;
        nod->copil_stanga = NULL;
        if(adresa_din_parinte)
            *adresa_din_parinte = nod;
        return nod;
    }else{
        if(nod->masina->id > masina->id){
            return adauga_r((nod_t *)(nod->copil_stanga), &(nod->copil_stanga), masina);
        }else{
            return adauga_r((nod_t *)(nod->copil_dreapta), &(nod->copil_dreapta), masina);
        }
    }
    
}

void adauga(nod_t **radacina, masina_t *masina){
    if(*radacina)
        adauga_r(*radacina, NULL, masina);
    else
        *radacina = adauga_r(*radacina, NULL, masina);
}

void dezaloca_arbore(nod_t *nod){
    if(!nod)
        return;
    dezaloca_arbore((nod_t *)(nod->copil_stanga));
    dezaloca_arbore((nod_t *)(nod->copil_dreapta));
    dezaloca_masina(nod->masina);
    free(nod);
}

void afiseaza_r(nod_t *nod){
    if(!nod)
        return;
    afiseaza_r((nod_t *)(nod->copil_stanga));
    printf("ID %d: usi %d, pret %.2f, brand %s\n", nod->masina->id, nod->masina->usi, nod->masina->pret, nod->masina->brand);
    afiseaza_r((nod_t *)(nod->copil_dreapta));
}

masina_t *citeste_masina(char *line){
    masina_t *masina = aloca_masina();
    int newline_end_pos;
    masina->id = atoi(strtok(line, SEPARATOR_FISIER));
    masina->usi = atoi(strtok(NULL, SEPARATOR_FISIER));
    masina->pret = atof(strtok(NULL, SEPARATOR_FISIER));
    strcpy(masina->brand, strtok(NULL, SEPARATOR_FISIER));
    newline_end_pos = strlen(masina->brand)-1;
    if(masina->brand[newline_end_pos] == '\n')
        masina->brand[newline_end_pos] = 0;
    return masina;
}

nod_t *citeste_graf(const char* path){
    FILE *file = fopen(path, "r");
    char *line = (char*)malloc(sizeof(char)*STRING_SIZE);
    nod_t *radacina = NULL;
    line = fgets(line, sizeof(char)*STRING_SIZE, file);
    while(line){
        adauga(&radacina, citeste_masina(line));
        line = fgets(line, sizeof(char)*STRING_SIZE, file);
    }
    free(line);
    return radacina;
}

int main(){
    nod_t *radacina = NULL;
    masina_t *masina1 = aloca_masina();
    strcpy(masina1->brand, "BMW");
    masina1->id = 5;
    masina1->pret = 5000;
    masina1->usi = 10; 
    adauga(&radacina, masina1);
    masina_t *masina2 = aloca_masina();
    strcpy(masina2->brand, "Renault");
    masina2->id = 56;
    masina2->pret = 4321;
    masina2->usi = 130; 
    adauga(&radacina, masina2);
    masina_t *masina3 = aloca_masina();
    strcpy(masina3->brand, "Dacia");
    masina3->id = 51231;
    masina3->pret = 556436;
    masina3->usi = 13210; 
    adauga(&radacina, masina3);
    masina_t *masina4 = aloca_masina();
    strcpy(masina4->brand, "Porsche");
    masina4->id = 50;
    masina4->pret = 9;
    masina4->usi = 0; 
    adauga(&radacina, masina4);
    afiseaza_r(radacina);
    dezaloca_arbore(radacina);
    radacina = citeste_graf("masini.txt");
    printf("\n");
    afiseaza_r(radacina);
    dezaloca_arbore(radacina);
    return 0;
}