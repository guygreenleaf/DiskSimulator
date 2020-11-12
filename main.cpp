//
// Created by yaweh on 11/10/2020.
//

#include "CommonFiles/Request.hpp"
#include "SimulationFiles/Disk.hpp"
#include "FCFS_Queue/FCFSQueue.hpp"
#include "ST_Queue/STQueue.hpp"
#include "LookUp_Queue/LookUpQueue.hpp"
#include "CLookUp_Queue/CLookUpQueue.hpp"
#include "PickUp_Queue/PickUpQueue.hpp"
#include "SimulationFiles/Disk.hpp"
#include "EventDriver/EventQueue.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>

std::vector<Request *>generateRequestVector(int argc, char *argv[]){
    std::vector<Request *> reqs;
    int time, track, sector;

    if( argc != 2) {
        std::cout << "usage: " << argv[0] << " nameOfAnInputFile\n";
        exit(1);
    }
    std::ifstream inputStream;
    inputStream.open(argv[1], std::ios::in);
    if( ! inputStream.is_open()) {
        std::cout << "Unable top open " << argv[1] << ". Terminating...";
        perror("Error when attempting to open the input file.");
        exit(1);
    }
    while(inputStream >> time && inputStream >> track && inputStream >> sector) {
        auto *request = new Request(time, track, sector);
        reqs.push_back(request);
    }
    return reqs;
}

int main(int argc, char *argv[]){

    //vector to initially hold requests
    std::vector<Request *> reqVec = generateRequestVector(argc, argv);

    Queue *fcfs = new FCFSQueue();
    Queue *st = new STQueue();
    Queue *pu = new PickUpQueue();
    Queue *lu = new LookUpQueue();
    Queue *clu = new CLookUpQueue();


    //Need to create other disks as well
    Disk *fcfsDisk = new Disk(fcfs, "FCFS");
    Disk *stDisk = new Disk(st, "ST");
    Disk *puDisk = new Disk(pu, "PICKUP");
    Disk *lookupDisk = new Disk(lu, "LOOKUP");
    Disk *clookDisk = new Disk(clu, "CLOOK");

    //This will end up having 5 entries in it.
    std::vector<Disk *> disks;
    disks.push_back(fcfsDisk);
    disks.push_back(stDisk);
    disks.push_back(puDisk);
    disks.push_back(lookupDisk);
    disks.push_back(clookDisk);

    EventQueue *eQueue = new EventQueue();

    Request *testReq = new Request(10, 5, 20);
    TimerEvent *testTimer = new TimerEvent(50);

    //Start of simulation
    eQueue->addRequest(testReq /*add a request to the event queue*/);
    eQueue->addTimerEvent(testTimer);
    eQueue->print();
    std::cout << "Simulation started" << std::endl;
    while(!eQueue->isEmpty()){
        std::cout << "Working..." << std::endl;
//        Get the next event, whatever it may be
        EventNode *event = eQueue->getEvent();

//        //Process the event:
        if(event->isRequestEvent()){
            fcfsDisk->processRequest(event->getRequest(), eQueue);
            stDisk->processRequest(event->getRequest(), eQueue);

            puDisk->processRequest(event->getRequest(), eQueue);
            lookupDisk->processRequest(event->getRequest(), eQueue);
            clookDisk->processRequest(event->getRequest(), eQueue);
            if(!reqVec.empty()){
                eQueue->addRequest(reqVec.front());
                reqVec.erase(reqVec.begin());
            }
        }
//                1. Event is a request event
//                    a.) Give this to every disk using processRequest

        else if(event->isTimerEvent()){
//                2. Event is a timer event:
//                    -Ask each disk to provide the number of entires in its wait queue
//                    If eQueue is NOT empty, add a new timer event to it.;
            if(!eQueue->isEmpty()){
                eQueue->setTime(event->getEventTime());
                TimerEvent *timer = new TimerEvent(event->getTimer()->getTime() + 50);
                eQueue->addTimerEvent(timer);
            }
            else
                eQueue->setTime(event->getEventTime());
        }

        //DISK DONES ARENT TRIGGERING NEW DISK DONES WHEN PUSHING NEW SERVICES INTO DISKS
        //FIX THIS SHIT QUICK BITCH
        else if(event->isDiskDoneEvent()){
            if(event->getDiskDone()->getType() == "FCFS") {
                fcfsDisk->processDiskDone(event->getRequest(), eQueue, event->getDiskDone());
                std::cout << "DDONE FOR FCFS\n";
            }
            else if(event->getDiskDone()->getType() == "ST") {
                stDisk->processDiskDone(event->getRequest(), eQueue, event->getDiskDone());
                std::cout << "DDONE FOR ST\n";
            }
            else if(event->getDiskDone()->getType() == "PICKUP") {
                puDisk->processDiskDone(event->getRequest(), eQueue, event->getDiskDone());
                std::cout << "DDONE FOR PICKUP\n";
            }
            else if(event->getDiskDone()->getType() == "LOOKUP") {
                lookupDisk->processDiskDone(event->getRequest(), eQueue, event->getDiskDone());
                std::cout << "DDONE FOR LOOKUP\n";
            }
            else if(event->getDiskDone()->getType() == "CLOOK") {
                clookDisk->processDiskDone(event->getRequest(), eQueue, event->getDiskDone());
                std::cout << "DDONE FOR CLOOK\n";
            }
        }
//                3. event is a disk-done event:
//                    -Event node has access to the disk whose disk-done event is being removed
//                    from the event queue. i.e. you have a pointer to the disk
//
//                    disk->processDiskDoneEvent(eQueue, ....);
//
    }
    std::cout << "Simulation complete" << std::endl;
    std::cout << "Simulation time: " << eQueue->getTime() << " milliseconds" << std::endl;


    //When timer event goes off and we get the current size of a disks' wait queue, we can store those in vectors and shit

}
