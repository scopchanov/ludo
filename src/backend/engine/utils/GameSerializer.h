/**
MIT License

Copyright (c) 2022-2025 Michael Scopchanov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef GAMESERIALIZER_H
#define GAMESERIALIZER_H

#include <QJsonObject>

class GamePrivate;
class Board;
class Path;

class GameSerializer
{
public:
	explicit GameSerializer(GamePrivate *game_p);

	QJsonObject serialize() const;
	void deserialize(const QJsonObject &json);

private:
	QJsonObject serializeBoard() const;
	QJsonArray serializeWinners() const;
	QJsonArray serializeBaseAreas() const;
	QJsonArray serializeHomeAreas() const;
	QJsonArray serializePath(Path *path) const;
	void deserializeBoard(const QJsonObject &json);
	void deserializeWinners(const QJsonArray &winners);
	void deserializeBaseAreas(const QJsonArray &baseAreas);
	void deserializeHomeAreas(const QJsonArray &homeAreas);
	void deserializePath(Path *path, const QJsonArray &pawns);

	GamePrivate *_game_p;
};

#endif // GAMESERIALIZER_H
