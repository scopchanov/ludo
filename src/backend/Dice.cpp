#include "Dice.h"
#include <QRandomGenerator>

Dice::Dice(QObject *parent) :
	QObject{parent},
	_score{0}
{

}

int Dice::score() const
{
	return _score;
}

void Dice::roll()
{
	_score = QRandomGenerator::global()->bounded(1, 7);
}
