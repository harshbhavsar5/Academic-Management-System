#include "../include/Marks.h"
#include<iostream>
using namespace std;

Marks::Marks(){
    marksId=0;
    enrollmentId=0;
    internalMarks=0;
    externalMarks=0;
    totalMarks=0;
    grade="";
    gradePoint=0;
}
Marks::Marks(int marksId, int enrollmentId, float internalMarks, float externalMarks, string grade){
    this->marksId=marksId;
    this->enrollmentId=enrollmentId;
    this->internalMarks=internalMarks;
    this->externalMarks=externalMarks;
    this->totalMarks=internalMarks+externalMarks;
    this->grade=grade;
    if (grade == "A+" || grade == "A*"){
        this->gradePoint = 10;
    }
    else if (grade == "A"){
        this->gradePoint = 9;
    }
    else if (grade == "B+"){
        this->gradePoint = 8;
    }
    else if (grade == "B"){
        this->gradePoint = 7;
    }
    else if (grade == "C+"){
        this->gradePoint = 6;
    }
    else if (grade == "C"){
        this->gradePoint = 5;
    }
    else if (grade == "D+"){
        this->gradePoint = 4;
    }
    else if (grade == "D"){
        this->gradePoint =3;
    }
    else if (grade == "E+"){
        this->gradePoint =2;
    }
    else if (grade == "E"){
        this->gradePoint =1;
    }
    else{
        this->gradePoint = 0;
    }
}

//Setter
void Marks::setMarksId(int marksId){
    this->marksId=marksId;
}
void Marks::setEnrollmentId(int enrollmentId){
    this->enrollmentId=enrollmentId;
}
void Marks::setInternalMarks(float internalMarks){
    this->internalMarks=internalMarks;
    this->totalMarks = this->internalMarks + this->externalMarks;
}
void Marks::setExternalMarks(float externalMarks){
    this->externalMarks=externalMarks;
    this->totalMarks = this->internalMarks + this->externalMarks;
}
void Marks::setGrade(string grade){
    this->grade=grade;
}

//Getter
int Marks::getMarksId(){
    return marksId;
}
int Marks::getEnrollmentId(){
    return enrollmentId;
}
float Marks::getInternalMarks(){
    return internalMarks;
}
float Marks::getExternalMarks(){
    return externalMarks;
}
float Marks::getTotalMarks(){
    return totalMarks;
}
string Marks::getGrade(){
    return grade;
}
int Marks::getGradePoint(){
    return gradePoint;
}

void Marks::displayMarks(){
    cout << "\n===== Marks DASHBOARD =====" << endl;

    cout << "Marks ID: " << marksId << endl;
    cout << "Enrollment ID: " << enrollmentId << endl;
    cout << "Internal Marks: " << internalMarks << endl;
    cout << "External Marks: " << externalMarks << endl;
    cout << "Total Marks: " << totalMarks << endl;
    cout << "Grade: " << grade << endl;
    cout << "Grade Point: " << gradePoint << endl;
}

Marks::~Marks(){
}