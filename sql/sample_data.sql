-- MySQL dump 10.13  Distrib 8.0.46, for macos15 (arm64)
--
-- Host: localhost    Database: academic_management
-- ------------------------------------------------------
-- Server version	8.0.46

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `courses`
--

DROP TABLE IF EXISTS `courses`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `courses` (
  `course_id` int NOT NULL AUTO_INCREMENT,
  `course_code` varchar(20) NOT NULL,
  `course_name` varchar(100) NOT NULL,
  `credits` int NOT NULL,
  `department_id` int NOT NULL,
  PRIMARY KEY (`course_id`),
  UNIQUE KEY `course_code` (`course_code`),
  KEY `fk_course_department` (`department_id`),
  CONSTRAINT `fk_course_department` FOREIGN KEY (`department_id`) REFERENCES `departments` (`department_id`),
  CONSTRAINT `chk_credits` CHECK ((`credits` between 1 and 5))
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `courses`
--

LOCK TABLES `courses` WRITE;
/*!40000 ALTER TABLE `courses` DISABLE KEYS */;
INSERT INTO `courses` VALUES (1,'MA205','Algebra',4,1),(2,'MA202','Differential Equation',4,1),(3,'MA203','Numerical Analysis',5,1),(4,'CS222','DSA',5,2),(5,'CS210','Computer Networks',3,2),(6,'ME207','Manufacturing',3,4),(7,'ME215','Thermodynamics',4,4),(8,'EE325','Circuits',2,3);
/*!40000 ALTER TABLE `courses` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `departments`
--

DROP TABLE IF EXISTS `departments`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `departments` (
  `department_id` int NOT NULL AUTO_INCREMENT,
  `department_code` varchar(10) NOT NULL,
  `department_name` varchar(100) NOT NULL,
  PRIMARY KEY (`department_id`),
  UNIQUE KEY `department_code` (`department_code`),
  UNIQUE KEY `department_name` (`department_name`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `departments`
--

LOCK TABLES `departments` WRITE;
/*!40000 ALTER TABLE `departments` DISABLE KEYS */;
INSERT INTO `departments` VALUES (1,'MnC','Mathematics and Computing'),(2,'CSE','Computer Science and Engineering'),(3,'EE','Electrical Engineering'),(4,'ME','Mechanical Engineering');
/*!40000 ALTER TABLE `departments` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `enrollments`
--

DROP TABLE IF EXISTS `enrollments`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `enrollments` (
  `enrollment_id` int NOT NULL AUTO_INCREMENT,
  `student_id` int NOT NULL,
  `offering_id` int NOT NULL,
  `enrolled_on` date NOT NULL,
  PRIMARY KEY (`enrollment_id`),
  UNIQUE KEY `uq_student_offering` (`student_id`,`offering_id`),
  KEY `fk_enrollment_offering` (`offering_id`),
  CONSTRAINT `fk_enrollment_offering` FOREIGN KEY (`offering_id`) REFERENCES `semester_offerings` (`offering_id`),
  CONSTRAINT `fk_enrollment_student` FOREIGN KEY (`student_id`) REFERENCES `students` (`student_id`)
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `enrollments`
--

LOCK TABLES `enrollments` WRITE;
/*!40000 ALTER TABLE `enrollments` DISABLE KEYS */;
INSERT INTO `enrollments` VALUES (1,1,1,'2025-07-01'),(2,1,2,'2025-07-01'),(3,6,3,'2024-07-01'),(4,2,4,'2026-07-01'),(5,3,4,'2026-07-01'),(6,2,5,'2026-07-01'),(7,4,5,'2026-07-01'),(8,5,5,'2026-07-01'),(9,4,6,'2026-07-01'),(10,5,6,'2026-07-01'),(11,3,7,'2026-07-01'),(12,6,8,'2024-07-01');
/*!40000 ALTER TABLE `enrollments` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `marks`
--

DROP TABLE IF EXISTS `marks`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `marks` (
  `marks_id` int NOT NULL AUTO_INCREMENT,
  `enrollment_id` int NOT NULL,
  `internal_marks` decimal(5,2) NOT NULL DEFAULT '0.00',
  `endsem_marks` decimal(5,2) NOT NULL DEFAULT '0.00',
  PRIMARY KEY (`marks_id`),
  UNIQUE KEY `enrollment_id` (`enrollment_id`),
  CONSTRAINT `fk_marks_enrollment` FOREIGN KEY (`enrollment_id`) REFERENCES `enrollments` (`enrollment_id`) ON DELETE CASCADE,
  CONSTRAINT `chk_endsem` CHECK ((`endsem_marks` between 0 and 60)),
  CONSTRAINT `chk_internal` CHECK ((`internal_marks` between 0 and 40))
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `marks`
--

LOCK TABLES `marks` WRITE;
/*!40000 ALTER TABLE `marks` DISABLE KEYS */;
INSERT INTO `marks` VALUES (1,1,38.00,59.00),(2,2,37.00,58.00),(3,3,33.00,50.00),(4,4,30.00,45.00),(5,5,23.00,54.00),(6,6,29.00,49.00),(7,7,28.00,47.00),(8,8,31.00,51.00),(9,9,32.00,50.00),(10,10,39.00,49.00),(11,11,37.00,52.00),(12,12,30.00,50.00);
/*!40000 ALTER TABLE `marks` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `semester_offerings`
--

DROP TABLE IF EXISTS `semester_offerings`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `semester_offerings` (
  `offering_id` int NOT NULL AUTO_INCREMENT,
  `course_id` int NOT NULL,
  `semester_number` int NOT NULL,
  `academic_year` varchar(20) NOT NULL,
  PRIMARY KEY (`offering_id`),
  UNIQUE KEY `uq_course_offering` (`course_id`,`semester_number`,`academic_year`),
  CONSTRAINT `fk_offering_course` FOREIGN KEY (`course_id`) REFERENCES `courses` (`course_id`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `semester_offerings`
--

LOCK TABLES `semester_offerings` WRITE;
/*!40000 ALTER TABLE `semester_offerings` DISABLE KEYS */;
INSERT INTO `semester_offerings` VALUES (1,1,4,'2025-2026'),(3,2,2,'2024-2025'),(2,2,4,'2025-2026'),(4,3,5,'2026-2027'),(5,4,5,'2026-2027'),(6,5,5,'2026-2027'),(7,6,5,'2026-2027'),(8,7,2,'2024-2025'),(9,8,3,'2026-2027');
/*!40000 ALTER TABLE `semester_offerings` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `students`
--

DROP TABLE IF EXISTS `students`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `students` (
  `student_id` int NOT NULL AUTO_INCREMENT,
  `roll_number` varchar(20) NOT NULL,
  `full_name` varchar(100) NOT NULL,
  `email` varchar(100) NOT NULL,
  `admission_year` int NOT NULL,
  `current_semester` int NOT NULL,
  `department_id` int NOT NULL,
  `is_active` tinyint(1) NOT NULL DEFAULT '1',
  `created_at` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`student_id`),
  UNIQUE KEY `roll_number` (`roll_number`),
  KEY `fk_student_department` (`department_id`),
  CONSTRAINT `fk_student_department` FOREIGN KEY (`department_id`) REFERENCES `departments` (`department_id`),
  CONSTRAINT `chk_semester` CHECK ((`current_semester` between 1 and 8))
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `students`
--

LOCK TABLES `students` WRITE;
/*!40000 ALTER TABLE `students` DISABLE KEYS */;
INSERT INTO `students` VALUES (1,'2403310','Harsh Bhavsar','2403310@iitgoa.ac.in',2024,4,1,1,'2026-07-18 19:07:22'),(2,'2403304','Amisha Kohli','2403304@iitgoa.ac.in',2024,5,1,1,'2026-07-18 19:07:22'),(3,'2406328','Atharva Pargaonkar','2406328@iitgoa.ac.in',2024,5,4,1,'2026-07-18 19:07:22'),(4,'2403109','Bhushan Kamble','2403109@iitgoa.ac.in',2024,5,2,1,'2026-07-18 19:07:22'),(5,'2403128','Shraddha Patil','2403128@iitgoa.ac.in',2024,5,2,1,'2026-07-18 19:07:22'),(6,'2406329','Janhavi Patil','2406329@iitgoa.ac.in',2024,2,4,1,'2026-07-18 19:07:22');
/*!40000 ALTER TABLE `students` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2026-07-19 16:10:27
