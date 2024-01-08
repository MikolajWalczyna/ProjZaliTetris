// GameWindow.cpp
#include "GameWindow.h"

void GameWindow::drawBoard(sf::RenderWindow& window, const Board& board, const Tetrimino& currentTetrimino, const Tetrimino& tempTetrimino) {
    // Pobierz dwuwymiarowy wektor reprezentuj�cy plansz�
    const std::vector<std::vector<int>>& grid = board.getGrid();

    // Rozmiary kafelka (kom�rki) na planszy
    const float tileSize = 30.0f;

    // Ustaw grubo�� i kolor linii granicznych
    const float borderThickness = 2.0f;
    const sf::Color borderColor = sf::Color::Black;
    // Kolor dla pierwszych 3 rz�d�w
    const sf::Color grayColor = sf::Color(120, 120, 120);  // Jasno szary

    // P�tle do iteracji przez kafelki planszy i ich rysowania
    for (size_t i = 0; i < grid.size(); ++i) {
        //size_t jest wieksze niz int (64 bity) i nie ma znaku
        for (size_t j = 0; j < grid[i].size(); ++j) {
            // Okre�l kolor w zale�no�ci od warto�ci kom�rki (0 - pusta, inna - zaj�ta)
            sf::Color tileColor = (grid[i][j] == 0) ? sf::Color::White : sf::Color::Blue;
            // Je�li jeste�my w pierwszych 3 rz�dach, zmie� kolor na jasno szary
            if (i < 3) {
                tileColor = grayColor;
            }

            // Stw�rz prostok�t reprezentuj�cy kafelek
            sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize)); //rysuje prostokat reprezentujacy kafelek
            tile.setPosition(static_cast<float>(j) * tileSize, static_cast<float>(i) * tileSize); //ustawia jego pozycje 
            //konwertuje j/i na floata bo setPosition tego oczekuje 
            
                        // Sprawd�, czy obecny klocek to RevControlTetrimino i dostosuj kolor rzutuj i jak nie ma b��dy to zmien kolor
            if (dynamic_cast<const RevControlTetrimino*>(&currentTetrimino) != nullptr) {
                tileColor = dynamic_cast<const RevControlTetrimino*>(&currentTetrimino)->getColor();
            }
            tile.setFillColor(tileColor); //ustawia kolor

            // Rysuj granice kafelka
            tile.setOutlineThickness(borderThickness);
            tile.setOutlineColor(borderColor);

            // Narysuj kafelek na oknie
            window.draw(tile);
        }
    }

    // Rysuj tymczasowy klocek
    drawTetrimino(window, tempTetrimino, tileSize, borderThickness, borderColor, sf::Color::Red);

    // Rysuj aktualny klocek
    drawTetrimino(window, currentTetrimino, tileSize, borderThickness, borderColor, sf::Color::Green);
}

void GameWindow::drawTetrimino(sf::RenderWindow& window, const Tetrimino& tetrimino, float tileSize, float borderThickness, const sf::Color& borderColor, const sf::Color& fillColor) {
    const std::vector<sf::Vector2i>& shape = tetrimino.getShape();

    for (const auto& block : shape) {//iterujemy po blokach w klocku i je rysujemy
        sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
        tile.setPosition(static_cast<float>(tetrimino.getPosition().x + block.x) * tileSize, static_cast<float>(tetrimino.getPosition().y + block.y) * tileSize);
        tile.setFillColor(fillColor);

        // Rysuj granice kafelka
        tile.setOutlineThickness(borderThickness);
        tile.setOutlineColor(borderColor);

        window.draw(tile);
    }
}
