#include "../include/Enrollment.h"
#include <iostream>
using namespace std;

// Default constructor
Enrollment::Enrollment(){
    enrollmentId = 0;
    studentId = 0;
    offeringId = 0;
    enrollmentDate = "";
    status = "";
}

// Parameterized constructor
Enrollment::Enrollment(int enrollmentId,int studentId,int offeringId,string enrollmentDate,string status){
    this->enrollmentId = enrollmentId;
    this->studentId = studentId;
    this->offeringId = offeringId;
    this->enrollmentDate = enrollmentDate;
    this->status = status;
}

// Setters
void Enrollment::setEnrollmentId(int enrollmentId){
    this->enrollmentId = enrollmentId;
}

void Enrollment::setStudentId(int studentId){
    this->studentId = studentId;
}

void Enrollment::setOfferingId(int offeringId){
    this->offeringId = offeringId;
}

void Enrollment::setEnrollmentDate(string enrollmentDate){
    this->enrollmentDate = enrollmentDate;
}

void Enrollment::setStatus(string status){
    this->status = status;
}

// Getters
int Enrollment::getEnrollmentId(){
    return enrollmentId;
}

int Enrollment::getStudentId(){
    return studentId;
}

int Enrollment::getOfferingId(){
    return offeringId;
}

string Enrollment::getEnrollmentDate(){
    return enrollmentDate;
}

string Enrollment::getStatus(){
    return status;
}

// Display enrollment details
void Enrollment::displayEnrollment(){
    cout << "\n===== ENROLLMENT DETAILS =====" << endl;
    cout << "Enrollment ID: " << enrollmentId << endl;
    cout << "Student ID: " << studentId << endl;
    cout << "Offering ID: " << offeringId << endl;
    cout << "Enrollment Date: " << enrollmentDate << endl;
    cout << "Status: " << status << endl;
}

Enrollment::~Enrollment(){
}