#include "../include/Passenger.h"

using namespace std;

//================ CONSTRUCTORS =================//

Passenger::Passenger()
{
    passengerID = 0;
    name = "";
    age = 0;
    gender = ' ';
    phoneNumber = "";
}

Passenger::Passenger(
    int id,
    string n,
    int a,
    char g,
    string phone)
{
    passengerID = id;
    name = n;
    age = a;
    gender = g;
    phoneNumber = phone;
}

//================ GETTERS =================//

int Passenger::getPassengerID() const
{
    return passengerID;
}

string Passenger::getName() const
{
    return name;
}

int Passenger::getAge() const
{
    return age;
}

char Passenger::getGender() const
{
    return gender;
}

string Passenger::getPhoneNumber() const
{
    return phoneNumber;
}

//================ DISPLAY =================//

void Passenger::displayPassenger() const
{
    cout << "\n========== PASSENGER DETAILS ==========\n";

    cout << "Passenger ID : " << passengerID << endl;
    cout << "Name         : " << name << endl;
    cout << "Age          : " << age << endl;
    cout << "Gender       : " << gender << endl;
    cout << "Phone Number : " << phoneNumber << endl;
}   