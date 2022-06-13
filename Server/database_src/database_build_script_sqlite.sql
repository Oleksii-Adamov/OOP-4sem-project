
-- -----------------------------------------------------
-- Table `User`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `User` (
  `UserID` INTEGER UNIQUE NOT NULL PRIMARY KEY AUTOINCREMENT,
  `Login` VARCHAR(20) UNIQUE NOT NULL,
  `UserName` VARCHAR(20) NOT NULL);
CREATE UNIQUE INDEX IF NOT EXISTS `UserID_UNIQUE` ON `User`(`UserID`);
CREATE UNIQUE INDEX IF NOT EXISTS `Login_UNIQUE` ON `User`(`Login`);


-- -----------------------------------------------------
-- Table `Authorization`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Authorization` (
  `UserID` INTEGER UNIQUE NOT NULL PRIMARY KEY,
  `Password` VARCHAR(66) NOT NULL,
  FOREIGN KEY (`UserID`) REFERENCES `User`(`UserID`) ON UPDATE CASCADE ON DELETE CASCADE);
CREATE UNIQUE INDEX IF NOT EXISTS `UserID1_UNIQUE` ON `Authorization`(`UserID`);


-- -----------------------------------------------------
-- Table `Class`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Class` (
  `ClassID` INTEGER UNIQUE NOT NULL PRIMARY KEY AUTOINCREMENT,
  `TeacherUserID` INT NOT NULL,
  FOREIGN KEY (`TeacherUserID`) REFERENCES `User`(`UserID`) ON UPDATE CASCADE ON DELETE CASCADE);
CREATE UNIQUE INDEX IF NOT EXISTS `RoomID_UNIQUE` ON `Class`(`ClassID`);
CREATE INDEX IF NOT EXISTS `fk_Class_User_idx` ON `Class`(`TeacherUserID`);


-- -----------------------------------------------------
-- Table `Assignment`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Assignment` (
  `AssignmentID` INTEGER UNIQUE NOT NULL PRIMARY KEY AUTOINCREMENT,
  `TeacherUserID` INTEGER NOT NULL,
  `AssignmentCreationDate` DATETIME NOT NULL DEFAULT current_timestamp,
  `AssignmentData` VARCHAR(66) NOT NULL,
  FOREIGN KEY (`TeacherUserID`) REFERENCES `User`(`UserID`) ON UPDATE CASCADE ON DELETE CASCADE);
CREATE UNIQUE INDEX IF NOT EXISTS `TaskID_UNIQUE` ON `Assignment`(`AssignmentID`);
CREATE INDEX IF NOT EXISTS `fk_Assignment_User1_idx` ON `Assignment`(`TeacherUserID`);


-- -----------------------------------------------------
-- Table `Student_Class`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Student_Class` (
  `StudentUserID` INTEGER NOT NULL PRIMARY KEY,
  `ClassID` INTEGER NOT NULL,
  FOREIGN KEY (`StudentUserID`) REFERENCES `User`(`UserID`) ON UPDATE CASCADE ON DELETE CASCADE,
  FOREIGN KEY (`ClassID`) REFERENCES `Class`(`ClassID`) ON UPDATE CASCADE ON DELETE CASCADE);
CREATE INDEX IF NOT EXISTS `fk_User_has_Class_User1_idx` ON `Student_Class`(`StudentUserID`);
CREATE INDEX IF NOT EXISTS `fk_User_has_Class_Class1_idx` ON `Student_Class`(`ClassID`);


-- -----------------------------------------------------
-- Table `Student_Assignment`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Student_Assignment` (
  `StudentUserID` INTEGER NOT NULL PRIMARY KEY,
  `AssignmentID` INTEGER NOT NULL,
  `StudentAssignmentAnswer` VARCHAR(66) NULL,  
  FOREIGN KEY (`AssignmentID`) REFERENCES `Assignment`(`AssignmentID`) ON UPDATE CASCADE ON DELETE CASCADE,
  FOREIGN KEY (`StudentUserID`) REFERENCES `User`(`UserID`) ON UPDATE CASCADE ON DELETE CASCADE);
CREATE INDEX IF NOT EXISTS `fk_Assignment_has_User_User1_idx` ON `Student_Assignment`(`StudentUserID`);
CREATE INDEX IF NOT EXISTS `fk_Assignment_has_User_Assignment1_idx` ON `Student_Assignment`(`AssignmentID`);
