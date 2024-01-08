#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
class Tetrimino {
public:
    Tetrimino();
    ~Tetrimino();

    virtual void moveLeft();
    virtual void moveRight();
    void moveDown();
    void setShape(const std::vector<sf::Vector2i>& shape);
    void rotateShape();
    bool hasReversedControls() const;

    sf::Vector2i getPosition() const;
    const std::vector<sf::Vector2i>& getShape() const;

    

protected:

    std::vector<sf::Vector2i> currentShape; //przechowuje wektor wektorów 2d z pozycja \/
    sf::Vector2i position;//Vector2i to dwuwymiarowy wektor dla 2licz blakowitych uzywany w sfml w kontekscie grafiki position przchowuje pozycje aktualnego klocka
    bool RevControl = false;
    static std::vector<sf::Vector2i> getRandomShape();
};
