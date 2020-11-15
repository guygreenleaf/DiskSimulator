//
// Created by Guy on 11/11/2020.
//

#include "DiskDoneEvent.hpp"
#include <cstdlib>

DiskDoneEvent:: DiskDoneEvent(float currTime, Request *req, Disk *currDisk){
    timeDone = ((abs(req->track() - currDisk->getTrack())) * 3) + (sectorDistance(req, currDisk)* 0.1) + 0.1 + currTime;
    queueType = currDisk->getName();
 }

// DiskDoneEvent:: DiskDoneEvent(float theTime, Request *requ, int track, int sector){
//    timeDone = ((abs(requ->track()-track))*3) + (sectorDistance2(requ,sector) *0.1) + 0.1 + theTime;
//}



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

//float DiskDoneEvent::sectorDistance2(Request *requ, int sector){
//    float rotDist = 0;
//    float currSect = sector;
//    float reqSect = requ->sector();
//
//    while(currSect != reqSect){
//        if(currSect == 30){
//            currSect = 0;
//            rotDist++;
//            continue;
//        }
//        currSect++;
//        rotDist++;
//    }
//    return rotDist;
//}