//
// Created by Guy on 11/10/2020.
//

#ifndef DISKSIM_X_DISKDONEEVENT_HPP
#define DISKSIM_X_DISKDONEEVENT_HPP
#include <string>
#include <cstdlib> //Included to use abs() for dist calcs
#include "../CommonFiles/Request.hpp"
#include "../SimulationFiles/Disk.hpp"
#include "../EventDriver/EventQueue.hpp"
#include "../EventDriver/EventNode.hpp"


class Disk;
class EventQueue;

class DiskDoneEvent{
public:
    DiskDoneEvent(float currTime, Request *req, Disk *currDisk);

//    DiskDoneEvent(float theTime, Request *requ, int track, int sector);

    float sectorDistance(Request *req, Disk *currDisk);
//    float sectorDistance2(Request *requ, int sector);
    float getTimeDone(){
        return timeDone;
    }

    std::string getType(){return queueType;}

private:
    float timeDone;
    std::string queueType;
};
#endif //DISKSIM_X_DISKDONEEVENT_HPP
