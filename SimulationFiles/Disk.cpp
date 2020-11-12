//
// Created by yaweh on 11/10/2020.
//

#include "Disk.hpp"


Disk::Disk(Queue *wait, std::string nameOfThisDisk){
    waitQueue = wait;
    nameOfDisk = nameOfThisDisk;
    track = 0;
    sector = 0;
    isProcessing = false;
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

    if(accessWaitQueue()->empty() && !getState()){
        evQueue->setTime(req->time());
        DiskDoneEvent *newDDone = new DiskDoneEvent(evQueue->getTime(), req, this);
        evQueue->addDiskDoneEvent(newDDone);
        track = req->track();
        sector = req->sector()+1;
        evQueue->setTime(req->time());
        setState(true);
    }
    else if(getState()){
        accessWaitQueue()->addRequest(req, track, sector);
    }
}

void Disk::processDiskDone() {
    setState(false);
}

