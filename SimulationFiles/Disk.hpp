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
class DiskDoneEvent;

class Disk{
public:
    //A disk is id'd by its wait-queue and the name of the disk -- FCFS, ST, etc.
     Disk(Queue *waitQueue, std::string nameOfThisDisk);
    //Return type is our decision for this:
     void processRequest(Request *req, EventQueue *evQueue);
     void processDiskDone(Request *req, EventQueue *evQueue, DiskDoneEvent *ddone);

     std::string getName();
     int getTrack();
     int getSector();
     Queue *accessWaitQueue();

     void setState(bool set);
     bool getState();

    int getnumJobs();

    void setnumJobs(int newSize);

    int getnumTimers();

    void setnumTimers();
    void hasJob();

private:
    bool isProcessing;
    int track, sector;
    Queue *waitQueue;
    std::string nameOfDisk;

    int numJobs;

    int numTimers;

    int maxTimeInSys, minTimeInSys=0, avgTimeInSys;
    int minWaitTime, maxWaitTime, avgWaitTime;
    int maxNumInQueue, avgNumInWaitQueue;

    int totalRequestsProcessed = 0;
    int cumulativeTimeInSystem = 0;

};

#endif //DISKSIM_X_DISK_HPP
