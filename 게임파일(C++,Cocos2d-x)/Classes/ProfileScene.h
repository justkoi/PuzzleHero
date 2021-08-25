#ifndef __PROFILE_SCENE_H__
#define __PROFILE_SCENE_H__

#include "stdafx.h"

USING_NS_CC;

class ProfileScene : public LayerColor
{
public:

	static Scene* createScene();

	Point MousePoint;
	int selectsw;
	int selectnum;
	int sw;

	virtual bool init();
	CREATE_FUNC(ProfileScene);
	
	virtual void onTouchesBegan(const std::vector<Touch*>&touches, Event *unused_event);
	virtual void onTouchesMoved(const std::vector<Touch*>&touches, Event *unused_event);
	virtual void onTouchesEnded(const std::vector<Touch*>&touches, Event *unused_event);
	void changeScene();

};

#endif