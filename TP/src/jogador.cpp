// //---------------------------------------------------------------------
// // Arquivo	: matriz.cpp
// // Conteudo	: implementacao do TAD MATRIZ
// // Autor	: Igor Joaquim da Silva Costa (igor.joaquim@dcc.ufmg.br)
// //---------------------------------------------------------------------

#include <iostream>
#include "jogador.h"
#include "memlog.h"
#include "msgassert.h"

jogador::jogador(std::string &nome, int quantidade_inicial)
// Descricao: Construtor da classe jogador. Todo jogador comeca com o valor de jogada nulo (-1,-1).
// entrada: string nome = nome do jogador, int quantidade_inicial = dinheiro no inicio do jogo.
{
    erroAssert(nome.length(), "Nome nulo");
    this->nome = nome;
    this->dinheiro = quantidade_inicial;
    this->dinheiro_inicio_aposta = quantidade_inicial;
    this->valor_jogada = std::make_pair(-1, -1);
}

jogador::~jogador()
// Descricao: Destrutor do TAD jogador. Todas as cartas na mão devem ser deletadas.
{
    this->limpa_mao();
}

carta *jogador::insert(std::string &str)
// Descricao: Insere carta na lista/mao do jogador.
// entrada: string str = carta em formato de string.
// saida: ponteiro para a carta criada.
{
    return (mao.insert(new carta(str)));
}

void jogador::limpa_mao()
// Descricao: Apaga todos os elementos presentes na mão do jogador, se a mesma possuir algum.
{
    
    dinheiro_inicio_aposta = dinheiro;
    if (!mao.exist())
        return;

    auto aux1 = mao.begin();
    auto aux2 = aux1;
    while (aux1 != nullptr)
    {
        aux2 = aux1;
        aux1 = aux1->next;
        delete aux2;
    }

    //Retornando a mão ao estado inicial.
    mao.inicio = nullptr;
    mao.fim = nullptr;
    valor_jogada = std::make_pair(-1, -1);
}

std::string &jogador::get_nome()
// Descricao: acesso ao nome privado do jogador.
// saida: nome do jogador.
{
    return nome;
}

int jogador::get_dinheiro()
// Descricao: acesso ao dinheiro privado do jogador.
// saida: dinheiro do jogador.
{
    return dinheiro;
}

void jogador::reseta_dinheiro()
// Descricao: atribui ao montante atual, o ultimo montante armazenado, antes de alguma atualização.
{
    dinheiro = dinheiro_inicio_aposta;
}

lista_ordenada<carta> *jogador::get_mao()
// Descricao: acesso a mão privada do jogador.
// saida: mão do jogador.
{
    return &mao;
}

std::pair<int, int> jogador::set_valor_jogada(int x, int y)
// Descricao: Atribuição de uma nova jogada ao jogador.
// Entrada: x = valor da jogada, y = criterio de desempate.
// saida: valor da jogada.
{
    valor_jogada = std::make_pair(x, y);
    return valor_jogada;
}

std::pair<int, int> jogador::get_valor_jogada()
// Descricao: acesso ao valor_jogada privado do jogador.
// saida: valor da jogada.
{
    return valor_jogada;
}

bool jogador::set_aposta(int x)
// Descricao: Retira pingo do montante do jogador, se possivel.
// entrada: int x = valor da aposta.
// saida: TRUE se todo jogador consegue contribuir com a aposta, FALSE se não.
{
    dinheiro_inicio_aposta = dinheiro;
    if(x % 50) return false;
    if(x == 0) return false;

    if (dinheiro < x)
        return false;
    else
        dinheiro -= x;
    
    return true;
}

// OPERADORES
bool operator<(const jogador &a, const jogador &b)
// True se o par (jogada,desempate) do jogador 1 for menor do que o do jogador 2.
{
    if(a.valor_jogada == b.valor_jogada) return (a.nome > b.nome);
    return (a.valor_jogada < b.valor_jogada);
}

bool operator==(const jogador &a, const jogador &b)
// True se os 2 jogadores tiverem o mesmo NOME.X
{
    return (a.nome == b.nome);
}
