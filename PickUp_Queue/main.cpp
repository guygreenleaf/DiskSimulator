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
#include "PickUpQueue.hpp"

//PickUpQueue *createSTQueueFromInputFile( int argc, char *argv[] ) {
//
//    if( argc != 2) {
//        std::cout << "usage: " << argv[0] << " nameOfAnInputFile\n";
//        exit(1);
//    }
//
//    std::ifstream inputStream;
//    inputStream.open(argv[1], std::ios::in);
//    if( ! inputStream.is_open()) {
//        std::cout << "Unable top open " << argv[1] << ". Terminating...";
//        perror("Error when attempting to open the input file.");
//        exit(1);
//    }
//
//    auto *queue = new PickUpQueue();
//
//    int time, track, sector;
//    while(inputStream >> time && inputStream >> track && inputStream >> sector) {
//        auto *request = new Request(time, track, sector);
//        queue->addRequest(request, 0, 0);
//    }
//
//    return queue;
//}



Request *generateRandomRequest() {
    // Randomly generates and returns a request. The time of each
    // subsequent request is larger than that of the previous one.

    static int currentTime = 0;

    enum {
        MAX_TIME_INTERVAL = 100,
        MAX_TRACK = 100,
        MAX_SECTOR = 30
    };

    currentTime += (int) (rand() % MAX_TIME_INTERVAL + 1);   // advance current time by at most 100 msecs
    int track = (int) (rand() % MAX_TRACK);
    int sector = (int) (rand() % MAX_SECTOR);

    return new Request(currentTime, track, sector);
}

enum Actions {
    ADD_A_REQUEST = 0,
    GET_A_REQUEST = 5,
    INSPECT_QUEUE = 9,
};

const int ACTION_RANGE = 10;


PickUpQueue *createPickUpQueueFromRandomValues(int numRequestsToGenerate, int numTestsToRun) {
    // This function runs numTestsToRun to test the FCFS queue. Each test consists of one
    // of the following operations:
    //
    //   1. adding a random request to the queue.
    //   2. removing (and deleting) a request from the queue.
    //   3. determining if the queue is empty or not.

    // numRequestsToGenerate provides a limit on the number of requests to be generated.
    // You can force the queue to become empty by setting the value of numTestsToRun
    // far greater than numRequestsToGenerate. Setting numRequestsToGenerate greater
    // than numTestsToRun will keep many requests in the queue.

    // Once all tests are run, the queue gets emptied, if it is not already empty.

    // FCFS is a simple queue and as a result, testing whether it organizes the requests
    // correctly or not is simple. To that end, we keep track of the timestamp of
    // the last request that we remove from the queue. Every time that we remove
    // a request from the queue, we expect its timestamp to be larger than that of
    // the previous one. If that relationship doesn't hold, we print an error message.

    // We use enum Action to give weight to each of the three operations that
    // we perform to test the queue. To perform a test, we draw a random number between
    // 0 and 9 and depending on how its value relates to the range of values that enum
    // Action provides and run a test accordingly.
    //
    // For example, currently, the value of GET_A_REQUEST of enum Action is 5. That means
    // we will add a request to the queue, if the value that the random number that we
    // generate is greater than or equal to ADD_A_REQUEST (which is zero) and less
    // than GET_A_REQUEST (which is 5). Therefore, the weight of adding a request is
    // 5/10 = 1/2 (we have 10 values in the interval of 0 and 9.) That is, 50 percent
    // of the times we add a request to the queue. On the other hand, 40% of the times
    // we remove a request from the queue and 10% of the times we inspect the queue to
    // determine if it is empty or not.

    // Please note that numTestsToGenerate bounds the number of requests that we
    // generate. Therefore, we will skip generating requests if we ever reach this
    // value.

    // This is a long function, however breaking it up into more functions would require
    // many arguments to be passed to helper functions. That is a trade off.

    auto *queue = new PickUpQueue();
    srand(getpid());

    int numRequestsGenerated = 0, numTestsRun = 0, numRequestsInTheQueue = 0;
    int currentTrack = 0, currentSector = 0;
    double previousTimeStamp = 0.0;

    while ( numTestsRun < numTestsToRun ) {
        Request *request = nullptr;
        int actionRange = (int) (rand() % ACTION_RANGE);
        if (numRequestsGenerated < numRequestsToGenerate && actionRange >= ADD_A_REQUEST && actionRange < GET_A_REQUEST) {
            std::cout << "Testing addRequest\n";
            request = generateRandomRequest();
            std::cout << "Adding the following request to the FCFSQueue.\n";
            request->print();
            queue->addRequest(request, currentTrack, currentSector);
            numRequestsGenerated++;
            numRequestsInTheQueue++;
        } else if (actionRange < INSPECT_QUEUE) {
            std::cout << "Testing getRequest\n";
            if (queue->empty())
                std::cout << "FCFSQueue is empty.\n";
            else {
                request = queue->getRequest();
                std::cout << "Removed the following request from the FCFSQueue via getRequest.\n";
                request->print();
                if(request->time() < previousTimeStamp)
                    std::cout << "Error: The FCFSQueue just returned a request whose timestamp is out of order.\n";
                previousTimeStamp = request->time();
                delete request; // We do not have a use for this request any longer.
                currentTrack = request->track();
                currentSector = request->sector();
                numRequestsInTheQueue--;
            }
        } else {
            std::cout << "Testing whether the queue is empty or not.\n";
            if (numRequestsInTheQueue != 0 && queue->empty()) {
                std::cout << "FCFSQueue::empty() returns true, but the queue should have " <<
                          numRequestsInTheQueue << " elements in it." << std::endl;
                exit(1);
            } else if (numRequestsInTheQueue == 0 && !queue->empty()) {
                std::cout << "FCFSQueue::empty() returns false, but the queue should be empty." << std::endl;
                exit(1);
            }
        }
        numTestsRun++;
    }

    while(! queue->empty() ) {
        std::cout << "Removed the following request from the FCFSQueue after having tested the queue.\n";
        auto *request = queue->getRequest();
        request->print();
        delete request;
        numRequestsInTheQueue--;
    }

    if( numRequestsInTheQueue > 0 ) {
        std::cout << "In the process of testing, the FCFSQueue lost " << numRequestsInTheQueue <<
                  ". This means the queue contains a bug!\n";
    } else if(numRequestsInTheQueue < 0) {
        std::cout << "In the process of testing, the FCFSQueue did not remove " << -numRequestsInTheQueue <<
                  "requests as a result of getRequest having been called. This means the queue contains a bug!\n";
    }

    return queue;
}

PickUpQueue *createPickUpQueueFromInputFile( int argc, char *argv[] ) {

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

    PickUpQueue *queue = new PickUpQueue();

    int time, track, sector;
    int headPos = 79;
    int testHeadPosZero = 0;
    int testHeadPosOverMax = 98;
    int testHeadPosMovingFromStart = 79;
    while(inputStream >> time && inputStream >> track && inputStream >> sector) {
        auto *request = new Request(time, track, sector);
        queue->addRequest(request, headPos, 0);
        testHeadPosMovingFromStart = track;
    }

    return queue;
}

int main(int argc, char *argv[]) {
    std::cout << "Pickup -- Main function.\n";

    PickUpQueue *bigQueue = createPickUpQueueFromInputFile(argc, argv);

    bigQueue->print();
    std::cout << "_----------------------------------------" << std::endl;

    PickUpQueue *randQueue = createPickUpQueueFromRandomValues(6, 6);
    randQueue->print();

//    Request *testReq = new Request(290, 49, 3);
//    Request *test2Req = new Request(210, 62, 4);
//    bigQueue->addRequest(testReq, 0, 0);
//    bigQueue->addRequest(test2Req, 0, 0);
//    std::cout << "Testing addrequest for new request" << std::endl;
//    bigQueue->print();
//
//    Request *newReq = new Request(823, 79, 3);
//    bigQueue->addRequest(newReq, 0, 0);
//    std::cout << "new request added" << std::endl;
//    bigQueue->print();
//    bigQueue->getRequest();
//    bigQueue->getRequest();
//    bigQueue->getRequest();
//    std::cout << "test print" << std::endl;
//    bigQueue->print();
    return 0;
}
