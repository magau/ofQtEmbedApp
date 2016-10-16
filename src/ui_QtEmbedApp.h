/********************************************************************************
** Form generated from reading UI file 'QtEmbedApp.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef QTEMBEDAPP_H
#define QTEMBEDAPP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_openframeworks
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QWidget *ofWindow;
    QVBoxLayout *ofVerticalLayout;
    QMenuBar *menubar;

    void setupUi(QMainWindow *openframeworks)
    {
        if (openframeworks->objectName().isEmpty())
            openframeworks->setObjectName(QString::fromUtf8("openframeworks"));
        openframeworks->resize(448, 208);
        centralwidget = new QWidget(openframeworks);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        ofWindow = new QWidget(centralwidget);
        ofWindow->setObjectName(QString::fromUtf8("ofWindow"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ofWindow->sizePolicy().hasHeightForWidth());
        ofWindow->setSizePolicy(sizePolicy);
        ofVerticalLayout = new QVBoxLayout(ofWindow);
        ofVerticalLayout->setObjectName(QString::fromUtf8("ofVerticalLayout"));

        horizontalLayout->addWidget(ofWindow);

        openframeworks->setCentralWidget(centralwidget);
        menubar = new QMenuBar(openframeworks);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 448, 25));
        openframeworks->setMenuBar(menubar);

        retranslateUi(openframeworks);

        QMetaObject::connectSlotsByName(openframeworks);
    } // setupUi

    void retranslateUi(QMainWindow *openframeworks)
    {
        openframeworks->setWindowTitle(QApplication::translate("openframeworks", "openframeworks", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class openframeworks: public Ui_openframeworks {};
} // namespace Ui

QT_END_NAMESPACE

#endif // QTEMBEDAPP_H
