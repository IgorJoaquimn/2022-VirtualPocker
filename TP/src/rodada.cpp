// //---------------------------------------------------------------------
// // Arquivo	: rodada.cpp
// // Conteudo	: implementacao do LISTA JOGADORES
// // Autor	: Igor Joaquim da Silva Costa (igor.joaquim@dcc.ufmg.br)
// //---------------------------------------------------------------------

#include "rodada.h"
#include "jogadas.h"
#include "memlog.h"
#include "msgassert.h"

// CONSTANTES
std::function<int(jogador &jogador)> jogada[] = {&HC, &OP, &TP, &TK, &S, &F, &FH, &FK, &SF, &RSF};
std::string nome_jogada[] = {"HC", "OP", "TP", "TK", "S", "F", "FH", "FK", "SF", "RSF"};
// FIM CONSTANTES

jogador *rodada::insert(jogador *jogador)
// Descricao: insere jogador na lista.
// entrada: novo jogador a ser inserido.
// saida: ponteiro para o novo jogador.
{
    return (lista.insert(jogador));
}

jogador *rodada::find(std::string &str)
// Descricao: Procura jogador dentro da lista, se o mesmo não for encontrado, ele é criado.
// entrada: string str = nome do jogador a ser procurado.
// saida: ponteiro para o jogador procurado.
{
    jogador a(str, 0);
    jogador *b = lista.find(a);
    if (b == nullptr)
        b = lista.insert(new jogador(str, dinheiro_inicial));
    return (b);
}

int rodada::length()
// Descricao: Quantidade de jogadores presentes na lista.
// saida: quantidade de jogadores presentes na lista.
{
    return this->lista.length();
}

bool rodada::set_pingo(int pingo)
// Descricao: Retira pingo do montante de cada jogador, se possivel. Se nao for possivel, os jogadores retornam para o estado inicial.
// entrada: int pingo = valor do pingo.
// saida: TRUE se todo jogador consegue contribuir com o pingo, FALSE se não.
{
    node_t<jogador> *jogador = lista.inicio;
    int count = 0;
    while (jogador != nullptr)
    {
        if (!jogador->value->set_aposta(pingo))
        {
            reseta_dinheiro();
            return false;
        }
        jogador = jogador->next;
        count ++;
    }
    return true;
}

void rodada::calcula_ganhadores(lista_ordenada<jogador> &ganhadores, std::function<int(jogador &jogador)> jogada)
// Descricao: Funcao principal para calcular quais jogadores podem fazer certa jogada.
// entrada: ganhadores = lista onde os ganhadores são inseridos, jogada = ponteiro para a função avaliada.
{
    node_t<jogador> *jogador = lista.begin();
    int count = 0;
    while (jogador != nullptr)
    {
        // Se jogador possuir uma mao valida e essa mao for passível de se construir a jogada, o jogador é considerado ganhador.
        if (jogador->value->get_mao()->exist() && jogada(*jogador->value))
            ganhadores.insert(jogador->value);
        jogador = jogador->next;
        count ++;
    }
}

std::string rodada::calcula_rodada()
// Descricao: Funcao principal para calcular quais jogadores ganharam determinada partida, além de distribuir o valor do pote
// entre eles.
// Atenção: as funções para calcular as jogadas estão no arquivo "jogadas.cpp", a lista de jogadores possui um array
// com essas funções para auxiliar na determinação dos vencedores, chamada  "std::function<int(jogador &jogador)> jogada[10]",
// localizada como variavel global no começo desse arquivo.
// saida: string com o resultado da partida.
{
    std::string retorno;
    // Para cada uma das 10 possíveis jogadas, da maior para a menor.
    for (int i = 9; i >= 0; i--)
    {
        // Lista para armazenar os possíveis ganhadores.
        lista_ordenada<jogador> ganhadores;

        calcula_ganhadores(ganhadores, jogada[i]);

        // Se ninguem ganhou usando essa jogada, a proxima é considerada.
        if (!ganhadores.exist())
            continue;

        // Para qualquer jogada, ganham aqueles que passam do criterio de desempate (a variavel y no atributo valor_jogada)
        // Se existir mais de 1 jogador com o MAIOR critério de desempate, o pote é repartido entre eles.
        // Exemplo: no caso da ocorrência de multiplos Flushs, com a maior carta sendo a mesma entre os jogadores, o pote é 
        // repartido entre eles.
        // Criterio de desempate do jogador com a maior jogada.
        std::pair<int, int> desempate = ganhadores.end()->value->get_valor_jogada();

        int len = 0;
        // Para cada possivel ganhador, deve-se contar quais possuem o critério de desempate igual ao maior.
        for (auto it = ganhadores.end(); it != nullptr; it = it->prev)
        {
            if (it->value->get_valor_jogada() < desempate)
                break;
            len++;
        }

        // Saida = Quantidade de jogadores com maior criterio, a razão do pote pela quantidade de ganhadores e a jogada
        // correspondente.
        retorno += std::to_string(len) + " " + std::to_string(pote / len) + " " + nome_jogada[i] + "\n";
        
        int count = 0;
        // Para cada ganhador, acontece a partição do pote, além de armazenar seu nome.
        for (auto it = ganhadores.end(); it != nullptr; it = it->prev)
        {
            if (it->value->get_valor_jogada() != desempate)
                break;
            it->value->set_aposta(-pote / len);
            retorno += it->value->get_nome() + "\n";
            count++;
        }

        // Se o código executou até aqui, a jogada[i] é valida, logo, a maior jogada ja foi calculada e não há
        // necessidade de continuar, já que jogada[i-1] < jogada[i];
        break; 
    }
    return retorno;
}

void rodada::reseta_jogadas()
// Descricao: Funcao para retornar rodada ao estado vazio. Para cada jogador na lista, sua mão deve voltar ao estado inicial, além do pote ser atribuido a zero.
{
    node_t<jogador> *jogador = lista.begin();
    int count = 0;
    while (jogador != nullptr)
    {
        jogador->value->limpa_mao();
        jogador = jogador->next;
        count++;
    }
    pote = 0;
}

void rodada::reseta_dinheiro()
// Descricao: Funcao para retornar rodado ao estado anterior. Para cada jogador, seu dinheiro retorna ao ultimo estado armazenado.
{
    node_t<jogador> *jogador = lista.begin();
    while (jogador != nullptr)
    {
        jogador->value->reseta_dinheiro();
        jogador = jogador->next;
    }
}

std::string rodada::estado_final()
// Descricao: Funcao para gerar placar final do jogo, a partir do estado atual da lista.
// saida: string com placar final, ordenado primeiramente pela quantidade de dinheiro dos jogadores, e , em caso de empate, por ordem alfabetica.
{
    std::string ret;

    // Lista ordenada do par (dinheiro,nome), dessa forma, a ordenação acontece da forma esperada.
    lista_ordenada<std::pair<int, std::string>> lista_ordenada_dinheiro;
    node_t<jogador> *it = lista.begin();
    while (it != nullptr)
    {
        jogador *jogador = it->value;
        // Instanciação de um novo par_dinheiro_nome, o dinheiro é armazenado multiplicado por -1, pois a lista_ordenada ordena do menor para o maior.
        auto par_dinheiro_nome = new std::pair<int, std::string>(-jogador->get_dinheiro(), jogador->get_nome());

        lista_ordenada_dinheiro.insert(par_dinheiro_nome);

        it = it->next;
    }

    auto aux = lista_ordenada_dinheiro.begin();
    while (aux != nullptr)
    {
        // Retorno armazenado no formato ($Nome $Dinheio)
        ret += (aux->value->second) + " " + std::to_string(-aux->value->first);
        if (aux->next != nullptr)
            ret.push_back('\n');
        aux = aux->next;
    }
    return ret;
}
