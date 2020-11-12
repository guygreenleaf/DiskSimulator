//
// Created by yaweh on 11/11/2020.
//

#include "DiskDoneEvent.hpp"
#include <cstdlib>

DiskDoneEvent:: DiskDoneEvent(float currTime, Request *req, Disk *currDisk){
    timeDone = (abs(currDisk->getTrack() - req->track()) * 3) + (sectorDistance(req, currDisk)* 0.1) + 0.1 + currTime;
    queueType = currDisk->getName();
}

float DiskDoneEvent::sectorDistance(Request *req, Disk *currDisk){
    float rotDist = 0;
    float currSect = currDisk->getSector();
    float reqSect = req->sector();

    while(currSect != reqSect){
        if(currSect == 30){
            currSect = 0;
            rotDist++;
            continue;
        }
        currSect++;
        rotDist++;
    }
    return rotDist;
}