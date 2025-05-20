// Main.cpp : Este arquivo cont�m a fun��o 'main'. A execu��o do programa come�a e termina ali.
//Ola, esse projeto sera um estudo sobre a biblioteca SFML e sobre Orientacao a Objetos basica!!!!
#include "Tetris.hpp"  
#include <SFML/Graphics.hpp>


int main()
{
    std::srand(std::time(0));
    // Criando um ponteiro inteligente do tipo shared_ptr para a classe Tetris
    // Usando shared_ptr para garantir que a mem�ria seja liberada automaticamente
    auto tetris = std::make_shared<Tetris>();
    tetris->run();
}

// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depura��o
// Depurar programa: F5 ou menu Depurar > Iniciar Depura��o
