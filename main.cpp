#include<iostream>
#include<string>
using namespace std;
class Room //room class is done
{
    protected:
    int roomID;
    bool isExit;
    bool occupy;
    public:
    Room() // set room id when object is created
    {
        roomID = 1;
        isExit=false;
        occupy=false;
    }
    void setRoomID(int id) // setter
    {
        roomID = id;
    }
    int showRoomId()
    {
        return roomID;
    }
    void showRoom() //getter
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
        if (occupy)
        {
            cout << " - Occupied";
        }
        else
        {
            cout << " - Empty";
        }
        cout << endl; 
    }
    void setIsExit(bool exitStatus)
    {
        isExit = exitStatus;
    }
    void SetIsOccupy(bool status)
    {
        occupy=status;
    }
    

};
class Floor 
{
   protected:
    int floor_num;
    int room_num;
    Room r[50] ;// max 50 rooom per floor
    public:
    Floor(int no_of_floor,int no_of_rooms_per_floor)
    {
        floor_num=no_of_floor;
        room_num=no_of_rooms_per_floor;
        for(int i=0;i<=room_num;i++)
        {
            r[i].setRoomID(floor_num * 100 + i + 1);// give id to all the rooms with formula

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
    void showFloor() {
        cout << "Floor " << floor_num << " has " << room_num << " rooms:\n";
        for (int i = 0; i < room_num; i++) {
            r[i].showRoom();
            
        }
    }
    //how many room --done
    //exit make after room are created 
    //condition after 10 room there are exist
    
};
class building
{
    protected:
    Floor* f[10];
    int floor_count;
    public:
    building(int num_of_floor,int no_of_room[])
    {
        floor_count=num_of_floor;
        for (int i = 0; i < num_of_floor; i++) {
            f[i] = new Floor(i + 1, no_of_room[i]);
        }
        
    }
    void occupy_room(int a )
    {
        
     
    }
    //how many floor
    //
    void showBuilding() {
        for (int i = 0; i < floor_count; i++) {
            f[i]->showFloor();
            cout << "-----------------------------\n";
        }
    }
   
};
int main() {
    int roomsPerFloor[7] = {10, 20, 30, 20, 40, 2, 10}; 
    building b(7, roomsPerFloor);
    b.showBuilding();
    return 0;
}