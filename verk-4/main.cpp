#include <iostream>
#include <string>
#include <limits>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;


class FlightBooking {
    public:
        FlightBooking(int, int, int);
        void printStatus();
        bool reserveSeats(int);
        bool cancelReservations(int);
        int getId() { return id; };
    private:
        int id;
        int capacity;
        int reserved;
        int percent() {return ((float)reserved / (float)capacity) * 100;}
};

FlightBooking::FlightBooking (int i = 0, int c = 0, int r = 0) : id(i), capacity(c) {
    reserved = (r > 0) ? r : 0;
    while (percent() > 105) {reserved--;}
}

void FlightBooking::printStatus() {
    cout << "Flight " << id << ": " << reserved << "/" << capacity
         << " (" << percent() << "%) Seats reserved" << endl;
}

bool FlightBooking::reserveSeats(int howMany) {
    int oldReserved = reserved;
    reserved += howMany;
    if (percent() > 105) {
        reserved = oldReserved;
        return false;
    }
    return true;
}

bool FlightBooking::cancelReservations(int howMany) {
    int oldReserved = reserved;
    reserved -= howMany;
    if (reserved < 0) {
        reserved = oldReserved;
        return false;
    }
    return true;
}

pair <int, bool> findBookById(int id, vector<FlightBooking>& books) {
    for (int i = 0; i < 10; i++) {
        if (books[i].getId() == id) {
            return make_pair(i, true);
        }
    }
    return make_pair(NULL, false);
}

bool createFlight(int id, int cap, vector<FlightBooking>& books) {
    if (!findBookById(0, books).second || findBookById(id, books).second){
        return false; 
    }
    books.push_back(FlightBooking(id, cap));
    return true;
}

bool deleteFlight(int id, vector<FlightBooking>& books) {
    if (!findBookById(id, books).second){
        return false; 
    }
    books.erase(books.begin()+findBookById(id, books).first+1);
    return true;
}


int main() {
    int id, n;
    vector<FlightBooking> booking;
    string command;

    // init
    booking.push_back(FlightBooking(1, 400, 0));

    while(command != "quit") {
        if (command != "\n") {
            // prentar öll books
            for_each(booking.begin(), booking.end(), [](FlightBooking x){x.printStatus();});
        }
        cout << "Enter command: ";
        cin >> command;
        if (command == "create") {
            cin >> id >> n;

            if (!createFlight(id, n, booking)) {
                cout << "Creating flight went horribly wrong..." << endl;
            } else {
                cout << "Flight " << id << " created" << endl;
            }
        }
        else if (command == "delete") {
            cin >> id;

            if (!deleteFlight(id, booking)) {
                cout << "Deleting flight failed, wrong id probably..." << endl;
            } else {
                cout << "Flight deleted" << endl;
            }
        }
        else if (command == "add") { 
            cin >> id >> n;
            
            if (!findBookById(id, booking).second) {
                cout << "Flight not found..." << endl;
            } else {
                booking[findBookById(id, booking).first].reserveSeats(n);
                cout << "Added " << n << " reservations to flight " << id << endl;
            }
        }
        else if (command == "cancel") {
            cin >> id >> n;
            if (!findBookById(id, booking).second) {
                cout << "Flight not found..." << endl;
            } else {
                booking[findBookById(id, booking).first].cancelReservations(n);
                cout << "Removed " << n << " reservations from flight " << id << endl;
            }
        } else if (command == "quit") {
            cout << "Goodbye..." << endl;
        } else { cout << "Unknown command..." << endl; }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return 0;
}

