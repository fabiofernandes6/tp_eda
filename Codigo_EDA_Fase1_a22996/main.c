/**
* @file main.c
* @author Fábio Fernandes
* @date 30/03/2025
* @brief Programa principal para gerir antenas e efeitos nefastos.
*/

#include <stdio.h>
#include <stdlib.h>
#include "ListaAntenas/antenas.h"
#include "EfeitosNefastos/nefastos.h"


/**
 * @brief Mostra a matriz no terminal, preenchendo-a com os efeitos nefastos ou somente com as antenas.
 * 
 * @param lista Apontador para a lista de antenas.
 * @param efeitos Apontador para a lista de efeitos nefastos.
 * @param largura Largura da matriz.
 * @param altura Altura da matriz.
 */
void mostrarMatriz(Antena* lista, EfeitoNefasto* efeitos, int largura, int altura) 
{
    // Aloca memória para a matriz (altura linhas)
    char** matriz = (char**)malloc(altura * sizeof(char*));
    for (int i = 0; i < altura; i++) 
    {
        // Para cada linha, aloca memória para armazenar a largura, colunas
        matriz[i] = (char*)malloc(largura * sizeof(char));
    }

    // Inicializa a matriz com o caracter '.' para representar áreas vazias
    for (int i = 0; i < altura; i++) 
    {
        for (int j = 0; j < largura; j++) 
        {
            matriz[i][j] = '.';
        }
    }

    // Percorre a lista de antenas e marca suas posições na matriz
    for (Antena* aux = lista; aux; aux = aux->proximo) 
    {
        // Insere a frequência da antena na posição correspondente
        // Supondo que 'x' e 'y' estão dentro dos limites da matriz
        matriz[aux->y][aux->x] = aux->frequencia;
    }

    // Chama a função que preenche a matriz com os efeitos nefastos
    preencherMatrizComEfeitos(matriz, largura, altura, efeitos);

    // Imprime a matriz na tela
    for (int i = 0; i < altura; i++) 
    {
        for (int j = 0; j < largura; j++) 
        {
            printf("%c ", matriz[i][j]); // Exibe cada elemento seguido de um espaço
        }
        printf("\n"); // Nova linha após imprimir cada linha da matriz
    }

    // Liberta a memória alocada para a matriz
    for (int i = 0; i < altura; i++) 
    {
        free(matriz[i]); // Liberta cada linha individualmente
    }
    free(matriz); // Liberta o apontador principal da matriz
}


int main() 
{
    Antena* listaAntenas = NULL;
    EfeitoNefasto* listaEfeitos = NULL;
    
    // Carregar a matriz original a partir do ficheiro
    carregarFicheiro(&listaAntenas, "estrutura.txt");
    
    // Exibir a matriz original
    printf("\nMATRIZ ORIGINAL:\n");
    mostrarMatriz(listaAntenas, listaEfeitos, 12, 12);

    // Exibir as coordenadas das antenas
    printf("\nLISTA DE ANTENAS:\n");
    mostrarAntenas(listaAntenas);

    // Deduzir e exibir os efeitos nefastos iniciais
    printf("\nLISTA DE EFEITOS NEFASTOS:\n");
    deduzirEfeitosNefastos(listaAntenas, &listaEfeitos, 12, 12);
    mostrarEfeitosNefastos(listaEfeitos);

    // Mostrar matriz com os efeitos nefastos
    printf("\nMATRIZ COM OS EFEITOS NEFASTOS:\n");
    mostrarMatriz(listaAntenas, listaEfeitos, 12, 12);

    // Inserir novas antenas, B(3, 3) e B(5, 5), e mostrar a matriz
    printf("\nMATRIZ APOS INSERIR NOVAS ANTENAS:\n");
    inserirAntena(&listaAntenas, 'B', 3, 3);
    inserirAntena(&listaAntenas, 'B', 5, 5);
    limparEfeitosNefastos(&listaEfeitos);
    mostrarMatriz(listaAntenas, listaEfeitos, 12, 12);

    //Mostrar lista de antenas após inserção, recalcular os efeitos nefastos, e mostrar a matriz com os efeitos nefastos e sem os efeitos nefastos
    printf("\nLISTA DE ANTENAS:\n");
    mostrarAntenas(listaAntenas);
    printf("\nLISTA DE EFEITOS NEFASTOS APOS INSERCAO:\n");
    deduzirEfeitosNefastos(listaAntenas, &listaEfeitos, 12, 12);
    mostrarEfeitosNefastos(listaEfeitos);
    printf("\nMATRIZ COM OS EFEITOS NEFASTOS APOS INSERCAO:\n");
    mostrarMatriz(listaAntenas, listaEfeitos, 12, 12);

    // Remover as antenas B(3, 3) e B(5, 5)
    printf("\nMATRIZ APOS REMOVER AS ANTENAS INSERIDAS:\n");
    removerAntena(&listaAntenas, 3, 3);
    removerAntena(&listaAntenas, 5, 5);
    limparEfeitosNefastos(&listaEfeitos);
    mostrarMatriz(listaAntenas, listaEfeitos, 12, 12);

    // Recalcular os efeitos nefastos após remover as antenas B(3, 3) e B(5, 5)
    printf("\nMATRIZ DE EFEITOS NEFASTOS APOS REMOVER AS ANTENAS INSERIDAS:\n");
    deduzirEfeitosNefastos(listaAntenas, &listaEfeitos, 12, 12);
    mostrarMatriz(listaAntenas, listaEfeitos, 12, 12);
    
    // Liberar memória alocada
    limparEfeitosNefastos(&listaEfeitos);
    limparAntenas(&listaAntenas);
    
    return 0;
}