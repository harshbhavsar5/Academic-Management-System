#ifndef SEMESTEROFFERING_H
#define SEMESTEROFFERING_H
#include <string>
using namespace std;

class SemesterOffering{
private:
    int offeringId;
    int courseId;
    int facultyId;
    int semesterNumber;
    string academicYear;
    int maxStudents;

public:
    SemesterOffering();

    SemesterOffering(int offeringId,int courseId,int facultyId,int semesterNumber,string academicYear,int maxStudents);

    // Setters
    void setOfferingId(int offeringId);
    void setCourseId(int couurseId);
    void setFacultyId(int facultyId);
    void setSemesterNumber(int semesterNumber);
    void setAcademicYear(string academicYear);
    void setMaxStudents(int maxStudents);

    // Getters
    int getOfferingId();
    int getCourseId();
    int getFacultyId();
    int getSemesterNumber();
    string getAcademicYear();
    int getMaxStudents();

    void displayOffering();

    ~SemesterOffering();
};
#endif