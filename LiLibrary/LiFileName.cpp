#include <LiLibrary/LiFileName.h>

//Dir should be ended with "/"
//Format should NOT start with "."

QString GetDirByPath(QString path)
{
    return path.left(path.lastIndexOf("/")+1);
}

QString GetNameByPath(QString path)
{
    return path.mid(path.lastIndexOf("/")+1,path.lastIndexOf(".")-path.lastIndexOf("/")-1);
}

QString GetFormatByPath(QString path)
{
    return path.right(path.length()-path.lastIndexOf(".")-1);
}

QString GetFullNameByPath(QString path)
{
    return GetNameByPath(path)+"."+GetFormatByPath(path);
}

QString ChangeDir(QString path,QString dir)
{
    return dir+GetNameByPath(path)+"."+GetFormatByPath(path);
}

QString ChangeName(QString path,QString name)
{
    return GetDirByPath(path)+name+"."+GetFormatByPath(path);
}

QString ChangeFormat(QString path,QString format)
{
    return GetDirByPath(path)+GetNameByPath(path)+"."+format;
}

QString StandardDir(QStandardPaths::StandardLocation dirType)
{
    return QStandardPaths::writableLocation(dirType);
}


