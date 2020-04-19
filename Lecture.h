//
// Created by User on 11/05/2019.
//

#ifndef WET1_LECTURE_H
#define WET1_LECTURE_H

#endif //WET1_LECTURE_H
#include <iostream>

struct Lecture{
    int hour;
    int room;
    Lecture(int hour,int room):hour(hour),room(room){};
    Lecture():hour(0),room(0){};
    bool operator==(const Lecture& l) const;
    bool operator>(const Lecture& l) const;
    friend std::ostream& operator<<(std::ostream& os, const Lecture& l){
        return os << l.hour << "." << l.room ;
    }
};
bool Lecture::operator==(const Lecture& l) const{
    return l.hour==hour && l.room==room;
}

bool Lecture::operator>(const Lecture& l) const{
    if(hour==l.hour){
        return room>l.room;
    }
    else
        return hour>l.hour;
}

bool operator<(const Lecture& lec1,const Lecture& lec2) {
    return !((lec1>lec2)||lec1==lec2);
}

bool operator<=(const Lecture& lec1,const Lecture& lec2) {
    return ((lec1<lec2)||lec1==lec2);
}

bool operator>=(const Lecture& lec1,const Lecture& lec2) {
    return ((lec1>lec2)||lec1==lec2);
}

bool operator!=(const Lecture& lec1,const Lecture& lec2) {
    return !(lec1==(lec2));
}
/*
std::ostream& operator<<(std::ostream& os, const lecture& l){
    return os << l.hour << "." << l.room << "i";
}*/
