#include"library.h"
#include"Schedule.h"

StatusType convertScheduleResultToStatusType(ScheduleResult r){
    switch (r){
        case SCHEDULE_SUCCESS:
            return SUCCESS;
        case SCHEDULE_FAILURE:
            return FAILURE;
        case SCHEDULE_ALLOCATION_ERROR:
            return ALLOCATION_ERROR;
        case SCHEDULE_INVALID_INPUT:
            return INVALID_INPUT;
    }
    return SUCCESS;
};

void *Init(int hours, int rooms) {
    try {
        if (hours <= 0 || rooms <= 0) return NULL;
        Schedule *DS = new Schedule(hours, rooms);
        return (void *) DS;
    }catch (std::bad_alloc& e){
        return NULL;
    }
}
StatusType AddLecture(void *DS, int hour, int roomID, int courseID) {
    if (!DS){
        return INVALID_INPUT;
    }
    ScheduleResult result =  ((Schedule *)DS)-> AddLecture(hour, roomID,
                                                           courseID);
    return convertScheduleResultToStatusType(result);
}

StatusType GetCourseID(void *DS, int hour, int roomID, int *courseID){
    if (!DS || !courseID){
        return INVALID_INPUT;
    }
    ScheduleResult result =  ((Schedule *)DS)-> GetCourseID(hour, roomID,
                                                            courseID);
    return convertScheduleResultToStatusType(result);
}

StatusType DeleteLecture(void *DS, int hour, int roomID){
    if (!DS){
        return INVALID_INPUT;
    }
    ScheduleResult result =  ((Schedule *)DS)-> DeleteLecture(hour, roomID);
    return convertScheduleResultToStatusType(result);

}


StatusType CalculateScheduleEfficiency(void *DS, float *efficiency){
    if (!DS){
        return INVALID_INPUT;
    }
    ScheduleResult result =  ((Schedule *)DS)-> CalculateScheduleEfficiency(efficiency);
    return convertScheduleResultToStatusType(result);
}

StatusType ChangeCourseID(void *DS, int oldCourseID, int newCourseID){
    if (!DS){
        return INVALID_INPUT;
    }
    ScheduleResult result =  ((Schedule *)DS)-> ChangeCourseID( oldCourseID,newCourseID);
    return convertScheduleResultToStatusType(result);
}

StatusType GetAllFreeRoomsByHour(void *DS, int hour, int **rooms, int*
numOfRooms){
    if (!DS || !rooms || !numOfRooms || hour<0){
        return INVALID_INPUT;
    }
    ScheduleResult result =  ((Schedule *)DS)-> GetAllFreeRoomsByHour( hour,
                                                                       rooms,numOfRooms);
    return convertScheduleResultToStatusType(result);
}


StatusType GetAllLecturesByCourse(void *DS, int courseID, int **hours, int
**rooms, int *numOfLectures){
    if (!DS || !rooms || !hours || courseID<=0||!numOfLectures){
        return INVALID_INPUT;
    }
    ScheduleResult result =  ((Schedule *)DS)-> GetAllLecturesByCourse
            ( courseID,hours, rooms,numOfLectures);
    return convertScheduleResultToStatusType(result);
}

void Quit(void** DS){
    if (!DS){
        return;
    }
    ((Schedule *)*DS)->quit();
    *DS = NULL;
}
