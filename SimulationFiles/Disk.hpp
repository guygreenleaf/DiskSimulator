//
// Created by yaweh on 11/10/2020.
//

#ifndef DISKSIM_X_DISK_HPP
#define DISKSIM_X_DISK_HPP

#include <stdlib.h>
#include <string>
#include "../CommonFiles/Queue.hpp"
#include "../EventDriver/EventQueue.hpp"
#include "../EventDriver/EventNode.hpp"
#include "../EventDriver/DiskDoneEvent.hpp"

class EventQueue;

class Disk{
public:
    //A disk is id'd by its wait-queue and the name of the disk -- FCFS, ST, etc.
     Disk(Queue *waitQueue, std::string nameOfThisDisk);
    //Return type is our decision for this:
     void processRequest(Request *req, EventQueue *evQueue);
     void processDiskDone();

     std::string getName();
     int getTrack();
     int getSector();
     Queue *accessWaitQueue();

     void setState(bool set);
     bool getState();


private:
    bool isProcessing;
    int track, sector;
    Queue *waitQueue;
    std::string nameOfDisk;
};

#endif //DISKSIM_X_DISK_HPP
