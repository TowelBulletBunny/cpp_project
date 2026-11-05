#include "device.h"
#include <iostream>
using namespace std;

const int NUM_DEVICES = 3;  // Number of devices to be entered

int main() {
    Device* devices[NUM_DEVICES];  // array of 3 pointers

    inputDevices(devices, NUM_DEVICES);
    sortByEnergy(devices, NUM_DEVICES);
    displayDevices(devices, NUM_DEVICES);
    deleteDevices(devices, NUM_DEVICES);

    cin.get(); // Wait for user input before closing the console window
    return 0;
}