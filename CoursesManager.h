//
// Created by basil on 12/1/2020.
//

#ifndef HW1_COURSESMANAGER_H
#define HW1_COURSESMANAGER_H
#include <iostream>
#include "linkedList.h"
#include "three.h"
#include "library2.h"
#include "classLecture.h"
#include "AVLtree.h"
#include <exception>
#include <new>
#define ZERO 0
#define DYNAMIC 2
#define NO_CLASSES -1

class CoursesManager{
    public:
    AVLTree<three,int>* times_tree;
    LinkedList<classLecture<treeNode<three,int>>>** hash_dynamic_courses;
    int current_dynamic_size;
    int current_nodes;
    CoursesManager();
    ~CoursesManager();
    linkedNode<classLecture<treeNode<three,int>>>* findInHash(int course_idd);
    LinkedList<classLecture<treeNode<three,int>>>* findInHashRetList(int course_idd);
    StatusType AddCourseManger(void *DS, int courseID);
    StatusType RemoveCourseManger(void *DS, int courseID);
    StatusType AddClassManger(void* DS, int courseID, int* classID);
    StatusType WatchClassManger(void* DS, int courseID, int classID, int time);
    StatusType TimeViewedManger(void* DS, int courseID, int classID, int* timeViewed);
    treeNode<three, int>* Select(treeNode<three, int>* head, int k);
    StatusType GetIthWatchedClassManger(void* DS, int i, int* courseID, int* classID);
};

CoursesManager::CoursesManager()
{
    this->current_dynamic_size=DYNAMIC;
    this->current_nodes=0;//no courses yet
    this->times_tree = new AVLTree<three,int>();
    this->hash_dynamic_courses = new LinkedList<classLecture<treeNode<three,int>>>*[DYNAMIC];
    int i=0;
    for(i=0;i<this->current_dynamic_size;i++)
        this->hash_dynamic_courses[i]= nullptr;
}

CoursesManager::~CoursesManager()
{
    delete this->times_tree;
    int i=0;
    for(i=0;i<this->current_dynamic_size;i++)
        delete this->hash_dynamic_courses[i];
    delete[] this->hash_dynamic_courses;
}

linkedNode<classLecture<treeNode<three,int>>> *CoursesManager::findInHash(int course_idd)
{
    if(this->hash_dynamic_courses== nullptr)
        return nullptr;
    int i=course_idd % (this->current_dynamic_size) ;

    if(this->hash_dynamic_courses[i]== nullptr)
        return nullptr;
    linkedNode<classLecture<treeNode<three,int>>>* ptr=this->hash_dynamic_courses[i]->head;
    while (ptr!= nullptr)
    {
        if(ptr->course_id ==course_idd )
            return ptr;
        ptr= ptr->next;
    }
    return nullptr;
}

LinkedList<classLecture<treeNode<three, int>>> *CoursesManager::findInHashRetList(int course_idd)
{
    if(this->hash_dynamic_courses== nullptr)
        return nullptr;
    int i=course_idd % (this->current_dynamic_size) ;
    if(this->hash_dynamic_courses[i]== nullptr)
        return nullptr;
    linkedNode<classLecture<treeNode<three, int>>>* ptr=this->hash_dynamic_courses[i]->head;
    while (ptr!= nullptr)
    {
        if(ptr->course_id ==course_idd )
            return this->hash_dynamic_courses[i];
        ptr= ptr->next;
    }

    return nullptr;
}

StatusType CoursesManager::AddCourseManger(void *DS, int courseID)
{
    if(courseID<=0 || DS==NULL)
    {
        return INVALID_INPUT;
    }
    if(findInHash(courseID)!= nullptr)
    {
        return FAILURE;
    }
    ////add course
    if(this->current_nodes >= this->current_dynamic_size-1)
    {
        //update size required 2*size
        LinkedList<classLecture<treeNode<three, int>>>** new_hashD;
        try
        {
            new_hashD = new LinkedList<classLecture<treeNode<three, int>>>*[2*this->current_dynamic_size];
            int i=0;
            for(i=0;i<2*this->current_dynamic_size;i++)
                new_hashD[i]= nullptr;
        }
        catch (std::bad_alloc& ba)
        {
            return ALLOCATION_ERROR;
        }
        int i=0;
        for(i=0;i<this->current_dynamic_size;i++)
        {
            if(this->hash_dynamic_courses[i]== nullptr)
                continue;
            linkedNode<classLecture<treeNode<three, int>>>* ptr=this->hash_dynamic_courses[i]->head;
            while(ptr!= nullptr)
            {
                int pos = ptr->course_id % (2*this->current_dynamic_size);
                if(new_hashD[pos]== nullptr)
                {
                    try
                    {
                        new_hashD[pos] = new LinkedList<classLecture<treeNode<three, int>>>();
                    }
                    catch (std::bad_alloc& ba)
                    {
                        return ALLOCATION_ERROR;
                    }
                }
                linkedNode<classLecture<treeNode<three, int>>>* newPtr = ptr;
                ptr=ptr->next;
                this->hash_dynamic_courses[i]->head = ptr;
                new_hashD[pos]->addNewNode(newPtr);
            }
            this->hash_dynamic_courses[i]->head = nullptr;
            this->hash_dynamic_courses[i]->last = nullptr;
            delete this->hash_dynamic_courses[i];
            this->hash_dynamic_courses[i]= nullptr;
            //
        }
        //
        int ssize = 2*this->current_dynamic_size;
        int nodeC = this->current_nodes;
        delete[] this->hash_dynamic_courses;
        this->hash_dynamic_courses= new_hashD;
        this->current_dynamic_size = ssize;
        this->current_nodes = nodeC;

    }
    //add course
    int pos = courseID % this->current_dynamic_size;
    linkedNode<classLecture<treeNode<three, int>>>* new_course = new linkedNode<classLecture<treeNode<three, int>>>(courseID);
    if(this->hash_dynamic_courses[pos]== nullptr)
    {
        try
        {
            this->hash_dynamic_courses[pos] = new LinkedList<classLecture<treeNode<three, int>>>();
        }
        catch (std::bad_alloc& ba)
        {
            return ALLOCATION_ERROR;
        }
    }
    this->hash_dynamic_courses[pos]->addNewNode(new_course);
    //
    this->current_nodes++;
    return SUCCESS;
}

StatusType CoursesManager::RemoveCourseManger(void *DS, int courseID)
{
    try
    {
        if(courseID<=0 || DS==NULL)
        {
            return INVALID_INPUT;
        }
        linkedNode<classLecture<treeNode<three, int>>>* found = findInHash(courseID);
        if(found== nullptr)
        {
            return FAILURE;
        }
        LinkedList<classLecture<treeNode<three, int>>>* courselist = findInHashRetList(courseID);
//        if(courselist== nullptr)//never true;
//        {
//            return FAILURE;
//        }
        //remove
        int i=0;
        for(i=0;i<found->current_size;i++)
        {
            //find node time
            if(found->data[i]== nullptr)
                continue;
            treeNode<three,int>* timeN = found->data[i]->class_time_node;
                this->times_tree->removeTreeNode(timeN);
                //this->times_tree->SetMinValueAndRet();
            //delete found->data[i];
            //found->data[i]= nullptr;
        }
        //
        //delete[] found->data; no need
        courselist->removeNodeFromThis(found);
        this->current_nodes--;
        //
        //update size if needed
        if(this->current_nodes < this->current_dynamic_size/4 && this->current_dynamic_size > 8)
        {
            //update size required 2*size
            LinkedList<classLecture<treeNode<three, int>>>** new_hashD;
            try
            {
                new_hashD = new LinkedList<classLecture<treeNode<three, int>>>*[this->current_dynamic_size/2];
                int i=0;
                for(i=0;i<this->current_dynamic_size/2;i++)
                    new_hashD[i]= nullptr;
            }
            catch (std::bad_alloc& ba)
            {
                return ALLOCATION_ERROR;
            }
            int i=0;
            for(i=0;i<this->current_dynamic_size;i++)
            {
                if(this->hash_dynamic_courses[i]== nullptr)
                    continue;
                linkedNode<classLecture<treeNode<three, int>>>* ptr=this->hash_dynamic_courses[i]->head;
                while(ptr!= nullptr)
                {
                    int pos = ptr->course_id % (this->current_dynamic_size/2);
                    if(new_hashD[pos]== nullptr)
                    {
                        try
                        {
                            new_hashD[pos] = new LinkedList<classLecture<treeNode<three, int>>>();
                        }
                        catch (std::bad_alloc& ba)
                        {
                            return ALLOCATION_ERROR;
                        }
                    }
                    linkedNode<classLecture<treeNode<three, int>>>* newPtr = ptr;
                    ptr=ptr->next;
                    this->hash_dynamic_courses[i]->head = ptr;
                    new_hashD[pos]->addNewNode(newPtr);
                }
                this->hash_dynamic_courses[i]->head = nullptr;
                this->hash_dynamic_courses[i]->last = nullptr;
                delete this->hash_dynamic_courses[i];
                this->hash_dynamic_courses[i]= nullptr;
                //
            }
            //
            int ssize = this->current_dynamic_size/2;
            int nodeC = this->current_nodes;
            delete[] this->hash_dynamic_courses;
            this->hash_dynamic_courses= new_hashD;
            this->current_dynamic_size = ssize;
            this->current_nodes = nodeC;
        }
        //end
    }
    catch (std::bad_alloc& ba)
    {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType CoursesManager::AddClassManger(void *DS, int courseID, int *classID)
{
    if(courseID<=0 || DS==NULL)
    {
        return INVALID_INPUT;
    }
    linkedNode<classLecture<treeNode<three, int>>>* found = findInHash(courseID);
    if(found== nullptr)
    {
        return FAILURE;
    }
    //add course
    //add to found dynamic array classid = last+1;
    int pos=0;
    pos = found->last_class + 1;
    if(found->last_class==NO_CLASSES)
    {
        pos=0;
    }
    if(found->last_class >= found->current_size - 1)
    {
        //needs size update
        classLecture<treeNode<three, int>>** new_dynamic;
        try{
            new_dynamic = new classLecture<treeNode<three, int>>*[(found->current_size)*2];
            int i=0;
            for(i=0;i<(found->current_size)*2;i++)
            {
                if(i>=(found->current_size))
                {
                    new_dynamic[i]= nullptr;
                    continue;
                }
                new_dynamic[i]=found->data[i];
                found->data[i]= nullptr;
            }
            found->current_size=(found->current_size)*2;
            delete[] found->data;
            found->data = new_dynamic;
        }
        catch (std::bad_alloc& ba)
        {
            return ALLOCATION_ERROR;
        }
    }
    //add to found dynamic array classid = pos;
    found->last_class=pos;
    *classID=pos;
    return SUCCESS;
}

StatusType CoursesManager::WatchClassManger(void *DS, int courseID, int classID, int time)
{
    if(DS==NULL || courseID<=0 || classID<0 || time<=0)
    {
        return INVALID_INPUT;
    }
    linkedNode<classLecture<treeNode<three, int>>>* found = findInHash(courseID);
    if(found== nullptr)
    {
        return FAILURE;
    }
    if(found!= nullptr && found->last_class <  classID)
    {
        return INVALID_INPUT;
    }
    try
    {
        //watch class
        int time_to_add = 0;
        bool need_to_delete= false;
        if(found->data[classID]== nullptr)
        {
            //0 watched yet
            auto* newClass = new classLecture<treeNode<three, int>>(classID);
            found->data[classID]=newClass;
            time_to_add = time;
            found->data[classID]->class_id=classID;
            need_to_delete= false;
        } else
        {
            time_to_add=(found->data[classID]->class_time_node->Key->time ) + time;
            need_to_delete= true;
        }

        //remove timenode = time

        if(need_to_delete== true)
        {
            //if(found->data[classID]->class_time_node!= nullptr)
            times_tree->removeTreeNode(found->data[classID]->class_time_node);
            found->data[classID]->class_time_node= nullptr;
        }
        //
            three *a = new three(time_to_add,courseID,classID);
            int *nothing = new int(5);
            auto* newTimeN = new treeNode<three,int>(*a, *nothing);
            delete nothing;
            delete a;
            times_tree->addthisTreeNodep(newTimeN);
            //point to it
            found->data[classID]->class_time_node = newTimeN;
            newTimeN->changeMyPointer = found->data[classID];
            //
            //setMinValue
            //times_tree->SetMinValueAndRet();
            //treeNode<int,AVLTree<int,AVLTree<int,int>>>* tN = times_tree->getByKey(time_to_add);
            //tN->getData()->SetMinValueAndRet();
            //treeNode<int,AVLTree<int,int>>* co = tN->getData()->getByKey(courseID);
            //co->getData()->SetMinValueAndRet();
            return SUCCESS;
        //end of watch class
    }
    catch (std::bad_alloc& ba)
    {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType CoursesManager::TimeViewedManger(void *DS, int courseID, int classID, int *timeViewed)
{
    try
    {
        if (DS == NULL || courseID <= 0 || classID < 0) {
            return INVALID_INPUT;
        }
        linkedNode<classLecture<treeNode<three, int>>> *found = findInHash(courseID);
        if (found == nullptr) {
            return FAILURE;
        }
        if (found->last_class < classID ) {
            return INVALID_INPUT;
        }
        if(found->data[classID]== nullptr)
        {
            *timeViewed=0;
            return SUCCESS;
        }
        *timeViewed = found->data[classID]->class_time_node->Key->time;
        return SUCCESS;
    }
    catch (std::bad_alloc& ba)
    {
        return ALLOCATION_ERROR;
    }
}

treeNode<three, int> *CoursesManager::Select(treeNode<three, int> *head, int k){
    if(head==nullptr||k<=0){
        return nullptr;
    }
    int RNum=0;
    if(head->Right!=nullptr){
        RNum=head->Right->rank;
    }
    if(RNum==k-1){
        return head;
    }
    else if(RNum>k-1){
        return Select(head->Right, k);
    }
    else{
        return Select(head->Left, k-RNum-1);
    }
    //return nullptr; ///doesnt get here, added in LINUX
}

StatusType CoursesManager::GetIthWatchedClassManger(void *DS, int i, int *courseID, int *classID)
{
    if(i<=0 || DS==NULL)
    {
        return INVALID_INPUT;
    }
    try {
        if(times_tree->Head== nullptr || times_tree->Head->rank < i)
            return FAILURE;
        treeNode<three, int> *info = Select(times_tree->Head,i);
        if(info== nullptr)
            return FAILURE;;
        *courseID = info->Key->course_id;
        *classID = info->Key->class_id;
        return SUCCESS;
    }
    catch (std::bad_alloc& ba)
    {
        return ALLOCATION_ERROR;
    }
}


#endif //HW1_COURSESMANAGER_H
