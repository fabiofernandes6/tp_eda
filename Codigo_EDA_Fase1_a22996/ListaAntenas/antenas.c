/**
* @file antenas.c
* @author Fábio Fernandes
* @date 30/03/2025
* @brief Implementação das funções para gerir a lista de antenas.
*
* Este módulo permite criar, inserir, remover e exibir antenas, além de carregar
* uma lista de antenas a partir de um ficheiro.
*/

#include "antenas.h"
#include <stdio.h>
#include <stdlib.h>

/**
* @brief Cria uma nova antena e retorna um apontador para ela.
*
* @param frequencia Carácter representando a frequência da antena.
* @param x Coordenada X da antena.
* @param y Coordenada Y da antena.
* @return Apontador para a nova antena ou NULL em caso de erro.
*/
Antena* criarAntena(char frequencia, int x, int y) 
{
    Antena* nova = (Antena*)malloc(sizeof(Antena));
    if (!nova) 
    {
        printf("Erro ao alocar memória para a antena!\n");
        return NULL;
    }
    nova->frequencia = frequencia;
    nova->x = x;
    nova->y = y;
    nova->proximo = NULL;
    return nova;
}

/**
* @brief Insere uma nova antena na lista.
*
* @param lista Apontador para o apontador da lista de antenas.
* @param frequencia Carácter representando a frequência da antena.
* @param x Coordenada X da antena.
* @param y Coordenada Y da antena.
*/
void inserirAntena(Antena** lista, char frequencia, int x, int y) 
{
    Antena* nova = criarAntena(frequencia, x, y);
    if (!nova) return;
    
    // Insere no início da lista
    nova->proximo = *lista;
    *lista = nova;
}

/**
* @brief Remove uma antena com coordenadas específicas.
*
* @param lista Apontador para o apontador da lista de antenas.
* @param x Coordenada X da antena a remover.
* @param y Coordenada Y da antena a remover.
*/
void removerAntena(Antena** lista, int x, int y) 
{
    Antena *atual = *lista, *anterior = NULL;

    // Percorre a lista até encontrar a antena com as coordenadas especificadas
    while (atual != NULL && (atual->x != x || atual->y != y)) 
    {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL) return; // Se não encontrou, sai da função

    // Se a antena a remover for a primeira da lista
    if (anterior == NULL) *lista = atual->proximo;
    else anterior->proximo = atual->proximo;

    free(atual); // Liberta a memória da antena removida
}

/**
* @brief Mostra todas as antenas registadas.
*
* @param lista Apontador para a lista de antenas.
*/
void mostrarAntenas(Antena* lista) 
{
    if (!lista) 
    {
        printf("Nenhuma antena registada.\n");
        return;
    }
    
    // Percorre a lista e imprime cada antena
    while (lista) 
    {
        printf("Frequencia: %c | Coordenadas: (%d, %d)\n", lista->frequencia, lista->x, lista->y);
        lista = lista->proximo;
    }
}

/**
* @brief Liberta a memória de todas as antenas da lista.
*
* @param lista Apontador para o Apontador da lista de antenas.
*/
void limparAntenas(Antena** lista) 
{
    // Percorre a lista e liberta cada antena
    while (*lista) 
    {
        Antena* temp = *lista;
        *lista = (*lista)->proximo;
        free(temp);
    }

    *lista = NULL; // Garante que a lista fica vazia
}

/**
* @brief Carrega uma lista de antenas a partir de um ficheiro.
*
* @param lista Apontador para o Apontador da lista de antenas.
* @param nomeFicheiro Nome do ficheiro a ser lido.
*/
void carregarFicheiro(Antena** lista, const char* nomeFicheiro) 
{
    FILE* ficheiro = fopen(nomeFicheiro, "r");
    if (!ficheiro) 
    {
        printf("Erro ao abrir o ficheiro %s!\n", nomeFicheiro);
        return;
    }

    char linha[100];
    int y = 0;

    // Lê o ficheiro linha a linha
    while (fgets(linha, sizeof(linha), ficheiro)) 
    {
        // Percorre cada carácter da linha
        for (int x = 0; linha[x] != '\0' && linha[x] != '\n'; x++) 
        {
            if (linha[x] != '.') 
            {  // Assume que '.' significa "vazio"
                inserirAntena(lista, linha[x], x, y);
            }
        }
        y++; // Incrementa a coordenada Y
    }
    fclose(ficheiro);
}