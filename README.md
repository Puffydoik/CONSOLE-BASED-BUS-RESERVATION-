# CityLink Bus Reservation System

This is a console-based C++ bus reservation project built using object-oriented programming.

## What was improved

The original project structure was preserved. The following existing files were enhanced:

- `src/ReservationSystem.cpp`: polished menus, banners, colors, clearer messages, and 12 sample buses.
- `src/Bus.cpp`: improved bus cards, fare formatting, available-seat count, and seat-map layout.

The existing classes are still used:

- `Bus`, `ACSeater`, `NonACSeater`, and `ACSleeper`
- `Passenger`
- `Booking`
- `Seat`
- `Waitlist`
- `ReservationSystem`

## Routes included

The sample catalog now contains routes for Pune, Mumbai, Bangalore, Hyderabad, Nashik, Satara, Kolhapur, Ahmedabad, Goa, and Delhi.

## How to build in VS Code with MinGW

Open the project folder in VS Code and run:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp src/*.cpp -o BusReservation.exe
```

Then run:

```bash
BusReservation.exe
```

The existing `BusReservation.exe` should be rebuilt after pulling these source changes, because an executable does not update automatically when a `.cpp` file changes.

## Current functionality

The application supports showing all buses, booking tickets, validating passenger details, reserving seats, cancelling tickets, searching bookings, and displaying seat maps. The upgraded interface uses colored terminal sections when the terminal supports ANSI colors.

## Admin/project extension ideas

Possible next improvements include saving bookings to files, loading buses from `data/buses.txt`, adding route search by source and destination, implementing waitlist promotion after cancellation, and adding an administrator menu.
