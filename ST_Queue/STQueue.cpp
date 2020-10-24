//
// Created by yaweh on 10/22/2020.
//

#include "STQueue.hpp"
#include "../CommonFiles/Request.hpp"


void STQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {
//
//    if(!this->empty()) {
//        cRWHeadTrack = head->request()->track();
//        cRWHeadSector = head->request()->sector();
//    }
//    else{
//        cRWHeadTrack = 0;
//        cRWHeadSector = 0;
//    }

    STQueueNode *currNode = head;

    STQueueNode *rNode = new STQueueNode(request);
    if( empty() ) {
        head = tail = rNode;
    } else {
        while(currNode != tail ) {
            if (rNode->request()->track() != currNode->next()->request()->track()  && rNode->request()->track() == currNode->request()->track()) {
                rNode->next(currNode->next());
                currNode->next(rNode);
                break;
            }
            else if(currNode->next() == tail){
                tail->next(rNode);
                tail = rNode;
                break;
            }
            currNode = currNode->next();
        }
        if(head != nullptr && head == tail){
            tail->next(rNode);
            tail = rNode;
        }
    }
}

//CHANGE HOW THIS BEHAVES TO HANDLE SAME TRACK REQUESTS AT ANY TIME.
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

bool STQueue::empty() {
    return head == nullptr;
}

void STQueue::print() {
    for(auto cur = head; cur; cur = cur->next() )
        cur->request()->print();
}

STQueue::~STQueue() {
    while( head != nullptr ) {
        STQueueNode *node = head;
        head = node->next();
        delete node;
    }
}
