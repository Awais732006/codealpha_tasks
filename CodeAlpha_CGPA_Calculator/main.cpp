// Task 1: CGPA Calculator. Grade points are entered on a 0.0 to 4.0 scale.
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <stdexcept>
using namespace std;

double readNumber(const string& prompt, double low, double high, bool integer = false) {
    string line; double value;
    while (true) {
        cout << prompt;
        if (!getline(cin, line)) throw runtime_error("Input ended.");
        istringstream input(line);
        if ((input >> value) && (input >> ws).eof() && isfinite(value)
            && value >= low && value <= high && (!integer || floor(value) == value))
            return value;
        cout << "Enter " << (integer ? "a whole number" : "a number")
             << " from " << low << " to " << high << ".\n";
    }
}
struct Course { string name; double grade, credits; };
int main() {
    try {
        cout << "CGPA CALCULATOR (4.0 scale)\n";
        double previousCredits = readNumber("Previously completed credits (0 for first semester): ", 0, 10000);
        double previousCGPA = 0;
        if (previousCredits > 0) previousCGPA = readNumber("Previous CGPA: ", 0, 4);
        int count = static_cast<int>(readNumber("Number of courses this semester: ", 1, 100, true));
        vector<Course> courses;
        double credits = 0, points = 0;
        for (int i = 0; i < count; ++i) {
            Course c;
            cout << "\nCourse " << i + 1 << "\n";
            do {
                cout << "Course name: ";
                if (!getline(cin, c.name)) throw runtime_error("Input ended.");
            } while (c.name.find_first_not_of(" \t\r") == string::npos);
            c.grade = readNumber("Grade points (0-4, not marks): ", 0, 4);
            c.credits = readNumber("Credit hours: ", 0.5, 30);
            courses.push_back(c);
            credits += c.credits;
            points += c.grade * c.credits;
        }
        cout << fixed << setprecision(2) << "\nCOURSE RESULTS\n";
        for (const Course& c : courses)
            cout << c.name << " | Grade: " << c.grade << " | Credits: " << c.credits
                 << " | Weighted points: " << c.grade * c.credits << '\n';
        cout << "Semester credits: " << credits << "\nSemester grade points: " << points
             << "\nSemester GPA: " << points / credits
             << "\nOverall credits: " << previousCredits + credits
             << "\nOverall CGPA: " << (previousCGPA * previousCredits + points) / (previousCredits + credits) << '\n';
    } catch (const exception& e) { cerr << e.what() << '\n'; return 1; }
}
