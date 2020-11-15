//
// Created by Guy Greenleaf on 10/22/2020.
//

#include "STQueue.hpp"
#include "../CommonFiles/Request.hpp"

//For the purpose of this project, throughout comments I'll be referring to requests in the queue and requests coming
//in as "nodes."  This is the simplest of the 4 implementations.
void STQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {
    reqTracker++;
    request->setTracker(reqTracker);
    //Create pointer to head
    STQueueNode *currNode = head;
    //Create pointer to new request
    STQueueNode *rNode = new STQueueNode(request);

    if( empty() ) {
        //If the queue is empty, insert the request and set it equal to the tail and the head. Otherwise:
        head = tail = rNode;
    } else {
        //While the current node we're on is not equal to the tail, do the following:
        while(currNode != tail ) {
            //If the read/write head is on the same track as the request, put the request on the head since we can directly
            //read from the position we are already at.
            if(cRWHeadTrack == rNode->request()->track()){
                rNode->next(currNode);
                head = rNode;
                break;
            }
            //If the incoming request's track is not equal to the track of the current place we are in the queue (starts at the head)
            //and the incoming request's track equals the current track of the request we're at in the queue,
            //set the requests next "node" to the next place in the queue, and then set the current node's next to the incoming request "node"
            if (rNode->request()->track() != currNode->next()->request()->track()  && rNode->request()->track() == currNode->request()->track()) {
                rNode->next(currNode->next());
                currNode->next(rNode);
                break;
            }
            //Otherwise, if the next place in the queue is the tail, set the tails next to the request node
            //And set the tail to the incoming request node. This is because this is serviced in a FCFS fashion.
            else if(currNode->next() == tail){
                tail->next(rNode);
                tail = rNode;
                break;
            }
            //Otherwise, go to the next node in the queue
            currNode = currNode->next();
        }
        //Check if the head is not null and the head == tail (This is after the first node is inserted into the queue).
        //If this is true, set the incoming request node to the tail.
        if(head != nullptr && head == tail){
            if(rNode->request()->track() == cRWHeadTrack){
                rNode->next(currNode);
                head = rNode;
                tail = currNode;
            }
            else {
                tail->next(rNode);
                tail = rNode;
            }
        }
    }
}


Request *STQueue::getRequest() {
    if( empty() ) {
        std::cout << "Calling STQueueNode::getRequest() on an empty queue. Terminating...\n";
        exit(1);
    }
    STQueueNode *stQueueNode = head;
    Request *request = stQueueNode->request();
    head = head->next();
    if( head == nullptr )
        tail = nullptr;
    delete stQueueNode;
    return request;
}

////Used in testing
//int STQueue::currHead(){
//    return rwHead;
//}
//
////Used in testing
//void STQueue::changeRwHead(int track){
//    rwHead = track;
//}

bool STQueue::empty() {
    return head == nullptr;
}

void STQueue::print() {
    for(auto cur = head; cur; cur = cur->next() )
        cur->request()->print();
}

void STQueue::incReqTracker(){
    reqTracker++;
}

int STQueue::getReqTracker(){
    return reqTracker;
}

STQueue::~STQueue() {
    while( head != nullptr ) {
        STQueueNode *node = head;
        head = node->next();
        delete node;
    }
}
