#include "../include/Bus.h"
#include <iomanip>

using namespace std;

namespace
{
    const char* const RESET = "\033[0m";
    const char* const CYAN = "\033[1;36m";
    const char* const BLUE = "\033[1;34m";
    const char* const GREEN = "\033[1;32m";
    const char* const YELLOW = "\033[1;33m";

    void busDivider()
    {
        cout << BLUE << string(78, '=') << RESET << '\n';
    }
}

//================ BUS =================//

Bus::Bus(int id,
         string op,
         string src,
         string dest,
         string dep,
         string arr,
         double fare)
{
    busID = id;
    operatorName = op;
    source = src;
    destination = dest;
    departureTime = dep;
    arrivalTime = arr;
    baseFare = fare;

    // Create 40 seats
    for (int i = 1; i <= 40; i++)
    {
        seats.push_back(Seat(i));
    }
}

Bus::~Bus()
{
}

void Bus::displayDetails() const
{
    int availableSeats = 0;
    for (const Seat& seat : seats)
    {
        if (!seat.isReserved())
            availableSeats++;
    }

    cout << '\n';
    busDivider();
    cout << CYAN << "Bus ID: " << YELLOW << busID << RESET
         << "   " << CYAN << "Operator: " << YELLOW << operatorName << RESET
         << "   " << CYAN << "Type: " << YELLOW << getBusType() << RESET
         << "   " << CYAN << "Fare: " << GREEN << "Rs. " << fixed << setprecision(2) << calculateFare() << RESET << '\n';
    busDivider();
    cout << CYAN << "Route: " << YELLOW << source << " -> " << destination << RESET
         << "   " << CYAN << "Departure: " << YELLOW << departureTime << RESET
         << "   " << CYAN << "Arrival: " << YELLOW << arrivalTime << RESET << '\n';
    cout << CYAN << "Available seats: " << GREEN << availableSeats << "/40" << RESET << '\n';
    busDivider();
}

bool Bus::reserveSeat(int seatNo)
{
    if (seatNo < 1 || seatNo > 40)
        return false;

    if (seats[seatNo - 1].isReserved())
        return false;

    seats[seatNo - 1].reserve();
    return true;
}

void Bus::cancelSeat(int seatNo)
{
    if (seatNo >= 1 && seatNo <= 40)
    {
        seats[seatNo - 1].cancel();
    }
}

bool Bus::isSeatAvailable(int seatNo) const
{
    if (seatNo < 1 || seatNo > 40)
        return false;

    return !seats[seatNo - 1].isReserved();
}

void Bus::displaySeatMap() const
{
    cout << "\n                 +--------+\n";
    cout << "                 | DRIVER |\n";
    cout << "                 +--------+\n\n";

    for (int i = 0; i < 40; i++)
    {
        seats[i].displaySeat();

        // Aisle after every 2 seats
        if ((i + 1) % 2 == 0)
            cout << "   ";

        // Next row after 4 seats
        if ((i + 1) % 4 == 0)
            cout << endl;
    }

    cout << "\n";
    cout << "\nLegend:\n";
    cout << "[01-40] = Available\n";
    cout << "[XX]    = Reserved\n"; 
}

//================ AC SEATER =================//

ACSeater::ACSeater(int id,
                   string op,
                   string src,
                   string dest,
                   string dep,
                   string arr,
                   double fare)
    : Bus(id, op, src, dest, dep, arr, fare)
{
}

double ACSeater::calculateFare() const
{
    return baseFare * 1.25;
}

string ACSeater::getBusType() const
{
    return "AC Seater";
}


//================ NON AC =================//

NonACSeater::NonACSeater(int id,
                         string op,
                         string src,
                         string dest,
                         string dep,
                         string arr,
                         double fare)
    : Bus(id, op, src, dest, dep, arr, fare)
{
}

double NonACSeater::calculateFare() const
{
    return baseFare;
}

string NonACSeater::getBusType() const
{
    return "Non AC Seater";
}


//================ AC SLEEPER =================//

ACSleeper::ACSleeper(int id,
                     string op,
                     string src,
                     string dest,
                     string dep,
                     string arr,
                     double fare)
    : Bus(id, op, src, dest, dep, arr, fare)
{
}

double ACSleeper::calculateFare() const
{
    return baseFare * 1.50;
}

string ACSleeper::getBusType() const
{
    return "AC Sleeper";
}

//================== GETTERS ==================

int Bus::getBusID() const
{
    return busID;
}

std::string Bus::getSource() const
{
    return source;
}

std::string Bus::getDestination() const
{
    return destination;
}
