#pragma once

#include <iostream>
#include <string>

#include "Bus.h"
#include "Passenger.h"

class Booking
{
private:
    int bookingID;
    Bus* bus;
    Passenger* passenger;
    int seatNumber;
    double totalFare;
    std::string bookingStatus;

public:
    Booking();
    Booking(int id, Bus* b, Passenger* p, int seatNo);

    int getBookingID() const;
    int getSeatNumber() const;
    double getFare() const;
    std::string getStatus() const;
    Bus* getBus() const;
    Passenger* getPassenger() const;

    void cancelBooking();
    void restoreStatus(const std::string& status);
    void displayBooking() const;
};
