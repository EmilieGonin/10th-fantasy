#include "Interface.h"

TextField* newTextField(std::string string) {
	TextField* textField = TextField::create(string, "Arial", 30);
	textField->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::BEGAN) {
				log("began");
			}
		}
	);
	
	return textField;
}

Button* newButton(std::string string) {
	Button* button = Button::create();
	button->setTitleText(string);

	return button;
}

Label* newLabel(std::string string) {
	Label* label = Label::createWithTTF(string, "fonts/arial.ttf", 25);
	return label;
}

Vec2 center() {
	Size visibleSize = Director::getInstance()->getVisibleSize();

	return cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2);
}

float centerWidth() {
	Size visibleSize = Director::getInstance()->getVisibleSize();

	return visibleSize.width / 2;
}

float centerHeight() {
	Size visibleSize = Director::getInstance()->getVisibleSize();

	return visibleSize.height / 2;
}