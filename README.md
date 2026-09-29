# 🚌 CityLink Bus Reservation System

> A console-based Bus Reservation System built in **C++** using Object-Oriented Programming.

![C++](https://img.shields.io/badge/C%2B%2B-17-blue?style=for-the-badge&logo=cplusplus)
![OOP](https://img.shields.io/badge/Concept-Object--Oriented-orange?style=for-the-badge)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey?style=for-the-badge)

---

## 🌟 About the Project

**CityLink Bus Reservation System** is a console-based C++ application designed to simulate a real-world bus booking platform.

The project demonstrates core **Object-Oriented Programming principles** through a structured reservation system that handles buses, passengers, seats, bookings, cancellations, and waitlists.

The application features an interactive terminal interface with formatted menus, seat maps, booking details, and sample bus routes.

---

## ✨ Features

- 🚌 View available buses
- 🎫 Book bus tickets
- 👤 Validate passenger details
- 💺 Reserve specific seats
- 🗺️ Display seat maps
- ❌ Cancel bookings
- 🔎 Search bookings
- 📋 Display booking information
- ⏳ Waitlist management
- 🎨 Colored and formatted console interface
- 🚌 Multiple sample routes and buses

---

## 🧠 Object-Oriented Concepts

This project demonstrates several important OOP concepts:

| Concept | Implementation |
|---|---|
| **Encapsulation** | Classes encapsulate passenger, bus, booking and seat data |
| **Inheritance** | Different bus types inherit from common bus functionality |
| **Polymorphism** | Different bus categories provide specialized behaviour |
| **Abstraction** | Complex reservation operations are handled through dedicated classes |
| **Composition** | The reservation system works with buses, passengers, bookings and seats |

### Main Classes

```text
Bus
├── ACSeater
├── NonACSeater
└── ACSleeper

Passenger
Booking
Seat
Waitlist
ReservationSystem and destination, implementing waitlist promotion after cancellation, and adding an administrator menu.
