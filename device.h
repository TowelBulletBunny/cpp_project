#ifndef DEVICE_H
#define DEVICE_H

#include <string>

class Device {
private:
    std::string name;
    double powerWatts;
    double hoursPerDay;

public:
    Device(const std::string& n, double p, double h);
    double dailyEnergyKWh() const;
    void print(int number) const;
};

// Functions used by main()
void inputDevices(Device* devices[], int count);
void sortByEnergy(Device* devices[], int count);
void displayDevices(Device* devices[], int count);
void deleteDevices(Device* devices[], int count);

#endif