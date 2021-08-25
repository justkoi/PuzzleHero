#ifndef __LOGO_SCENE_H__
#define __LOGO_SCENE_H__

#include "stdafx.h"

USING_NS_CC;

class LogoScene : public Layer
{
public:

	static Scene* createScene();

	virtual bool init();
	CREATE_FUNC(LogoScene);
	
	void changeScene(float dt);

};

#endif