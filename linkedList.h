//
// Created by basil on 11/30/2020.
//

#ifndef HW1_LINKEDLIST_H
#define HW1_LINKEDLIST_H
#define EMPTY_LIST 0
#include "linkedListNode.h"
template <class data_type>
class LinkedList {
public:
    int size_of_list;
    int complex_check;
    linkedNode<data_type> *head;
    linkedNode<data_type> *last;
    linkedNode<data_type> * ifTimeAlReadyExists(int course_id);
    LinkedList<data_type>();
    ~LinkedList<data_type>();
    void addNewNode(linkedNode<data_type> * add_this_node);
    bool isEmpty();
    void removeNodeFromThis(linkedNode<data_type>* node_to_delete);
    linkedNode<data_type>* GetFirst();
    linkedNode<data_type>* GetLast();
};

template <class data_type>
LinkedList<data_type>::LinkedList():complex_check(0)
{

    //linkedNode<data_type> *ini_node = new linkedNode<data_type>(0); //time zero
    this->head = nullptr;
    this->last= nullptr;
    this->size_of_list=EMPTY_LIST;
}

template<class data_type>
LinkedList<data_type>::~LinkedList<data_type>()
{
    linkedNode<data_type>* get_head = this->head;
    while(get_head){
        linkedNode<data_type>* ptr = get_head;
        get_head = get_head->next;
        if(ptr!= nullptr)
        {
            delete ptr;
        }
    }
    this->head= nullptr;
    this->last= nullptr;
}

template<class data_type>
bool LinkedList<data_type>::isEmpty()
{
    if(this->head== nullptr)
        return true;
    return false;
}

template<class data_type>
void LinkedList<data_type>::addNewNode(linkedNode<data_type> * add_this_node)
{
    if (this->isEmpty())
    {
        this->head = add_this_node;
        add_this_node->previous = nullptr;
        add_this_node->next = nullptr;
        //add_this_node->node_time=node_time;
        this->last = add_this_node;
        this->size_of_list++;
        return;
    }
    linkedNode<data_type> *ptr = this->head;
    ptr->previous = add_this_node;
    add_this_node->previous = nullptr;
    add_this_node->next=ptr;
    this->head = add_this_node;
    this->size_of_list++;
    complex_check++;
    complex_check--;
}

template<class data_type>
linkedNode<data_type> *LinkedList<data_type>::GetFirst()
{
    if(this->head== nullptr)
        return nullptr;
    return this->head;
}

template<class data_type>
linkedNode<data_type> *LinkedList<data_type>::GetLast()
{
    if(this->last== nullptr)
        return nullptr;
    return this->last;
}

template<class data_type>
void LinkedList<data_type>::removeNodeFromThis(linkedNode<data_type> *node_to_delete)
{
    if(node_to_delete== nullptr)
    {
        return;
    }
    if(node_to_delete->next== nullptr&&node_to_delete->previous== nullptr){
        this->last= nullptr;
        this->head= nullptr;
        delete node_to_delete;
        this->size_of_list= 0;
        return;
    }
    if(node_to_delete->previous== nullptr){
        node_to_delete->next->previous= nullptr;
        this->head=node_to_delete->next;
        delete node_to_delete;
        this->size_of_list--;
        return;
    }
    if(node_to_delete->next== nullptr){
        node_to_delete->previous->next= nullptr;
        this->last=node_to_delete->previous;
        delete node_to_delete;
        this->size_of_list--;
        return;
    } else{
        node_to_delete->next->previous=node_to_delete->previous;
        node_to_delete->previous->next=node_to_delete->next;
        delete node_to_delete;
        this->size_of_list--;
        return;
    }
}

template<class data_type>
linkedNode<data_type> *  LinkedList<data_type>::ifTimeAlReadyExists(int course_idd)
{
    linkedNode<data_type> *p= this->head;
    while(p!= nullptr)
    {
        if(p->course_id == course_idd)
            return p;
        p = p->next;
    }
    return nullptr;
}


#endif //HW1_LINKEDLIST_H
