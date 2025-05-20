#include "Tetris.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

//metodo construtor
Tetris::Tetris() {
    //ao invez de declarar um vetor e colocar varios {}{}{}{}, podemos ultilizas os padros definidos la na classe

    //definindo a area do jogo ( area = {{}{}{}{}{}{}{}{}{}{}}.......)
    area.resize(lines);
    //definindo colunas
    for (std::size_t i{}; i  < area.size(); ++i)
    {
        area[i].resize(coluns);
    }

    //formas das pe�as
    forms = {
                //pe�a | Id 
        {1,3,5,7}, //I   0
        {2,4,5,7}, //Z   1
        {3,5,4,6}, //S   2
        {3,5,4,7}, //T   3
        {2,3,5,7}, //L   4
        {3,5,7,6}, //j   5
        {2,3,4,5}, //O   6
    };

    newPiece = true;

    //cria a janela principal importando a classe make_shared com renderizador da biblioteca SFML no objeto window
    window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode({ 570, 720 }),
        "Pestana�s TETRIS",
        sf::Style::Titlebar | sf::Style::Close
    );
    //posicao inicial da janela (onde ela vai aparecer)
    window->setPosition(sf::Vector2i(200, 100));
    //carregando e vereficando os sprites carregados
    if (!tiles.loadFromFile("C:/Users/gabri/OneDrive/Documentos/C++Lib/source/repos/PestanaTetris/x64/Debug/resources/img/squares.png")) {
        std::cout << "Erro ao carregar a imagem!" << std::endl;
    }
    //carregando e vereficando os sprites carregados
    if (!backG.loadFromFile("C:/Users/gabri/OneDrive/Documentos/C++Lib/source/repos/PestanaTetris/x64/Debug/resources/img/background.png")) {
        std::cout << "Erro ao carregar a imagem!" << std::endl;
    }

    //instanciando o objeto sprite ultilizando o sprite do projeto
    background = std::make_shared<sf::Sprite>();
    background->setTexture(backG);
    //instanciando o objeto sprite ultilizando o sprite do projeto
    sprite = std::make_shared<sf::Sprite>();
    //carregando o sprite
    sprite->setTexture(tiles);
    //recortando o sprite De (0, 0) ate (36, 36) pixels
    

    dirx = { 0 };
    rotate = { false };
    timerCount = {0.f};
    delay = { 0.5f };
    color = { 1 };
    lockTimer = { 0.f };
    lockDelay = { 0.10f };
    onGround = false;
    
    //escolher a pe�a
    std::uint32_t number = std::rand() % shapes;
    // Loop para cada bloco da pe�a (normalmente s�o 4 blocos)
    for (std::size_t i{}; i < squares; ++i) {

        // Converte o �ndice 1D da matriz (forms[number][i]) em coordenada 2D
        // Calcula a coordenada X (coluna) usando o m�dulo
        z[i].x = forms[number][i] % 2;

        // Calcula a coordenada Y (linha) usando a divis�o inteira
        z[i].y = forms[number][i] / 2;
    }
}

//Loop de eventos
void Tetris::events() {

    //iniciando tick
    float time = clock.getElapsedTime().asSeconds();
    //reniciando tick
    clock.restart();
    //incrementando tick
    timerCount += time;

    sf::Event evn;
    while (window->pollEvent(evn)) { // Processa eventos um por um
        //verifica se a janela foi fechada
        if (evn.type == sf::Event::Closed) {
            window->close();
        }
        //comandos do jogo, leitura por teclado
        if (evn.type == sf::Event::KeyPressed) {
            if (evn.key.code == sf::Keyboard::Up) {
                rotate = true;
                std::cout << "UP";
            }
            else if (evn.key.code == sf::Keyboard::Right) {
                ++dirx;
            }
            else if (evn.key.code == sf::Keyboard::Left) {
                --dirx;
            }

        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        delay = 0.05f;
    }
}

//funcao que renderiza
void Tetris::draw() {
    window->clear(sf::Color::Black);
    window->draw(*background);
    //desenha area do jogo
    for (size_t i{}; i < lines; ++i)
    {
        for (std::size_t j{}; j < coluns; ++j) {
            if (area[i][j] != 0) {
                sprite->setTextureRect(sf::IntRect(area[i][j] * 36, 0, 36, 36));
                sprite->setPosition( j * 36, i * 36);
                window->draw(*sprite);
            }
        }
    }
    for (std::size_t i{}; i < squares; ++i) {
        sprite->setTextureRect(sf::IntRect(color * 36, 0, 36, 36));
        sprite->setPosition(z[i].x * 36, z[i].y * 36);
        window->draw(*sprite);
    }
    drawHDU();
    window->display();
}

void Tetris::drawHDU() {
    // �rea da pr�xima pe�a
    sf::RectangleShape nextBox(sf::Vector2f(144, 108)); // 4x3 quadrados de 36px
    nextBox.setOutlineColor(sf::Color::Blue);
    nextBox.setOutlineThickness(3);
    nextBox.setFillColor(sf::Color::Transparent);
    nextBox.setPosition(400, 100); // Posi��o do lado direito
    window->draw(nextBox);

    // Caixa do SCORE
    sf::RectangleShape scoreBox(sf::Vector2f(144, 36));
    scoreBox.setOutlineColor(sf::Color::Blue);
    scoreBox.setOutlineThickness(3);
    scoreBox.setFillColor(sf::Color::Transparent);
    scoreBox.setPosition(400, 220);
    window->draw(scoreBox);
    
    // Texto do SCORE
    sf::Font font;
    if (!font.loadFromFile("C:/Users/gabri/OneDrive/Documentos/C++Lib/source/repos/PestanaTetris/x64/Debug/resources/font/Montserrat-SemiBold.ttf")) return; // Voc� precisa da fonte na pasta do projeto
    
    int score = 8000;
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString(std::to_string(score)); // score � um atributo inteiro que voc� precisa criar
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(430, 222);
    window->draw(scoreText);

    // Texto "SCORE"
    sf::Text scoreLabel("SCORE", font, 16);
    scoreLabel.setFillColor(sf::Color::White);
    scoreLabel.setPosition(440, 260);
    window->draw(scoreLabel);
}

//funcao que da inicio as funcionalidades
void Tetris::run() {
    while (window->isOpen())
    {
        events();
        setRotate();
        //verifica se h� pe�a
        if (newPiece) {
            spawnPiece();
            newPiece = false;
        }
        moveToDown();
        line();
        changePosition();
        resetValues();
        draw();
    }
}

//mover as pe�as para baixo
void Tetris::moveToDown() {
    if (timerCount > delay) {
        // move para k e z
        for (std::size_t i{}; i < squares; ++i) {
            k[i] = z[i];
            ++z[i].y;
        }
        // verifica colis�o DEPOIS de simular descida
        if (maxLimit()) {
            //houve colisao
            onGround = true;
            // restaura posi��o anterior
            for (std::size_t i{}; i < squares; ++i) {
                z[i] = k[i];
            }
            //inicia timer antes da pe�a fixar
            lockTimer += timerCount;

            if (lockTimer >= lockDelay) {
                // fixa a pe�a no campo
                for (std::size_t i{}; i < squares; ++i) {
                    area[z[i].y][z[i].x] = color;
                }
            }
            //houve colisao
            //reseta as variaveis de condi�ao 
            //reseta o timer de prender a pe�a
            //gera nova pe�a
            newPiece = true; // sinaliza que precisa gerar uma nova pe�a
            onGround = false;
            lockTimer = 0.f;
        }
        //caso nao, o loop ocorre normalmente
        else {
            onGround = false;
            lockTimer = 0.f;
        }

        timerCount = 0;
    }
}

//gerar pe�a
void Tetris::spawnPiece() {
    
    
    // Verifica se a pe�a ainda n�o foi inicializada (evita reatribui��es desnecess�rias)
    if (maxLimit()) {
        //std::cout << "COLIDIU!\n";
        
        for (std::size_t i{}; i < squares; ++i)
        {
            area[k[i].y][k[i].x] = color;
        }
        //escolher cor
        color = std::rand() % shapes +1;
        //escolher a pe�a
        std::uint32_t number = std::rand()% shapes;
        // Loop para cada bloco da pe�a (normalmente s�o 4 blocos)
        for (std::size_t i{}; i < squares; ++i) {

            // Converte o �ndice 1D da matriz (forms[number][i]) em coordenada 2D
            // Calcula a coordenada X (coluna) usando o m�dulo
            z[i].x = forms[number][i] % 2;

            // Calcula a coordenada Y (linha) usando a divis�o inteira
            z[i].y = forms[number][i] / 2;
        }
    }
}

//rota�ao das pe�as 
void Tetris::setRotate() {
    //verificar se ouve rota�ao
    if (rotate) {
        //variavel que armazena o centro
        Coords coords = z[1];
        for (std::size_t i{}; i < squares; ++i) {
            //adquire nova coordenada
            int x = z[i].y - coords.y;
            int y = z[i].x - coords.x;

            //incrementa essa nova coordenada 
            // modificando as posicoes dos quadrados
            z[i].x = coords.x - x;
            z[i].y = coords.y + y;
        }

        if (maxLimit()) {
            for (std::size_t i{}; i < squares; ++i)
            {
                z[i] = k[i];
            }
        }
    }
}

//movimenta��o das pe�as pra esquerda e direita
void Tetris::changePosition() {
    //movimenta todos os quadrados
    for (std::size_t i{}; i < squares; ++i)
    {
        k[i] = z[i];
        z[i].x += dirx;
    }
    if (maxLimit()) {
        for (std::size_t i{}; i < squares; ++i)
        {
            z[i] = k[i];
        }
    }
}

//funcao de colizao
bool Tetris::maxLimit() {
    for (std::size_t i{}; i < squares; ++i)
    {
        //condicoes de colizao
        if (z[i].x < 0 ||
            z[i].x >= coluns ||
            z[i].y >= lines ||
            area[z[i].y] [z[i].x]) {
            return true;
        }
    }
    return false;
}

//fun�ao que verifica se uma linha foi peenchida
void Tetris::line() {

    std::uint32_t match = lines - 1;
    
    for (std::size_t i = match; i >= 1; --i)
    {
        std::uint32_t sum{};
        for (std::size_t j{}; j < coluns; j++) {
            if (area[i][j]) {
                ++sum;
            }
            area[match][j] = area[i][j];
        }

        if (sum < coluns) {
            --match;

        }
    }
}

//reseta valores de rota�ao e de movimenta�ao 
void Tetris::resetValues() {
    dirx = 0;
    rotate = false;
    delay = 0.3f;
}


//pahts futuros 
//
//melhorar a aletoriedade das pe�as e das cores
