//
// Created by Guy on 11/13/2020.
//

#ifndef DISKSIM_X_QUEUEREPORT_HPP
#define DISKSIM_X_QUEUEREPORT_HPP

class QueueReport{
public:
    QueueReport(int numInQueueOrder, int track, int sector, float entry, float initTime, float complete, float waitTime, float servTime, float timeInSys);
    QueueReport();


    float comp;
    int trac;
    int sec;
    int numInQueue;
    float entr;
    float init;
    float wait;
    float serv;
    float timInSys;

};

#endif //DISKSIM_X_QUEUEREPORT_HPP
