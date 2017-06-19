#include "res.h"
#include <qt/QtWidgets/QApplication>
#include "GameView.h"

#include <stdlib.h> // srand and rand
#include <time.h> 
#include "MainScreen.h"

/*! \mainpage 
 * DeepHarvest is a simple game written to play with the basics of C++ software development.
 * 
 * This project features external libraries integration (tensorflow, opencv) and graphic environment (Qt5).
 * 
 * PPS Project - 2016-2017 - Simone Marullo
 *
 * \section howto How to run
 * Double click on launcher.sh; hopefully it will correctly manage static libraries linking and path detection.
 */

// make game a global variable
GameView * game_v;

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	srand(time(0));
	MainScreen main;
	main.setFixedSize(800,540);
	main.show();

	return a.exec();
}
