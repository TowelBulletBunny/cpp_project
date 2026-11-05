#include "device.h"
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
using namespace std;

const string STUDENT_ID = "20715019";   // appended to every device name
const double NO_LIMIT = numeric_limits<double>::max();

// Column widths for the table (change these to adjust spacing)
const int W_NO     = 6;
const int W_NAME   = 24;
const int W_POWER  = 16;
const int W_HOURS  = 14;
const int W_ENERGY = 20;

// ===================== Device class =====================

Device::Device(const string& n, double p, double h)
    : name(n), powerWatts(p), hoursPerDay(h) {}

double Device::dailyEnergyKWh() const {
    return (powerWatts * hoursPerDay) / 1000.0;
}

void Device::print(int number) const {
    cout << left << fixed << setprecision(2)
         << setw(W_NO)     << number
         << setw(W_NAME)   << name
         << setw(W_POWER)  << powerWatts
         << setw(W_HOURS)  << hoursPerDay
         << setw(W_ENERGY) << dailyEnergyKWh() << "\n";
}

// ===================== Input helpers (private to this file) =====================

namespace {

// Keeps asking until the user enters a number between minVal and maxVal
double readNumber(const string& prompt, double minVal, double maxVal) {
    string line;
    while (true) {
        cout << prompt;
        getline(cin, line);

        try {
            size_t pos;
            double value = stod(line, &pos);
            if (pos == line.size() && value >= minVal && value <= maxVal) {
                return value;
            }
        } catch (...) {
            // not a number, fall through to the error message
        }

        if (maxVal == NO_LIMIT) {
            cout << "  Invalid. Enter a number of at least " << minVal << ".\n";
        } else {
            cout << "  Invalid. Enter a number between "
                 << minVal << " and " << maxVal << ".\n";
        }
    }
}

// Keeps asking until the user enters a non-empty name
string readName(const string& prompt) {
    string name;
    while (true) {
        cout << prompt;
        getline(cin, name);
        if (!name.empty()) {
            return name;
        }
        cout << "  Name cannot be empty.\n";
    }
}

}  // end of unnamed namespace

// ===================== Functions used by main() =====================

void inputDevices(Device* devices[], int count) {
    cout << "Enter the details for " << count << " devices.\n";

    for (int i = 0; i < count; ++i) {
        cout << "\n--- Device " << (i + 1) << " of " << count << " ---\n";

        string name  = readName("  Name: ") + STUDENT_ID;
        double hours = readNumber("  Hours used per day (0-24): ", 0, 24);
        double watts = readNumber("  Power rating (watts): ", 0.1, NO_LIMIT);

        devices[i] = new Device(name, watts, hours);
    }
}

// Bubble sort: device using the most energy per day comes first
void sortByEnergy(Device* devices[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (devices[j]->dailyEnergyKWh() < devices[j + 1]->dailyEnergyKWh()) {
                Device* temp = devices[j];
                devices[j] = devices[j + 1];
                devices[j + 1] = temp;
            }
        }
    }
}

// Prints all devices as a table: a header row, a separator line,
// then one row per device (the rows themselves are printed by Device::print).
void displayDevices(Device* devices[], int count) {
    // --- Header row ---
    // "left" aligns text to the left of each column;
    // setw(W_...) sets how many characters wide each column is.
    cout << "\n" << left
         << setw(W_NO)     << "No."
         << setw(W_NAME)   << "Name"
         << setw(W_POWER)  << "Power (W)"
         << setw(W_HOURS)  << "Hours/day"
         << setw(W_ENERGY) << "Energy (kWh/day)" << "\n"
         << string(W_NO + W_NAME + W_POWER + W_HOURS + W_ENERGY, '-') << "\n";

    // --- Device rows ---
    // Devices are already sorted, so row numbers (i + 1) double as a ranking
    for (int i = 0; i < count; ++i) {
        devices[i]->print(i + 1);
    }
}

// Frees the memory for every Device created with "new" in inputDevices.
// Must be called once at the end of the program, otherwise the memory leaks.
void deleteDevices(Device* devices[], int count) {
    for (int i = 0; i < count; ++i) {
        delete devices[i];
    }
}