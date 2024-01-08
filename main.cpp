#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "GameWindow.h"
#include <iostream>
#include "TetriminoFactory.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(300, 600), "Tetris");// Tworzenie okna o rozmiarze 300x600 pikseli z tytu³em "Tetris"
    GameWindow gameWindow;  // Utwórz obiekt obs³uguj¹cy interfejs graficzny
    sf::Clock clock;// Utworzenie obiektu zegara, który bêdzie u¿ywany do œledzenia czasu
    sf::Time elapsedTime;// Zmienna przechowuj¹ca up³ywaj¹cy czas od ostatniej aktualizacji
    Board board; 
    TetriminoFactory tetriminoFactory; // Utwórz obiekt fabryki klocków

    Tetrimino* tetro = tetriminoFactory.createTetrimino();
    Tetrimino* nextTetro = tetriminoFactory.createTetrimino();
    bool leftKeyPressed = false;//Zmienna, która œledzi stan klawisza strza³ki w lewo. 
    bool rightKeyPressed = false;
    bool downKeyPressed = false;
    bool upKeyPressed = false;
    while (window.isOpen()) {//Ta pêtla dzia³a dopóki okno (reprezentowane przez obiekt window) jest otwarte. 
        sf::Event event;// Tworzenie obiektu zdarzenia SFML
        while (window.pollEvent(event)) { // Pêtla obs³ugi zdarzeñ SFML, sprawdzaj¹ca i pobieraj¹ca wszystkie zdarzenia zwi¹zane z oknem
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
                // Warunek sprawdzaj¹cy, czy zdarzenie to zwolnienie klawisza klawiatury
                    // Nastêpnie sprawdzane s¹ konkretne kody zwolnionych klawiszy
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
        elapsedTime += clock.restart(); //clock.restart() to metoda zegara (sf::Clock), która zwraca up³ywaj¹cy czas od ostatniego zresetowania zegara, a nastêpnie resetuje go
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
        // Ruch klocka w dó³ co pewien czas
        window.clear(); // czysci okno przed nowa klatka
        gameWindow.drawBoard(window, board,*tetro,*nextTetro);//rysuje plansze i klocki
        window.display();//aktualizuje okno zeby wyswietlic narysowana klatke
    }

    return 0;
}


