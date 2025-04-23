#include "floor.h"
#include <cstdlib>
#include <algorithm>
#include <random>
#include <ctime>

Floor::Floor(int floorNum)
    : floorNumber(floorNum) {
    clearRooms();
    generateRooms();
}

const std::vector<Room>& Floor::getRooms() const {
    return rooms;
}

int Floor::getFloorNumber() const {
    return floorNumber;
}

int Floor::getCurrentRoomNumber() const {
    return currentRoom;
}

RoomType Floor::getRoomType(int roomNumber) const {
    return rooms[roomNumber].type;
}

std::string Floor::getRoomDesc(int roomNumber) const {
    return rooms[roomNumber].description;
}

void Floor::generateRooms() {

    rooms.push_back({ RoomType::Rest, "Don't you dare go Hollow... ", true});

    int numberOfRooms = static_cast<int>(floorNumber * 1.5) + 1;
    std::vector<Room> randomRooms;

    if (floorNumber % 5 == 0) {
        rooms.push_back({ RoomType::Boss, "A terrifying presence awaits...", true});
        rooms.push_back({ RoomType::Chest, "Reward for defeating the terrifying presence...", true});
    } else {
        for (int i = 1;i < numberOfRooms; i++) {
            int rng = rand() % 100;

            if (rng < 90) {
                randomRooms.push_back({ RoomType::Spawner, "Room filled with enemies that want you dead...", false});
            } else {
                int srng = rand() % 2;
                if (srng == 0) {
                    randomRooms.push_back({ RoomType::Elite, "Enemies That are Sure to kill you...", true});
                } else {
                    randomRooms.push_back({ RoomType::Trader, "Mysterious Trader that want to sell you his treasures...", true});
                }
            }
        }
        // Shuffle rooms
        std::shuffle(randomRooms.begin(), randomRooms.end(), std::default_random_engine(static_cast<unsigned>(std::time(nullptr))));

        // Add shuffled rooms
        rooms.insert(rooms.end(), randomRooms.begin(), randomRooms.end());
    }
    rooms.push_back({ RoomType::NextFloor, "Your ticket to next floor...", true});
}

void Floor::setRoomComplete() {
    rooms[currentRoom].isRoomCompleted = true;
}

void Floor::moveForward() {
    if (rooms[currentRoom].isRoomCompleted && currentRoom + 1 < rooms.size()) {
        currentRoom++;
    } else if (rooms[currentRoom].type == RoomType::NextFloor && rooms[currentRoom].isRoomCompleted) {
        nextFloor();
    }
}

void Floor::nextFloor() {
    floorNumber++;
    clearRooms();
    generateRooms();
    currentRoom = 0;
}

const Room& Floor::getCurrentRoom() const {
    return rooms[currentRoom];
}

void Floor::clearRooms() {
    rooms.clear();
}