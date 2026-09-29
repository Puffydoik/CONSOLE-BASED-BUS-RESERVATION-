#include "../include/ReservationSystem.h"

#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

namespace
{
    const int SEAT_COUNT = 40;

    // ANSI escape codes are supported by modern Windows terminals and keep
    // console styling separate from the reservation-system logic.
    const char* const RESET = "\033[0m";
    const char* const CYAN = "\033[1;36m";
    const char* const BLUE = "\033[1;34m";
    const char* const GREEN = "\033[1;32m";
    const char* const YELLOW = "\033[1;33m";
    const char* const RED = "\033[1;31m";
    const char* const MAGENTA = "\033[1;35m";

    void divider(char character = '-', int width = 64)
    {
        cout << BLUE << string(width, character) << RESET << '\n';
    }

    void heading(const string& title)
    {
        cout << '\n';
        cout << CYAN << "================================================================\n";
        cout << "|" << setw(62) << left << ("  " + title) << "|\n";
        cout << "================================================================" << RESET << "\n";
    }

    void message(const string& text)
    {
        cout << "\n" << YELLOW << "> " << text << RESET << '\n';
    }

    void prompt(const char* text)
    {
        cout << MAGENTA << text << RESET;
    }

    bool isDigitsOnly(const string& value)
    {
        if (value.empty())
            return false;

        for (unsigned char character : value)
        {
            if (!isdigit(character))
                return false;
        }
        return true;
    }
}

ReservationSystem::ReservationSystem()
    : nextPassengerID(1), nextBookingID(1001)
{
    loadSampleBuses();
    loadBookings();
}

ReservationSystem::~ReservationSystem()
{
    saveBookings();

    for (Bus* bus : buses)
        delete bus;
}

void ReservationSystem::loadSampleBuses()
{
    buses.push_back(new ACSeater(101, "VRL", "Pune", "Mumbai", "06:30", "11:45", 450));
    buses.push_back(new NonACSeater(102, "SRS", "Pune", "Bangalore", "08:00", "20:00", 700));
    buses.push_back(new ACSleeper(103, "Orange Travels", "Mumbai", "Hyderabad", "21:00", "08:00", 900));
    buses.push_back(new NonACSeater(104, "Neeta Travels", "Pune", "Nashik", "08:00", "12:30", 520));
    buses.push_back(new ACSeater(105, "Shivneri", "Pune", "Satara", "07:15", "09:45", 280));
    buses.push_back(new ACSleeper(106, "IntrCity SmartBus", "Pune", "Bengaluru", "20:00", "08:00", 1250));
    buses.push_back(new ACSeater(107, "MSRTC Express", "Pune", "Kolhapur", "09:30", "14:30", 650));
    buses.push_back(new NonACSeater(108, "Raj Travels", "Mumbai", "Pune", "15:00", "19:00", 450));
    buses.push_back(new ACSleeper(109, "Orange Travels", "Pune", "Ahmedabad", "18:30", "07:00", 1100));
    buses.push_back(new ACSeater(110, "VRL", "Mumbai", "Goa", "21:00", "08:30", 980));
    buses.push_back(new ACSleeper(111, "Konduskar", "Pune", "Hyderabad", "19:45", "09:15", 1350));
    buses.push_back(new ACSleeper(112, "SRS Travels", "Pune", "Delhi", "16:00", "12:00", 2100));
}

void ReservationSystem::saveBookings() const
{
    ofstream output("bookings.txt");
    if (!output)
        return;

    for (const Booking& booking : bookings)
    {
        const Passenger* passenger = booking.getPassenger();
        const Bus* bus = booking.getBus();

        output << booking.getBookingID() << ' '
               << bus->getBusID() << ' '
               << booking.getSeatNumber() << ' '
               << passenger->getPassengerID() << ' '
               << passenger->getAge() << ' '
               << passenger->getGender() << ' '
               << quoted(passenger->getName()) << ' '
               << quoted(passenger->getPhoneNumber()) << ' '
               << quoted(booking.getStatus()) << '\n';
    }
}

void ReservationSystem::loadBookings()
{
    ifstream input("bookings.txt");
    if (!input)
        return;

    int bookingID;
    int busID;
    int seatNumber;
    int passengerID;
    int age;
    char gender;
    string name;
    string phone;
    string status;

    while (input >> bookingID >> busID >> seatNumber >> passengerID >> age >> gender
                 >> quoted(name) >> quoted(phone) >> quoted(status))
    {
        Bus* bus = findBus(busID);
        if (bus == nullptr || seatNumber < 1 || seatNumber > SEAT_COUNT)
            continue;

        passengers.emplace_back(passengerID, name, age, gender, phone);
        bookings.emplace_back(bookingID, bus, &passengers.back(), seatNumber);
        bookings.back().restoreStatus(status);

        if (passengerID >= nextPassengerID)
            nextPassengerID = passengerID + 1;
        if (bookingID >= nextBookingID)
            nextBookingID = bookingID + 1;
    }
}

Bus* ReservationSystem::findBus(int busID) const
{
    for (Bus* bus : buses)
    {
        if (bus->getBusID() == busID)
            return bus;
    }
    return nullptr;
}

int ReservationSystem::readInteger(const char* prompt, int minimum, int maximum)
{
    int value;
    while (true)
    {
        ::prompt(prompt);
        if (cin >> value)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (value >= minimum && value <= maximum)
                return value;
            cout << RED << "Please enter a number from " << minimum << " to " << maximum << "." << RESET << "\n";
        }
        else
        {
            cout << RED << "Invalid input. Numbers only, please." << RESET << "\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

string ReservationSystem::readName()
{
    string name;
    while (true)
    {
        ::prompt("Enter passenger name : ");
        getline(cin, name);

        bool hasLetter = false;
        for (unsigned char character : name)
        {
            if (isalpha(character))
            {
                hasLetter = true;
                break;
            }
        }

        if (hasLetter)
            return name;
        cout << RED << "Please enter a valid name." << RESET << "\n";
    }
}

char ReservationSystem::readGender()
{
    string input;
    while (true)
    {
        ::prompt("Enter gender (M/F) : ");
        getline(cin, input);
        if (input.size() == 1)
        {
            char gender = static_cast<char>(toupper(static_cast<unsigned char>(input[0])));
            if (gender == 'M' || gender == 'F')
                return gender;
        }
        cout << RED << "Please enter M or F." << RESET << "\n";
    }
}

string ReservationSystem::readPhoneNumber()
{
    string phone;
    while (true)
    {
        ::prompt("Enter 10-digit phone number : ");
        getline(cin, phone);
        if (phone.size() == 10 && isDigitsOnly(phone))
            return phone;
        cout << RED << "Phone number must contain exactly 10 digits." << RESET << "\n";
    }
}

void ReservationSystem::pause()
{
    cout << "\n" << MAGENTA << "[ Press Enter to continue ]" << RESET;
    cin.get();
}

void ReservationSystem::start()
{
    bool running = true;
    while (running)
    {
        heading("TRAVEL DESK : BUS RESERVATION PORTAL");
        cout << MAGENTA
             << "  [1]  Browse bus directory\n"
             << "  [2]  Make a new reservation\n"
             << "  [3]  Cancel a reservation\n"
             << "  [4]  Find a reservation\n"
             << "  [5]  View bus seating\n"
             << "  [6]  View reservation history\n"
             << "  [7]  Close the portal\n"
             << RESET;
        divider();

        const int choice = readInteger("Select an option: ", 1, 7);
        cout << '\n';

        switch (choice)
        {
        case 1: showAllBuses(); break;
        case 2: bookTicket(); break;
        case 3: cancelTicket(); break;
        case 4: searchBooking(); break;
        case 5: displaySeatMap(); break;
        case 6: showAllBookings(); break;
        case 7:
            cout << "\n" << GREEN << "Travel Desk closed. Thank you and travel safely!" << RESET << "\n";
            running = false;
            continue;
        }
        pause();
        cout << '\n';
    }
}

void ReservationSystem::showAllBuses() const
{
    heading("BUS DIRECTORY");
    cout << GREEN << "Browse the routes currently available for booking." << RESET << "\n";
    divider();

    for (const Bus* bus : buses)
    {
        bus->displayDetails();
        cout << '\n';
    }
}

void ReservationSystem::bookTicket()
{
    heading("NEW RESERVATION");
    cout << YELLOW << "Step 1 of 3 - Choose a bus" << RESET << "\n";
    divider();
    showAllBuses();

    Bus* selectedBus = nullptr;
    while (selectedBus == nullptr)
    {
        const int busID = readInteger("Bus ID: ", 1, 9999);
        selectedBus = findBus(busID);
        if (selectedBus == nullptr)
            message("No matching bus was found. Try another ID.");
    }

    cout << "\n" << YELLOW << "Step 2 of 3 - Pick an open seat" << RESET << "\n";
    divider();
    cout << CYAN << "Seat layout for bus " << selectedBus->getBusID() << ":" << RESET << "\n";
    selectedBus->displaySeatMap();

    int seatNumber;
    while (true)
    {
        seatNumber = readInteger("Seat number (1-40): ", 1, SEAT_COUNT);
        if (selectedBus->isSeatAvailable(seatNumber))
            break;
        message("That seat has already been reserved.");
    }

    cout << "\n" << YELLOW << "Step 3 of 3 - Passenger information" << RESET << "\n";
    divider();
    const string name = readName();
    const int age = readInteger("Enter age : ", 1, 120);
    const char gender = readGender();
    const string phone = readPhoneNumber();

    passengers.emplace_back(nextPassengerID++, name, age, gender, phone);

    // Booking's constructor reserves the chosen seat; do not reserve it here too.
    bookings.emplace_back(nextBookingID++, selectedBus, &passengers.back(), seatNumber);
    saveBookings();

    heading("RESERVATION SUCCESSFUL");
    cout << GREEN << "Your seat has been secured and the booking was saved." << RESET << "\n";
    bookings.back().displayBooking();
}

void ReservationSystem::cancelTicket()
{
    heading("CANCEL RESERVATION");

    if (bookings.empty())
    {
        message("There are no reservations available to cancel.");
        return;
    }

    const int bookingID = readInteger("Booking ID: ", 1, numeric_limits<int>::max());
    for (Booking& booking : bookings)
    {
        if (booking.getBookingID() == bookingID)
        {
            if (booking.getStatus() == "Cancelled")
            {
                message("This reservation was already cancelled.");
                return;
            }

            booking.cancelBooking();
            saveBookings();
            message("The reservation has been cancelled and its seat is open again.");
            booking.displayBooking();
            return;
        }
    }
    message("No reservation exists with that ID.");
}

void ReservationSystem::searchBooking() const
{
    heading("FIND RESERVATION");

    if (bookings.empty())
    {
        message("There are no saved reservations to search.");
        return;
    }

    const int bookingID = readInteger("Booking ID: ", 1, numeric_limits<int>::max());
    for (const Booking& booking : bookings)
    {
        if (booking.getBookingID() == bookingID)
        {
            message("Reservation found.");
            booking.displayBooking();
            return;
        }
    }
    message("No reservation exists with that ID.");
}

void ReservationSystem::displaySeatMap() const
{
    heading("BUS SEATING VIEW");

    Bus* selectedBus = nullptr;
    while (selectedBus == nullptr)
    {
        const int busID = readInteger("Bus ID: ", 1, 9999);
        selectedBus = findBus(busID);
        if (selectedBus == nullptr)
            message("No matching bus was found. Try another ID.");
    }

    cout << "\n" << CYAN << "Current seat layout for bus " << selectedBus->getBusID() << ":" << RESET << "\n";
    selectedBus->displaySeatMap();
}

void ReservationSystem::showAllBookings() const
{
    heading("RESERVATION HISTORY");

    if (bookings.empty())
    {
        message("There are no saved reservations yet.");
        return;
    }

    for (const Booking& booking : bookings)
        booking.displayBooking();
}
