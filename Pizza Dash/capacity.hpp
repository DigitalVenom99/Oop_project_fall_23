#ifndef CAPACITY_HPP
#define CAPACITY_HPP

class Capacity {
public:
    Capacity(int initialCapacity);

    void decrement();

    void increment(int x);

    int getCurrentCapacity() const;

    int getTotalCapacity() const;

    void reset();

private:
    int totalCapacity;
    int currentCapacity;
    // bool increase_cap_flag = true;
};

#endif // CAPACITY_HPP
