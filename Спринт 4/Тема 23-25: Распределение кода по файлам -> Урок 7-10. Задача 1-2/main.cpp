#include "builder.h"
#include "painter.h"
#include "carpenter.h"
#include "accountant.h"

#include <iostream>

using namespace std;

int main() {
    Builder tom;
    //Painter bill;
    Carpenter jack;
    Accountant ray;
    Wall wall(3.5, 2.45);

    cout << ray.CalcBricksNeeded(wall) << endl;
    cout << ray.CalcPaintNeeded(wall) << endl;

    jack.InstallDoor(wall, tom);
    cout << wall.IsDoorInstalled() << endl;
    return 0;
}
