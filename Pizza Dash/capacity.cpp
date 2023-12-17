#include "capacity.hpp"

Capacity::Capacity(int initialCapacity) : totalCapacity(initialCapacity), currentCapacity(initialCapacity) {}

void Capacity::decrement() {
    if (currentCapacity > 0) {
        --currentCapacity;
    }
}

void Capacity::increment(int x) {
    currentCapacity = currentCapacity + x;
}

int Capacity::getCurrentCapacity() const {
    return currentCapacity;
}

int Capacity::getTotalCapacity() const {
    return totalCapacity;
}

void Capacity::reset() {
    currentCapacity = totalCapacity;
}
