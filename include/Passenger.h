#pragma once

#include <iostream>
#include <string>

class Passenger
{
private:
    int passengerID;
    std::string name;
    int age;
    char gender;
    std::string phoneNumber;

public:
    // Constructors
    Passenger();
    Passenger(
        int id,
        std::string name,
        int age,
        char gender,
        std::string phone);

    // Getters
    int getPassengerID() const;
    std::string getName() const;
    int getAge() const;
    char getGender() const;
    std::string getPhoneNumber() const;

    // Display
    void displayPassenger() const;
};