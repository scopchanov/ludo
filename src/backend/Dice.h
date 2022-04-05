#ifndef DICE_H
#define DICE_H

#include <QObject>

class Dice : public QObject
{
	Q_OBJECT
public:
	explicit Dice(QObject *parent = nullptr);

	int score() const;
	void roll();

private:
	int m_score;
};

#endif // DICE_H
