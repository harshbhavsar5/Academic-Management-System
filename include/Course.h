#ifndef COURSE_H
#define COURSE_H
#include<string>
using namespace std;

class Course{
private : 
    int courseId;
    string courseCode;
    string courseName;
    int credits;
    int departmentId;
    int recommendedSemester;
public : 
    Course();

    Course(int courseId, string courseCode, string courseName, int credits, int departmentId, int recommendedSemester);

    //Setters
    void setCourseId(int subjectId);
    void setCourseCode(string subjectCode);
    void setCourseName(string subjectName);
    void setCredits(int credits);
    void setDepartmentId(int departmentId);
    void setRecommendedSemester(int recommendedSemester);

    //Getters
    int getCourseId();
    string getCourseCode();
    string getCourseName();
    int getCredits();
    int getDepartmentId();
    int getRecommendedSemester();

    void displayCourse();

    ~Course();
};

#endif