//
// Created by mayfl on 08/05/2019.
//

#ifndef WET1_SCHEDULE_H
#define WET1_SCHEDULE_H

#include "avl.h"
#include "Lecture.h"
#include "List.h"
#include "iostream"
#define AVAILABLE -1

typedef enum {
    SCHEDULE_SUCCESS = 0,
    SCHEDULE_FAILURE = -1,
    SCHEDULE_ALLOCATION_ERROR = -2,
    SCHEDULE_INVALID_INPUT = -3
} ScheduleResult;

class Schedule{

    int hours;
    int rooms;
    int* schedulesOfRooms;
    AvlTree<AvlTree<int,Lecture>,int> classesOfCourses;
    List* freeRoomsByHour;
    ListNode** pointersToFreeRooms;
    int numOfClasses;
    int* numOfFreeRoomsInHour;
    int numOfHoursWithClasses;



public:

    Schedule(int hours, int rooms): hours(hours), rooms(rooms),
                                    schedulesOfRooms(new int [hours*rooms]),
                                    freeRoomsByHour (new List[hours]),
                                    pointersToFreeRooms(new ListNode*[hours*rooms])
            ,numOfClasses(0),
                                    numOfFreeRoomsInHour(new int[hours]),
                                    numOfHoursWithClasses(0){

        for (int i=0; i<hours; i++){
            for (int j=0; j<rooms; j++){
                ListNode* insertAddress=freeRoomsByHour[i].insertTop(j);
                *(pointersToFreeRooms+i*rooms+j) = insertAddress;
                *(schedulesOfRooms+i*rooms+j)=AVAILABLE;

            }
            freeRoomsByHour[i].pointBottomToTail();
            numOfFreeRoomsInHour[i]=rooms;
        }
    }
    ScheduleResult AddLecture(int hour, int roomID, int courseID){
        try {
            if (hour < 0 || roomID < 0 || courseID <= 0 || hour >= hours ||
                roomID >= rooms) {
                return SCHEDULE_INVALID_INPUT;
            }
            if (*(schedulesOfRooms + hour * rooms + roomID) != AVAILABLE) {
                return SCHEDULE_FAILURE;
            }
            *(schedulesOfRooms + hour * rooms + roomID) = courseID;
            Lecture lecture(hour, roomID);
            if (!classesOfCourses.isExsist(courseID)) {
                AvlTree<int, Lecture> *course = new AvlTree<int, Lecture>;
                classesOfCourses.insert(courseID, course);
                delete course;

            }
            AvlTree<int, Lecture> *course1 = classesOfCourses.searchAvlData(courseID);
            course1->insert(lecture, NULL);
            ListNode *address = *(pointersToFreeRooms + hour * rooms + roomID);
            freeRoomsByHour[hour].pushNodeToTheEnd(address);
            numOfClasses++;
            if (numOfFreeRoomsInHour[hour] == rooms) {
                numOfHoursWithClasses++;
            }
            numOfFreeRoomsInHour[hour]--;
            return SCHEDULE_SUCCESS;
        }catch (std::bad_alloc& e){
            return SCHEDULE_ALLOCATION_ERROR;
        }
    }

    ScheduleResult GetCourseID (int hour, int roomID, int *courseID){
        if(hour<0 || roomID<0 || hour>=hours || roomID>=rooms){
            return SCHEDULE_INVALID_INPUT;
        }
        if (*(schedulesOfRooms+hour*rooms+roomID) == AVAILABLE){
            return SCHEDULE_FAILURE;
        } else *courseID = *(schedulesOfRooms+hour*rooms+roomID);
        return SCHEDULE_SUCCESS;
    }


    ScheduleResult DeleteLecture (int hour, int room){
        if (hour<0||room<0||hour>=hours||room>=rooms){
            return SCHEDULE_INVALID_INPUT;
        }
        if (*(schedulesOfRooms+hour*rooms+room) == AVAILABLE){
            return SCHEDULE_FAILURE;
        }
        int courseID= *(schedulesOfRooms+hour*rooms+room);
        *(schedulesOfRooms+hour*rooms+room) = AVAILABLE;
        //AvlTree<int,Lecture>* course= new AvlTree<int,Lecture>;
        AvlTree<int,Lecture>* course=  classesOfCourses.searchAvlData(courseID);
        Lecture lecture(hour,room);
        course->remove(lecture);
        if (course->countNodesInTree()== 0){
            classesOfCourses.remove(courseID);
        }
        ListNode* address = *(pointersToFreeRooms+hour*rooms+room);
        freeRoomsByHour[hour].pushNodeToTheStart(address);
        numOfFreeRoomsInHour[hour]++;
        if (numOfFreeRoomsInHour[hour] == rooms){
            numOfHoursWithClasses--;
        }
        numOfClasses--;
        return SCHEDULE_SUCCESS;
    }

    ScheduleResult CalculateScheduleEfficiency(float *efficiency){
        if  (numOfClasses==0)
            return SCHEDULE_FAILURE;
        *efficiency= ((float)(numOfClasses))/((float)(rooms*numOfHoursWithClasses));
        return SCHEDULE_SUCCESS;
    }


    ScheduleResult ChangeCourseID(int oldCourseID, int newCourseID){
        try {
            if (oldCourseID <= 0 || newCourseID <= 0) {
                return SCHEDULE_INVALID_INPUT;
            }
            if (!classesOfCourses.isExsist(oldCourseID)) {
                return SCHEDULE_FAILURE;
            }
            if (oldCourseID == newCourseID) return SCHEDULE_SUCCESS;
            AvlTree<int, Lecture> *course = classesOfCourses.searchAvlData
                    (oldCourseID);//save data;
            int numOfLectures = (course)->countNodesInTree();
            Lecture *array = new Lecture[numOfLectures];
            (course)->printTreeInArray(array);
            for (int i = 0; i < numOfLectures; i++) {
                *(schedulesOfRooms + array[i].hour * rooms + array[i].room) = newCourseID;
            }
            delete[] array;
            //case1: new course exists
            if (classesOfCourses.isExsist(newCourseID)) {
                AvlTree<int, Lecture> *course2 = classesOfCourses.searchAvlData
                        (newCourseID);
                AvlTree<int, Lecture> *newCourseData = new AvlTree<int, Lecture>;
                newCourseData->mergeTrees(course->root, course2->root);
                classesOfCourses.remove(oldCourseID);
                classesOfCourses.changeData(newCourseID, newCourseData);
            }
                //case2:new course not exists
            else {
                AvlTree<int, Lecture> *oldCourseData = new AvlTree<int, Lecture>;
                *oldCourseData = *course;
                classesOfCourses.remove(oldCourseID);
                classesOfCourses.insert(newCourseID, oldCourseData);
                delete oldCourseData;
            }
            return SCHEDULE_SUCCESS;
        }catch (std::bad_alloc& e){
            return SCHEDULE_ALLOCATION_ERROR;
        }
    }

    ScheduleResult GetAllFreeRoomsByHour(int hour, int **rooms, int*numOfRooms){
        if (hour<0 ||hour>=hours)return SCHEDULE_INVALID_INPUT;
        if(numOfFreeRoomsInHour[hour]==0 ){
            return SCHEDULE_FAILURE;
        }
        *numOfRooms = numOfFreeRoomsInHour[hour];
        *rooms = (int*)malloc((sizeof(**rooms))*(*numOfRooms));
        if(*rooms==NULL) return SCHEDULE_ALLOCATION_ERROR;
        ListNode* current= freeRoomsByHour[hour].getFirst();
        int counter = 0;
        while (!freeRoomsByHour[hour].isBottom(current)){
            (*rooms)[counter] = freeRoomsByHour[hour].getData(current);
            counter++;
            current=freeRoomsByHour[hour].getNext(current);
        }
        //need bottom data also
        (*rooms)[counter]=freeRoomsByHour[hour].getData(current);
        return SCHEDULE_SUCCESS;
    }

    ScheduleResult GetAllLecturesByCourse(int courseID, int **hours, int
    **rooms, int *numOfLectures){
        if (!classesOfCourses.isExsist(courseID)){
            return SCHEDULE_FAILURE;
        }
        AvlTree<int,Lecture>* course=  classesOfCourses.searchAvlData(courseID);
        *numOfLectures = (*course).countNodesInTree();
        Lecture *arr=(Lecture*)malloc((sizeof(*arr))*(*numOfLectures));
        *rooms = (int*)malloc((sizeof(**rooms))*(*numOfLectures));
        if(*rooms==NULL) return SCHEDULE_ALLOCATION_ERROR;
        *hours = (int*)malloc((sizeof(**hours))*(*numOfLectures));
        if(*hours==NULL){
            free(*rooms);
            return SCHEDULE_ALLOCATION_ERROR;
        }
        (*course).printTreeInArray(arr);
        for(int i=0; i<*numOfLectures;i++){
            (*rooms)[i]=arr[i].room;
            (*hours)[i]=arr[i].hour;
        }
        return SCHEDULE_SUCCESS;
    }

    void quit(){
        delete this;
    }

    ~Schedule(){
        //classesOfCourses.avlDestroy(classesOfCourses.root);
        delete[] schedulesOfRooms;
        delete[] freeRoomsByHour;
        delete[] pointersToFreeRooms;
        delete[]numOfFreeRoomsInHour;
    }

};

#endif //WET1_SCHEDULE_H
