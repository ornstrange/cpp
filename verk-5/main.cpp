#include <iostream>
#include <string>
#include <limits>
#include <utility>
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

struct node {
    FlightBooking data;
    node *next;
};

class LinkedList {
    private:
        node *head, *tail;
    public:
        LinkedList() {
            head = NULL;
            tail = NULL;
        }

        node* gethead() {
            return head;
        }

        void add_node(FlightBooking n) {
            node *tmp = new node;
            tmp->data = n;
            tmp->next = NULL;

            if (head == NULL) {
                head = tmp;
                tail = tmp;
            } else {
                tail->next = tmp;
                tail = tail->next;
            }
        }

        pair<FlightBooking*, bool> findById(int id) {
            node *tmp;
            tmp = head;
            while (tmp != NULL) {
                if (tmp->data.getId() == id) {
                    return make_pair(&tmp->data, true);
                }
                tmp = tmp->next;
            }
            return make_pair(nullptr, false);
        }

        void printAll() {
            node *tmp;
            tmp = head;
            while (tmp != NULL) {
                tmp->data.printStatus();
                tmp = tmp->next;
            }
        }

        void del_node(int id) {
            node* temp;
            node* tmpPrev;
            temp = head;
            while (temp != NULL) {
                if (temp->data.getId() == id) {
                    break;
                }
                tmpPrev = temp;
                temp = temp->next;
            }
            tmpPrev->next = temp->next;
            delete temp;
        }
};

int main() {
    int id, n;
    LinkedList booking;
    string command;

    // init
    booking.add_node(FlightBooking(1, 400, 0));

    while(command != "quit") {
        if (command != "\n") {
            // prentar öll books
            booking.printAll();
        }
        cout << "Enter command: ";
        cin >> command;
        if (command == "create") {
            cin >> id >> n;
            if (booking.findById(id).second) {
                cout << "Creating flight went horribly wrong..." << endl;
            } else {
                booking.add_node(FlightBooking(id, n, 0));
                cout << "Flight " << id << " created" << endl;
            }
        }
        else if (command == "delete") {
            cin >> id;

            if (!booking.findById(id).second) {
                cout << "Deleting flight failed, wrong id probably..." << endl;
            } else {
                booking.del_node(id);
                cout << "Flight deleted" << endl;
            }
        }
        else if (command == "add") { 
            cin >> id >> n;
            
            if (!booking.findById(id).second) {
                cout << "Flight not found..." << endl;
            } else {
                booking.findById(id).first->reserveSeats(n);
                cout << "Added " << n << " reservations to flight " << id << endl;
            }
        }
        else if (command == "cancel") {
            cin >> id >> n;
            if (!booking.findById(id).second) {
                cout << "Flight not found..." << endl;
            } else {
                booking.findById(id).first->cancelReservations(n);
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

