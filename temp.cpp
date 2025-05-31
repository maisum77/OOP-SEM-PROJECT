#include<iostream>
#include<string>
#include<cmath> // Required for abs() function
#include<limits> // Required for numeric_limits

using namespace std;

// Room class represents individual rooms in the building.
class Room
{
protected:
    int roomID;      // Unique identifier for the room.
    bool isExit;     // Flag to indicate if this room is an exit.
    bool isOccupied; // Flag to indicate if this room is occupied.

public:
    // Default constructor: Initializes roomID to 1, isExit to false, and isOccupied to false.
    Room()
    {
        roomID = 1;
        isExit = false;
        isOccupied = false; // Room is empty by default.
    }

    // Setter for roomID: Assigns a new ID to the room.
    void setRoomID(int id)
    {
        roomID = id;
    }

    // Setter for isExit: Sets the exit status of the room.
    void setIsExit(bool exitStatus)
    {
        isExit = exitStatus;
    }

    // Method to attempt to occupy the room.
    // Returns true if successfully occupied, false if already taken.
    bool occupy() {
        if (!isOccupied) { // Check if the room is currently empty.
            isOccupied = true; // Mark as occupied.
            return true;       // Successfully occupied.
        }
        return false; // Room is already occupied.
    }

    // Getter for room information: Displays the room ID, exit status, and occupation status.
    void showRoom()
    {
        if (isExit)
        {
            cout << "Exit (Room ID: " << roomID << ")";
        }
        else
        {
            cout << "Room ID: " << roomID;
        }

        // Display occupation status.
        if (isOccupied)
        {
            cout << " - Occupied";
        }
        else
        {
            cout << " - Empty";
        }
        cout << endl; // Newline after each room's information.
    }

    // Getter for roomID.
    int getRoomID() const {
        return roomID;
    }

    // Getter for occupation status.
    bool getIsOccupied() const {
        return isOccupied;
    }

    // Getter for exit status.
    bool getIsExit() const {
        return isExit;
    }
};

// Floor class represents a single floor in the building, containing multiple rooms.
class Floor
{
protected:
    int floor_num; // The floor number.
    int room_num;  // The number of rooms on this floor.
    Room r[50];    // An array to store up to 50 Room objects (max rooms per floor).

public:
    // Constructor for Floor: Initializes floor number and creates rooms.
    // It also assigns room IDs and sets exit points based on specified conditions.
    Floor(int no_of_floor, int no_of_rooms_per_floor)
    {
        floor_num = no_of_floor;
        room_num = no_of_rooms_per_floor;

        // Loop through and initialize each room on the floor.
        for (int i = 0; i < room_num; i++)
        {
            // Assign a unique room ID based on floor number and room index.
            r[i].setRoomID(floor_num * 100 + i + 1);

            // Determine if the current room should be an exit.
            if (i == 0 || i == room_num - 1 || (i + 1) % 10 == 0)
            {
                r[i].setIsExit(true); // Mark as an exit.
            }
            else
            {
                r[i].setIsExit(false); // Otherwise, it's a regular room.
            }
        }
    }

    // Displays all rooms on the current floor, indicating exits and occupation status.
    void showFloor()
    {
        cout << "Floor " << floor_num << " has " << room_num << " rooms:\n";
        for (int i = 0; i < room_num; i++)
        {
            r[i].showRoom(); // Call showRoom for each room.
        }
    }

    // Method to get a room by its local index within the floor.
    // Returns a pointer to the Room object, or nullptr if the index is out of bounds.
    Room* getRoomByIndex(int index) {
        if (index >= 0 && index < room_num) {
            return &r[index];
        }
        return nullptr; // Return nullptr if index is out of bounds.
    }

    // Method to get the number of rooms on this floor.
    int getRoomCount() const {
        return room_num;
    }

    // Getter for floor_num.
    int getFloorNum() const {
        return floor_num;
    }
};

// Building class represents the entire building, composed of multiple floors.
class building
{
protected:
    Floor* f[10];      // An array of pointers to Floor objects (max 10 floors).
    int floor_count;   // The actual number of floors in the building.

    // Helper method to find a room by its ID.
    // Returns a pointer to the Room object if found, nullptr otherwise.
    Room* findRoomByID(int targetRoomID) {
        for (int i = 0; i < floor_count; i++) {
            for (int j = 0; j < f[i]->getRoomCount(); j++) {
                Room* currentRoom = f[i]->getRoomByIndex(j);
                if (currentRoom != nullptr && currentRoom->getRoomID() == targetRoomID) {
                    return currentRoom; // Room found.
                }
            }
        }
        return nullptr; // Room not found.
    }

    // Helper method to find the nearest exit for a given room ID.
    // Returns the roomID of the nearest exit, or -1 if no exits are found.
    int findNearestExit(int currentRoomID) {
        int nearestExitID = -1;
        int minDistance = numeric_limits<int>::max(); // Initialize with a very large number.

        for (int i = 0; i < floor_count; i++) {
            for (int j = 0; j < f[i]->getRoomCount(); j++) {
                Room* potentialExit = f[i]->getRoomByIndex(j);
                if (potentialExit != nullptr && potentialExit->getIsExit()) {
                    // Calculate simple numerical distance between room IDs.
                    int distance = abs(currentRoomID - potentialExit->getRoomID());
                    if (distance < minDistance) {
                        minDistance = distance;
                        nearestExitID = potentialExit->getRoomID();
                    }
                }
            }
        }
        return nearestExitID;
    }

public:
    // Constructor for building: Initializes the building with a specified number of floors
    // and the number of rooms for each floor.
    building(int num_of_floor, int no_of_room[])
    {
        floor_count = num_of_floor;
        // Dynamically create Floor objects for each floor.
        for (int i = 0; i < num_of_floor; i++)
        {
            f[i] = new Floor(i + 1, no_of_room[i]);
        }
    }

    // Destructor to free dynamically allocated memory for Floor objects.
    ~building() {
        for (int i = 0; i < floor_count; i++) {
            delete f[i]; // Free memory for each Floor object.
            f[i] = nullptr; // Set pointer to nullptr after deletion.
        }
    }

    // Displays all floors and their rooms within the building.
    void showBuilding()
    {
        for (int i = 0; i < floor_count; i++)
        {
            f[i]->showFloor(); // Call showFloor for each floor.
            cout << "-----------------------------\n"; // Separator for readability.
        }
    }

    // Method to occupy a specific room by its roomID.
    // This method now delegates the 'occupy' logic to the Room class.
    bool occupyRoom(int targetRoomID) {
        Room* roomToOccupy = findRoomByID(targetRoomID); // Use the helper method to find the room.

        if (roomToOccupy != nullptr) { // Check if the room was found.
            if (roomToOccupy->occupy()) { // Let the Room object handle the occupancy logic.
                cout << "Room ID: " << targetRoomID << " successfully occupied." << endl;
                return true; // Room occupied successfully.
            } else {
                // The Room reported it's already occupied.
                cout << "Room ID: " << targetRoomID << " is already occupied." << endl;
                return false; // Room already occupied.
            }
        } else {
            cout << "Room ID: " << targetRoomID << " not found." << endl;
            return false; // Room not found.
        }
    }

    // NEW: Method to handle an evacuation event.
    // For each occupied room, it finds and suggests the nearest exit.
    void handleEvacuation() {
        cout << "\n--- Evacuation Event Initiated ---\n";
        bool evacuatedAny = false;

        for (int i = 0; i < floor_count; i++) {
            for (int j = 0; j < f[i]->getRoomCount(); j++) {
                Room* currentRoom = f[i]->getRoomByIndex(j);
                if (currentRoom != nullptr && currentRoom->getIsOccupied()) {
                    int nearestExit = findNearestExit(currentRoom->getRoomID());
                    if (nearestExit != -1) {
                        cout << "Room " << currentRoom->getRoomID()
                             << " (Occupied) should evacuate to Exit " << nearestExit << "." << endl;
                        evacuatedAny = true;
                    } else {
                        cout << "Room " << currentRoom->getRoomID()
                             << " (Occupied) - No exit found!" << endl;
                    }
                }
            }
        }

        if (!evacuatedAny) {
            cout << "No occupied rooms to evacuate." << endl;
        }
        cout << "--- Evacuation Event Concluded ---\n";
    }
};

// Main function where the program execution begins.
int main()
{
    // Define the number of rooms for each floor.
    int roomsPerFloor[7] = {10, 20, 30, 20, 40, 2, 10};
    
    // Create a building object with 7 floors using the defined room counts.
    building b(7, roomsPerFloor);

    int choice;
    do {
        cout << "\n--- Building Management Menu ---\n";
        cout << "1. Show Building State\n";
        cout << "2. Occupy a Room\n";
        cout << "3. Trigger Evacuation\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                b.showBuilding();
                break;
            case 2: {
                int roomIDToOccupy;
                cout << "Enter Room ID to occupy: ";
                cin >> roomIDToOccupy;
                b.occupyRoom(roomIDToOccupy);
                break;
            }
            case 3:
                b.handleEvacuation();
                break;
            case 4:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0; // Indicate successful program execution.
}
