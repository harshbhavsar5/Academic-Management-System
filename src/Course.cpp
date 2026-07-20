#include "../include/Course.h"
#include<iostream>
using namespace std;

Course::Course(){
    courseId=0;
    courseCode="";
    courseName="";
    credits=0;
    departmentId=0;
    recommendedSemester=0;
}

Course::Course(int courseId, string courseCode, string courseName, int credits, int departmentId, int recommendedSemester){
    this->courseId=courseId;
    this->courseCode=courseCode;
    this->courseName=courseName;
    this->credits=credits;
    this->departmentId=departmentId;
    this->recommendedSemester=recommendedSemester;
}

//Setters
void Course::setCourseId(int subjectId){
    this->courseId=subjectId;
}
void Course::setCourseCode(string subjectCode){
    this->courseCode=subjectCode;
}
void Course::setCourseName(string subjectName){
    this->courseName=subjectName;
}
void Course::setCredits(int credits){
    this->credits=credits;
}
void Course::setDepartmentId(int departmentId){
    this->departmentId=departmentId;
}
void Course::setRecommendedSemester(int recommendedSemester){
    this->recommendedSemester=recommendedSemester;
}

//Getters
int Course::getCourseId(){
    return courseId;
}
string Course::getCourseCode(){
    return courseCode;
}
string Course::getCourseName(){
    return courseName;
}
int Course::getCredits(){
    return credits;
}
int Course::getDepartmentId(){
    return departmentId;
}
int Course::getRecommendedSemester(){
    return recommendedSemester;
}

void Course::displayCourse(){
    cout<<"\n===== COURSE DETAILS ====="<<endl;
    cout << "Course ID: " << courseId << endl;
    cout << "Course Code: " << courseCode << endl;
    cout << "Course Name: " << courseName << endl;
    cout << "Credits: " << credits << endl;
    cout << "Department ID: " << departmentId << endl;
    cout << "Recommended Semester: " << recommendedSemester << endl;
}

Course::~Course(){
}