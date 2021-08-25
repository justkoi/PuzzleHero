#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "stdafx.h"

USING_NS_CC;

class MenuScene : public LayerColor
{
public:
	


	static Scene* createScene();

	virtual bool init();
	CREATE_FUNC(MenuScene);
	int countnum;
	void Update(float delta);
	void loadData();

	virtual void onTouchesBegan(const std::vector<Touch*>&touches, Event *unused_event);
};

#endif