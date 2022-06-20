
-- -----------------------------------------------------
-- Table `User`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `User` (
  `UserID` INTEGER UNIQUE NOT NULL PRIMARY KEY AUTOINCREMENT,
  `Login` TEXT UNIQUE NOT NULL,
  `UserName` TEXT NOT NULL);
CREATE UNIQUE INDEX IF NOT EXISTS `UserID_UNIQUE` ON `User`(`UserID`);
CREATE UNIQUE INDEX IF NOT EXISTS `Login_UNIQUE` ON `User`(`Login`);


-- -----------------------------------------------------
-- Table `Authorization`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Authorization` (
  `UserID` INTEGER UNIQUE NOT NULL PRIMARY KEY,
  `Password` TEXT NOT NULL,
  FOREIGN KEY (`UserID`) REFERENCES `User`(`UserID`) ON UPDATE CASCADE ON DELETE CASCADE);
CREATE UNIQUE INDEX IF NOT EXISTS `UserID1_UNIQUE` ON `Authorization`(`UserID`);


-- -----------------------------------------------------
-- Table `Classroom`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Classroom` (
  `ClassroomID` INTEGER UNIQUE NOT NULL PRIMARY KEY AUTOINCREMENT,
  `TeacherUserID` INTEGER NOT NULL,
  `ClassroomName` TEXT NOT NULL,
  FOREIGN KEY (`TeacherUserID`) REFERENCES `User`(`UserID`) ON UPDATE CASCADE ON DELETE CASCADE);
CREATE UNIQUE INDEX IF NOT EXISTS `ClassroomID_UNIQUE` ON `Classroom`(`ClassroomID`);
CREATE INDEX IF NOT EXISTS `fk_Classroom_User_idx` ON `Classroom`(`TeacherUserID`);


-- -----------------------------------------------------
-- Table `Assignment`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Assignment` (
  `AssignmentID` INTEGER UNIQUE NOT NULL PRIMARY KEY AUTOINCREMENT,
  `TeacherUserID` INTEGER NOT NULL,
  `AssignmentName` TEXT NOT NULL,
  `AssignmentCreationDate` DATETIME NOT NULL DEFAULT current_timestamp,
  `AssignmentData` TEXT NOT NULL,
  `AssignmentMaxScore` INTEGER NULL,
  FOREIGN KEY (`TeacherUserID`) REFERENCES `User`(`UserID`) ON UPDATE CASCADE ON DELETE CASCADE);
CREATE UNIQUE INDEX IF NOT EXISTS `TaskID_UNIQUE` ON `Assignment`(`AssignmentID`);
CREATE INDEX IF NOT EXISTS `fk_Assignment_User1_idx` ON `Assignment`(`TeacherUserID`);


-- -----------------------------------------------------
-- Table `Student_Classroom`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Student_Classroom` (
  `StudentUserID` INTEGER NOT NULL PRIMARY KEY,
  `ClassroomID` INTEGER NOT NULL,
  FOREIGN KEY (`StudentUserID`) REFERENCES `User`(`UserID`) ON UPDATE CASCADE ON DELETE CASCADE,
  FOREIGN KEY (`ClassroomID`) REFERENCES `Classroom`(`ClassroomID`) ON UPDATE CASCADE ON DELETE CASCADE);
CREATE INDEX IF NOT EXISTS `fk_User_has_Classroom_User1_idx` ON `Student_Classroom`(`StudentUserID`);
CREATE INDEX IF NOT EXISTS `fk_User_has_Classroom_Classroom1_idx` ON `Student_Classroom`(`ClassroomID`);


-- -----------------------------------------------------
-- Table `AssignmentSession`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `AssignmentSession` (
  `AssignmentSessionID` INTEGER UNIQUE NOT NULL PRIMARY KEY AUTOINCREMENT,
  `AssignmentID` INTEGER NOT NULL,
  `AssignmentSessionStartDate` DATETIME NOT NULL DEFAULT current_timestamp,
  `AssignmentSessionFinishDate` DATETIME NULL,
  FOREIGN KEY (`AssignmentID`) REFERENCES `Assignment`(`AssignmentID`) ON UPDATE CASCADE ON DELETE CASCADE);
CREATE UNIQUE INDEX IF NOT EXISTS `AssignmentSessionID_UNIQUE` ON `AssignmentSession`(`AssignmentSessionID`);
CREATE INDEX IF NOT EXISTS `fk_AssignmentSession_Assignment1_idx` ON `AssignmentSession`(`AssignmentID`);


-- -----------------------------------------------------
-- Table `Student_AssignmentSession`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Student_AssignmentSession` (
  `StudentUserID` INTEGER NOT NULL PRIMARY KEY,
  `AssignmentSessionID` INTEGER NOT NULL,
  `StudentAssignmentSessionStatus` INTEGER NOT NULL,
  `StudentAssignmentSessionAnswer` TEXT NULL,
  `StudentAssignmentSessionScore` INTEGER NULL,
  `StudentAssignmentSessionFinishDate` DATETIME NULL,
  FOREIGN KEY (`StudentUserID`) REFERENCES `User`(`UserID`) ON UPDATE CASCADE ON DELETE CASCADE,
  FOREIGN KEY (`AssignmentSessionID`) REFERENCES `AssignmentSession`(`AssignmentSessionID`) ON UPDATE CASCADE ON DELETE CASCADE);
CREATE INDEX IF NOT EXISTS `fk_Assignment_has_User_User1_idx` ON `Student_AssignmentSession`(`StudentUserID`);
CREATE INDEX IF NOT EXISTS `fk_Student_AssignmentSession_AssignmentSession1_idx` ON `Student_AssignmentSession`(`AssignmentSessionID`);

