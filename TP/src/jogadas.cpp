#include "jogadas.h"

// Lista com as jogadas sendo seu respectivo valor no jogo, da menor para a maior.
enum jogades {hc,op,tp,tk,s,f,fh,fk,sf,rsf};

int RSF(jogador &jogador)
// Descrição: Jogada Royal Straight Flush - São 5 cartas seguidas do mesmo naipe do 10 até ao Ás;
{
    // Para ser 5 do mesmo naipe, deve ser necessariamente um FLUSH.
    if (F(jogador))
    {
        lista_ordenada<carta> *mao = jogador.get_mao();

        // Para ser RSF, a primeira carta deve ser 1 e a ultima 13.
        if (mao->begin()->value->get_numero() == 1 && mao->end()->value->get_numero() == 13)
        {
            node_t<carta> *it = mao->begin()->next;
            int count = 10;
            // Enquanto existe uma sequencia do 10 ao 13, o contador cont é incrementado, se não existir a jogada não pode ser executada.
            while (it != nullptr)
            {
                if (count == it->value->get_numero())
                    count++;
                else
                    return 0;
                it = it->next;
            }
            
            jogador.set_valor_jogada(rsf, 0);
            return 1;
        }
        else
            return 0;
    }
    else
        return 0;
}

int SF(jogador &jogador)
// Descrição: Jogada Straight Flush [SF] - São 5 cartas seguidas do mesmo naipe que não seja do 10 até ao Ás;
{
    // Para ser um SF, deve ser necessariamente um FLUSH
    if (F(jogador))
    {
        lista_ordenada<carta> * mao = jogador.get_mao();

        //Primeiro numero da sequencia.
        int count = mao->begin()->value->get_numero();
        node_t<carta> * it = mao->begin();

        // Enquanto existe uma sequencia do inicio ao fim, o contador cont é incrementado, se não existir a jogada não pode ser executada.
        while (it != nullptr)
        {
            if (count == it->value->get_numero())
                count++;
            else
                return 0;
            it = it->next;
        }
        jogador.set_valor_jogada(sf, 0);
        return 1;
    }
    else
        return 0;
}

int FK(jogador &jogador)
// Descrição: Jogada Four of a kind [FK] - São 4 cartas iguais, e em caso de empate ganha o jogador com a Quadra mais alta;
{
    lista_ordenada<carta> *mao = jogador.get_mao();
    node_t<carta> * it = mao->begin();
    // Para cada numero possivel, o contador começa em 0.
    int pares[13] = {0};

    // Para cada numero na mao, o contador é incrementado.
    while (it != nullptr)
    {
        carta *carta_atual = it->value;
        pares[carta_atual->get_numero() - 1]++;
        it = it->next;
    }

    // Para cada numero possivel, se existir um contado 4 vezes, a jogada é uma quadra.
    for (int i = 0; i < 13; i++)
        if (pares[i] == 4)
        {
            // Criterio de desempate: valor da quadra.
            jogador.set_valor_jogada(fk, i + 1);
            return 1;
        }
    return 0;
}

int FH(jogador &jogador)
// Descrição: Jogada Full House [FH] - Uma tripla e um par. Em caso de empate ganha o jogador com a trinca
// mais alta, caso permaneça o empate ganha aquele que possuir o maior par;
{
    lista_ordenada<carta> *mao = jogador.get_mao();
    node_t<carta> * it = mao->begin();
    // Para cada numero possivel, o contador começa em 0.
    int pares[13] = {0};

    // Para cada numero na mao, o contador é incrementado.
    while (it != nullptr)
    {
        auto *carta_atual = it->value;
        pares[carta_atual->get_numero() - 1]++;
        it = it->next;
    }

    // Para cada numero possivel, verifica a existência de uma tripla e uma dupla.
    for (int i = 0; i < 13; i++)
        if (pares[i] == 3)
        {
            for (int j = 0; j < 13; j++)
                if (pares[j] == 2)
                {
                    // Criterio de desempate: composição da tripla e da quadra, a tripla é multiplicada por 100 
                    // para garantir que ela é o critério de desempate predominante.
                    jogador.set_valor_jogada(fh, (i + 1) * 100 + (j +1));
                    return 1;
                }
        }
    return 0;
}

int F(jogador &jogador)
// Descrição: Flush [F] - São 5 cartas do mesmo naipe sem serem seguidas. Caso dois jogadores
// possuam Flush ganha aquele que possuir a carta mais alta;
{
    lista_ordenada<carta> * mao = jogador.get_mao();
    carta * carta_inicial = mao->begin()->value;
    
    node_t<carta> * it = mao->begin();
    
    // Enquanto a carta atual tiver o mesmo naipe da inicial, o programa continua, ao encontrar alguma 
    //diferença, conclui-se que a jogada não pode ser executada.
    while (it != nullptr)
    {
        carta *carta_atual = it->value;
        if (carta_atual->get_naipe() != carta_inicial->get_naipe())
        {
            return 0;
        }
        it = it->next;
    }
    // Criterio de desempate: maior carta.
    jogador.set_valor_jogada(f, mao->end()->value->get_numero());
    return 1;
}

int S(jogador &jogador)
// Descrição: Jogada Straight [S] - São 5 cartas seguidas sem importar o naipe. Em caso de empate ganha
// aquele que possuir a carta mais alta;
{
    lista_ordenada<carta> * mao = jogador.get_mao();
    
    node_t<carta> * it = mao->begin();
    int count = it->value->get_numero();

    // Enquanto encontrar sequencia, a jogada é valida, ao encontrar algum numero fora da sequencia, ela é invalidada.
    while (it != nullptr)
    {
        if (count == it->value->get_numero())
            count++;
        else
            return 0;
        it = it->next;
    }
    jogador.set_valor_jogada(s, count);
    return 1;
}

int TK(jogador &jogador)
// Descrição: Jogada Three of a kind [TK]: São 3 cartas iguais mais duas cartas diferentes, em caso de empate
// ganha aquele com a maior tripla.
{
    lista_ordenada<carta> * mao = jogador.get_mao();
    node_t<carta> * it = mao->begin();
    // Para cada numero possivel, o contador começa em 0.
    int pares[13] = {0};

    // Para cada numero na mao o contador respectivo é incrementado.
    while (it != nullptr)
    {
        auto *carta_atual = it->value;
        pares[carta_atual->get_numero() - 1]++;
        it = it->next;
    }

    // Para cada numero possivel, procura aquele que ocorreu 3 vezes;
    for (int i = 0; i < 13; i++)
        if (pares[i] == 3)
        {
            // Criterio de desempate: maior carta de tripla.
            jogador.set_valor_jogada(tk, (i + 1) * 100 + mao->end()->value->get_numero());
            return 1;
        }
    return 0;
}

int TP(jogador &jogador)
// Descrição: Jogada Two Pairs [TP]: São 2 pares de cartas. Em caso de empate ganha aquele que possuir o
// maior par maior, caso permaneça o empate ganha aquele que possuir o maior par menor, caso
// permaneça o empate ganha aquele que possuir a carta mais alta;
{
    lista_ordenada<carta> * mao = jogador.get_mao();
    node_t<carta> * it = mao->begin();
    // Para cada numero possivel, o contador começa em 0.
    int pares[13] = {0};

    // Para cada numero na mao, o contador é incrementado.
    while (it != nullptr)
    {
        auto *carta_atual = it->value;
        pares[carta_atual->get_numero() - 1]++;
        it = it->next;
    }
    
    // Procura-se o numero que não participa de uma par.
    int distinto = -1;
    for (int i = 0; i < 13; i++)
        if (pares[i] == 1)
            distinto = i + 1;


    // Para cada numero possivel, procura-se os 2 pares
    for (int i = 0; i < 13; i++)
        if (pares[i] == 2)
        {
            for (int j = i + 1; j < 13; j++)
                if (pares[j] == 2)
                {
                    // Criterio de desempate: Quadra maior = J, já que i < j sempre, Quadra menor = i e 
                    // numero não participante = distinto
                    // Os valores estão multiplicados por potências de 100 para garantir a ordem de importância.
                    jogador.set_valor_jogada(tp, (j + 1) * 10000 + (i + 1) * 100 + distinto);
                    return 1;
                }
        }
    return 0;
}

int OP(jogador &jogador)
// Descrição: Jogada One Pair [OP]: São 2 cartas iguais e três diferentes. Em caso de empate ganha aquele
// que possuir o maior par, caso permaneça o empate ganha aquele que possuir a carta mais alta;
{
    lista_ordenada<carta> * mao = jogador.get_mao();
    node_t<carta> * it = mao->begin();
    // Para cada numero possivel, o contador começa em 0.
    int pares[13];
    for (int i = 0; i < 13; i++)
        pares[i] = 0;

    // Para cada numero na mao o contador respectivo é incrementado.
    while (it != nullptr)
    {
        carta *carta_atual = it->value;
        pares[carta_atual->get_numero() - 1]++;
        it = it->next;
    }

    // Para cada numero possivel, procura-se o par.
    for (int i = 0; i < 13; i++)
        if (pares[i] == 2)
        {
            // Criterio de desempate: (1) Maior quadra (2) maior numero 
            // Se 2 jogadores tiveram a mesma quadra, onde o maior numero pertence a quadra, ambos ganham
            // (comportamento não especificado nas regras do jogo).
            jogador.set_valor_jogada(op, (i + 1) * 100 + mao->end()->value->get_numero());
            return 1;
        }
    return 0;
}

int HC(jogador &jogador)
// Descrição: Jogada Higher Card - maior carta do jogador.
{
    jogador.set_valor_jogada(hc, jogador.get_mao()->end()->value->get_numero());
    return 1;
}