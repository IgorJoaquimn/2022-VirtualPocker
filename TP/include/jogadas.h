#ifndef JOGADAS
#define JOGADAS

#include "memlog.h"
#include "jogador.h"
#include "carta.h"

// Descrição: Funções para computar jogadas de um jogador, com base nas regras do jogo de poker.

int RSF(jogador &jogador);

int SF(jogador &jogador);

int FK(jogador &jogador);

int FH(jogador &jogador);

int F(jogador &jogador);

int S(jogador &jogador);

int TK(jogador &jogador);

int TP(jogador &jogador);

int OP(jogador &jogador);

int HC(jogador &jogador);

#endif
