#include "../include/SemesterOffering.h"
#include <iostream>
using namespace std;

SemesterOffering::SemesterOffering(){
    offeringId = 0;
    courseId = 0;
    facultyId = 0;
    semesterNumber = 0;
    academicYear = "";
    maxStudents = 0;
}

SemesterOffering::SemesterOffering(int offeringId,int courseId,int facultyId,int semesterNumber,string academicYear,int maxStudents){
    this->offeringId = offeringId;
    this->courseId = courseId;
    this->facultyId = facultyId;
    this->semesterNumber = semesterNumber;
    this->academicYear = academicYear;
    this->maxStudents = maxStudents;
}

// Setters
void SemesterOffering::setOfferingId(int offeringId){
    this->offeringId = offeringId;
}

void SemesterOffering::setCourseId(int courseId){
    this->courseId = courseId;
}

void SemesterOffering::setFacultyId(int facultyId){
    this->facultyId = facultyId;
}

void SemesterOffering::setSemesterNumber(int semesterNumber){
    this->semesterNumber = semesterNumber;
}

void SemesterOffering::setAcademicYear(string academicYear){
    this->academicYear = academicYear;
}

void SemesterOffering::setMaxStudents(int maxStudents){
    this->maxStudents = maxStudents;
}

// Getters
int SemesterOffering::getOfferingId(){
    return offeringId;
}

int SemesterOffering::getCourseId()
{
    return courseId;
}

int SemesterOffering::getFacultyId(){
    return facultyId;
}

int SemesterOffering::getSemesterNumber(){
    return semesterNumber;
}

string SemesterOffering::getAcademicYear(){
    return academicYear;
}

int SemesterOffering::getMaxStudents(){
    return maxStudents;
}

void SemesterOffering::displayOffering(){
    cout << "\n===== SEMESTER OFFERING DETAILS =====" << endl;
    cout << "Offering ID: " << offeringId << endl;
    cout << "Course ID: " << courseId << endl;
    cout << "Faculty ID: " << facultyId << endl;
    cout << "Semester Number: " << semesterNumber << endl;
    cout << "Academic Year: " << academicYear << endl;
    cout << "Maximum Students: " << maxStudents << endl;
}

SemesterOffering::~SemesterOffering(){
}