//
// Created by yaweh on 11/13/2020.
//


#include "QueueReport.hpp"


QueueReport::QueueReport(int numInQueueOrder, int track, int sector, float entry, float initTime, float complete, float waitTime, float servTime, float timeInSys){
    numInQueue = numInQueueOrder;
    trac = track;
    sec = sector;
    entr = entry;
    init = initTime;
    comp = complete;
    wait = waitTime;
    serv = servTime;
    timInSys = timeInSys;
}

