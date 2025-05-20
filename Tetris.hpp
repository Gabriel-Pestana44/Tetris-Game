//evitar que o cabe�alho se repita
#pragma once

//decla�ao das bibliotecas ultilizadas
#include <SFML/Graphics.hpp>
#include <memory>

//criar classes do jogo
class Tetris {

	//defini�oes estaticas para as: Linhas, Colunas, quantidade de Quadrados, e quantidade das Formas
	//ultilizando o UINT32_T para evitar conver�oes implicitase permite controle total do tamanhho da variavel
	//evitando disperdicio e lixo de memoria
	static const std::uint32_t lines   { 20 };
	static const std::uint32_t coluns  { 10 };
	static const std::uint32_t squares { 4 };
	static const std::uint32_t shapes  { 7 };

	//vetores Bidimencionais
	//std::vector<std::vector<std::uint32_t>> equivale a:____uint32_t area [][]____

	//Area do jogo
	std::vector<std::vector<std::uint32_t>> area;
	//Formas
	std::vector<std::vector<std::uint32_t>> forms;

	struct Coords {
		//cordenada das pe�as
		std::uint32_t x, y;

	};//Z = pe�a atual K = temporario
	Coords z[squares], k[squares];

	//Tela (area aonde sera renderizada)
	std::shared_ptr < sf::RenderWindow>window;
	//Textura que esta na memoria a ser alocada
	sf::Texture tiles, backG;
	//Sprite que receber� a  futura Textura 
	std::shared_ptr < sf::Sprite> sprite,background;
	//tick(time) do jogo
	sf::Clock clock;

	//movimenta�ao para esquerda e direita e cores
	int dirx,
		color;
	//verifica�ao se a pe�a ja foi girada
	bool rotate;
	//verificar se h� ou nao uma pe�a
	bool newPiece,
		onGround;
	//ticks
	float timerCount, 
		  delay,
		  lockTimer,
		  lockDelay;

//proteger as funcoes de eventos
protected:
	void events();
	void draw();
	void drawHDU();
	void moveToDown();
	void spawnPiece();
	void setRotate();
	void resetValues();
	void changePosition();
	void line();
	bool maxLimit();
//deixar fun�oes operantes publicas
public:
	Tetris();
	void run();
};





