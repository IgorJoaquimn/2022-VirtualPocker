#ifndef JOGADOR
#define JOGADOR

#include <iostream>
#include "memlog.h"
#include "carta.h"
#include "lista_ordenada.h"

class jogador
// Descrição: Cabeçalho para o TAD jogador. Todo jogador tem um nome, uma quantia de dinheiro e um conjunto de cartas
{
    private:
        // Variaveis para representar jogador.
        std::string nome;
        int  dinheiro, dinheiro_inicio_aposta;
        std::pair<int, int> valor_jogada;
        lista_ordenada<carta> mao;

    public:
        // Construtor
        jogador(std::string &nome, int quantidade_inicial);
        // Destrutor
        ~jogador();

        // Funções de acesso
        lista_ordenada<carta> *get_mao();
        std::string &get_nome();
        int get_dinheiro();

        std::pair<int, int> set_valor_jogada(int x, int y);
        std::pair<int, int> get_valor_jogada();
        bool set_aposta(int x);

        //Funções para manipulação do jogador no contexto de alguma rodada.
        carta *insert(std::string &str);
        void reseta_dinheiro();
        void limpa_mao();

        // Operadores.
        friend bool operator<(const jogador &a, const jogador &b);
        friend bool operator==(const jogador &a, const jogador &b);
};
#endif
