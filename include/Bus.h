#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Seat.h"

class Bus
{
protected:
    int busID;
    std::string operatorName;
    std::string source;
    std::string destination;
    std::string departureTime;
    std::string arrivalTime;
    double baseFare;

    std::vector<Seat> seats;

public:
    Bus(int id,
        std::string op,
        std::string src,
        std::string dest,
        std::string dep,
        std::string arr,
        double fare);

    virtual ~Bus();

    virtual void displayDetails() const;

    virtual double calculateFare() const = 0;

    virtual std::string getBusType() const = 0;

    bool reserveSeat(int seatNo);

    void cancelSeat(int seatNo);

    bool isSeatAvailable(int seatNo) const;

    void displaySeatMap() const;

    int getBusID() const;
    std::string getSource() const;
    std::string getDestination() const;
};

class ACSeater : public Bus
{
public:
    ACSeater(
        int id,
        std::string op,
        std::string src,
        std::string dest,
        std::string dep,
        std::string arr,
        double fare);

    double calculateFare() const override;

    std::string getBusType() const override;
};

class NonACSeater : public Bus
{
public:
    NonACSeater(
        int id,
        std::string op,
        std::string src,
        std::string dest,
        std::string dep,
        std::string arr,
        double fare);

    double calculateFare() const override;

    std::string getBusType() const override;
};

class ACSleeper : public Bus
{
public:
    ACSleeper(
        int id,
        std::string op,
        std::string src,
        std::string dest,
        std::string dep,
        std::string arr,
        double fare);

    double calculateFare() const override;

    std::string getBusType() const override;
};