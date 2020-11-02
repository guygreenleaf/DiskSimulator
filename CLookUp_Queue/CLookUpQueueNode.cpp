//
// Created by Guy Greenleaf on 10/26/2020.
//
#include "CLookUpQueueNode.hpp"

class Request;

CLookUpQueueNode::CLookUpQueueNode(Request *req) : _request(req), _next(nullptr) {}

CLookUpQueueNode *CLookUpQueueNode::next() {
    return _next;
}

void CLookUpQueueNode::next(CLookUpQueueNode *node) {
    _next = node;
}

Request *CLookUpQueueNode::request() {
    return _request;
}
