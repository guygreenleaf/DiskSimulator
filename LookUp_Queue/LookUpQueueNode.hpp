//
// Created by yaweh on 10/26/2020.
//

#ifndef DISKSIM_X_LOOKUPQUEUENODE_HPP
#define DISKSIM_X_LOOKUPQUEUENODE_HPP
class Request;

class LookUpQueueNode {
public:

    LookUpQueueNode(Request *req);
    LookUpQueueNode *next();
    void next(LookUpQueueNode *node);
    Request *request();

private:
    LookUpQueueNode *_next;
    Request *_request;
};


#endif //DISKSIM_X_LOOKUPQUEUENODE_HPP
