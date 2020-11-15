//
// Created by Guy on 11/10/2020.
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

        accessWaitQueue()->incReqTracker();
        req->setTracker(accessWaitQueue()->getReqTracker());


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


        if((newDDone->getTimeDone() - req->time()) - (evQueue->getTime() - req->time()) < minServeTime ){
            minServeTime = (newDDone->getTimeDone() - req->time()) - (evQueue->getTime() - req->time());
        }
        cumulativeServiceTime = cumulativeServiceTime + (newDDone->getTimeDone() - req->time()) - (evQueue->getTime() - req->time());
        findMaxInQueue();


        track = req->track();
        sector = req->sector()+1;


        setState(true);
    }
    else if(getState()){
        accessWaitQueue()->addRequest(req, track, sector);
        numJobs++;

        findMaxInQueue();
        evQueue->setTime(req->time());
    }
}

QueueReport *Disk::processDiskDone(Request *req, EventQueue *evQueue, DiskDoneEvent *ddone) {
    QueueReport *Reporter = new QueueReport();

    setState(false);

    if(ddone->getTimeDone() >= evQueue->getTime()) {
        evQueue->setTime(ddone->getTimeDone());
    }

    if(!accessWaitQueue()->empty()){
        Reporter->init = evQueue->getTime();

        Request *processedRequest = accessWaitQueue()->getRequest();

        Reporter->numInQueue = processedRequest->reqTracker;
        Reporter->trac = processedRequest->track();
        Reporter->sec = processedRequest->sector();
        Reporter->entr = processedRequest->time();

        DiskDoneEvent *newDDone = new DiskDoneEvent(evQueue->getTime(), processedRequest, this);
        cumulativeTimeInSystem = cumulativeTimeInSystem + newDDone->getTimeDone() - processedRequest->time();
        cumulativeWaitTime = cumulativeWaitTime + evQueue->getTime() - processedRequest->time();

        Reporter->comp = newDDone->getTimeDone();
        Reporter->timInSys = Reporter->comp - Reporter->entr;
        Reporter->wait = Reporter->init - Reporter->entr;
        Reporter->serv = Reporter->comp - Reporter->init;





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

        if((newDDone->getTimeDone() - processedRequest->time()) - (evQueue->getTime() - processedRequest->time()) < minServeTime ){
            minServeTime = (newDDone->getTimeDone() - processedRequest->time()) - (evQueue->getTime() - processedRequest->time());
        }
        cumulativeServiceTime = cumulativeServiceTime + (newDDone->getTimeDone() - processedRequest->time()) - (evQueue->getTime() - processedRequest->time());
        findMaxInQueue();

        evQueue->addDiskDoneEvent(newDDone);

        track = processedRequest->track();
        sector = processedRequest->sector() +1 ;
        numJobs--;

        setState(true);
    }
    else if (accessWaitQueue()->empty() && isProcessing){
        setState(false);

    }
    else if(accessWaitQueue()->empty() && !isProcessing){
        numJobs = 0;
    }
    findMaxInQueue();
    avgTimeInSys = cumulativeTimeInSystem / totalRequestsProcessed;

    return Reporter;
}

void Disk:: findMaxInQueue(){
    if(getnumJobs() > maxNumInQueue){
        maxNumInQueue = getnumJobs();
    }
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
float Disk::getMinServTime(){
    return minServeTime;
}
float Disk::getMaxServeTime(){
    return maxServeTime;
}
float Disk::getAvgServeTime(){
    avgServeTime = cumulativeServiceTime / totalRequestsProcessed;
    return avgServeTime;
}

float Disk::getAvgWaitTime() {
    avgWaitTime = cumulativeWaitTime/totalRequestsProcessed;
    return avgWaitTime;
}

float Disk::getMaxInQueue() {
    return maxNumInQueue;
}

void Disk::addCumulativeRequests(){
    cumulativeRequestsProcessed = cumulativeRequestsProcessed + numJobs;
}

float Disk::getAvgRequests(){
    avgNumInWaitQueue = cumulativeRequestsProcessed/numTimers;
    return avgNumInWaitQueue;
}

int Disk::getReqTrackNumber(int reqNumber){
    reqTrackNumber = reqNumber;
    return reqTrackNumber;

}

int Disk::getTotalReqProcessed(){return totalRequestsProcessed;}

void Disk::setDDoneNext(DiskDoneEvent *ddEvent) {
    ddoneNext = ddEvent;
}

DiskDoneEvent *Disk::getDDoneNext(){
    return ddoneNext;
}