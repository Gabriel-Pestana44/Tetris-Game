// Main.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//Ola, esse projeto sera um estudo sobre a biblioteca SFML e sobre Orientacao a Objetos basica!!!!
#include "Tetris.hpp"  
#include <SFML/Graphics.hpp>


int main()
{
    std::srand(std::time(0));
    // Criando um ponteiro inteligente do tipo shared_ptr para a classe Tetris
    // Usando shared_ptr para garantir que a memória seja liberada automaticamente
    auto tetris = std::make_shared<Tetris>();
    tetris->run();
}

// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração
