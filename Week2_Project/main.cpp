//********************************************************************
// Author: Luis Rios
// Assignment: 2-1
// Description: This program reads student data from a file,
//              calculates the average GPA, finds the highest
//              GPA, and identifies the youngest and oldest students.
//********************************************************************


#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    const int MAX_STUDENTS = 100;

    string names[MAX_STUDENTS];
    int ages[MAX_STUDENTS];
    double gpas[MAX_STUDENTS];

    int studentCount = 0;

    ifstream inFile("student_data.txt");

    if (!inFile) {
        cout << "Error. Cannot open file." << endl;
        return 1;
    }

    while (inFile >> names[studentCount]
                  >> ages[studentCount]
                  >> gpas[studentCount]) {
        studentCount++;
    }

    inFile.close();

    // Requirement 1: Average GPA
    double gpaSum = 0.0;
    for (int i = 0; i < studentCount; i++) {
        gpaSum += gpas[i];
    }

    double averageGPA = gpaSum / studentCount;

    cout << fixed << setprecision(2);
    cout << "Average GPA: " << averageGPA << endl << endl;

    // Requirement 2: Highest GPA 
    double highestGPA = gpas[0];
    for (int i = 1; i < studentCount; i++) {
        if (gpas[i] > highestGPA) {
            highestGPA = gpas[i];
        }
    }

    cout << "Highest GPA: " << highestGPA << endl;
    cout << "Students with the highest GPA:" << endl;
    for (int i = 0; i < studentCount; i++) {
        if (gpas[i] == highestGPA) {
            cout << names[i] << endl;
        }
    }
    cout << endl;

    // Requirement 3: Youngest and Oldest
    int youngestAge = ages[0];
    int oldestAge = ages[0];

    for (int i = 1; i < studentCount; i++) {
        if (ages[i] < youngestAge) {
            youngestAge = ages[i];
        }
        if (ages[i] > oldestAge) {
            oldestAge = ages[i];
        }
    }

    cout << "Youngest students:" << endl;
    for (int i = 0; i < studentCount; i++) {
        if (ages[i] == youngestAge) {
            cout << names[i] << endl;
        }
    }
    cout << endl;

    cout << "Oldest students:" << endl;
    for (int i = 0; i < studentCount; i++) {
        if (ages[i] == oldestAge) {
            cout << names[i] << endl;
        }
    }

    return 0;
}
