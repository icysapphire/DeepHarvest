#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <qt/QtWidgets/QWidget>

/**
 * @class MainScreen
 * @brief The MainScreen class represents the startup screen.
 */

class MainScreen: public QWidget {
	Q_OBJECT
public:
	MainScreen(QWidget * parent=0);
	void play(const int mode);
private:
	char* argv;
public slots:
	void play_1() {
		play(1);
	}
	void play_2() {
		play(2);
	}
};

#endif // MAINSCREEN_H
