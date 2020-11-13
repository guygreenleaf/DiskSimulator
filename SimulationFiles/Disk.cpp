//
// Created by yaweh on 11/10/2020.
//

#include "Disk.hpp"
#include <cmath>


Disk::Disk(Queue *wait, std::string nameOfThisDisk){
    waitQueue = wait;
    nameOfDisk = nameOfThisDisk;
    track = 0;
    sector = 0;
    isProcessing = false;
    numJobs = 0;
    numTimers = 0;
}

int Disk::getnumJobs(){
    return numJobs;
}

void Disk::setnumJobs(int newSize){
    numJobs = newSize + numJobs;
}

int Disk::getnumTimers(){
    return numTimers;
}

void Disk::setnumTimers(){
    numTimers++;
}

std::string Disk::getName(){
    return nameOfDisk;
}

int Disk::getTrack(){
    return track;
}

int Disk::getSector(){
    return sector;
}

Queue *Disk::accessWaitQueue(){
    return waitQueue;
}

bool Disk::getState() {
    return isProcessing;

}

void Disk::setState(bool set) {
    isProcessing = set;
}


void Disk::processRequest(Request *req, EventQueue *evQueue) {
    totalRequestsProcessed++;


    if(accessWaitQueue()->empty() && !getState()){
        numJobs++;
        evQueue->setTime(req->time());
        DiskDoneEvent *newDDone = new DiskDoneEvent(evQueue->getTime(), req, this);
        evQueue->addDiskDoneEvent(newDDone);
        if(track == 0 && sector == 0){
            minWaitTime = evQueue->getTime() - req->time();
        }

        cumulativeTimeInSystem = cumulativeTimeInSystem + newDDone->getTimeDone() - req->time();


        if(minWaitTime > evQueue->getTime() - req->time()){
            minWaitTime = evQueue->getTime() - req->time();
        }
        if(maxWaitTime < evQueue->getTime() - req->time()){
            maxWaitTime = evQueue->getTime() - req->time();
        }


        if(newDDone->getTimeDone() - req->time() > maxTimeInSys){
            maxTimeInSys = newDDone->getTimeDone()-req->time();

        }

        if(minTimeInSys == 0){
            minTimeInSys = newDDone->getTimeDone() - req->time();
        }

        if(minTimeInSys > newDDone->getTimeDone() - req->time()){
            minTimeInSys = newDDone->getTimeDone() - req->time();
        }

        if(maxServeTime < maxTimeInSys - maxWaitTime){
            maxServeTime = maxTimeInSys - maxWaitTime;
        }

        if(track == 0 && sector ==0){
            minServeTime = (newDDone->getTimeDone() - req->time()) - (req->time() - evQueue->getTime());
        }

//        if(minServeTime > (newDDone->getTimeDone() - req->time()) - (evQueue->getTime() - req->time())){
//            minServeTime = (newDDone->getTimeDone() - req->time()) - (req->time() - evQueue->getTime());
//        }


        track = req->track();
        sector = req->sector()+1;

//        evQueue->setTime(req->time());
        setState(true);
    }
    else if(getState()){
        accessWaitQueue()->addRequest(req, track, sector);
        numJobs++;
        evQueue->setTime(req->time());
    }
}

void Disk::processDiskDone(Request *req, EventQueue *evQueue, DiskDoneEvent *ddone) {
    setState(false);

    if(ddone->getTimeDone() >= evQueue->getTime()) {
        evQueue->setTime(ddone->getTimeDone());
    }

    if(!accessWaitQueue()->empty()){
        Request *processedRequest = accessWaitQueue()->getRequest();

        DiskDoneEvent *newDDone = new DiskDoneEvent(evQueue->getTime(), processedRequest, this);
        cumulativeTimeInSystem = cumulativeTimeInSystem + newDDone->getTimeDone() - processedRequest->time();
        cumulativeWaitTime = cumulativeWaitTime + evQueue->getTime() - processedRequest->time();

        if(newDDone->getTimeDone()-processedRequest->time() > maxTimeInSys){
            maxTimeInSys = newDDone->getTimeDone() - processedRequest->time();
        }

        if(maxWaitTime < evQueue->getTime() - processedRequest->time()){
            maxWaitTime = evQueue->getTime() - processedRequest->time();
        }

        if(minTimeInSys == 0){
            minTimeInSys = newDDone->getTimeDone() - processedRequest->time();
        }

        if(minTimeInSys > newDDone->getTimeDone() - processedRequest->time()){
            minTimeInSys = newDDone->getTimeDone() - processedRequest->time();
        }



        if(maxServeTime < maxTimeInSys - maxWaitTime){
            maxServeTime = maxTimeInSys - maxWaitTime;
        }

//        if(track == 0 && sector ==0){
//            minServeTime = maxTimeInSys - maxWaitTime;
//        }

//        if(minServeTime > (newDDone->getTimeDone() - processedRequest->time()) - (evQueue->getTime() - processedRequest->time())){
//            minServeTime = (newDDone->getTimeDone() - processedRequest->time()) - (processedRequest->time() - evQueue->getTime());
//        }
//       LEFT OFF HERE FIGURE THIS SHIT OUT HOMEBOY
        if(minServeTime > maxTimeInSys - maxWaitTime){
            minServeTime = maxTimeInSys - maxWaitTime;
        }

        evQueue->addDiskDoneEvent(newDDone);

        track = processedRequest->track();
        sector = processedRequest->sector() +1 ;
        numJobs--;


//        evQueue->setTime(accessWaitQueue()->getRequest()->time());
        setState(true);
    }
    else if (accessWaitQueue()->empty() && isProcessing){
        setState(false);
//        numJobs = 0;
    }
    else if(accessWaitQueue()->empty() && !isProcessing){
        numJobs = 0;
    }
    avgTimeInSys = cumulativeTimeInSystem / totalRequestsProcessed;
}

void Disk::hasJob() {
    if(isProcessing){
        numJobs++;
    }
}

float Disk:: getMaxTimeInSys(){
    return maxTimeInSys;
}

float Disk::getMinTimeInSys() {
    return minTimeInSys;
}

float Disk::getAvgTimeInSys() {
    return avgTimeInSys;
}


float Disk::getMinWaitTime() {
    return  minWaitTime;
}

float Disk::getMaxWaitTime() {
    return maxWaitTime;
}

float Disk::getAvgWaitTime() {
    avgWaitTime = cumulativeWaitTime/totalRequestsProcessed;
    return avgWaitTime;
}