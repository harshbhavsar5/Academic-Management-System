# Academic Management System

A beginner-friendly Academic Management System developed using C++, Object-Oriented Programming, and MySQL.

The project is designed to manage academic information such as users, students, faculty members, administrators, departments, courses, enrollments, marks, and results.

## Technologies Used

- C++
- Object-Oriented Programming
- MySQL
- SQL
- Visual Studio Code
- Git and GitHub

## OOP Concepts Implemented

- Classes and Objects
- Encapsulation
- Inheritance
- Function Overriding
- Runtime Polymorphism
- Virtual Functions
- Constructors and Destructors
- Header and Source File Separation

## Modules Implemented

### User

Base class containing common user information:

- User ID
- Name
- Email
- Password
- Virtual dashboard function

### Student

Derived from the User class.

Contains:

- Student ID
- Roll Number
- Department ID
- Current Semester
- Admission Year

### Faculty

Derived from the User class.

Contains:

- Faculty ID
- Employee Code
- Department ID
- Designation

### Admin

Derived from the User class.

Provides an administrator dashboard for managing the academic system.

### Department

Represents an academic department.

Contains:

- Department ID
- Department Name
- HOD Name

## Database Design

The MySQL database is designed to manage:

- Users
- Students
- Faculty
- Departments
- Courses
- Semester Offerings
- Enrollments
- Marks
- Results

## Current Status

The following parts are completed:

- MySQL database schema
- Sample database records
- User base class
- Student class
- Faculty class
- Admin class
- Department class
- Runtime polymorphism demonstration
- Modular header and source file structure

## Planned Features

- MySQL and C++ database connectivity
- User login and authentication
- Student course enrollment
- Faculty course assignment
- Marks entry and updates
- Semester result calculation
- Academic report generation
- Menu-driven console interface

## Project Structure

```text
Academic-Management-System/
├── include/
│   ├── User.h
│   ├── Student.h
│   ├── Faculty.h
│   ├── Admin.h
│   └── Department.h
├── src/
│   ├── User.cpp
│   ├── Student.cpp
│   ├── Faculty.cpp
│   ├── Admin.cpp
│   └── Department.cpp
├── build/
├── main.cpp
├── sample_data.sql
├── README.md
└── .gitignore