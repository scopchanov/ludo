#include "Dice.h"
#include <QRandomGenerator>

Dice::Dice(QObject *parent) :
	QObject{parent},
	m_score{0}
{

}

int Dice::score() const
{
	return m_score;
}

void Dice::roll()
{
	m_score = QRandomGenerator::global()->bounded(1, 7);
}
