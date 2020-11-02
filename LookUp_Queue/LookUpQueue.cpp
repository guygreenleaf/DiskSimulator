//
// Created by Guy Greenleaf on 10/26/2020.
//
#include "LookUpQueue.hpp"
#include "../CommonFiles/Request.hpp"


void LookUpQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {

    LookUpQueueNode *currNode = head;

    LookUpQueueNode *rNode = new LookUpQueueNode(request);
    //Set a easy to reference variable to the track for the request coming in.
    int reqTrack = rNode->request()->track();

    if( empty() ) {
        head = tail = rNode;

    } else {
        //While we haven't reached the tail, do the following:
        while (currNode != tail) {
            //If the request track is greater than the read write head:
            if(reqTrack > cRWHeadTrack){
                //If the request track is bigger than the current node's request track AND the request track
                //is less than the next request,
                //Set the request node to the next node in the queue and then set the current nodes next to the request node
                //Then break.
                if(reqTrack > currNode->request()->track() && reqTrack < currNode->next()->request()->track()){
                    rNode->next(currNode->next());
                    currNode->next(rNode);
                    break;
                }
                //If the request track is greater than the current node's track AND the request track is greater than
                //the next node's track, check the following:
                if(reqTrack > currNode->request()->track() && reqTrack > currNode->next()->request()->track()){
                    //If the current node's NEXT TRACK is less than OR EQUAL TO the current read write head AND
                    // the current node's NEXT TRACK is not equal to the current track, do the following:
                    if(currNode->next()->request()->track() <= cRWHeadTrack && currNode->next()->request()->track() != currNode->request()->track()){
                        //If the current node is the head AND the next node in the queue's track is greater than the request track,
                        //set the request node as the new head and break.
                        if(currNode == head && currNode->next()->request()->track() > reqTrack){
                            rNode->next(currNode);
                            head = rNode;
                            break;
                        }
                        //otherwise, if the current node is the head AND the current node's track is less than the request track
                        //AND the head track is less than the read write head, set the request node as the new head and break.
                        else if(currNode == head && currNode->request()->track() < reqTrack && head->request()->track() < cRWHeadTrack){
                            rNode->next(currNode);
                            head = rNode;
                            break;
                        }

                        //Otherwise,
                        //Set the request node to the next node in the queue and then set the current nodes next to the request node
                        //Then break.
                        else {
                            rNode->next(currNode->next());
                            currNode->next(rNode);
                            break;
                        }
                    }

                    //If the above block of code doesn't run, that means either the next node in the queues track
                    //is greater than the read write head, or the next node's track happens to equal the current node's track
                    //in both cases, set the current node to the next in the queue.
                    else
                        currNode = currNode->next();

                    //If the current node is the tail AND the request track is greater than or equal to the current node,
                    //Set the request as the new tail in the queue, and then break.
                    if(currNode == tail && reqTrack >= currNode->request()->track()){
                        currNode->next(rNode);
                        tail = rNode;
                        break;
                    }
                }
                //If the request track is greater than the readwrite head and the request track is less than the
                //current node's request track, make the request track the new head, then break.
                if(reqTrack > cRWHeadTrack && reqTrack < currNode->request()->track()){
                    rNode->next(head);
                    head = rNode;
                    break;
                }
                //If the request track is greater than the current node's track and the request track is less than OR EQUAL
                //to the next node's track, do one of the following:
                if(reqTrack > currNode->request()->track() && reqTrack <= currNode->next()->request()->track()){
                    //If the current node's next track equals the request track,
                    //Set the request node to the node two spaces down the queue and then set the current node's next so that its
                    //next is the rNode.  I.E. checking two spaces ahead and inserting if equal.
                    //then break. This is done to maintain the same sort of structure that ST queue holds.
                    if(currNode->next()->request()->track() == reqTrack){
                        rNode->next(currNode->next()->next());
                        currNode->next()->next(rNode);
                        break;
                    }
                    //Otherwise,
                    //Set the request node to the next node in the queue and then set the current nodes next to the request node
                    //Then break.
                    else {
                        rNode->next(currNode->next());
                        currNode->next(rNode);
                        break;
                    }
                }
                //END OF FIRST RWHEAD LOGIC
            }

            //Go into this code block if the request track is less than the read/write head.
            if(reqTrack < cRWHeadTrack){
                //If the current node is the head AND the current node's track is less than OR EQUAL TOO the
                //read/write head AND the request track is greater than the current node's track, make the incoming
                //request node the head, then break.
                if(currNode == head && currNode->request()->track() <= cRWHeadTrack && reqTrack > currNode->request()->track()){
                    rNode->next(currNode);
                    head = rNode;
                    break;
                }
                //If the request track is bigger than the current node's NEXT track,
                //Set the request node to the next node in the queue and then set the current nodes next to the request node
                //Then break.
                if(reqTrack > currNode->next()->request()->track()){
                    rNode->next(currNode->next());
                    currNode->next(rNode);
                    break;
                }
                //Otherwise, go to the next node in the queue.
                else {
                    currNode = currNode->next();
                }

            }
            //If the request track is equal to the read/write head,
            //make the request track the new head of the queue, then break.
            if(reqTrack == cRWHeadTrack){
                rNode->next(head);
                head = rNode;
                break;
            }
            //If the request track is equal to the current node's track,
            //Set the request node to the next node in the queue and then set the current nodes next to the request node
            //Then break.
            if(reqTrack == currNode->request()->track()){
                rNode->next(currNode->next());
                currNode->next(rNode);
                break;
            }
            //END OF WHILE LOOP
        }

        //If we've reached this point, one of two things has occured.

        //First: if the head is not equal to the tail, but we've reached the end of the queue,
        //check if the request track is less than or equal to to the tail.
        //If it is, tack it on to the end of the queue. if it isn't, insert it between the current node and the tail.
        if (head != tail && currNode == tail) {
            if(reqTrack <= tail->request()->track()) {
                tail->next(rNode);
                tail = rNode;
            }
            else{
                rNode->next(tail);
                currNode->next(rNode);
            }
        }
        //If the head isn't null pointer but the head is the tail (There's only one thing in the queue), do the following:
        if(head != nullptr && head == tail){
            //Check if the incoming request is less than the read/write head. If it is, do the following:
            if(reqTrack < cRWHeadTrack) {
                //If the request track is bigger than the current node, set the request node to the head
                //and the tail to the current node.
               if(reqTrack > currNode->request()->track()){
                   rNode->next(currNode);
                   head = rNode;
                   tail = currNode;
               }
               //Otherwise, do the oppposite.
               else{
                   currNode->next(rNode);
                   head = currNode;
                   tail = rNode;
               }
            }
            //Othwerise, if the request track is BIGGER than the read write head, do the following:
            if(reqTrack > cRWHeadTrack){
                //If the current node's track is greater than or equal to the read/write head, do the following:
                if(currNode->request()->track() >= cRWHeadTrack){
                    //If the request track is grater than or equal to the current node's track,
                    //Set the incoming request node to the tail and the current node to the head.
                    if(reqTrack >= currNode->request()->track()){
                        currNode->next(rNode);
                        tail = rNode;
                        head = currNode;
                    }
                    //Otherwise, do the opposite.
                    else{
                        rNode->next(currNode);
                        head = rNode;
                        tail = currNode;
                    }
                }
                //If the current node's track is less than the read/write track, do the following:
                if(currNode->request()->track() < cRWHeadTrack){
                    //If the request track is less than or equal to the current node's track,
                    //set the request node to the tail and the current node to the head.
                    if(reqTrack <= currNode->request()->track()){
                        currNode->next(rNode);
                        tail = rNode;
                        head = currNode;
                    }
                    //Otherwise do the opposite.
                    if(reqTrack > currNode->request()->track()){
                        rNode->next(currNode);
                        head = rNode;
                        tail = currNode;
                    }
                }
            }
            //If the request track is equal to the current read/write head,
            //set the current node equal to the head and the incoming request node to the tail.
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
    //Keep track of rwHead when getting a request.
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
