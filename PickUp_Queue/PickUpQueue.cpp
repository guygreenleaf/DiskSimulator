//
// Created by Guy Greenleaf on 10/22/2020.
//

#include "PickUpQueue.hpp"
#include "../CommonFiles/Request.hpp"




void PickUpQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {
    reqTracker++;
    request->setTracker(reqTracker);
    PickUpQueueNode *currNode = head;

    PickUpQueueNode *rNode = new PickUpQueueNode(request);
    //Set a reference to the track of the request for ease of use
    int reqTrack = rNode->request()->track();
    if( empty() ) {
        head = tail = rNode;
    } else {
        //While the current node in the queue has not reached the tail, do the following:
        while(currNode != tail){
            //If the request track is greater than the current read write head track, check the following and proceed accordingly:
            if( reqTrack > cRWHeadTrack /**&& reqTrack < currNode->request()->track()**/ ){
                //If the request track is equal to the track of the current node in the queue,
                //Set the request node to the next node in the queue and then set the current nodes next to the request node
                //Then break.
                if(reqTrack == currNode->request()->track()){
                    rNode->next(currNode->next());
                    currNode->next(rNode);
                    break;
                }
                //If the request track is less than the current node's track, it means we're at the head of the queue.
                //So, set the request node's next to the current node and set it to head, then break.
                if(reqTrack < currNode->request()->track()){
                    rNode->next(currNode);
                    head = rNode;
                    break;
                }
                //If the request track is bigger than the current node's track, check the following:
                if(reqTrack > currNode->request()->track()){
                    //If the request track is bigger than the current track AND the request track is smaller than the next node's track in the queue,
                    //Set the request node to the next node in the queue and then set the current nodes next to the request node
                    //Then break.
                    if(reqTrack > currNode->request()->track() && reqTrack < currNode->next()->request()->track()){
                        rNode->next(currNode->next());
                        currNode->next(rNode);
                        break;
                    }
                    //Otherwise, if the request track is bigger than the current track AND the next node is a nullptr,
                    //set the current node's next node to the request node and set the tail to the request node, then break.
                    else if (reqTrack > currNode->request()->track() && currNode->next() == nullptr){
                        currNode->next(rNode);
                        tail = rNode;
                        break;
                    }
                    //Otherwise, go to the next node in the queue.
                    else
                        currNode = currNode->next();
                }

            }
            //If the above doesn't run, it's because the request track is smaller or equal to the read/write head.
            //This type of logic where the function checks against the read/write head is used from here on out in
            //the successive queue algorithms.
            else if(reqTrack <= cRWHeadTrack){
                //If the request track equals the current node,
                //Set the request node to the next node in the queue and then set the current nodes next to the request node
                //Then break.
                if(reqTrack == currNode->request()->track()){
                    rNode->next(currNode->next());
                    currNode->next(rNode);
                    break;
                }
                //If the request track is greater than the current node's track, set the rNode's next to the current node
                //and set the head to the request node, then break.
                if(reqTrack > currNode->request()->track()){
                    rNode->next(currNode);
                    head = rNode;
                    break;
                }
                //If the request track is less than the current node's track, check the following:
                if(reqTrack < currNode->request()->track()){
                    //If the request track is less than the current node's track AND the request track
                    //is greater than the NEXT node in the queue's track,
                    //Set the request node to the next node in the queue and then set the current nodes next to the request node
                    //Then break.
                    if(reqTrack < currNode->request()->track() && reqTrack > currNode->next()->request()->track()){
                        rNode->next(currNode->next());
                        currNode->next(rNode);
                        break;
                    }
                    //Otherwise, if the request track is less than the current node's track and the next node in the queue
                    //is not a nullptr, set the incoming request node as the tail and then break.
                    else if (reqTrack < currNode->request()->track() && currNode->next() == nullptr){
                        currNode->next(rNode);
                        tail = rNode;
                        break;
                    }
                    //Otherwise, move to the next node.
                    else
                        currNode = currNode->next();
                }
            }
            //WHILE LOOP ENDS HERE
        }

        //If the head is not equal to the tail but we've reached the tail, tack the request node on to the end of the
        //queue.
        if(head != tail && currNode == tail){
            tail->next(rNode);
            tail = rNode;
        }

        //If we only have one thing in the queue, do similar logic to the while loop, adding in the request to the
        //appropriate place, either behind or in front of the one thing that's in the queue.
        if(head != nullptr && head == tail){
            if(reqTrack >= cRWHeadTrack){
                if(reqTrack >= currNode->request()->track()){
                    currNode->next(rNode);
                    head = currNode;
                    tail = rNode;
                }
                else{
                    rNode->next(currNode);
                    head = rNode;
                    tail = currNode;
                }

            }
            else if(reqTrack < cRWHeadTrack){
                if(reqTrack < currNode->request()->track()){
                    currNode->next(rNode);
                    head = currNode;
                    tail = rNode;
                }
                else{
                    rNode->next(currNode);
                    head = rNode;
                    tail = currNode;
                }
            }
        }
    }
}


Request *PickUpQueue::getRequest() {
    if( empty() ) {
        std::cout << "Calling STQueueNode::getRequest() on an empty queue. Terminating...\n";
        exit(1);
    }
    PickUpQueueNode *stQueueNode = head;
    Request *request = stQueueNode->request();
    //Since we move to the track, set the rwHead to that track.
//    rwHead = request->track();
    head = head->next();
    if( head == nullptr )
        tail = nullptr;
    delete stQueueNode;
    return request;
}

////Used in testing
//int PickUpQueue::currHead(){
//    return rwHead;
//}
//
////Used in testing
//void PickUpQueue::changeRwHead(int track){
//    rwHead = track;
//}

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
int PickUpQueue::getReqTracker(){
    return reqTracker;
}

void PickUpQueue::incReqTracker(){
    reqTracker++;
}
