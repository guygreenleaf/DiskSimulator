//
// Created by Guy Greenleaf on 10/26/2020.
//

#include <iostream>
#include <fstream>
#include <random>
#include <cstdlib>
#include <unistd.h>
#include "../CommonFiles/Request.hpp"

#include "LookUpQueue.hpp"




LookUpQueue *createLookUpQueueFromInputFile( int argc, char *argv[] ) {

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

    auto *queue = new LookUpQueue();

    int time, track, sector;
    int currTrack = 95;
    int testHeadPosZero = 0;
    int testHeadPosOverMax = 98;
    int testHeadPosMovingFromStart = 79;

    while(inputStream >> time && inputStream >> track && inputStream >> sector) {
        auto *request = new Request(time, track, sector);
        queue->addRequest(request, 43, 0);
        //Optional r/w head simulation
        testHeadPosMovingFromStart = track;
    }
    return queue;
}

int main(int argc, char *argv[]) {
    std::cout << "Lookup -- Main function.\n";

    LookUpQueue *bigQueue = createLookUpQueueFromInputFile(argc, argv);

    bigQueue->print();
//    Request *testReq = new Request(290, 49, 3);
//    Request *test2Req = new Request(210, 62, 4);
//    bigQueue->addRequest(testReq, 95, 0);
//    bigQueue->addRequest(test2Req, 95, 0);
//    std::cout << "Testing addrequest for new requests" << std::endl;
//    bigQueue->print();
//
//    std::cout << "Further testing:" << std::endl;

      //Further testing

//    Request *newReq = new Request(823, 79, 3);
//    bigQueue->addRequest(newReq, 0, 0);
//    std::cout << "new request added" << std::endl;
//    bigQueue->print();
//    bigQueue->getRequest();
//    bigQueue->getRequest();
//    bigQueue->getRequest();
//    bigQueue->getRequest();
//    bigQueue->getRequest();

//    std::cout << "test print" << std::endl;
//    bigQueue->print();

    return 0;
}

