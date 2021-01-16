//
// Created by basil on 1/15/2021.
//

#include "library2.h"
#include "CoursesManager.h"
void *Init()
{
    CoursesManager *DS = new CoursesManager ();
    return (void*)DS;
}


StatusType AddCourse(void* DS, int courseID)
{
    if(DS==NULL)
        return INVALID_INPUT;
    return ((CoursesManager *)DS)-> AddCourseManger(DS,courseID);
}

StatusType RemoveCourse(void *DS, int courseID)
{
    if(DS==NULL)
        return INVALID_INPUT;
    return ((CoursesManager *)DS)->RemoveCourseManger(DS,courseID);
}

StatusType AddClass(void* DS, int courseID, int* classID)
{
    if(DS==NULL)
        return INVALID_INPUT;
    return ((CoursesManager *)DS)->AddClassManger(DS,courseID,classID);
}

StatusType WatchClass(void *DS, int courseID, int classID, int time)
{
    if(DS==NULL)
        return INVALID_INPUT;
    return ((CoursesManager *)DS)-> WatchClassManger(DS,courseID, classID,time);
}

StatusType TimeViewed(void *DS, int courseID, int classID, int *timeViewed)
{
    if(DS==NULL)
        return INVALID_INPUT;
    return ((CoursesManager *)DS)->TimeViewedManger(DS,courseID,classID,timeViewed);
}

StatusType GetIthWatchedClass(void* DS, int i, int* courseID, int* classID)
{
    if(DS==NULL)
        return INVALID_INPUT;
    return ((CoursesManager *)DS)->GetIthWatchedClassManger(DS,i,courseID,classID);
}

void Quit(void** DS)
{
    if(DS==NULL)
        return;
    delete (CoursesManager*)(*DS) ;
    *DS = nullptr ;
}