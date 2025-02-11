#include "carpenter.h"
#include "square_calculation.h"

// Определите методы класса здесь
int Carpenter::CalcShelves(const Wall& wall) {
    return static_cast<int>(CalcSquare(wall.GetHeight(), wall.GetWidth()) / 2);
}
