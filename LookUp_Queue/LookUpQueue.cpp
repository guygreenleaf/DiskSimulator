//
// Created by Guy on 10/26/2020.
//
#include "LookUpQueue.hpp"
#include "../CommonFiles/Request.hpp"


void LookUpQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {

    LookUpQueueNode *currNode = head;

    LookUpQueueNode *rNode = new LookUpQueueNode(request);

    if( empty() ) {
        head = tail = rNode;

    } else {
        while (currNode != tail) {
            //To be used in Phase 2
//            cRWHeadTrack = currNode->request()->track();

            if (rNode->request()->track() > currNode->request()->track()) {
                if (currNode->next() == nullptr) {
                    currNode->next(rNode);
                    tail = rNode;
                    break;
                } else if (currNode->next()->request()->track() > rNode->request()->track()) {
                    rNode->next(currNode->next());
                    currNode->next(rNode);
                    break;
                } else if (currNode->next() != nullptr) {
                    rNode->next(currNode->next());
                    currNode->next(rNode);
                    break;
                }
            } else if (rNode->request()->track() <= currNode->request()->track()) {
                if (currNode->next() == nullptr) {
                    currNode->next(rNode);
                    tail = rNode;
                    break;
                } else if (currNode->next()->request()->track() <= rNode->request()->track() &&
                           currNode->request()->track() > rNode->request()->track()) {
                    if(currNode->request()->track() == rNode->request()->track()){
                       currNode->next(rNode);
                       rNode->next(currNode->next());
                       break;
                    }
                    rNode->next(currNode->next());
                    currNode->next(rNode);
                    break;
                } else
                    currNode = currNode->next();
            }
        }

        if (head != tail && currNode == tail) {
            tail->next(rNode);
            tail = tail->next();
        }

        if(head != nullptr && head == tail){
              currNode->next(rNode);
              head = currNode;
              tail = rNode;
        }
    }
}


//CHANGE HOW THIS BEHAVES TO HANDLE SAME TRACK REQUESTS AT ANY TIME.
Request *LookUpQueue::getRequest() {
    if( empty() ) {
        std::cout << "Calling STQueueNode::getRequest() on an empty queue. Terminating...\n";
        exit(1);
    }
    LookUpQueueNode *stQueueNode = head;
    Request *request = stQueueNode->request();
    head = head->next();
    if( head == nullptr )
        tail = nullptr;
    delete stQueueNode;
    return request;
}

bool LookUpQueue::empty() {
    return head == nullptr;
}

void LookUpQueue::print() {
    for(auto cur = head; cur; cur = cur->next() )
        cur->request()->print();
}

LookUpQueue::~LookUpQueue() {
    while( head != nullptr ) {
        LookUpQueueNode *node = head;
        head = node->next();
        delete node;
    }
}
