#pragma once

#include <iostream>

class Seat
{
private:
    int seatNumber;
    bool reserved;

public:
    // Constructors
    Seat();
    Seat(int number);

    // Seat Operations
    void reserve();
    void cancel();

    // Getters
    bool isReserved() const;
    int getSeatNumber() const;

    // Display
    void displaySeat() const;
};