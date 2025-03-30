/**
* @file nefastos.c
* @author Fábio Fernandes
* @date 30/03/2025
* @brief Implementação das funções para detetar, exibir e limpar efeitos nefastos causados por antenas.
*
* O código analisa uma lista de antenas e determina os pontos onde ocorre o efeito nefasto
* com base nas condições especificadas: acontece quando duas antenas da mesma frequência
* estão alinhadas e uma está exatamente o dobro da distância da outra.
*/

#include <stdio.h>
#include <stdlib.h>
#include "nefastos.h"
 
/**
* @brief Deduz e regista os efeitos nefastos causados pelas antenas.
**
* @param lista Apontador para a lista de antenas.
* @param efeitos Apontador para a lista onde serão armazenados os efeitos nefastos.
* @param largura Largura do espaço disponível (matriz).
* @param altura Altura do espaço disponível (matriz).
*/
void deduzirEfeitosNefastos(Antena* lista, EfeitoNefasto** efeitos, int largura, int altura) 
{
    // Percorrer todas as antenas existentes
    for (Antena* a1 = lista; a1 != NULL; a1 = a1->proximo) 
    {       
        for (Antena* a2 = a1->proximo; a2 != NULL; a2 = a2->proximo) 
        {  
            // Só interessa se forem da mesma frequência
            if (a1->frequencia == a2->frequencia) 
            {
                // Determina o deslocamento entre as duas antenas
                int dx = a2->x - a1->x;
                int dy = a2->y - a1->y;
 
                // Calcula as posições onde surgem os efeitos nefastos
                int ex1_x = a1->x - dx;
                int ex1_y = a1->y - dy;
                int ex2_x = a2->x + dx;
                int ex2_y = a2->y + dy;
 
                // Se o primeiro ponto calculado estiver dentro dos limites, adiciona à lista
                if (ex1_x >= 0 && ex1_x < largura && ex1_y >= 0 && ex1_y < altura) 
                {
                    EfeitoNefasto* novo1 = (EfeitoNefasto*)malloc(sizeof(EfeitoNefasto));
                    if (!novo1) 
                    {
                        printf("Erro ao alocar memória para efeito nefasto!\n");
                        return;
                    }
                    novo1->x = ex1_x;
                    novo1->y = ex1_y;
                    novo1->proximo = *efeitos;
                    *efeitos = novo1; 
                }
 
                // Se o segundo ponto calculado estiver dentro dos limites, adiciona à lista
                if (ex2_x >= 0 && ex2_x < largura && ex2_y >= 0 && ex2_y < altura) 
                {
                    EfeitoNefasto* novo2 = (EfeitoNefasto*)malloc(sizeof(EfeitoNefasto));
                    if (!novo2) 
                    {
                        printf("Erro ao alocar memória para efeito nefasto!\n");
                        return;
                    }
                    novo2->x = ex2_x;
                    novo2->y = ex2_y;
                    novo2->proximo = *efeitos;
                    *efeitos = novo2;
                }
            }
        }
    }
}
 
/**
* @brief Mostra no terminal todos os efeitos nefastos detetados.
*
* @param lista Apontador para a lista de efeitos nefastos.
*/
void mostrarEfeitosNefastos(EfeitoNefasto* lista) 
{
    if (!lista) 
    {
        printf("Nenhum efeito nefasto detetado.\n");
        return;
    }
 
    // Percorre a lista e imprime cada efeito encontrado
    while (lista) 
    {
        printf("Efeito Nefasto em: (%d, %d)\n", lista->x, lista->y);
        lista = lista->proximo;
    }
}
 
/**
* @brief Adiciona os efeitos nefastos à matriz, marcando-os com '#'.
*
* @param matriz Matriz que representa o espaço.
* @param largura Largura da matriz.
* @param altura Altura da matriz.
* @param efeitos Apontador para a lista de efeitos nefastos.
*/
void preencherMatrizComEfeitos(char** matriz, int largura, int altura, EfeitoNefasto* efeitos) 
{
    // Percorre a lista de efeitos e marca-os na matriz
    for (EfeitoNefasto* aux = efeitos; aux; aux = aux->proximo) 
    {
        if (aux->x >= 0 && aux->x < largura && aux->y >= 0 && aux->y < altura) 
        {
            if (matriz[aux->y][aux->x] == '.') 
            {  // Apenas marca como '#' se a posição ainda não tiver sido ocupada
                matriz[aux->y][aux->x] = '#';
            }
        }
    }
}
 
/**
* @brief Liberta a memória associada à lista de efeitos nefastos.
*
* @param lista Apontador para o apontador da lista de efeitos nefastos.
*/
void limparEfeitosNefastos(EfeitoNefasto** lista) 
{
    // Percorre a lista e liberta cada nó
    while (*lista) 
    {
        EfeitoNefasto* temp = *lista;
        *lista = (*lista)->proximo;
        free(temp);
    }
    *lista = NULL; // Garante que a lista fica vazia
}