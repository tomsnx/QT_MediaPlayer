#ifndef CUSTOMSPLITTERHANDLE_H
#define CUSTOMSPLITTERHANDLE_H

#include <QObject>

class CustomSplitterHandle : public QObject
{
    Q_OBJECT
public:
    explicit CustomSplitterHandle(QObject *parent = nullptr);

signals:
};

#endif // CUSTOMSPLITTERHANDLE_H
