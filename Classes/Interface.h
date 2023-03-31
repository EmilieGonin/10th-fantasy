#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameManager.h"

using namespace cocos2d::ui;
using namespace cocos2d;

class Interface {
protected:
	Scene* _scene;
	//On stocke les différents éléments d'interface à afficher
	std::vector<TextField*> _textFields;
	std::vector<Button*> _buttons;
	std::vector<Label*> _labels;
	std::vector<Sprite*> _sprites;

	int _nextText;

public:
	Interface();

	//Création d'éléments automatiquement ajoutés dans la scène définie
	TextField* newTextField(std::string);
	Button* newButton(std::string);
	Button* newButton(std::string, std::string);
	Button* newButton(std::string, std::string, int);
	Label* newLabel(std::string);
	Label* newLabel(std::string, int);
	Label* newLabel(std::string, int, int, int);
	Label* newOutlinedLabel(std::string);
	Label* newOutlinedLabel(std::string, int);
	Sprite* newSprite(std::string);
	Sprite* newSprite(std::string, int);
	Sprite* newSprite(std::string, Sprite*);

	//Des wrappers pour set les positions
	Vec2 center();
	float centerWidth();
	float centerHeight();
	float top(float);

	//On retire tous les éléments d'interface créés
	void clean();
	void newTextBox(std::string);

	//Setters
	void setScene(Scene*);
};