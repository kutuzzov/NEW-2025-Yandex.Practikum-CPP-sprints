#include "wall.h"

class Painter {
public:
    // Напишите класс Painter
    void Paint(Wall& wall, const Wall::Color& color) {
        wall.SetColor(color);
    }
};
