//
// Created by yaweh on 10/26/2020.
//
#include "LookUpQueueNode.hpp"

class Request;

LookUpQueueNode::LookUpQueueNode(Request *req) : _request(req), _next(nullptr) {}

LookUpQueueNode *LookUpQueueNode::next() {
    return _next;
}

void LookUpQueueNode::next(LookUpQueueNode *node) {
    _next = node;
}

Request *LookUpQueueNode::request() {
    return _request;
}

