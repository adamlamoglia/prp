#include "vehicle.h"

Vehicle::Vehicle(int id, int capacity){

    this->id = id;
    this->capacity = capacity;

}

void Vehicle::setId(int id){
    this->id = id;
}

void Vehicle::setCapacity(int capacity){
    this->capacity = capacity;
}

int Vehicle::getId(){
    return id;
}

int Vehicle::getCapacity(){
    return capacity;
}