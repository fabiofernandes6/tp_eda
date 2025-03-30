/**
* @file antenas.h
* @author Fábio Fernandes
* @date 30/03/2025
* @brief Declarações das funções para gerir a lista de antenas.
*/

#pragma once

// Estrutura para representar uma antena
typedef struct Antena {
    char frequencia;   // Frequência da antena
    int x, y;         // Coordenadas da antena
    struct Antena *proximo; // Apontador para a próxima antena (lista ligada)
} Antena;

// Funções para gerir antenas
Antena* criarAntena(char frequencia, int x, int y);
void inserirAntena(Antena **lista, char frequencia, int x, int y);
void removerAntena(Antena **lista, int x, int y);
void mostrarAntenas(Antena *lista);
void limparAntenas(Antena **lista);
void carregarFicheiro(Antena **lista, const char* nomeFicheiro);