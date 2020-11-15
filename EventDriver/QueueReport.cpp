//
// Created by Guy on 11/13/2020.
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
QueueReport::QueueReport(){
    numInQueue = 0;
    trac = 0;
    sec = 0;
    entr = 0;
    init = 0;
    comp = 0;
    wait = 0;
    serv = 0;
    timInSys = 0;
};

