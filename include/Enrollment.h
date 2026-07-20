#ifndef ENROLLMENT_H
#define ENROLLMENT_H

#include <string>
using namespace std;

class Enrollment{
private:
    int enrollmentId;
    int studentId;
    int offeringId;
    string enrollmentDate;
    string status;

public:
    Enrollment();

    Enrollment(
        int enrollmentId,
        int studentId,
        int offeringId,
        string enrollmentDate,
        string status
    );

    // Setters
    void setEnrollmentId(int enrollmentId);
    void setStudentId(int studentId);
    void setOfferingId(int offeringId);
    void setEnrollmentDate(string enrollmentDate);
    void setStatus(string status);

    // Getters
    int getEnrollmentId();
    int getStudentId();
    int getOfferingId();
    string getEnrollmentDate();
    string getStatus();

    void displayEnrollment();

    ~Enrollment();
};
#endif