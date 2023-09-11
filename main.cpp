#include <iostream>
#include "Car_full.h"


int main() {
    Spark sp;
    ModelS s;
    // use the car container
    // What is the c’tr and d’tr order?
    CarDealer dealer;
    // Which clone() is called each time?
    dealer.add(sp);
    dealer.add(s);
    dealer.what_cars_do_you_have();
    return 0;
}
