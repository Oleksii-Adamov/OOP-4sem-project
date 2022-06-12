#include "editablelabel.h"
#include <QKeyEvent>
#include <QVBoxLayout>

EditableLabel::EditableLabel(QWidget *parent):
    QWidget(parent),
    mLabel(new QLabel),
    mLineEdit(new QLineEdit)
{
    setLayout(new QVBoxLayout);
    layout()->setSpacing(0);
    layout()->addWidget(&stacked);

    stacked.addWidget(mLabel);
    stacked.addWidget(mLineEdit);
    mLabel->installEventFilter(this);
    mLineEdit->installEventFilter(this);
    setSizePolicy(mLineEdit->sizePolicy());
    connect(mLineEdit, &QLineEdit::textChanged, this, &EditableLabel::setText);
}
EditableLabel::EditableLabel(const QString& text, QWidget *parent):
    EditableLabel(parent)
{
    mLabel->setText(text);
    mLineEdit->setText(text);
    mText = text;
}
bool EditableLabel::eventFilter(QObject *watched, QEvent *event){
    if (watched == mLineEdit) {
        if(event->type() == QEvent::KeyPress){
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if(keyEvent->key() == Qt::Key_Return ||
                    keyEvent->key() == Qt::Key_Escape ||
                    keyEvent->key() == Qt::Key_Enter)
            {
                mLabel->setText(mLineEdit->text());
                stacked.setCurrentIndex(0);
            }
        }
        else if (event->type() == QEvent::FocusOut) {
            mLabel->setText(mLineEdit->text());
            stacked.setCurrentIndex(0);
        }
    }
    else if (watched == mLabel) {
        if(event->type() == QEvent::MouseButtonDblClick){
            stacked.setCurrentIndex(1);
            mLineEdit->setText(mLabel->text());
            mLineEdit->setFocus();
        }
    }
    return QWidget::eventFilter(watched, event);
}

QString EditableLabel::text() const{
    return mText;
}
void EditableLabel::setText(const QString &text){
    if(text == mText)
        return;
    mText = text;
    emit textChanged(mText);
}

void EditableLabel::setFont(const QFont& font)
{
    mLabel->setFont(font);
    mLineEdit->setFont(font);
}
void EditableLabel::setAlignment(Qt::Alignment alignment)
{
    mLabel->setAlignment(alignment);
    mLineEdit->setAlignment(alignment);
}
void EditableLabel::setSizePolicy(QSizePolicy size_policy)
{
    mLabel->setSizePolicy(size_policy);
    mLineEdit->setSizePolicy(size_policy);
}
