//
// Created by yaweh on 11/10/2020.
//

#ifndef DISKSIM_X_DISKDONEEVENT_HPP
#define DISKSIM_X_DISKDONEEVENT_HPP
#include <string>
#include <cstdlib> //Included to use abs() for dist calcs
#include "../CommonFiles/Request.hpp"
#include "../SimulationFiles/Disk.hpp"
#include "../EventDriver/EventQueue.hpp"
#include "../EventDriver/EventNode.hpp"

//class Request;
class Disk;
class EventQueue;

class DiskDoneEvent{
public:
    DiskDoneEvent(float currTime, Request *req, Disk *currDisk);

    float sectorDistance(Request *req, Disk *currDisk);

    float getTimeDone(){
        return timeDone;
    }

    std::string getType(){return queueType;}

private:
    float timeDone;
    std::string queueType;
};
#endif //DISKSIM_X_DISKDONEEVENT_HPP
