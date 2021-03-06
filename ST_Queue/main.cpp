//
// Created by Ali A. Kooshesh on 2020-10-21.
//
#include <iostream>
#include <fstream>
#include <random>
#include <cstdlib>
#include <unistd.h>
#include "../CommonFiles/Request.hpp"
#include "../EventDriver/EventNode.hpp"
#include "STQueue.hpp"

STQueue *createSTQueueFromInputFile( int argc, char *argv[] ) {

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

    auto *queue = new STQueue();

    int time, track, sector;
    while(inputStream >> time && inputStream >> track && inputStream >> sector) {
        auto *request = new Request(time, track, sector);
        queue->addRequest(request, 0, 0);
    }

    return queue;
}

int main(int argc, char *argv[]) {
    std::cout << "ST -- Main function.\n";

    auto bigQueue = createSTQueueFromInputFile(argc, argv);

    bigQueue->print();
    Request *newReq = new Request(823, 79, 3);
    bigQueue->addRequest(newReq, 0, 0);
    std::cout << "new request added" << std::endl;
    bigQueue->print();
    bigQueue->getRequest();
    bigQueue->getRequest();
    bigQueue->getRequest();
    std::cout << "test print" << std::endl;
    bigQueue->print();
    return 0;
}
