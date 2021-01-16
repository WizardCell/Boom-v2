//
// Created by basil on 11/30/2020.
//

#ifndef HW1_LINKEDLISTNODE_H
#define HW1_LINKEDLISTNODE_H
#define NO_CLASSES -1

template <class data_type>
class linkedNode{
public:
    data_type** data;
    int course_id;
    int last_class;
    int current_size;
    linkedNode* next;
    linkedNode* previous;
    linkedNode<data_type>(int course_ini);
    ~linkedNode();
};

template <class data_type>
linkedNode<data_type>::linkedNode(int course_ini)
        {
            this->next= nullptr;
            this->previous= nullptr;
            this->data= new data_type*[2];
            this->course_id=course_ini;
            this->last_class=NO_CLASSES;//we didnt add classes yet
            this->current_size=2;
            int i=0;
            for(i=0;i<2;i++)
            {
                this->data[i]= nullptr;
            }
        }

template <class data_type>
linkedNode<data_type>::~linkedNode()
{
    int i=0;
    for(i=0;i<this->current_size;i++)
    {
        if(this->data[i]!= nullptr)
        delete this->data[i];
    }
    delete[] data;
}

#endif //HW1_LINKEDLISTNODE_H
