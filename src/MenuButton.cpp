#include "MenuButton.h"

MenuButton::MenuButton(const QString &text, QWidget *parent) :
	QPushButton{text, parent}
{
	setFixedSize(250, 48);
	setFlat(true);
}
