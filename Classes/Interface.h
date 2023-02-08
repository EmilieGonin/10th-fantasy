#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;
using namespace cocos2d;

class Interface {
protected:
	Scene* _scene;
	//On stocke les diff�rents �l�ments d'interface � afficher
	std::vector<TextField*> _textFields;
	std::vector<Button*> _buttons;
	std::vector<Label*> _labels;

public:
	Interface();
	TextField* newTextField(std::string);
	Button* newButton(std::string);
	Label* newLabel(std::string);
	Vec2 center();
	float centerWidth();
	float centerHeight();

	//On retire tous les �l�ments d'interface cr��s
	void clean();

	//Setters
	void setScene(Scene*);
};