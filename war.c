#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

void inicializarMapa(Territorio *mapa);
void exibirMapa(const Territorio *mapa);
void atacar(Territorio *atacante, Territorio *defensor);
int verificarMissao(const Territorio *mapa, int missao);

int main() {
    srand(time(NULL));

    Territorio *mapa = calloc(5, sizeof(Territorio));
    inicializarMapa(mapa);

    int missao = rand() % 2 + 1;

    printf("\n=== Missao Sorteada ===\n");
    if (missao == 1) printf("1) Destruir o exercito VERDE.\n");
    else printf("2) Conquistar 3 territorios.\n");

    int opcao;

    while (1) {
        printf("\n=== MENU ===\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missao\n");
        printf("0 - Sair\n");
        scanf("%d", &opcao);

        if (opcao == 0) break;

        if (opcao == 1) {
            int a, d;
            exibirMapa(mapa);
            printf("Escolha atacante (1-5): ");
            scanf("%d", &a);
            printf("Escolha defensor (1-5): ");
            scanf("%d", &d);

            atacar(&mapa[a - 1], &mapa[d - 1]);
        }

        if (opcao == 2) {
            if (verificarMissao(mapa, missao)) {
                printf("\n===== MISSAO CUMPRIDA! PARABENS! =====\n");
                break;
            } else {
                printf("\nMissao ainda NAO concluida!\n");
            }
        }
    }

    free(mapa);
    return 0;
}

void inicializarMapa(Territorio *mapa) {
    strcpy(mapa[0].nome, "Alaska");     strcpy(mapa[0].cor, "Vermelho"); mapa[0].tropas = 3;
    strcpy(mapa[1].nome, "Brasil");     strcpy(mapa[1].cor, "Verde");    mapa[1].tropas = 4;
    strcpy(mapa[2].nome, "China");      strcpy(mapa[2].cor, "Azul");     mapa[2].tropas = 5;
    strcpy(mapa[3].nome, "Egito");      strcpy(mapa[3].cor, "Verde");    mapa[3].tropas = 2;
    strcpy(mapa[4].nome, "Islandia");   strcpy(mapa[4].cor, "Vermelho"); mapa[4].tropas = 3;
}

void exibirMapa(const Territorio *mapa) {
    printf("\n===== MAPA =====\n");
    for (int i = 0; i < 5; i++) {
        printf("%d) %s | Cor: %s | Tropas: %d\n", 
               i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

void atacar(Territorio *a, Territorio *d) {
    int da = rand() % 6 + 1;
    int dd = rand() % 6 + 1;

    printf("\nDados -> Atacante: %d | Defensor: %d\n", da, dd);

    if (da >= dd) {
        d->tropas--;
        printf("Atacante venceu! Defensor perde 1 tropa.\n");
    } else {
        printf("Defensor resistiu!\n");
    }

    if (d->tropas <= 0) {
        printf("\nTerritorio conquistado!\n");
        strcpy(d->cor, a->cor);
        d->tropas = 1;
    }
}

int verificarMissao(const Territorio *mapa, int missao) {
    if (missao == 1) {
        for (int i = 0; i < 5; i++)
            if (strcmp(mapa[i].cor, "Verde") == 0)
                return 0;
        return 1;
    } else {
        int conquistados = 0;
        for (int i = 0; i < 5; i++)
            if (strcmp(mapa[i].cor, "Vermelho") == 0)
                conquistados++;
        return conquistados >= 3;
    }
}
