#ifndef LISTA_ORDENADA
#define LISTA_ORDENADA

#include "memlog.h"

template <class T> class node_t
// Descricao: TAD Template para um nó da lista duplamente encadeada.
{
    public:
        node_t *next = nullptr;
        node_t *prev = nullptr;
        T * value = nullptr;
        node_t(T *&value) : value(value) {} 
};

template <class T> class lista_ordenada
// Descricao: TAD Template para uma lista duplamente encadeada.
// Para utilizar esse TAD, a classe T deve possuir os comparadores de igualdade e menor que.
{
    public:
        // Cabeça e rabo da lista.
        node_t<T> *inicio = nullptr;
        node_t<T> *fim   = nullptr;

        // Funcoes para manipulacao da lista.
        T *insert(T *value);
        T *find  (T value);
        bool exist();
        int length();

        // Funcoes para iterar sobre a lista.
        typedef node_t<T>* iterator;

        iterator begin()    { return inicio; }
        iterator end()      { return fim; }

        // Destrutor
        ~lista_ordenada();
};

//Implementaçao foi colocada junto do cabeçalho devido a problemas de compatibilidade dos templates do c++ com múltliplos arquivos. 
template <class T>
T *lista_ordenada<T>::insert(T *value)
// Descricao: Insere elemento na lista de forma ordenada, havendo possibilidade de repetições.
// entrada: T value = valor do tipo T com suporte a comparação.
// saida: ponteiro para o elemento criado.
{
    node_t<T> * node = new node_t<T>(value);

    // Caso base 
    if(inicio == nullptr)
    {
        inicio  = node;
        fim     = node;
        return value;
    }

    // Se houver mais de um elemento na lista, a mesma é percorrida até encontrar um valor menor do que aquele que está sendo inserido.
    node_t<T> * aux = inicio;
    int count = 0;
    while(aux != nullptr)
    {
        if( *(node->value) < *(aux->value))
        {   
            node->next = aux;
            node_t<T> * anterior = aux->prev;
            aux->prev = node;

            if(anterior != nullptr)
            {
                anterior->next = node;
                node->prev = anterior;
            }
            else
                inicio = node;

            return value;
        }
        if(aux->next == nullptr) break;
        aux = aux->next;
        count++;
    }
    
    // Se nao existe nenhum elemento menor do que aquele sendo inserido, o mesmo é adicionado ao final da lista.
    node->prev = fim;
    fim->next = node;
    fim = node;
    return value;
}

template <class T>
T *lista_ordenada<T>::find(T value)
// Descricao: Procura elemento dentro da lista, se o mesmo não for encontrado, retorna nullptr.
// entrada: T value = valor do tipo T com suporte a comparação.
// saida: ponteiro para o elemento procurado, se ele nao for encontrado, nullptr.
{
    node_t<T> * aux = inicio;
    int count = 0;
    while(aux != nullptr)
    {
        if(*aux->value == value) return aux->value;
        aux = aux->next;
        count++;
    }
    return nullptr;
}

template <class T>
bool lista_ordenada<T>::exist()
// Descricao: Verifica se existe algum elemento na lista.
// saida: true se existir ao menos 1, 0 se não.
{
    return (inicio != nullptr);
}

template <class T>
int lista_ordenada<T>::length()
// Descricao: Funcao para calcular quantos elementos existem na lista =.
// saida: tamanho da lista.
{
    int cont = 0;
    node_t<T> * aux = inicio;
    while(aux != nullptr)
    {
        cont ++;
        aux = aux->next;
    }
    return cont;
}

template <class T>
lista_ordenada<T>::~lista_ordenada()
// Destrutor do TAD lista_ordenada. Cada elemento armazenado na lista deve ser deletado, para evitar desperdício de memória.
{
    node_t<T> * aux1 = inicio;
    node_t<T> * aux2 = aux1;
    while(aux1 != nullptr)
    {
        aux2 = aux1;
        aux1 = aux1->next;
        delete (aux2);
    }
}
#endif
