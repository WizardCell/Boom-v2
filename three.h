//
// Created by basil on 1/14/2021.
//

#ifndef UNTITLED_THREE_H
#define UNTITLED_THREE_H

class three {
public:
    int time;
    int course_id;
    int class_id;
    three(int time_ini,int courseid_ini,int classid_ini)
    {
        this->time = time_ini;
        this->course_id = courseid_ini;
        this->class_id = classid_ini;
    }
    three(const three& b)
    {
        this->time = b.time;
        this->course_id = b.course_id;
        this->class_id = b.class_id;
    }
    ~three()= default;
    bool operator==(const three& b)
    {
        if(this->time==b.time && this->course_id==b.course_id && this->class_id==b.class_id)
            return true;
        return false;
    }
    void operator=(const three& b)
    {
        this->time=b.time;
        this->course_id=b.course_id;
        this->class_id=b.class_id;
    }
    bool operator<(const three& b)
    {
        if(this->time == b.time)
        {
            if(this->course_id==b.course_id)
            {
                return this->class_id > b.class_id;
            } else return this->course_id > b.course_id;
        }
        else return this->time < b.time;
    }
    bool operator>(const three& b)
    {
        if(this->time == b.time)
        {
            if(this->course_id==b.course_id)
            {
                return this->class_id < b.class_id;
            } else return this->course_id < b.course_id;
        }
        else return this->time > b.time;
    }
};


#endif //UNTITLED_THREE_H
