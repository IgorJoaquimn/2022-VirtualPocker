#ifndef RODADA
#define RODADA

#include <iostream>
#include <functional>
#include "lista_ordenada.h"
#include "jogador.h"
#include "carta.h"
#include "memlog.h"


class rodada
// Descrição: TAD para representar uma lista de jogadores, em alguma rodada em específico.
{  
    private:
        lista_ordenada<jogador> lista;
    
    public:
        int dinheiro_inicial = 0;
        int pote = 0;

        //Funções para manipulação de jogadores.
        void calcula_ganhadores(lista_ordenada<jogador> &ganhadores,std::function<int(jogador &jogador)> jogada);
        std::string calcula_rodada();
        bool set_pingo  (int pingo);

        // Funções para gerir a lista de jogadores.
        jogador * insert(jogador * jogador);
        jogador * find  (std::string &str);
        int length();

        std::string estado_final();
        void reseta_jogadas();
        void reseta_dinheiro();
};
#endif
