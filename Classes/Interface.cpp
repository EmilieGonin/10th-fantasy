#include "Interface.h"

Interface::Interface() {
	//_scene = Director::getInstance()->getRunningScene();
	_scene = nullptr;
}

TextField* Interface::newTextField(std::string string) {
	TextField* textField = TextField::create(string, "Arial", 30);
	textField->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::BEGAN) {
				log("began");
			}
		}
	);
	_textFields.push_back(textField);

	if (_scene != nullptr) {
		_scene->addChild(textField);
	}

	return textField;
}

Button* Interface::newButton(std::string string) {
	Button* button = Button::create();
	button->setTitleText(string);
	_buttons.push_back(button);

	if (_scene != nullptr) {
		_scene->addChild(button);
	}

	return button;
}

Button* Interface::newButton(std::string string, std::string sprite) {
	Button* button = Button::create(sprite, sprite, sprite);
	button->setTitleText(string);
	_buttons.push_back(button);

	if (_scene != nullptr) {
		_scene->addChild(button, 1);
	}

	return button;
}

Label* Interface::newLabel(std::string string) {
	Label* label = Label::createWithTTF(string, "fonts/arial.ttf", 25);
	_labels.push_back(label);

	if (_scene != nullptr) {
		_scene->addChild(label, 2);
	}

	return label;
}

Sprite* Interface::newSprite(std::string filename)
{
	Sprite* sprite = Sprite::create(filename);
	_sprite.push_back(sprite);

	if (_scene != nullptr) {
		_scene->addChild(sprite);
	}

	return sprite;
}

Vec2 Interface::center() {
	//Taille de la fen�tre de jeu
	Size size = Director::getInstance()->getVisibleSize();
	return cocos2d::Vec2(size.width / 2, size.height / 2);
}

float Interface::centerWidth() {
	//Taille de la fen�tre de jeu
	Size size = Director::getInstance()->getVisibleSize();
	return size.width / 2;
}

float Interface::centerHeight() {
	//Taille de la fen�tre de jeu
	Size size = Director::getInstance()->getVisibleSize();
	return size.height / 2;
}

void Interface::clean() {
	if (!_textFields.empty()) {
		for (TextField* item : _textFields) {
			_scene->removeChild(item);
		}
	}

	if (!_buttons.empty()) {
		for (Button* item : _buttons) {
			_scene->removeChild(item);
		}
	}

	if (!_labels.empty()) {
		for (Label* item : _labels) {
			_scene->removeChild(item);
		}
	}
	if (!_sprite.empty()) {
		for (Sprite* item : _sprite) {
			_scene->removeChild(item);
		}
	}
}

void Interface::setScene(Scene* scene) { _scene = scene; }