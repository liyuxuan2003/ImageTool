#ifndef LIFILENAME_H
#define LIFILENAME_H

#include <QString>
#include <QStandardPaths>

QString GetDirByPath(QString path);

QString GetNameByPath(QString path);

QString GetFormatByPath(QString path);

QString GetFullNameByPath(QString path);

QString ChangeDir(QString path,QString dir);

QString ChangeName(QString path,QString name);

QString ChangeFormat(QString path,QString format);

QString StandardDir(QStandardPaths::StandardLocation dirType);

#endif // LIFILENAME_H
