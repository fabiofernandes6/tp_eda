/**
* @file nefastos.h
* @author Fábio Fernandes
* @date 30/03/2025
* @brief Declarações das funções para gerir efeitos nefastos causados por antenas.
*/

#pragma once

#include "../ListaAntenas/antenas.h"

// Estrutura para representar um ponto com efeito nefasto
typedef struct EfeitoNefasto {
    int x, y;                      // Coordenadas do efeito nefasto
    struct EfeitoNefasto *proximo;  // Apontador para o próximo efeito nefasto
} EfeitoNefasto;

// Funções para gerir efeitos nefastos
void deduzirEfeitosNefastos(Antena* lista, EfeitoNefasto** efeitos, int largura, int altura);
void mostrarEfeitosNefastos(EfeitoNefasto *lista);
void preencherMatrizComEfeitos(char** matriz, int largura, int altura, EfeitoNefasto* efeitos);
void limparEfeitosNefastos(EfeitoNefasto **lista);