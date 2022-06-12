#ifndef FILEPATH_H
#define FILEPATH_H
#include <QString>

std::string GetAssignmentPath(const std::string& name);
void RenameFile(const QString& old_file_path, const QString& new_file_path);
void CreateFile(const QString& file_path);
QString GetAssignmentDir();
void InitAssignmentDir();

#endif // FILEPATH_H
