#include "Tetrimino.h"
#include "TetriminoTypes.h"
#include <vector>
#include <functional>

Tetrimino::Tetrimino() {
    position = sf::Vector2i(5, 0); // Pocz¹tkowa pozycja klocka
    currentShape = getRandomShape(); //wybiera losowy ksztalt ze wczeœniej zdefiniowanych
}
Tetrimino::~Tetrimino() {
    currentShape.clear();
}

std::vector<sf::Vector2i> Tetrimino::getRandomShape() {//losuje kszta³t
    std::vector<std::vector<sf::Vector2i>> shapes = {
        /*Tworzy wektor wektorów shapes, gdzie ka¿dy wektor reprezentuje jeden z siedmiu dostêpnych kszta³tów klocków Tetrimino.
        Ka¿dy kszta³t jest zdefiniowany za pomoc¹ zestawu punktów (sf::Vector2i), które reprezentuj¹ wspó³rzêdne danego klocka w danym kszta³ci*/
        //Vector2i to dwuwymiarowy wektor dla 2licz blakowitych uzywany w sfml w kontekscie grafiki position przchowuje pozycje aktualnego klocka

        {{0, 0}, {1, 0}, {2, 0}, {3, 0}},  // IBlock
        {{0, 0}, {1, 0}, {1, 1}, {1, 2}},  // JBlock
        {{0, 0}, {1, 0}, {2, 0}, {2, 1}},  // LBlock
        {{0, 0}, {0, 1}, {1, 0}, {1, 1}},  // OBlock
        {{1, 0}, {2, 0}, {0, 1}, {1, 1}},  // SBlock
        {{0, 1}, {1, 0}, {1, 1}, {2, 1}},  // TBlock
        {{0, 1}, {1, 1}, {1, 0}, {2, 0}}   // ZBlock
    };

    int randomIndex = rand() % shapes.size(); //Wybiera losowo jeden z kszta³tów z wektora shapes przez losowanie indexu
    return shapes[randomIndex];
}


void Tetrimino::moveLeft() {
    //Vector2i to dwuwymiarowy wektor dla 2licz blakowitych uzywany w sfml w kontekscie grafiki position przchowuje pozycje aktualnego klocka
        position.x -= 1;
}

void Tetrimino::moveRight() {

    position.x += 1;

}

void Tetrimino::moveDown(){
        position.y += 1;
    }

const std::vector<sf::Vector2i>& Tetrimino::getShape() const {//zwraca ref do wektora current shape przechowujacej aktualny ksztalt, unikamy kopiowania i modyfikacji obiektu
    return currentShape;
}

sf::Vector2i Tetrimino::getPosition() const { //zwraca kopie position
    return position;
}


void Tetrimino::rotateShape() {
    // Kopiujemy aktualny kszta³t do tymczasowego kontenera
    std::vector<sf::Vector2i> newShape = getShape();

    // Dla ka¿dego bloku w kszta³cie, dokonujemy rotacji wzglêdem œrodka klocka
    for (auto& block : newShape) {
        int temp = block.x;
        block.x = -block.y;
        block.y = temp;
    }

    // Aktualizujemy kszta³t po rotacji
    setShape(newShape);
}
void Tetrimino::setShape(const std::vector<sf::Vector2i>& shape) {//zmienia kszta³t klokca
    currentShape = shape;
}
bool Tetrimino::hasReversedControls() const {
    return RevControl;
}