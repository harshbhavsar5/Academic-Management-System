#ifndef MARKS_H
#define MARKS_H
#include<string>
using namespace std;

class Marks{
private : 
    int marksId;
    int enrollmentId;
    float internalMarks;
    float externalMarks;
    float totalMarks;
    string grade;
    int gradePoint;

public:
    Marks();
    Marks(int marksId, int enrollmentId, float internalMarks, float externalMarks, string grade);

    //Setter
    void setMarksId(int marksId);
    void setEnrollmentId(int enrollmentId);
    void setInternalMarks(float internalMarks);
    void setExternalMarks(float externalMarks);
    void setGrade(string grade);

    //Getter
    int getMarksId();
    int getEnrollmentId();
    float getInternalMarks();
    float getExternalMarks();
    float getTotalMarks();
    string getGrade();
    int getGradePoint();

    void displayMarks();

    ~Marks();
};

#endif