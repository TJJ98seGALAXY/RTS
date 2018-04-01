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

// ���j���[�o�[�̍��ڂ�I�������Ƃ��̍���
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

//���j���[�o�[�ɕ\������鍀��
class MenuObject :public CGUI{
	vector<MenuObjectItem *> item_list;
	string label;
	int label_x, label_y;
	int menuObjectClickedState; /* ���j���[�o�[�̍��ڂ��N���b�N���ꂽ�Ƃ��̏�� 
															���̕ϐ��̒l�̓I�[�g�}�g���̏�Ԃ������D
															(0,1�̂Ƃ���\���@2, 3�̂Ƃ��\��) */
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

// ���j���[�o�[
class CMenubar :public CGUI{
	vector<MenuObject *> mo_list;
public:
	CMenubar();
	void setMenuObject(MenuObject *a);
	void draw();

	~CMenubar();
};

#endif
