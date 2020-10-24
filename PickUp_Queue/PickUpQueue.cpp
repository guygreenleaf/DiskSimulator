//
// Created by yaweh on 10/22/2020.
//

#include "PickUpQueue.hpp"
#include "../CommonFiles/Request.hpp"
#include "PickUpQueueNode.hpp"


void PickUpQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {
    
    PickUpQueueNode *rNode = new PickUpQueueNode(request);
    if( empty() ) {
        head = tail = rNode;
    } else {
        tail->next(rNode);
        tail = rNode;
    }

}

//CHANGE HOW THIS BEHAVES TO HANDLE SAME TRACK REQUESTS AT ANY TIME.
Request *PickUpQueue::getRequest() {
    if( empty() ) {
        std::cout << "Calling STQueueNode::getRequest() on an empty queue. Terminating...\n";
        exit(1);
    }
    PickUpQueueNode *stQueueNode = head;
    Request *request = stQueueNode->request();
    head = head->next();
    if( head == nullptr )
        tail = nullptr;
    delete stQueueNode;
    return request;
}

bool PickUpQueue::empty() {
    return head == nullptr;
}

void PickUpQueue::print() {
    for(auto cur = head; cur; cur = cur->next() )
        cur->request()->print();
}

PickUpQueue::~PickUpQueue() {
    while( head != nullptr ) {
        PickUpQueueNode *node = head;
        head = node->next();
        delete node;
    }
}
