#include "../include/Booking.h"

#include <iomanip>

using namespace std;

Booking::Booking()
    : bookingID(0), bus(nullptr), passenger(nullptr), seatNumber(0),
      totalFare(0.0), bookingStatus("Not Booked")
{
}

Booking::Booking(int id, Bus* b, Passenger* p, int seatNo)
    : bookingID(id), bus(b), passenger(p), seatNumber(seatNo),
      totalFare(b->calculateFare()), bookingStatus("Confirmed")
{
    bus->reserveSeat(seatNo);
}

int Booking::getBookingID() const { return bookingID; }
int Booking::getSeatNumber() const { return seatNumber; }
double Booking::getFare() const { return totalFare; }
string Booking::getStatus() const { return bookingStatus; }
Bus* Booking::getBus() const { return bus; }
Passenger* Booking::getPassenger() const { return passenger; }

void Booking::cancelBooking()
{
    if (bookingStatus == "Cancelled")
    {
        cout << "\nBooking is already cancelled.\n";
        return;
    }

    bus->cancelSeat(seatNumber);
    bookingStatus = "Cancelled";
    cout << "\nBooking cancelled successfully.\n";
}

void Booking::restoreStatus(const string& status)
{
    if (status == "Cancelled")
    {
        bus->cancelSeat(seatNumber);
        bookingStatus = "Cancelled";
    }
}

void Booking::displayBooking() const
{
    cout << "\n==========================================================\n";
    cout << "                     BOOKING DETAILS\n";
    cout << "==========================================================\n";
    cout << "Booking ID : " << bookingID << endl;
    cout << "Passenger  : " << passenger->getName() << endl;
    cout << "Bus ID     : " << bus->getBusID() << endl;
    cout << "Bus Type   : " << bus->getBusType() << endl;
    cout << "Route      : " << bus->getSource() << " -> " << bus->getDestination() << endl;
    cout << "Seat No    : " << seatNumber << endl;
    cout << fixed << setprecision(2);
    cout << "Fare       : Rs. " << totalFare << endl;
    cout << "Status     : " << bookingStatus << endl;
    cout << "==========================================================\n";
}
