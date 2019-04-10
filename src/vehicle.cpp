#include "vehicle.h"

Vehicle::Vehicle(int capacity){

    this->capacity = capacity;

}

void Vehicle::setCapacity(int capacity){
    this->capacity = capacity;
}

int Vehicle::getCapacity(){
    return capacity;
}