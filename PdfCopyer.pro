HEADERS       = mainwindow.h \
	clipboardprocessor.h \
	processmode.h \
	qhotkey.h \
	qhotkey_p.h
SOURCES       = main.cpp \
				clipboardprocessor.cpp \
				mainwindow.cpp \
				qhotkey.cpp \
				qhotkey_win.cpp
RESOURCES     = systray.qrc

QT += widgets

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/desktop/systray
INSTALLS += target
