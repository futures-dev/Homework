#include <iostream>
#include <fstream>

using namespace std;

#include "course.h"
#include "safearray.h"

void initCourses(safearray<course> &);

void displayMenu(safearray<course> &);

const int NUM_COURSES = 10;
const int QUIT = 99;

int main(int argc, char *argv[]) {

    safearray<course> courses(NUM_COURSES);
    initCourses(courses);

    int choice = 0;
    while (true) {

        displayMenu(courses);
        cout << "Enter number of course to see more information on\n";
        cin >> choice;
        cin.clear();    // Defence from non int
        cin.sync();
        // a little change, because no need to try courses[QUIT]
        if (choice == QUIT) {
            break;
        }
        cout << "\n";
        // the great use of exception
        try {
            cout << courses[choice - 1] << "\n\n";
        }
        catch (out_of_range &e) {
            cout << e.what() << endl;
        }
    }
    return EXIT_SUCCESS;
}

void displayMenu(safearray<course> &courses) {

    for (int i = 1; i <= NUM_COURSES; i++) {
        cout << i << ". " << courses[i - 1].name << "\n";
    }
    cout << "99. Quit\n";
}

void initCourses(safearray<course> &courses) {
    ifstream inf("courses.txt");
    if (!inf) {
        cerr << "Could not open courses.txt" << endl;
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM_COURSES; i++) {
        inf >> courses[i];
    }
    inf.close();
}

