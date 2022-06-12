#include "filepath.h"
#include <QFile>
#include <QDir>

std::string GetAssignmentPath(const std::string& name)
{
    return "./Assignments/" + name + ".json";
}

void RenameFile(const QString& old_file_path, const QString& new_file_path)
{
    QFile file(old_file_path);

    if (file.exists()) {
        file.rename(new_file_path);
    }
    else {
        file.setFileName(new_file_path);
        file.open(QFile::NewOnly);
        file.close();
    }
}

void CreateFile(const QString& file_path)
{
    QFile file(file_path);
    file.open(QIODevice::NewOnly);
    file.close();
}

QString GetAssignmentDir() {
    return "./Assignments";
}

void InitAssignmentDir() {
    QDir dir;
    dir.mkdir(GetAssignmentDir());
}
