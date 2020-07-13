QT       += core gui sql multimedia network printsupport serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    amedicament.cpp \
    arduino.cpp \
    commande.cpp \
    commande1.cpp \
    compte.cpp \
    compte_medecin.cpp \
    connexion.cpp \
    creer_compte.cpp \
    crud_materiel.cpp \
    docteur2.cpp \
    main.cpp \
    login.cpp \
    materiel.cpp \
    medicament.cpp \
    modification.cpp \
    ordo.cpp \
    patient.cpp \
    rdv.cpp \
    secretaire.cpp \
    traitement.cpp

HEADERS += \
    admin.h \
    amedicament.h \
    arduino.h \
    commande.h \
    commande1.h \
    compte.h \
    compte_medecin.h \
    connexion.h \
    creer_compte.h \
    crud_materiel.h \
    docteur2.h \
    login.h \
    materiel.h \
    medicament.h \
    modification.h \
    ordo.h \
    patient.h \
    rdv.h \
    secretaire.h \
    traitement.h

FORMS += \
    admin.ui \
    amedicament.ui \
    commande.ui \
    compte_medecin.ui \
    creer_compte.ui \
    crud_materiel.ui \
    login.ui \
    modification.ui \
    secretaire.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
RC_ICONS = logo.ico
RESOURCES += \
    ressource.qrc
