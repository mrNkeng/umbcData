/*
class vs struct, In struct all data in public by default whereas in class its private unless declared otherwise

*/
#include <iostream>
using namespace std;

class LinkedList;

class LinkedListNode {
    friend LinkedList;
public:
    LinkedListNode(int new_data = 0) {
        m_data = new_data;
        p_next = nullptr;
    }

private:
    int m_data;
    LinkedListNode * p_next;

};


class LinkedList {
    public:
        LinkedList():p_head(nullptr) {

            }
            /*
            * Crud = Create Read Update Delete/Destroy
            */
            void insert_at_head(int new_data);
            bool insert_at_position(int position, int new_data);
            void display();
            bool remove_at_position(int position);
            bool remove_by_value(int value);
            bool remove_at_head();
            ~LinkedList();

    private:
            LinkedListNode * p_head;
            void rec_delete(LinkedListNode * p_node);
            void clear();
};