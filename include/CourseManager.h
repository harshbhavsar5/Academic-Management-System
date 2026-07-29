#ifndef COURSE_MANAGER_H
#define COURSE_MANAGER_H

#include <mysqlx/xdevapi.h>
#include <string>

class CourseManager
{
private:
    mysqlx::Session* session;

    void updateCourseName(const std::string& courseCode);
    void updateCourseCredits(const std::string& courseCode);
    void updateCourseDepartment(const std::string& courseCode);

public:
    CourseManager(mysqlx::Session* databaseSession);

    void showCourseManagementMenu();
    void addCourse();
    void viewAllCourses();
    void searchCourse();
    void updateCourse();
    void deleteCourse();
};

#endif
