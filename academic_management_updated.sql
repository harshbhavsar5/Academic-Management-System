-- Academic Management System
-- Updated database schema aligned with the current C++ manager modules
-- MySQL 8.x

CREATE DATABASE IF NOT EXISTS academic_management;
USE academic_management;

SET FOREIGN_KEY_CHECKS = 0;

-- Drop child tables before parent tables.
DROP TABLE IF EXISTS marks;
DROP TABLE IF EXISTS enrollments;
DROP TABLE IF EXISTS semester_offerings;
DROP TABLE IF EXISTS courses;
DROP TABLE IF EXISTS faculties;
DROP TABLE IF EXISTS students;
DROP TABLE IF EXISTS departments;

SET FOREIGN_KEY_CHECKS = 1;

-- =====================================================
-- 1. DEPARTMENTS
-- =====================================================
CREATE TABLE departments (
    department_id INT AUTO_INCREMENT PRIMARY KEY,
    department_code VARCHAR(10) NOT NULL UNIQUE,
    department_name VARCHAR(100) NOT NULL UNIQUE
) ENGINE = InnoDB;

-- =====================================================
-- 2. STUDENTS
-- Soft deletion is implemented using is_active.
-- Roll numbers remain unique even after deactivation.
-- =====================================================
CREATE TABLE students (
    student_id INT AUTO_INCREMENT PRIMARY KEY,
    roll_number VARCHAR(20) NOT NULL UNIQUE,
    full_name VARCHAR(100) NOT NULL,
    email VARCHAR(100) NOT NULL,
    admission_year INT NOT NULL,
    current_semester INT NOT NULL,
    department_id INT NOT NULL,
    is_active BOOLEAN NOT NULL DEFAULT TRUE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,

    CONSTRAINT fk_student_department
        FOREIGN KEY (department_id)
        REFERENCES departments(department_id),

    CONSTRAINT chk_student_semester
        CHECK (current_semester BETWEEN 1 AND 8)
) ENGINE = InnoDB;

-- =====================================================
-- 3. FACULTIES
-- Soft deletion is implemented using is_active.
-- Employee codes remain unique even after deactivation.
-- =====================================================
CREATE TABLE faculties (
    faculty_id INT AUTO_INCREMENT PRIMARY KEY,
    employee_code VARCHAR(20) NOT NULL UNIQUE,
    full_name VARCHAR(100) NOT NULL,
    email VARCHAR(100) NOT NULL UNIQUE,
    department_id INT NOT NULL,
    designation VARCHAR(100) NOT NULL,
    is_active BOOLEAN NOT NULL DEFAULT TRUE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,

    CONSTRAINT fk_faculty_department
        FOREIGN KEY (department_id)
        REFERENCES departments(department_id)
) ENGINE = InnoDB;

-- =====================================================
-- 4. COURSES
-- =====================================================
CREATE TABLE courses (
    course_id INT AUTO_INCREMENT PRIMARY KEY,
    course_code VARCHAR(20) NOT NULL UNIQUE,
    course_name VARCHAR(100) NOT NULL,
    credits INT NOT NULL,
    department_id INT NOT NULL,

    CONSTRAINT fk_course_department
        FOREIGN KEY (department_id)
        REFERENCES departments(department_id),

    CONSTRAINT chk_course_credits
        CHECK (credits BETWEEN 1 AND 5)
) ENGINE = InnoDB;

-- =====================================================
-- 5. SEMESTER OFFERINGS
-- One course can be offered in multiple semesters or years.
-- The same course/semester/year combination is unique.
-- =====================================================
CREATE TABLE semester_offerings (
    offering_id INT AUTO_INCREMENT PRIMARY KEY,
    course_id INT NOT NULL,
    semester_number INT NOT NULL,
    academic_year VARCHAR(20) NOT NULL,

    CONSTRAINT uq_course_offering
        UNIQUE (course_id, semester_number, academic_year),

    CONSTRAINT fk_offering_course
        FOREIGN KEY (course_id)
        REFERENCES courses(course_id),

    CONSTRAINT chk_offering_semester
        CHECK (semester_number BETWEEN 1 AND 8)
) ENGINE = InnoDB;

-- =====================================================
-- 6. ENROLLMENTS
-- A student cannot enroll in the same offering twice.
-- =====================================================
CREATE TABLE enrollments (
    enrollment_id INT AUTO_INCREMENT PRIMARY KEY,
    student_id INT NOT NULL,
    offering_id INT NOT NULL,
    enrolled_on DATE NOT NULL,

    CONSTRAINT uq_student_offering
        UNIQUE (student_id, offering_id),

    CONSTRAINT fk_enrollment_student
        FOREIGN KEY (student_id)
        REFERENCES students(student_id),

    CONSTRAINT fk_enrollment_offering
        FOREIGN KEY (offering_id)
        REFERENCES semester_offerings(offering_id)
) ENGINE = InnoDB;

-- =====================================================
-- 7. MARKS
-- One marks record is allowed for each enrollment.
-- Deleting an enrollment deletes its marks automatically.
-- =====================================================
CREATE TABLE marks (
    marks_id INT AUTO_INCREMENT PRIMARY KEY,
    enrollment_id INT NOT NULL UNIQUE,
    internal_marks DECIMAL(5,2) NOT NULL DEFAULT 0.00,
    endsem_marks DECIMAL(5,2) NOT NULL DEFAULT 0.00,

    CONSTRAINT fk_marks_enrollment
        FOREIGN KEY (enrollment_id)
        REFERENCES enrollments(enrollment_id)
        ON DELETE CASCADE,

    CONSTRAINT chk_internal_marks
        CHECK (internal_marks BETWEEN 0 AND 40),

    CONSTRAINT chk_endsem_marks
        CHECK (endsem_marks BETWEEN 0 AND 60)
) ENGINE = InnoDB;

-- =====================================================
-- SAMPLE DATA
-- =====================================================

INSERT INTO departments
    (department_id, department_code, department_name)
VALUES
    (1, 'MnC', 'Mathematics and Computing'),
    (2, 'CSE', 'Computer Science and Engineering'),
    (3, 'EE',  'Electrical Engineering'),
    (4, 'ME',  'Mechanical Engineering');

INSERT INTO students
    (student_id, roll_number, full_name, email, admission_year,
     current_semester, department_id, is_active)
VALUES
    (1, '2403310', 'Harsh Bhavsar', '2403310@iitgoa.ac.in', 2024, 4, 1, 1),
    (2, '2403304', 'Amisha Kohli', '2403304@iitgoa.ac.in', 2024, 5, 1, 1),
    (3, '2406328', 'Atharva Pargaonkar', '2406328@iitgoa.ac.in', 2024, 5, 4, 1),
    (4, '2403109', 'Bhushan Kamble', '2403109@iitgoa.ac.in', 2024, 5, 2, 1),
    (5, '2403128', 'Shraddha Patil', '2403128@iitgoa.ac.in', 2024, 5, 2, 1),
    (6, '2406329', 'Janhavi Patil', '2406329@iitgoa.ac.in', 2024, 2, 4, 1);

-- Faculty records are intentionally not hard-coded here because they may
-- differ from the records created while testing FacultyManager.
-- Export your current faculties table if you want those exact rows included.

INSERT INTO courses
    (course_id, course_code, course_name, credits, department_id)
VALUES
    (1, 'MA205', 'Algebra', 4, 1),
    (2, 'MA202', 'Differential Equation', 4, 1),
    (3, 'MA203', 'Numerical Analysis', 5, 1),
    (4, 'CS222', 'DSA', 5, 2),
    (5, 'CS210', 'Computer Networks', 3, 2),
    (6, 'ME207', 'Manufacturing', 3, 4),
    (7, 'ME215', 'Thermodynamics', 4, 4),
    (8, 'EE325', 'Circuits', 2, 3);

INSERT INTO semester_offerings
    (offering_id, course_id, semester_number, academic_year)
VALUES
    (1, 1, 4, '2025-2026'),
    (2, 2, 4, '2025-2026'),
    (3, 2, 2, '2024-2025'),
    (4, 3, 5, '2026-2027'),
    (5, 4, 5, '2026-2027'),
    (6, 5, 5, '2026-2027'),
    (7, 6, 5, '2026-2027'),
    (8, 7, 2, '2024-2025'),
    (9, 8, 3, '2026-2027');

INSERT INTO enrollments
    (enrollment_id, student_id, offering_id, enrolled_on)
VALUES
    (1, 1, 1, '2025-07-01'),
    (2, 1, 2, '2025-07-01'),
    (3, 6, 3, '2024-07-01'),
    (4, 2, 4, '2026-07-01'),
    (5, 3, 4, '2026-07-01'),
    (6, 2, 5, '2026-07-01'),
    (7, 4, 5, '2026-07-01'),
    (8, 5, 5, '2026-07-01'),
    (9, 4, 6, '2026-07-01'),
    (10, 5, 6, '2026-07-01'),
    (11, 3, 7, '2026-07-01'),
    (12, 6, 8, '2024-07-01');

INSERT INTO marks
    (marks_id, enrollment_id, internal_marks, endsem_marks)
VALUES
    (1, 1, 38.00, 59.00),
    (2, 2, 37.00, 58.00),
    (3, 3, 33.00, 50.00),
    (4, 4, 30.00, 45.00),
    (5, 5, 23.00, 54.00),
    (6, 6, 29.00, 49.00),
    (7, 7, 28.00, 47.00),
    (8, 8, 31.00, 51.00),
    (9, 9, 32.00, 50.00),
    (10, 10, 39.00, 49.00),
    (11, 11, 37.00, 52.00),
    (12, 12, 30.00, 50.00);

-- Keep future AUTO_INCREMENT values above the inserted sample IDs.
ALTER TABLE departments AUTO_INCREMENT = 5;
ALTER TABLE students AUTO_INCREMENT = 7;
ALTER TABLE faculties AUTO_INCREMENT = 1;
ALTER TABLE courses AUTO_INCREMENT = 9;
ALTER TABLE semester_offerings AUTO_INCREMENT = 10;
ALTER TABLE enrollments AUTO_INCREMENT = 13;
ALTER TABLE marks AUTO_INCREMENT = 13;

-- Quick verification
SHOW TABLES;
