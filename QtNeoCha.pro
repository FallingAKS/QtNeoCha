QT       += core gui

greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    pic/lower/a.jpg \
    pic/lower/b.jpg \
    pic/lower/c.jpg \
    pic/lower/d.jpg \
    pic/lower/e.jpg \
    pic/lower/f.jpg \
    pic/lower/g.jpg \
    pic/lower/h.jpg \
    pic/lower/i.jpg \
    pic/lower/j.jpg \
    pic/lower/k.jpg \
    pic/lower/l.jpg \
    pic/lower/m.jpg \
    pic/lower/n.jpg \
    pic/lower/o.jpg \
    pic/lower/p.jpg \
    pic/lower/q.jpg \
    pic/lower/r.jpg \
    pic/lower/s.jpg \
    pic/lower/s0.jpg \
    pic/lower/s1.jpg \
    pic/lower/s2.jpg \
    pic/lower/s3.jpg \
    pic/lower/sd.jpg \
    pic/lower/sl.jpg \
    pic/lower/sn.jpg \
    pic/lower/sq.jpg \
    pic/lower/sr.jpg \
    pic/lower/su.jpg \
    pic/lower/t.png \
    pic/lower/u.jpg \
    pic/lower/v.jpg \
    pic/lower/w.jpg \
    pic/lower/x.jpg \
    pic/lower/y.jpg \
    pic/lower/z.jpg \
    \
    pic/upper/a.jpg \
    pic/upper/b.jpg \
    pic/upper/c.jpg \
    pic/upper/d.jpg \
    pic/upper/e.jpg \
    pic/upper/f.jpg \
    pic/upper/g.jpg \
    pic/upper/h.jpg \
    pic/upper/i.jpg \
    pic/upper/j.jpg \
    pic/upper/k.jpg \
    pic/upper/l.jpg \
    pic/upper/m.jpg \
    pic/upper/n.jpg \
    pic/upper/o.jpg \
    pic/upper/p.jpg \
    pic/upper/q.jpg \
    pic/upper/r.jpg \
    pic/upper/s.jpg \
    pic/upper/s0.jpg \
    pic/upper/s1.jpg \
    pic/upper/s2.jpg \
    pic/upper/s3.jpg \
    pic/upper/sd.jpg \
    pic/upper/sl.jpg \
    pic/upper/sn.jpg \
    pic/upper/sq.jpg \
    pic/upper/sr.jpg \
    pic/upper/su.jpg \
    pic/upper/t.png \
    pic/upper/u.jpg \
    pic/upper/v.jpg \
    pic/upper/w.jpg \
    pic/upper/x.jpg \
    pic/upper/y.jpg \
    pic/upper/z.jpg \
    \
    pic/cursor.jpg \
    pic/icon.png
