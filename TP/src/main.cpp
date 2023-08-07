#include <iostream>
#include <fstream>
#include "memlog.h"
#include "msgassert.h"

#include "rodada.h"
#include "jogador.h"
#include "carta.h"
#include "jogadas.h"

bool le_partida(std::ifstream &input_file, rodada &rodada, int numero_jogadores)
{
// Descricao: Leitura de uma jogada completa
// entrada: input_file = arquivo de leitura, rodada =  rodada com os jogadores, numero_jogadores = numeros de jogadores participando na rodada
// saida: 1 se a rodada for valida, 0 se for inválida.
    bool rodada_valida = 1;
    int aposta_rodada = 0;
    while (numero_jogadores--)
    {
        std::string str("x"), nome;
        input_file >> nome >> str;
    
        //Leitura de nome composto: concatenacao de todas as strings que nao comecam com um char entre 1 e 9. 
        while (str[0] < '1' || str[0] > '9')
        {
            nome.append(" " + str);
            input_file >> str;
        }
        //Apos processar o nome composto, a variavel str armazena o valor da aposta.
        int aposta = std::stoi(str);

        // Procura jogador na rodada, se ele nao existir o mesmo é criado.
        jogador *player = rodada.find(nome);

        // Teste de sanidade 3: Verifica se aposta é multipla de 50 e se o jogador possui dinheiro para a aposta
        rodada_valida &= player->set_aposta(aposta);
        aposta_rodada += aposta;
        std::string carta_entrada;

        // Leitura das 5 cartas em uma mao de poker 
        for (int i = 0; i < 5; i++)
        {
            input_file >> carta_entrada;
            player->insert(carta_entrada);
        }
    }
    if (rodada_valida)
        rodada.pote += aposta_rodada;
    else
        rodada.reseta_dinheiro();
    return rodada_valida;
}

int main()
// Descricao: Parte principal do programa, função responsável por lidar com entradas e saídas, além de simular o jogo
// entrada: "entrada.txt"
// saida: "saida.txt"
{
    int qtd_rodadas, dinheiro_inicial;

    // Classe responsável por lidar com os estados dos jogadores e calcular jogadas
    rodada rodada;

    std::ifstream input_file;
    std::ofstream output_file;
    input_file.open("entrada.txt");
    output_file.open("saida.txt");
    erroAssert(input_file.is_open(),  "Arquivo de entrada inexistente");
    erroAssert(output_file.is_open(), "Erro ao abrir arquivo de saida");

    input_file >> qtd_rodadas >> dinheiro_inicial;
    rodada.dinheiro_inicial = dinheiro_inicial;

    while (qtd_rodadas--)
    {
        int numero_jogadores, pingo;
        input_file >> numero_jogadores >> pingo;


        // Teste de sanidade 1: Se algum jogador apostar mais do que ele possui, a jogada é invalidada.
        if (!le_partida(input_file, rodada, numero_jogadores))
        {
            rodada.reseta_jogadas();
            continue;
        }


        // Teste de sanidade 2: Se não for possível retirar pingo de algum jogador, a jogada é invalidada.
        if (!rodada.set_pingo(pingo))
            continue;

        // Pote = Soma das apostas (calculadas na função le_partida) + pingo * quantidade de jogadores.
        rodada.pote += pingo * rodada.length();
        // O resultado da rodada válida é armazenado saida.
        output_file << rodada.calcula_rodada();
        // "Limpa" a mão de cada jogador, além de zerar o pote.
        rodada.reseta_jogadas();
    }

    output_file << "####\n";
    output_file << rodada.estado_final();
    output_file.close();
    input_file.close();

    return 0;
}