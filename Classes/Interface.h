#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;
using namespace cocos2d;

class Interface {
protected:
	Scene* _scene;
	//On stocke les différents éléments d'interface à afficher
	std::vector<TextField*> _textFields;
	std::vector<Button*> _buttons;
	std::vector<Label*> _labels;
	std::vector<Sprite*> _sprite;

public:
	Interface();

	//Création d'éléments automatiquement ajoutés dans la scène définie
	TextField* newTextField(std::string);
	Button* newButton(std::string);
	Button* newButton(std::string, std::string);
	Label* newLabel(std::string);
	Sprite* newSprite(std::string);

	//Des wrappers pour set les positions
	Vec2 center();
	float centerWidth();
	float centerHeight();

	//On retire tous les éléments d'interface créés
	void clean();

	//Setters
	void setScene(Scene*);
};