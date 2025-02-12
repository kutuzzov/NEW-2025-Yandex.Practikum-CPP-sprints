#include <iostream>

#include "accountant.h"
#include "builder.h"
#include "carpenter.h"
#include "painter.h"

using namespace std;

int main() {
    Builder tom;
    Carpenter jack;
    Accountant ray;
    Wall wall(3.5, 2.45);

    cout << ray.CalcBricksNeeded(wall) << endl;
    cout << ray.CalcPaintNeeded(wall) << endl;

    jack.InstallDoor(wall, tom);
    cout << wall.IsDoorInstalled() << endl;
    return 0;
}
