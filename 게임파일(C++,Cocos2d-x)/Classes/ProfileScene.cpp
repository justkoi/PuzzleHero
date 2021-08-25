#include "stdafx.h"

Scene* ProfileScene::createScene()
{
	auto scene = Scene::create();

	auto layer = ProfileScene::create();
	scene->addChild(layer);

	return scene;
}

bool ProfileScene::init()
{
	if (!LayerColor::initWithColor(Color4B(255,255,255,255)))
	{
		return false;
	}
	if(bgsound == true)
		D_SOUNDMNG->playBackgroundMusic("BGM_MenuScene.mp3");
	
	auto profile = Sprite::create("BackGround_StageMenu.png");
	profile->setPosition(200,1000);
	profile->setScale(300./64.);
	this->addChild(profile);

	auto hp = Sprite::create("hp.png");
	hp->setPosition(520,1100);
	this->addChild(hp,1);

	auto mp = Sprite::create("mp.png");
	mp->setPosition(520,1000);
	this->addChild(mp,1);

	auto atk=Sprite::create("atk.png");
	atk->setPosition(520,900);
	this->addChild(atk,1);
	
	auto hplabel = LabelTTF::create(StringUtils::format("%d",g_nHeroHpConst), "Thonburi", 70);
	hplabel->setColor(Color3B(0,0,0));
	hplabel->setPosition(520,1100);
	this->addChild(hplabel,2);

	auto mplabel = LabelTTF::create(StringUtils::format("%d",g_nHeroMpConst), "Thonburi", 70);
	mplabel->setColor(Color3B(0,0,0));
	mplabel->setPosition(520,1000);
	this->addChild(mplabel,2);

	auto atklabel = LabelTTF::create(StringUtils::format("%d",g_nHeroAtk), "Thonburi", 70);
	atklabel->setColor(Color3B(0,0,0));
	atklabel->setAnchorPoint(Point(0,0.5));
	atklabel->setPosition(520,900);
	this->addChild(atklabel,2);
	
	for(int i=0;i<6;++i){
		auto skill = Sprite::create(StringUtils::format("Button_Skill_%d_3.png",i+1));
		skill->setPosition(150+200*(i%3),700-(i/3)*220);
		skill->setTag(i);
		if(!selSkill[i])
		{
			skill->setOpacity(75);
		}
		this->addChild(skill,1);

		auto addbtn = Sprite::create("addbtn.png");
		addbtn->setPosition(200+200*(i%3),590-(i/3)*220);
		addbtn->setTag(100+i);
		this->addChild(addbtn);

		auto minusbtn = Sprite::create("minusbtn.png");
		minusbtn->setPosition(100+200*(i%3),590-(i/3)*220);
		minusbtn->setTag(200+i);
		this->addChild(minusbtn);

		auto label = Label::createWithTTF(StringUtils::format("%d/6",g_Skill[i]),"Thonburi",30);
		label->setColor(Color3B(0,0,0));
		label->setPosition(150+200*(i%3),650-(i/3)*220);
		label->setTag(300+i);
		if(!selSkill[i])
		{
			label->setOpacity(75);
		}
		this->addChild(label,2);
	}

	auto resetbtn = Sprite::create("resetbtn.png");
	resetbtn->setPosition(170,250);
	resetbtn->setTag(10);
	this->addChild(resetbtn);

	auto selectbtn = Sprite::create("selectbtn.png");
	selectbtn->setPosition(470,250);
	selectbtn->setTag(11);
	this->addChild(selectbtn);

	auto backbtn = Sprite::create("backbtn.png");
	backbtn->setPosition(D_PHONE_WIDTH/2-10,100);
	backbtn->setTag(12);
	this->addChild(backbtn);

	selectsw=0;
	sw=0;

	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(ProfileScene::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(ProfileScene::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(ProfileScene::onTouchesEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener,1);
	
	return true;
}

void ProfileScene::onTouchesBegan(const std::vector<Touch*>&touches, Event *unused_event)
{
	for (auto iter = touches.begin(); iter != touches.end(); iter++){
		MousePoint=(*iter)->getLocation();
		if(selectsw==0)
		{
			auto spr=(Sprite*)this->getChildByTag(10);
			Rect rect = spr->getBoundingBox();
			if(rect.containsPoint(MousePoint))
			{
				selectnum=10;
				sw=1;
				spr->setScale(0.8);
				if(efsound == true)		
					D_SOUNDMNG->playEffect("Select.mp3");
				break;
			}
			spr=(Sprite*)this->getChildByTag(11);
			rect = spr->getBoundingBox();
			if(rect.containsPoint(MousePoint))
			{
				selectnum=11;
				sw=1;
				spr->setScale(0.8);
				if(efsound == true)		
					D_SOUNDMNG->playEffect("Select.mp3");
				break;
			}
			spr=(Sprite*)this->getChildByTag(12);
			rect = spr->getBoundingBox();
			if(rect.containsPoint(MousePoint))
			{
				selectnum=12;
				sw=1;
				spr->setScale(0.8);
				if(efsound == true)		
					D_SOUNDMNG->playEffect("Select.mp3");
				break;
			}
			for(int j=0; j<6;++j)
			{
				spr=(Sprite*)this->getChildByTag(200+j);
				rect=spr->getBoundingBox();
				if(rect.containsPoint(MousePoint))
				{
					sw=1;
					if(efsound == true)		
						D_SOUNDMNG->playEffect("Select.mp3");
					--g_Skill[j];
					if(j<4)
					{
						if(g_Skill[j]<1)
						{
							g_Skill[j]=1;
						}
					}
					else
					{
						if(selSkill[j])
						{
							if(g_Skill[j]<1)
							{
								g_Skill[j]=1;
							}
						}
						else
						{
							if(g_Skill[j]<0)
							{
								g_Skill[j]=0;
							}
						}
					}
					auto label = (Label*)this->getChildByTag(300+j);
					label->setString(StringUtils::format("%d/6",g_Skill[j]));
					char ms[7];
					sprintf(ms,"skill%d",j+1);
					UserDefault::getInstance()->setIntegerForKey(ms,g_Skill[j]);
					break;
				}
				spr=(Sprite*)this->getChildByTag(100+j);
				rect=spr->getBoundingBox();
				if(rect.containsPoint(MousePoint))
				{
					sw=1;
					if(efsound == true)		
						D_SOUNDMNG->playEffect("Select.mp3");
					++g_Skill[j];
					if(g_Skill[j]>6)
					{
						g_Skill[j]=6;
					}
					auto label = (Label*)this->getChildByTag(300+j);
					label->setString(StringUtils::format("%d/6",g_Skill[j]));
					char ms[7];
					sprintf(ms,"skill%d",j+1);
					UserDefault::getInstance()->setIntegerForKey(ms,g_Skill[j]);
					break;
				}
			}
			if(sw==1)
			{
				sw=0;
				break;
			}
		}
		else if(selectsw==1)
		{
			auto spr=(Sprite*)this->getChildByTag(11);
			Rect rect = spr->getBoundingBox();
			if(rect.containsPoint(MousePoint))
			{
				selectnum=11;
				sw=1;
				spr->setScale(0.8);
				break;
			}
			for(int j=0;j<6;++j)
			{
				spr=(Sprite*)this->getChildByTag(j);
				rect=spr->getBoundingBox();
				if(rect.containsPoint(MousePoint))
				{
					if(g_Skill[j]!=0)
					{
						selSkill[j]=!selSkill[j];
						if(selSkill[j])
						{
							spr->setOpacity(1000);
							auto label = (Label*)this->getChildByTag(300+j);
							label->setOpacity(1000);
						}
						else
						{
							spr->setOpacity(75);
							auto label = (Label*)this->getChildByTag(300+j);
							label->setOpacity(75);
						}
						char ms[10];
						sprintf(ms,"selskill%d",j+1);
						UserDefault::getInstance()->setBoolForKey(ms,selSkill[j]);
					}
				}
			}
		}
	}
}

void ProfileScene::onTouchesMoved(const std::vector<Touch*>&touches, Event *unused_event)
{
	if(sw==1)
	{
		for (auto iter = touches.begin(); iter != touches.end(); iter++){
			MousePoint=(*iter)->getLocation();
			if(selectsw==0)
			{
				auto spr=(Sprite*)this->getChildByTag(selectnum);
				Rect rect=spr->getBoundingBox();
				if(!rect.containsPoint(MousePoint))
				{
					sw=0;
					spr->setScale(1.0);
					break;
				}
			}
			if(selectsw==1)
			{
				auto spr=(Sprite*)this->getChildByTag(selectnum);
				Rect rect=spr->getBoundingBox();
				if(!rect.containsPoint(MousePoint))
				{
					sw=0;
					spr->setScale(1.0);
					break;
				}
			}
		}
	}
}

void ProfileScene::onTouchesEnded(const std::vector<Touch*>&touches, Event *unused_event)
{
	if(sw==1)
	{
		sw=0;
		if(selectsw==0)
		{
			auto spr = (Sprite*)this->getChildByTag(selectnum);
			spr->setScale(1.0);
			if(selectnum==10)
			{
				for(int i=0;i<6;++i)
				{
					auto skill = (Sprite*)this->getChildByTag(i);
					auto label = (Label*)this->getChildByTag(300+i);
					if(i<4)
					{
						g_Skill[i]=1;
						selSkill[i]=true;
						skill->setOpacity(1000);
						label->setOpacity(1000);
					}
					else
					{
						g_Skill[i]=0;
						selSkill[i]=false;
						skill->setOpacity(75);
						label->setOpacity(75);
					}
					char ms[7],ms2[10];
					sprintf(ms,"skill%d",i+1);
					sprintf(ms2,"selskill%d",i+1);
					UserDefault::getInstance()->setIntegerForKey(ms,g_Skill[i]);
					UserDefault::getInstance()->setBoolForKey(ms2,selSkill[i]);
					label->setString(StringUtils::format("%d/6",g_Skill[i]));
				}
			}
			else if(selectnum==11)
			{
				spr->setOpacity(75);
				selectsw=1;
			}
			else
			{
				changeScene();
			}
		}
		else if(selectsw==1)
		{
			auto spr = (Sprite*)this->getChildByTag(selectnum);
			spr->setScale(1.0);	
			int count=0;
			for(int i=0;i<6;++i)
			{
				if(selSkill[i])
				{
					++count;
				}
			}
			if(count==4)
			{
				if(selectnum==11)
				{
					spr->setOpacity(1000);
					selectsw=0;
				}
			}
		}
	}
}

void ProfileScene::changeScene()
{
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	auto scene = TransitionFade::create(1.0,StageScene::createScene());
	Director::getInstance()->replaceScene(scene);
}