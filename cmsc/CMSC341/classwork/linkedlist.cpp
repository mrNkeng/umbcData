#include "linkedlist.h"


void LinkedList::insert_at_head(int new_data){

    LinkedListNode * new_node = new LinkedListNode(new_data);
    new_node->p_next = p_head;
    // even if headptr is null its still ok
    p_head = new_node;

}

bool LinkedList::insert_at_position(int position, int new_data){
    // scanning into a linked list
    LinkedListNode * p_current = p_head;
    int count = 0; //position is the data we wanna find and count is the incrememtation up to that

    if(position == 0){
        insert_at_head(new_data);
        return true;
    }

    while (p_current != nullptr && count < position - 1){
        count++;
        p_current = p_current->p_next;
    }
    
    if(count != position - 1) {
        return false;
    }
    LinkedListNode * p_new_element = new LinkedListNode(new_data); // keeping this here so you wont have to delete
    p_new_element->p_next = p_current->p_next;
    p_current->p_next = p_new_element;

    return true;
}
void LinkedList::display(){

    LinkedListNode * p_current = p_head;
    int count = 0;

    if(!p_head){
        cout << "Empty List";
    }
    while (p_current != nullptr){
        cout << "[" << count << ", " << p_current->m_data << "] ->";
        count++;
        p_current = p_current->p_next;
    }
    cout << endl;

}

bool LinkedList::remove_at_position(int position){
    LinkedListNode * p_current = p_head;
    int count = 0; //position is the data we wanna find and count is the incrememtation up to that

    if(position == 0){
        return remove_at_head();
    }

while (p_current != nullptr && count < position - 1){
        count++;
        p_current = p_current->p_next;
    }
    
    if(count != position - 1) {
        return false;
    }
   
   LinkedListNode * old_next = p_current->p_next; // remember
    
   if (p_current->p_next == nullptr){
       return false;
   }
    p_current->p_next = p_current->p_next->p_next; // set the new next
    delete old_next; // delete it

    return true;

}
bool LinkedList::remove_by_value(int value){ // remove the first thing we find with that value
    if(p_head == nullptr){
        return false;
    }

    LinkedListNode * p_current = p_head;
    //if the value of p_head->m_data == value we ignore it...
    //LinkedListNode * p_previous = p_head;

    if(p_head->m_data == value){
        remove_at_head();
    }

    while(p_current->p_next && p_current->p_next->m_data != value){

        //p_current.p_next is protecting you from potentially segfaulting
        p_current = p_current->p_next;
    }
    if(p_current->p_next == nullptr){
        // scanned to the end didn't find it
        return false;
    }
    //auto * p_delete :LinkedList * = p_current->p_next;
    LinkedListNode * p_delete = p_current->p_next;
    p_current->p_next = p_current->p_next->p_next;
    delete p_delete;
    return true;

}
bool LinkedList::remove_at_head(){
    if(p_head == nullptr){
        return false;
    }
    LinkedListNode * p_remember = p_head;
    p_head = p_head->p_next;

    delete p_remember;
    return true;

}

LinkedList::~LinkedList(){ // destroy a linked list

    rec_delete(p_head);
    p_head = nullptr;

}

void LinkedList::rec_delete(LinkedListNode * p_node){
    if(p_node){
        rec_delete(p_node->p_next);
        delete p_node;
    }
}

void LinkedList::clear(){ // Same thing as recursive dlete only using a while loop.
    if (p_head){
        
        LinkedListNode * next_one = p_head->p_next;
        LinkedListNode * p_current = p_head;
        while(p_current){
            p_current = next_one;
            next_one = next_one->p_next;
            delete p_current;
        }
        // dont have to chexk if p_head == nullptr
        delete p_head;
    }// end if
}