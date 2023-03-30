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
		_scene->addChild(button);
	}

	return button;
}

Button* Interface::newButton(std::string string, std::string sprite, int layer) {
	Button* button = Button::create(sprite, sprite, sprite);
	button->setTitleText(string);
	_buttons.push_back(button);

	if (_scene != nullptr) {
		_scene->addChild(button, layer);
	}

	return button;
}

Label* Interface::newLabel(std::string string) {
	Label* label = Label::createWithTTF(string, "fonts/arial.ttf", 25);
	_labels.push_back(label);

	if (_scene != nullptr) {
		_scene->addChild(label);
	}

	return label;
}

Label* Interface::newLabel(std::string string, int layer) {
	Label* label = Label::createWithTTF(string, "fonts/arial.ttf", 25);
	_labels.push_back(label);

	if (_scene != nullptr) {
		_scene->addChild(label, layer);
	}

	return label;
}

Label* Interface::newLabel(std::string string, int posX, int posY, int layer) {
	Label* label = Label::createWithTTF(string, "fonts/arial.ttf", 20);
	_labels.push_back(label);
	label->setPosition(posX, posY);
	label->setAnchorPoint(Vec2::ZERO);

	if (_scene != nullptr) {
		_scene->addChild(label, layer);
	}

	return label;
}

void Interface::newTextBox(std::string story) {
	Sprite* _textBox = Sprite::create("Button/Rectangle.png");
	_textBox->setPosition(100, 280);
	_textBox->setScale(0.5);
	_textBox->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);

	newLabel(story, 100, 450, 11);

	if (_scene != nullptr) {
		_scene->addChild(_textBox, 10);
	}
}

Sprite* Interface::newSprite(std::string filename)
{
	Sprite* sprite = Sprite::create(filename);
	_sprites.push_back(sprite);

	if (_scene != nullptr) {
		_scene->addChild(sprite);
	}

	return sprite;
}

Vec2 Interface::center() {
	//Taille de la fenêtre de jeu
	Size size = Director::getInstance()->getVisibleSize();
	return cocos2d::Vec2(size.width / 2, size.height / 2);
}

float Interface::centerWidth() {
	//Taille de la fenêtre de jeu
	Size size = Director::getInstance()->getVisibleSize();
	return size.width / 2;
}

float Interface::centerHeight() {
	//Taille de la fenêtre de jeu
	Size size = Director::getInstance()->getVisibleSize();
	return size.height / 2;
}

float Interface::top(float height) {
	//height = height of the element
	//use getLineHeight() for labels
	Size size = Director::getInstance()->getVisibleSize();
	return size.height - height;
}

void Interface::clean() {
	if (!_textFields.empty()) {
		for (TextField* item : _textFields) {
			_scene->removeChild(item);
		}
		_textFields.clear();
	}

	if (!_buttons.empty()) {
		for (Button* item : _buttons) {
			_scene->removeChild(item);
		}
		_buttons.clear();
	}

	if (!_labels.empty()) {
		for (Label* item : _labels) {
			_scene->removeChild(item);
		}
		_labels.clear();
	}
	if (!_sprites.empty()) {
		for (Sprite* item : _sprites) {
			_scene->removeChild(item);
		}
		_sprites.clear();
	}
}

void Interface::setScene(Scene* scene) { _scene = scene; }