#include "../include/Seat.h"
#include <windows.h>

using namespace std;

//================ CONSTRUCTORS =================//

Seat::Seat()
{
    seatNumber = 0;
    reserved = false;
}

Seat::Seat(int number)
{
    seatNumber = number;
    reserved = false;
}

//================ RESERVE =================//

void Seat::reserve()
{
    reserved = true;
}

//================ CANCEL =================//

void Seat::cancel()
{
    reserved = false;
}

//================ GETTERS =================//

bool Seat::isReserved() const
{
    return reserved;
}

int Seat::getSeatNumber() const
{
    return seatNumber;
}

//================ DISPLAY =================//

void Seat::displaySeat() const
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    if (reserved)
    {
        SetConsoleTextAttribute(console, 12); // Red
        cout << "[XX]";
    }
    else
    {
        SetConsoleTextAttribute(console, 10); // Green

        if (seatNumber < 10)
            cout << "[0" << seatNumber << "]";
        else
            cout << "[" << seatNumber << "]";
    }

    SetConsoleTextAttribute(console, 7); // Reset to normal white
}