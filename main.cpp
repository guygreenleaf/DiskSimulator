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
#include <iomanip>

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
        auto *request = new Request(time/10, track, sector);
        reqs.push_back(request);
    }
    return reqs;
}

//KEEP NUMBER OF TIMES IT HAS BEEN INTERUPTED(given a timer event) <---TRACK NUMBER OF THIS IN DISK
//How many times has it received processTimer? Use cumulative variable to store number of entries in queue
//At end, divide cum number of entires in queue by number of times it was interrupted.

int main(int argc, char *argv[]){
    std::ofstream timerWaitQueues;
    timerWaitQueues.open("TimerWaitQueues.txt");
    timerWaitQueues << "TIMER REPORT\n" << "TIME" << std::setw(15) << "FCFS" << std::setw(20) << "SAME TRACK" << std::setw(15) << "PICKUP" << std::setw(15) << "C-LOOK" << std::setw(15) << "LOOK" << std::endl;


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



    Request *testReq = new Request(19.6, 79, 23);
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
            fcfsDisk->setnumTimers();
            stDisk->setnumTimers();
            puDisk->setnumTimers();
            lookupDisk->setnumTimers();
            clookDisk->setnumTimers();

//            fcfsDisk->hasJob();
//            stDisk->hasJob();
//            puDisk->hasJob();
//            lookupDisk->hasJob();
//            clookDisk->hasJob();



            timerWaitQueues << event->getEventTime() << std::setw(15) << fcfsDisk->getnumJobs() << std::setw(20) << stDisk->getnumJobs() << std::setw(15) << puDisk->getnumJobs() << std::setw(15) << clookDisk->getnumJobs() << std::setw(15) << lookupDisk->getnumJobs() << std::endl;


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
    timerWaitQueues.close();


    //When timer event goes off and we get the current size of a disks' wait queue, we can store those in vectors and shit
    //Timer event - gets # of entries in the queue in each disk, store in variable in Disk class
    //I.e. FCFS - timer goes off - how many entries? 5...
    //Okay, timer event goes off again with 10 entries in it: 15
    //Now say we get to end, divide 15 by two

    //
}
