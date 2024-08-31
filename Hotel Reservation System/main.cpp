#include <iostream>
#include <string>
using namespace std;

const int MAX_ROOMS = 100;

struct Room {
    int roomNumber;
    string roomType;
    bool isAvailable;
};

struct Reservation {
    int roomNumber;
    string customerName;
    int checkInDate;
    int checkOutDate;
};

Room rooms[MAX_ROOMS];
Reservation reservations[MAX_ROOMS];
int roomCount = 0;
int reservationCount = 0;

void addRoom() {
    if (roomCount >= MAX_ROOMS) {
        cout << "Cannot add more rooms!\n";
        return;
    }
    cout << "Enter Room Number: ";
    cin >> rooms[roomCount].roomNumber;
    cout << "Enter Room Type (Single/Double/Suite): ";
    cin >> rooms[roomCount].roomType;
    rooms[roomCount].isAvailable = true;
    roomCount++;
    cout << "Room added successfully!\n";
}

void displayRooms() {
    cout << "\nAvailable Rooms:\n";
    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].isAvailable) {
            cout << "Room Number: " << rooms[i].roomNumber 
                 << ", Type: " << rooms[i].roomType << endl;
        }
    }
}

void makeReservation() {
    int roomNumber;
    cout << "Enter Room Number to reserve: ";
    cin >> roomNumber;

    int roomIndex = -1;
    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].roomNumber == roomNumber && rooms[i].isAvailable) {
            roomIndex = i;
            break;
        }
    }

    if (roomIndex == -1) {
        cout << "Room not available or does not exist.\n";
        return;
    }

    cout << "Enter Customer Name: ";
    cin.ignore();
    getline(cin, reservations[reservationCount].customerName);
    reservations[reservationCount].roomNumber = roomNumber;
    cout << "Enter Check-In Date (YYYYMMDD): ";
    cin >> reservations[reservationCount].checkInDate;
    cout << "Enter Check-Out Date (YYYYMMDD): ";
    cin >> reservations[reservationCount].checkOutDate;

    rooms[roomIndex].isAvailable = false;
    reservationCount++;
    cout << "Reservation made successfully!\n";
}

void checkIn() {
    int roomNumber;
    cout << "Enter Room Number for Check-In: ";
    cin >> roomNumber;

    for (int i = 0; i < reservationCount; i++) {
        if (reservations[i].roomNumber == roomNumber) {
            cout << "Check-In successful for " << reservations[i].customerName << "!\n";
            return;
        }
    }
    cout << "No reservation found for this room number.\n";
}

void checkOut() {
    int roomNumber;
    cout << "Enter Room Number for Check-Out: ";
    cin >> roomNumber;

    int reservationIndex = -1;
    for (int i = 0; i < reservationCount; i++) {
        if (reservations[i].roomNumber == roomNumber) {
            reservationIndex = i;
            break;
        }
    }

    if (reservationIndex == -1) {
        cout << "No reservation found for this room number.\n";
        return;
    }

    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].roomNumber == roomNumber) {
            rooms[i].isAvailable = true;
            break;
        }
    }

    // Shift reservations to remove the checked-out reservation
    for (int i = reservationIndex; i < reservationCount - 1; i++) {
        reservations[i] = reservations[i + 1];
    }
    reservationCount--;

    cout << "Check-Out successful!\n";
}

void viewReservations() {
    cout << "\nCurrent Reservations:\n";
    for (int i = 0; i < reservationCount; i++) {
        cout << "Room Number: " << reservations[i].roomNumber 
             << ", Customer: " << reservations[i].customerName 
             << ", Check-In Date: " << reservations[i].checkInDate 
             << ", Check-Out Date: " << reservations[i].checkOutDate << endl;
    }
}

int main() {
    int choice;
    while (true) {
        cout << "\nHotel Reservation System\n";
        cout << "1. Add Room\n";
        cout << "2. Display Rooms\n";
        cout << "3. Make Reservation\n";
        cout << "4. Check-In\n";
        cout << "5. Check-Out\n";
        cout << "6. View Reservations\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addRoom();
                break;
            case 2:
                displayRooms();
                break;
            case 3:
                makeReservation();
                break;
            case 4:
                checkIn();
                break;
            case 5:
                checkOut();
                break;
            case 6:
                viewReservations();
                break;
            case 7:
                cout << "Exiting the system.\n";
                return 0;
            default:
                cout << "Invalid choice, please try again.\n";
        }
    }
    return 0;
}
