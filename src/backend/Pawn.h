#ifndef PAWN_H
#define PAWN_H

#include <QObject>

class Pawn : public QObject
{
	Q_OBJECT
public:
	explicit Pawn(int playerId, QObject *parent = nullptr);

	int playerId() const;
	void bust();

	int traveledDistance() const;
	void increaseTraveledDistance(int fieldCount);

private:
	int m_playerId;
	int m_traveledDistance;

signals:
	void busted();
};

#endif // PAWN_H
