#include "CMenubar.h"
#include "FontManager.h"
#include "CText.h"


MenuObjectItem::MenuObjectItem() {
	FontManager *a = FontManager::getInstance();
	setSize(GetDrawStringWidthToHandle(label.c_str(), label.length(), a->getFontHandle("Consolas-10")), 16);
}

MenuObject::MenuObject(){
	item_list.clear();
	FontManager *a = FontManager::getInstance();
	setSize(GetDrawStringWidthToHandle(label.c_str(), label.length(), a->getFontHandle("Consolas-10")), 16);
	this->menuObjectClickedState = 0;
}

MenuObject::~MenuObject() {
	while (!item_list.empty()) {
		delete item_list.back();
		item_list.pop_back();
	}
}

CMenubar::CMenubar(){
	mo_list.clear();
}

CMenubar::~CMenubar() {
	while (!(mo_list.empty())) {
		delete mo_list.back();
		mo_list.pop_back();
	}
}

void MenuObjectItem::draw() {
	FontManager *a = FontManager::getInstance();
	CText item(getPosX(), getPosY(), label, GetColor(0, 255, 0), a->getFontHandle("Consolas-20"));
	DrawBox(getPosX(), getPosY(), getPosX() + getSizeWidth(), getPosY() + getSizeHeight(), GetColor(255, 255, 255), FALSE);
	item.draw();
	//DrawString(getPosX(), getPosY(), "TEST", GetColor(0, 255, 0));
}

void MenuObject::setMenuObjectItem(MenuObjectItem *x) {
	item_list.push_back(x);
}

void MenuObject::draw() {
	FontManager *a = FontManager::getInstance();
	int mouseX, mouseY;
	CText item(getPosX(), getPosY(), label, GetColor(0, 255, 0), a->getFontHandle("Consolas-20"));
	DrawBox(getPosX(), getPosY(), getPosX() + getSizeWidth(), getPosY() + getSizeHeight(), GetColor(255, 255, 255), FALSE);
	item.draw(); // メニューバーの項目の描画
	GetMousePoint(&mouseX, &mouseY);

	/* ここでの変数menuObjectClickedStateは，オートマトンの状態を表している．*/

	// マウスを項目上でクリックしたらその項目に関する項目が現れる
	if ((menuObjectClickedState == 1) && (mouseX > getPosX()) && (mouseY > getPosY()) &&
		(mouseX < (getPosX() + getSizeWidth())) && (mouseY < (getPosY() + getSizeHeight())) &&
		(GetMouseInput() & MOUSE_INPUT_LEFT)) {
		menuObjectClickedState = 2;
	}

	// 項目をクリックして放したとき
	if ((menuObjectClickedState == 2)  &&
		(mouseX > getPosX()) && (mouseY > getPosY()) &&
		(mouseX < (getPosX() + getSizeWidth())) && (mouseY < (getPosY() + getSizeHeight())) &&
		(GetMouseInput() == 0)) {
		menuObjectClickedState = 3;
	}
	// 項目をクリックして項目を閉じる
	if ((menuObjectClickedState == 3) &&
		(mouseX > getPosX()) && (mouseY > getPosY()) &&
		(mouseX < (getPosX() + getSizeWidth())) && (mouseY < (getPosY() + getSizeHeight())) &&
		(GetMouseInput() & MOUSE_INPUT_LEFT)) {
		menuObjectClickedState = 0;
	}
	// 画面のかき替えが早すぎるので項目をクリックして閉じたいときクリックしたままでも閉じたことにする処理
	if ((menuObjectClickedState == 0) &&
		(mouseX > getPosX()) && (mouseY > getPosY()) &&
		(mouseX < (getPosX() + getSizeWidth())) && (mouseY < (getPosY() + getSizeHeight())) &&
		(GetMouseInput() == 0)) {
		menuObjectClickedState = 1;
	}

	// メニューの項目を表示．項目を再びクリックしたときはメニューの項目を閉じる
	if ((menuObjectClickedState == 2) || (menuObjectClickedState == 3)) {
		for (unsigned int i = 0;i < item_list.size();i++) {
			item_list[i]->draw();
		}
	}
}

void CMenubar::setMenuObject(MenuObject *a){
	mo_list.push_back(a);
}

void CMenubar::draw(){
	DrawBox(0, 0, WINDOW_W, MENU_SIZE_H, GetColor(255, 255, 255), FALSE);
	for(unsigned int i=0;i<mo_list.size();i++){
		mo_list[i]->draw();
	}
}

