#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <QPushButton>

class MenuButton : public QPushButton
{
	Q_OBJECT
public:
	explicit MenuButton(const QString &text, QWidget *parent = nullptr);
};

#endif // MENUBUTTON_H
