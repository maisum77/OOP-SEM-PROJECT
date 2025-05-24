#include<iostream>
#include<string>
using namespace std;

class Room {
    int roomID;
public:
    Room() {
        roomID = 1;
    }
    void setRoomID(int id) {
        roomID = id;
    }
    void showRoom() {
        cout << "Room ID: " << roomID << endl;
    }
};

class Floor {
    int floorNumber;
    Room rooms[50]; // Max 50 rooms per floor
    int roomCount;
public:
    Floor(int floorNum, int numRooms) {
        floorNumber = floorNum;
        roomCount = numRooms;
        for (int i = 0; i < roomCount; i++) {
            rooms[i].setRoomID(floorNumber * 100 + i + 1);  //formula to increase the room ids
        }
    }

    void showFloor() {
        cout << "Floor " << floorNumber << " has " << roomCount << " rooms:\n";
        for (int i = 0; i < roomCount; i++) {
            rooms[i].showRoom();
        }
    }
};

class Building {
    Floor* floors[10]; // Max 10 floors
    int floorCount;
public:
    Building(int noOfFloors, int roomsPerFloor[]) {
        floorCount = noOfFloors;
        for (int i = 0; i < floorCount; i++) {
            floors[i] = new Floor(i + 1, roomsPerFloor[i]);
        }
    }

    void showBuilding() {
        for (int i = 0; i < floorCount; i++) {
            floors[i]->showFloor();
            cout << "-----------------------------\n";
        }
    }
};

int main() {
    int roomsPerFloor[7] = {10, 20, 30, 20, 40, 2, 10}; // example: 7 floors
    Building b(7, roomsPerFloor);
    b.showBuilding();
    return 0;
}
