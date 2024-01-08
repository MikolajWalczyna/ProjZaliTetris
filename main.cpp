#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "GameWindow.h"
#include <iostream>
#include "TetriminoFactory.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(300, 600), "Tetris");// Tworzenie okna o rozmiarze 300x600 pikseli z tytu�em "Tetris"
    GameWindow gameWindow;  // Utw�rz obiekt obs�uguj�cy interfejs graficzny
    sf::Clock clock;// Utworzenie obiektu zegara, kt�ry b�dzie u�ywany do �ledzenia czasu
    sf::Time elapsedTime;// Zmienna przechowuj�ca up�ywaj�cy czas od ostatniej aktualizacji
    Board board; 
    TetriminoFactory tetriminoFactory; // Utw�rz obiekt fabryki klock�w

    Tetrimino* tetro = tetriminoFactory.createTetrimino();
    Tetrimino* nextTetro = tetriminoFactory.createTetrimino();
    bool leftKeyPressed = false;//Zmienna, kt�ra �ledzi stan klawisza strza�ki w lewo. 
    bool rightKeyPressed = false;
    bool downKeyPressed = false;
    bool upKeyPressed = false;
    while (window.isOpen()) {//Ta p�tla dzia�a dop�ki okno (reprezentowane przez obiekt window) jest otwarte. 
        sf::Event event;// Tworzenie obiektu zdarzenia SFML
        while (window.pollEvent(event)) { // P�tla obs�ugi zdarze� SFML, sprawdzaj�ca i pobieraj�ca wszystkie zdarzenia zwi�zane z oknem
            if (event.type == sf::Event::Closed) {
                window.close();
                board.~Board();
                delete tetro;
                delete nextTetro;
                return 0;
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left && !leftKeyPressed) {
                    leftKeyPressed = true;
                    if (board.moveTetriminoLeft(*tetro)) {//funkcja probuje rusza klockiem i zwraca czy ruch zostal wykonany czy byl niemozliwy
                        std::cout << "Left";
                    }
                    else {
                        std::cout << "Left illegal";
                    }
                }
                else if (event.key.code == sf::Keyboard::Right && !rightKeyPressed) {
                    rightKeyPressed = true;
                    if (board.moveTetriminoRight(*tetro)) {
                        std::cout << "Right";
                    }
                    else {
                        std::cout << "Right illegal";
                    }
                }
                else if (event.key.code == sf::Keyboard::Down && !downKeyPressed) {
                    downKeyPressed = true;
                    if (board.moveTetriminoDown(*tetro)) {
                        std::cout << "Down";
                        if (board.checkLossCondition()) {//sprawdza czy klocek znajduje sie powyzej max wysokosci
                            board.~Board();
                            delete tetro;
                            delete nextTetro;
                            return 0;
                        }
                    }
                    else {
                        std::cout << "Down illegal";
                        tetro = nextTetro; //podmienia klocek na nastepny
                        nextTetro = tetriminoFactory.createTetrimino(); // tworzy nastepny klocek
                        std::cout << "placed";
                        if (board.checkLossCondition()) {
                            board.~Board();
                            delete tetro;
                            delete nextTetro;
                            std::exit(0);
                        }
                    }
                }
                else if (event.key.code == sf::Keyboard::Up && !upKeyPressed) {
                    upKeyPressed = true;
                    board.rotateTetrimino(*tetro);
                }
            }
            else if (event.type == sf::Event::KeyReleased) {
                // Warunek sprawdzaj�cy, czy zdarzenie to zwolnienie klawisza klawiatury
                    // Nast�pnie sprawdzane s� konkretne kody zwolnionych klawiszy
                if (event.key.code == sf::Keyboard::Left) {
                    leftKeyPressed = false;
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    rightKeyPressed = false;
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    downKeyPressed = false;
                }
                else if (event.key.code == sf::Keyboard::Up) {
                    upKeyPressed = false;
                }
            }
        }
// Odliczanie czasu
        elapsedTime += clock.restart(); //clock.restart() to metoda zegara (sf::Clock), kt�ra zwraca up�ywaj�cy czas od ostatniego zresetowania zegara, a nast�pnie resetuje go
        if (elapsedTime >= sf::seconds(0.3)) {
            std::cout << "0.3s";
            if (board.moveTetriminoDown(*tetro)) {
                std::cout << "TimedDown";
                if (board.checkLossCondition()) {
                    board.~Board();
                    delete tetro;
                    delete nextTetro;
                    return 0;
                }
            }
            else {
                std::cout << "TimeDown illegal";
                tetro = nextTetro;
                nextTetro = tetriminoFactory.createTetrimino();
                std::cout << "placed";
                if (board.checkLossCondition()) {
                    board.~Board();
                    delete tetro;
                    delete nextTetro;
                    return 0;
                }
            }
            elapsedTime = sf::Time::Zero;//zeruje zegar zeby znowu odliczac do 0.3s
        }
        // Ruch klocka w d� co pewien czas
        window.clear(); // czysci okno przed nowa klatka
        gameWindow.drawBoard(window, board,*tetro,*nextTetro);//rysuje plansze i klocki
        window.display();//aktualizuje okno zeby wyswietlic narysowana klatke
    }

    return 0;
}


