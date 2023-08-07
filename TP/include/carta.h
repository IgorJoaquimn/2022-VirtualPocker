#ifndef CARTA
#define CARTA

#include <stdio.h>
#include <string>
#include "memlog.h"

class carta
// Descrição: TAD para representar uma carta com um numero e um naipe.
{
private:
    int numero;
    char naipe;

public:
    // Construtor.
    carta(std::string &str);

    // Funções de acesso
    int get_numero();
    char get_naipe();

    // Operadores
    bool operator==(const carta &outra) const;
    bool operator< (const carta &outra) const;
    friend class jogador;
};
#endif
