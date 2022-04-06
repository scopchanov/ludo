#include "ScoreDisplay.h"

ScoreDisplay::ScoreDisplay(QWidget *parent) :
	QLabel{parent}
{
	setFixedHeight(100);
	setAlignment(Qt::AlignCenter);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}
