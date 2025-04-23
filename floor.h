#pragma once
#include <vector>
#include <string>

//Room Types
enum class RoomType {
    Rest,
    Spawner,
    Trader,
    Elite,
    Boss,
    Chest,
    NextFloor
};

//Room Struct
struct Room {
    RoomType type;
    std::string description;
    bool isRoomCompleted = true;
};

//Floor class
class Floor {
    public:
        Floor(int floorNumber);

        const std::vector<Room>& getRooms() const;
        const Room& getCurrentRoom() const;
        int getFloorNumber() const;
        int getCurrentRoomNumber() const;
        RoomType getRoomType(int currentRoom) const;
        std::string getRoomDesc(int currentRoom) const;
        void moveForward();
        void setRoomComplete();

    private:
        int currentRoom = 0;
        int floorNumber;
        std::vector<Room> rooms;

        void generateRooms();
        void clearRooms();
        void nextFloor();
};
