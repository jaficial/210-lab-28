// COMSC-210 | Jed Aficial | Lab 28
// github link: https://github.com/jaficial/210-lab-28

#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
#include <algorithm>
#include <random>
#include <string>
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
void reverse_trip(list<Goat> &trip);
void clear_trip(list<Goat> &trip);
void pop_head(list<Goat> &trip);
void pop_tail(list<Goat> &trip);
void trip_empty(list<Goat> trip);
void find_goat(list<Goat> trip, Goat);

int main_menu();

/* NOTE: Implement 8 STL algorithms to this code. Original code contains add goat, delete goat, list goats
// note: find wont work so far since find is comparing the Goat type to a const int type
    list of added functions so far:
    - reverse trip order
    - clear trip
    - pop head of trip
    - pop tail of trip  
    - checks if trip is empty or not
    - find a specific goat
*/
int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 10) { // while sel doesnt equal 5, in which 5 is the end the program
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 4: // reverse function works 
                cout << "Reversing the order of the trip.\n";
                reverse_trip(trip);
                break;
            case 5:
                clear_trip(trip);
                break;
            case 6:
                cout << "Deleting the head goat of the trip.\n";
                pop_head(trip);
                break;
            case 7:
                cout << "Deleting the tail goat of the trip.\n";
                pop_tail(trip);
                break;
            case 8:
                cout << "Checking if the trip is empty or not.\n";
                trip_empty(trip);
                break;
            case 9:
                string temp_goat_name;
                int temp_goat_age;
                string temp_goat_color;
                cout << "Looking for a specific goat in the trip.\n";
                cout << "Name of the goat: ";
                getline(cin, temp_goat_name);
                cout << "Age of the goat: ";
                cin >> temp_goat_age;
                cout << "Color of the goat: ";
                getline(cin, temp_goat_color);
                Goat temp_goat(temp_goat_name, temp_goat_age, temp_goat_color);

                break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Reverse the trip\n";
    cout << "[5] Clear the trip\n";
    cout << "[6] Pop the head goat\n";
    cout << "[7] Pop the tail goat\n";
    cout << "[8] Check if the trip is empty or not\n";
    cout << "[9] Find a specific goat\n";
    cout << "[10] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 9) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

void reverse_trip(list<Goat> &trip){
    reverse(trip.begin(), trip.end());
}

void clear_trip(list<Goat> &trip){
    trip.clear();
    cout << "Trip is now cleared.\n";
}

void pop_head(list<Goat> &trip){
    trip.pop_front();
}

void pop_tail(list<Goat> &trip){
    trip.pop_back();
}

void trip_empty(list<Goat> trip){
    int empty_test = trip.empty();
    if (empty_test == 1) {
        cout << "There are no goats in the trip.\n";
    }
    else {
        cout << "There are goats in the trip.\n";
    }
}

void find_goat(list<Goat> trip, Goat temp_goat){
    cout << "Made it here"
}