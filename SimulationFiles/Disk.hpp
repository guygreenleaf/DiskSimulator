//
// Created by Guy on 11/10/2020.
//

#ifndef DISKSIM_X_DISK_HPP
#define DISKSIM_X_DISK_HPP

#include <stdlib.h>
#include <string>
#include "../CommonFiles/Queue.hpp"
#include "../EventDriver/EventQueue.hpp"
#include "../EventDriver/EventNode.hpp"
#include "../EventDriver/DiskDoneEvent.hpp"
#include "../EventDriver/QueueReport.hpp"

class EventQueue;
class DiskDoneEvent;

class Disk{
public:
    //A disk is id'd by its wait-queue and the name of the disk -- FCFS, ST, etc.
     Disk(Queue *waitQueue, std::string nameOfThisDisk);
    //Return type is our decision for this:
     void processRequest(Request *req, EventQueue *evQueue);
     QueueReport *processDiskDone(Request *req, EventQueue *evQueue, DiskDoneEvent *ddone);

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

    float getMaxTimeInSys();

    float getMinTimeInSys();

    float getAvgTimeInSys();

    float getMinWaitTime();

    float getMaxWaitTime();

    float getAvgWaitTime();

    float getMinServTime();
    float getMaxServeTime();
    float getAvgServeTime();
    void findMaxInQueue();
    float getMaxInQueue();
    int getReqTrackNumber(int reqNumber);
    int getTotalReqProcessed();
    void addCumulativeRequests();
    float getAvgRequests();

    void setDDoneNext(DiskDoneEvent *ddevent);

    DiskDoneEvent *getDDoneNext();

private:
    bool isProcessing;
    int track, sector;
    int reqTrackNumber;
    Queue *waitQueue;
    std::string nameOfDisk;

    int numJobs;

    int numTimers;

    float maxTimeInSys=0, minTimeInSys=0, avgTimeInSys=0;
    float minWaitTime=0, maxWaitTime=0, avgWaitTime;
    float maxNumInQueue=0, avgNumInWaitQueue;
    float currTimeInSys = 0;

    float maxServeTime=0, minServeTime, avgServeTime=0;

    int totalRequestsProcessed = 0;
    float cumulativeTimeInSystem = 0;
    float cumulativeWaitTime = 0;
    float cumulativeServiceTime = 0;
    float cumulativeRequestsProcessed = 0;

    int trackReqNum = 0;


    DiskDoneEvent *ddoneNext;



};

#endif //DISKSIM_X_DISK_HPP
