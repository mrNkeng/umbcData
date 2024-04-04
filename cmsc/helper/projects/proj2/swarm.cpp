//UMBC - CSEE - CMSC 341 - Fall 2021 - Proj2
#include "swarm.h"
Swarm::Swarm(){
    m_root = nullptr;
}

Swarm::~Swarm(){
    clear();
}

void Swarm::insert(const Robot& robot){
    insertHelp(robot, m_root);
}// end insert

void Swarm::insertHelp(const Robot& robot, Robot* r2) {
    if(m_root == nullptr){
        Robot* tempbot  = new Robot(robot);
        m_root = tempbot;
    }
    else if (r2 == nullptr) {
        Robot* tempbot  = new Robot(robot);
        r2 = tempbot;
        updateHeight(r2);
        checkImbalance(r2);
    } // end if
    else if(r2->getLeft() == nullptr && robot.getID() < r2->getID()){
            Robot* tempbot = new Robot(robot);
            r2->setLeft(tempbot);
             updateHeight(r2);
            checkImbalance(r2);
    } 
    else if(r2->getRight() == nullptr && robot.getID() > r2->getID()){
            Robot* tempbot = new Robot(robot);
            r2->setRight(tempbot);
             updateHeight(r2);
            checkImbalance(r2);
    } 
    else if (robot.getID() < r2->getID()){
        insertHelp(robot, r2->getLeft());
         updateHeight(r2);
         checkImbalance(r2);
    }
    else if (robot.getID() > r2->getID()){
        insertHelp(robot, r2->getRight());
        updateHeight(r2);
        checkImbalance(r2);
    }

}// end insertHelp

void Swarm::clear(){
    clearHelp(m_root);
}// end clear

void Swarm::clearHelp(Robot* r2){ // created a recusive helper function because the clear function accepts 0 Parameters
    if (r2 != nullptr) {
            clearHelp(r2->getRight());
            clearHelp(r2->getLeft());
        r2->setID(0);
        delete r2;
        r2 = nullptr;
    }// end if
}// end clearHelp


void Swarm::remove(int id){
  //  removeHelp(m_root, id);
    updateHeight(m_root);
    checkImbalance(m_root);
}// end remove

Robot* Swarm::removeHelp(Robot* r2, int id){
    if (r2 == nullptr){
        return r2;
    }
    if (id > r2->getID()) {
        r2->setRight(removeHelp(r2->getRight(), id));
    }
    else if (id < r2->getID()) {
        r2->setLeft(removeHelp(r2->getLeft(), id));
    }
    else {
    if (r2->getRight() != nullptr && r2->getLeft() != nullptr){
        Robot* d2 = leftSet(r2->getRight());
        r2->setID( d2->getID());
        r2->m_state = d2->m_state;
        r2->m_type = d2->m_type;
        r2->setRight(removeHelp(r2->getRight(), r2->getID()));
    }
    else {
        Robot* r2d2 = r2;
        if (r2->getLeft() == nullptr) {
            r2 = r2->getRight();
        }// end if
        else {
        r2 = r2->getLeft();
        }
        delete r2d2;
    }// end else
    return r2;
    }
    return r2;
}// end removeHelp

Robot* Swarm::leftSet(Robot* r2){
    if (r2->getLeft() == nullptr || r2 == nullptr){
        return r2;
    }
    return leftSet(r2->getLeft());
}

void Swarm::updateHeight(Robot* aBot){
    aBot->m_height = heightHelp(aBot);
}


int Swarm::max(int a, int b) { // calculate the max number
    if (b > a){
        return b;
    }
    return a;
}


int Swarm::heightHelp(Robot* r2){ // updateHeight helper fuction
    int rSubHeight = 0;
    int lSubHeight = 0;
    if (r2 != nullptr){
        if (r2->getLeft() != nullptr){
           lSubHeight = 1 + heightHelp(r2->getLeft());
        }
        if (r2->getRight() != nullptr){
            rSubHeight = 1 + heightHelp(r2->getRight());
        }
    }
    return(max(rSubHeight, lSubHeight));
}


int Swarm::checkImbalance(Robot* aBot){
    //calculating balance factors
    int left = -1;
    int right = -1;
    if (aBot->getLeft() != nullptr){
        left = aBot->getLeft()->m_height;
    }
    if (aBot->getRight() != nullptr){
        right = aBot->getRight()->m_height;
    }
    return left - right;
}// end checkImbalance


Robot* Swarm::leftRotation(Robot* r2) { // helper for the rebalance
    Robot* y;
    y = r2->getRight();
    r2->setRight(y->getLeft());
    y->setLeft(r2);

    return y;
}


Robot* Swarm::rightRotation(Robot* r2) { // helper for the rebalance
    Robot* y; 
    y = r2->getLeft();
    r2->setLeft(y->getRight());
    y->setRight(r2);

    return y;
}


Robot* Swarm::rebalance(Robot* aBot) {
   updateHeight(aBot);
        if(checkImbalance(aBot)== -2 && checkImbalance(aBot->getRight()) == -1) {
            aBot = leftRotation(aBot);
        }
        if(checkImbalance(aBot)== 2 && checkImbalance(aBot->getLeft()) == 1) {
            aBot = rightRotation(aBot);
        }
    return aBot;
}// end rebalance


void Swarm::listRobots() const {
    listHelp(m_root);
} // end listRobots

void Swarm::listHelp(Robot* r2) const {
    if (r2 == nullptr){
        return;
    }
    listHelp(r2->getLeft());
    cout << r2->getID() << " " << "\n";
    listHelp(r2->getRight());
        
}


bool Swarm::setState(int id, STATE state){
     Robot* r2;
     r2 = stateHelper(id, m_root);
    if(r2 != nullptr){
        r2->m_state = state;
        return true;
    }

    return false;
}// end set state

Robot* Swarm::stateHelper(int id, Robot* r2){
    if(r2 != nullptr) {
        if (r2->getID() == id){
            return r2;
        }
        if (r2->getID() > id){
        stateHelper(id, r2->getLeft());
        }
        if (r2->getID() < id) {
        stateHelper(id, r2->getRight());
        }
    }
    return nullptr;
}// end stateHelper

void Swarm::removeDead(){
    deadHelper(m_root);
}//end remove dead

void Swarm::deadHelper(Robot* r2){
    if (r2 != nullptr) {
            clearHelp(r2->getRight());
            clearHelp(r2->getLeft());
        r2->setID(0);
        if (r2->m_state == DEAD){
            remove(r2->getID());
        }
    }
}// end deadHelper


bool Swarm::findBot(int id) const {
    return fBotHelp(id, m_root);
}// end findbot



bool Swarm::fBotHelp(int id, Robot* r2) const { // find Bot helper function
    if(r2 != nullptr) {
        if (r2->getID() == id){
            return true;
        }
       return fBotHelp(id, r2->getLeft()) || fBotHelp(id, r2->getRight());
    }
    return false;
}

void Swarm::dumpTree() const {
    dump(m_root);
}

void Swarm::dump(Robot* aBot) const{
    if (aBot != nullptr){
        cout << "(";
        dump(aBot->getLeft());//first visit the left child
        cout << aBot->getID() << ":" << aBot->m_height;//second visit the node itself
        dump(aBot->getRight());//third visit the right child
        cout << ")";
    }
}