#pragma once

#include <deque>
#include <vector>

#include "Bus.h"
#include "Booking.h"
#include "Passenger.h"

// Coordinates buses, passengers, bookings, and the console menu.
class ReservationSystem
{
private:
    std::vector<Bus*> buses;
    // deque keeps stored Passenger addresses valid for Booking objects.
    std::deque<Passenger> passengers;
    std::vector<Booking> bookings;

    int nextPassengerID;
    int nextBookingID;

    void loadSampleBuses();
    void loadBookings();
    void saveBookings() const;
    Bus* findBus(int busID) const;

    static int readInteger(const char* prompt, int minimum, int maximum);
    static std::string readName();
    static char readGender();
    static std::string readPhoneNumber();
    static void pause();

public:
    ReservationSystem();
    ~ReservationSystem();

    // This class owns its Bus pointers, so copying it would be unsafe.
    ReservationSystem(const ReservationSystem&) = delete;
    ReservationSystem& operator=(const ReservationSystem&) = delete;

    void start();
    void showAllBuses() const;
    void bookTicket();
    void cancelTicket();
    void searchBooking() const;
    void displaySeatMap() const;
    void showAllBookings() const;
};
