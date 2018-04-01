#ifndef __CGMENUBAR_H__
#define __CGMENUBAR_H__

#include "CGUI.h"
#include <vector>
#include <string>

using namespace std;

#define MENU_SIZE_W 50
#define MENU_SIZE_H 30
#define MENU_ITEM_SIZE_W 50
#define MENU_ITEM_SIZE_H 30

// メニューバーの項目を選択したときの項目
class MenuObjectItem :public CGUI{
	string label;
	int label_x, label_y;
public:
	MenuObjectItem();
	void setLabel(string a){label = a;}
	void setLabelPos(int x, int y){
		label_x = x;
		label_y = y;
	}
	int getLabelPosX(){return label_x;}
	int getLabelPosY(){return label_y;}
	void draw();
};

//メニューバーに表示される項目
class MenuObject :public CGUI{
	vector<MenuObjectItem *> item_list;
	string label;
	int label_x, label_y;
	int menuObjectClickedState; /* メニューバーの項目がクリックされたときの状態 
															この変数の値はオートマトンの状態を示す．
															(0,1のとき非表示　2, 3のとき表示) */
public:
	MenuObject();
	~MenuObject();
	void setMenuObjectItem(MenuObjectItem *x);
	void draw();
	void setLabel(string a) { label = a; }
	void setLabelPos(int x, int y) {
		label_x = x;
		label_y = y;
	}
	int getLabelPosX() { return label_x; }
	int getLabelPosY() { return label_y; }
};

// メニューバー
class CMenubar :public CGUI{
	vector<MenuObject *> mo_list;
public:
	CMenubar();
	void setMenuObject(MenuObject *a);
	void draw();

	~CMenubar();
};

#endif
