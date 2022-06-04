#ifndef EDITABLELABEL_H
#define EDITABLELABEL_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QStackedWidget>
#include <QFont>

class EditableLabel: public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
private:
    QLabel *mLabel;
    QLineEdit *mLineEdit;
    QStackedWidget stacked;
    QString mText;
public:
        EditableLabel(QWidget *parent = nullptr);
        EditableLabel(const QString& text, QWidget *parent = nullptr);
        bool eventFilter(QObject *watched, QEvent *event);
        QString text() const;
        void setText(const QString &text);
        void setFont(const QFont& font);
        void setAlignment(Qt::Alignment alignment);
        void setSizePolicy(QSizePolicy size_policy);
signals:
        void textChanged(const QString & text);

};

#endif // EDITABLELABEL_H
