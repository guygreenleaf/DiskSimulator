//
// Created by Guy Greenleaf on 10/26/2020.
//
#include "LookUpQueue.hpp"
#include "../CommonFiles/Request.hpp"


void LookUpQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {

    LookUpQueueNode *currNode = head;

    LookUpQueueNode *rNode = new LookUpQueueNode(request);

    int reqTrack = rNode->request()->track();

    if( empty() ) {
        head = tail = rNode;

    } else {
        while (currNode != tail) {
            if(reqTrack > cRWHeadTrack){
                if(reqTrack > currNode->request()->track() && reqTrack < currNode->next()->request()->track()){
                    rNode->next(currNode->next());
                    currNode->next(rNode);
                    break;
                }
                if(reqTrack > currNode->request()->track() && reqTrack > currNode->next()->request()->track()){
                    if(currNode->next()->request()->track() <= cRWHeadTrack && currNode->next()->request()->track() != currNode->request()->track()){
                        if(currNode == head && currNode->next()->request()->track() > reqTrack){
                            rNode->next(currNode);
                            head = rNode;
                            break;
                        }
                        else if(currNode == head && currNode->request()->track() < reqTrack && head->request()->track() < cRWHeadTrack){
                            rNode->next(currNode);
                            head = rNode;
                            break;
                        }

                        else {
                            rNode->next(currNode->next());
                            currNode->next(rNode);
                            break;
                        }
                    }

                    else
                        currNode = currNode->next();

                    if(currNode == tail && reqTrack >= currNode->request()->track()){
                        currNode->next(rNode);
                        tail = rNode;
                        break;
                    }
                }
                if(reqTrack > cRWHeadTrack && reqTrack < currNode->request()->track()){
                    rNode->next(head);
                    head = rNode;
                    break;
                }
                if(reqTrack > currNode->request()->track() && reqTrack <= currNode->next()->request()->track()){
                    if(currNode->next()->request()->track() == reqTrack){
                        rNode->next(currNode->next()->next());
                        currNode->next()->next(rNode);
                        break;
                    }
                    else {
                        rNode->next(currNode->next());
                        currNode->next(rNode);
                        break;
                    }
                }
            }

            if(reqTrack < cRWHeadTrack){
                if(currNode == head && currNode->request()->track() <= cRWHeadTrack && reqTrack > currNode->request()->track()){
                    rNode->next(currNode);
                    head = rNode;
                    break;
                }
                if(reqTrack > currNode->next()->request()->track()){
                    rNode->next(currNode->next());
                    currNode->next(rNode);
                    break;
                }
                else {
                    currNode = currNode->next();
                }

            }

            if(reqTrack == cRWHeadTrack){
                rNode->next(head);
                head = rNode;
                break;
            }
            if(reqTrack == currNode->request()->track()){
                rNode->next(currNode->next());
                currNode->next(rNode);
                break;
            }
        }

        if (head != tail && currNode == tail) {
            if(reqTrack <= tail->request()->track()) {
                tail->next(rNode);
                tail = rNode;
            }
            else{
                currNode->next(rNode);
                tail = rNode;
            }
        }

        if(head != nullptr && head == tail){
            if(reqTrack < cRWHeadTrack) {
               if(reqTrack > currNode->request()->track()){
                   rNode->next(currNode);
                   head = rNode;
                   tail = currNode;
               }
//               else if( currNode->request()->track() < head->request()->track() && reqTrack < currNode->request()->track()){
//                   currNode->next(rNode);
//                   head = currNode;
//                   tail = rNode;
//               }
               else{
                   currNode->next(rNode);
                   head = currNode;
                   tail = rNode;
               }
            }

            if(reqTrack > cRWHeadTrack){
                if(currNode->request()->track() >= cRWHeadTrack){
                    if(reqTrack >= currNode->request()->track()){
                        currNode->next(rNode);
                        tail = rNode;
                        head = currNode;
                    }
                    else{
                        rNode->next(currNode);
                        head = rNode;
                        tail = currNode;
                    }
                }
                if(currNode->request()->track() < cRWHeadTrack){
                    if(reqTrack <= currNode->request()->track()){
                        currNode->next(rNode);
                        tail = rNode;
                        head = currNode;
                    }
                    if(reqTrack > currNode->request()->track()){
                        rNode->next(currNode);
                        head = rNode;
                        tail = currNode;
                    }
                }
            }
            if(reqTrack == cRWHeadTrack){
                currNode->next(rNode);
                head = currNode;
                tail = rNode;
            }
        }
    }
}



Request *LookUpQueue::getRequest() {
    if( empty() ) {
        std::cout << "Calling STQueueNode::getRequest() on an empty queue. Terminating...\n";
        exit(1);
    }
    LookUpQueueNode *stQueueNode = head;
    Request *request = stQueueNode->request();
    rwHead = request->track();
    head = head->next();
    if( head == nullptr )
        tail = nullptr;
    delete stQueueNode;
    return request;
}

//Used in testing
int LookUpQueue::currHead(){
    return rwHead;
}

//Used in testing
void LookUpQueue::changeRwHead(int track){
    rwHead = track;
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
