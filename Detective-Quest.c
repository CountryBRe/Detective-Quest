#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ================================
   SISTEMA DE CORES (ANSI)
================================ */
#define VERDE "\033[1;32m"
#define VERMELHO "\033[1;31m"
#define AMARELO "\033[1;33m"
#define AZUL "\033[1;34m"
#define RESET "\033[0m"

/* ================================
   STRUCT DA SALA (MAPA)
================================ */
typedef struct Sala {
    char nome[50];
    char pista[100];
    struct Sala *esq;
    struct Sala *dir;
} Sala;

/* ================================
   STRUCT BST DE PISTAS
================================ */
typedef struct PistaNode {
    char pista[100];
    struct PistaNode *esq;
    struct PistaNode *dir;
} PistaNode;

/* ================================
   STRUCT DA TABELA HASH
================================ */
typedef struct HashNode {
    char pista[100];
    char suspeito[50];
    struct HashNode *prox;
} HashNode;

/* ================================
   FUNÇÕES DO MAPA
================================ */
Sala* criarSala(char nome[], char pista[]) {
    Sala *nova = malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);
    nova->esq = NULL;
    nova->dir = NULL;
    return nova;
}

/* ================================
   FUNÇÕES DA BST
================================ */
void inserirPista(PistaNode **raiz, char pista[]) {
    if (*raiz == NULL) {
        *raiz = malloc(sizeof(PistaNode));
        strcpy((*raiz)->pista, pista);
        (*raiz)->esq = (*raiz)->dir = NULL;
    } else {
        if (strcmp(pista, (*raiz)->pista) < 0)
            inserirPista(&(*raiz)->esq, pista);
        else if (strcmp(pista, (*raiz)->pista) > 0)
            inserirPista(&(*raiz)->dir, pista);
    }
}

void mostrarPistas(PistaNode *raiz) {
    if (raiz) {
        mostrarPistas(raiz->esq);
        printf(AMARELO "🕵️  %s\n" RESET, raiz->pista);
        mostrarPistas(raiz->dir);
    }
}

/* ================================
   FUNÇÕES DA HASH
================================ */
int gerarHash(char *pista) {
    int soma = 0;
    for (int i = 0; pista[i]; i++)
        soma += pista[i];
    return soma % 10;
}

void inserirHash(HashNode *tabela[], char pista[], char suspeito[]) {
    int id = gerarHash(pista);
    HashNode *novo = malloc(sizeof(HashNode));

    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->prox = tabela[id];
    tabela[id] = novo;
}

char* buscarSuspeito(HashNode *tabela[], char pista[]) {
    int id = gerarHash(pista);
    HashNode *aux = tabela[id];

    while (aux) {
        if (strcmp(aux->pista, pista) == 0)
            return aux->suspeito;
        aux = aux->prox;
    }
    return "Desconhecido";
}

/* ================================
   EXPLORAÇÃO
================================ */
void explorar(Sala *atual, PistaNode **pistas, HashNode *hash[]) {
    char escolha;

    while (atual) {
        printf(AZUL "\n📍 Você entrou em: %s\n" RESET, atual->nome);

        if (strlen(atual->pista) > 0) {
            printf(VERDE "🔎 Você encontrou uma pista: %s\n" RESET, atual->pista);
            inserirPista(pistas, atual->pista);
        } else {
            printf(AMARELO "Nada suspeito aqui...\n" RESET);
        }

        printf("\nPara onde você quer ir?\n");
        printf("e = esquerda | d = direita | s = sair\n");
        printf("Escolha: ");
        scanf(" %c", &escolha);

        if (escolha == 'e' && atual->esq)
            atual = atual->esq;
        else if (escolha == 'd' && atual->dir)
            atual = atual->dir;
        else if (escolha == 's') {
            printf(AZUL "\nVocê decidiu encerrar a exploração.\n" RESET);
            break;
        } else {
            printf(VERMELHO "Caminho inválido! Tente de novo.\n" RESET);
        }
    }
}

/* ================================
   MAIN
================================ */
int main() {
    printf(AZUL "🏰 Bem-vindo ao Detective Quest!\n" RESET);
    printf("Explore a mansão e descubra quem é o culpado...\n");

    /* MAPA */
    Sala *hall = criarSala("Hall de Entrada", "");
    Sala *sala = criarSala("Sala de Estar", "Pegadas perto da janela");
    Sala *cozinha = criarSala("Cozinha", "Faca suja encontrada");
    Sala *jardim = criarSala("Jardim", "Luvas abandonadas");
    Sala *quarto = criarSala("Quarto", "Bilhete rasgado");

    hall->esq = sala;
    hall->dir = cozinha;
    sala->esq = quarto;
    cozinha->dir = jardim;

    /* HASH */
    HashNode *tabela[10] = {NULL};

    inserirHash(tabela, "Pegadas perto da janela", "Sr. Wilson");
    inserirHash(tabela, "Faca suja encontrada", "Mordomo");
    inserirHash(tabela, "Luvas abandonadas", "Mordomo");
    inserirHash(tabela, "Bilhete rasgado", "Inquilino");

    PistaNode *pistas = NULL;

    /* EXPLORAÇÃO */
    explorar(hall, &pistas, tabela);

    /* EXIBIR PISTAS */
    printf(AZUL "\n📋 Pistas coletadas:\n" RESET);
    mostrarPistas(pistas);

    /* ACUSAÇÃO */
    char nome[50];
    printf("\nAgora é hora da acusação!\n");
    printf("Quem você acha que é o culpado? ");
    scanf(" %[^\n]", nome);

    int cont = 0;
    PistaNode *temp = pistas;

    while (temp) {
        if (strcmp(buscarSuspeito(tabela, temp->pista), nome) == 0)
            cont++;
        temp = temp->dir;
    }

    if (cont >= 2)
        printf(VERDE "\n✅ Acusação correta! %s é o culpado!\n" RESET, nome);
    else
        printf(VERMELHO "\n❌ Provas insuficientes... %s não pôde ser condenado.\n" RESET, nome);

    printf(AZUL "\nObrigado por jogar Detective Quest!\n" RESET);
    return 0;

}
