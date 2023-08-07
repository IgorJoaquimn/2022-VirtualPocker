// //---------------------------------------------------------------------
// // Arquivo	: matriz.cpp
// // Conteudo	: implementacao do TAD MATRIZ
// // Autor	: Igor Joaquim da Silva Costa (igor.joaquim@dcc.ufmg.br)
// //---------------------------------------------------------------------

#include <iostream>
#include "carta.h"
#include "memlog.h"
#include "msgassert.h"

carta::carta(std::string &str)
// Descrição: A partir de uma carta no formato ($Numero&Naipe), gera uma nova carta.
// entrada: string str: string no formato especificado.
{
    erroAssert(str.length(), "String nula");

    // O ultimo elemento da string é sempre o Naipe, logo, tudo antes da ultima posição é o numero.
    int numero = std::stoi(str.substr(0, str.length() - 1));
    char naipe = str[str.length() - 1];

    this->numero = numero;
    this->naipe = naipe;
}

int carta::get_numero()
// Descrição: acesso ao numero;
// saida: numero da carta.
{
    return this->numero;
}

char carta::get_naipe()
// Descrição: acesso ao naipe;
// saida: naipe da carta.
{
    return this->naipe;
}

bool carta::operator==(const carta &outra) const
// True se as 2 carta tiverem o mesmo NUMERO.
{
    return (this->numero == outra.numero);
}

bool carta::operator<(const carta &outra) const
// True se o numero da carta 1 for menor do que o numero da carta 2.
{
    return (this->numero < outra.numero);
}
