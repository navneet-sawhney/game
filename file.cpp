#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

class Taxi {
public:
    string make;
    string model;
    string licensePlate;
    int numPassengers;

    // Constructor
    Taxi() {
        make = "";
        model = "";
        licensePlate = "";
        numPassengers = 0;
    }

    // Overload + operator to add total calls and total passengers
    Taxi operator+(const Taxi& other) {
        Taxi result;
        result.make = "Total";
        result.model = "";
        result.licensePlate = "";
        result.numPassengers = numPassengers + other.numPassengers;
        return result;
    }

    // Overload < operator to determine which taxi served most passengers
    bool operator<(const Taxi& other) {
        return numPassengers < other.numPassengers;
    }
};

void generateTaxiData(Taxi& taxi) {
    string makes[] = {"Toyota", "Honda", "Ford", "Chevrolet"};
    string models[] = {"Camry", "Accord", "F-150", "Silverado"};
    string licenseChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int numChars = licenseChars.length();

    taxi.make = makes[rand() % 4];
    taxi.model = models[rand() % 4];
    taxi.numPassengers = rand() % 4 + 1;

    for (int i = 0; i < 7; i++) {
        taxi.licensePlate += licenseChars[rand() % numChars];
    }
}

int main() {
    srand(time(0));
    int numTaxis = 5;

    // Create taxis and write to file
    ofstream outFile("taxi_data.txt");
    int totalPassengers = 0;ṇ
    for (int i = 0; i < numTaxis; i++) {
        Taxi taxi;
        generateTaxiData(taxi);
        totalPassengers += taxi.numPassengers;
        outFile << taxi.make << "," << taxi.model << "," << taxi.licensePlate << "," << taxi.numPassengers << endl;
    }
    outFile.close();

    // Read from file and print to console
    ifstream inFile("taxi_data.txt");
    string line;
    Taxi mostPassengers;
    int mostPassengersNum = 0;
    while (getline(inFile, line)) {
        Taxi taxi;
        stringstream ss(line);
        getline(ss, taxi.make, ',');
        getline(ss, taxi.model, ',');
        getline(ss, taxi.licensePlate, ',');
        ss >> taxi.numPassengers;

        if (taxi < mostPassengers) {
            mostPassengers = taxi;
            mostPassengersNum = 1;
        } else if (taxi.numPassengers == mostPassengers.numPassengers) {
            mostPassengersNum++;
        }

        totalPassengers += taxi.numPassengers;
    }
    inFile.close();

    // Print report to console and file
    ofstream reportFile("taxi_report.txt");
    reportFile << "Today " << mostPassengers.make << " " << mostPassengers.model << " served the most passengers with " << mostPassengers.numPassengers << " passengers." << endl;
    if (mostPassengersNum > 1) {
        reportFile << "There were " << mostPassengersNum << " taxis tied for most passengers." << endl;
    }
    reportFile << "Today on average each taxi served " << (float)totalPassengers / numTaxis <<
