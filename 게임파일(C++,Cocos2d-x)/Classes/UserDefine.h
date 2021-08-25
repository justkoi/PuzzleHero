#pragma once
//

#define D_BLOCK_CHANGE_SPEED 300.0f

#define RadToDeg(x) (57.29577951f * x)
#define DegToRad(x) (0.017453293f * x)

#define D_AGRO_FIRSTGAIN 35
#define D_AGRO_ATTACKGAIN 4

#define D_HERO_ATTACK_WIDTH 20

#define D_HP_PAD 10

#define D_TILE_SCALE 1.0f
//
//#define D_SOUND_MAX 4
//
#define D_PHONE_WIDTH 720
#define D_PHONE_HEIGHT 1280
//
#define D_SCREEN_SCALE_WIDTH(s) ((D_PHONE_WIDTH/100) * s)
#define D_SCREEN_SCALE_HEIGHT(s) ((D_PHONE_HEIGHT/100) * s)


#define D_SOUNDMNG CocosDenshion::SimpleAudioEngine::getInstance()

#define D_HERO_WIDTH (60 * D_TILE_SCALE)
#define D_HERO_HEIGHT (60 * D_TILE_SCALE)

#define D_TILE_WIDTH (64 * D_TILE_SCALE)
#define D_TILE_HEIGHT (64 * D_TILE_SCALE)

#define D_TILE_ENTERING_SENS ((D_TILE_WIDTH) * (25/100))

//!< Sensabilty //< 타일 빨려들어가는 감도 기본은 각 양쪽 25%로써 기본타일크기 x 25/100
//
#define D_MENU_TITLE_X 240
#define D_MENU_TITLE_Y 700
//
#define D_BLOCK_WIDTH 75.0f
#define D_BLOCK_HEIGHT 75.0f
//
#define D_BLOCK_MAX (D_BLOCKMAP_WIDTH * (D_BLOCKMAP_HEIGHT - 1))
#define D_BLOCKMAP_MAX (D_BLOCKMAP_WIDTH * (D_BLOCKMAP_HEIGHT))
//
#define D_BLOCK_SPEED 650.0f
#define D_BLOCK_PLUSSPEED 120.0f
////
#define	D_LINE_START_X 48.0f + 10.0f
#define	D_LINE_START_Y 760.0f + 50.0f + 262.0f
////!< DevOption 696.0f 734.0f
#define D_BLOCK_BOUNCE_FOWER 120.0f //90.0f
#define D_BLOCK_BOUNCE_FOWER_LOW 65.5f //35.5f
#define D_BLOCK_BOUNCE_HURISTIC 1.4f

#define D_BLOCKITEM_PARTICLE_MAX 15

#define D_PLAYTIME 60
//
//#define D_POP_LOOP 0
//
#define D_BLOCKMAP_WIDTH 9
#define D_BLOCKMAP_HEIGHT 11

#define D_SKILL_1_COST 20
#define D_SKILL_2_COST 30
#define D_SKILL_3_COST 20
#define D_SKILL_3_HEAL 20
#define D_SKILL_4_COST 30

#define D_BLOCK_ITEM_MP_PLUS 10
#define D_BLOCK_ITEM_HP_PLUS 20
//

//#define	D_LINE_START_X -192.0f + 300.0f
//#define	D_LINE_START_Y 340.0f + 300.0f
//
#define D_SCORE_POP 50
#define D_SCORE_POP_MUL 0.25f 

//
//#define D_SCORE_POP_PLUS 10 //!< 5이상 터트리면 + 100 * 갯수
//#define D_SCORE_POP_COMBO 0.2f //!< 콤보 추가 기본 배수
//#define D_SCORE_POP_LIGHTNING 10 //!< 아이템 전기로 터트린 점수
//#define D_SCORE_POP_BOMB 10 //!< 아이템 폭탄으로 터트린 점수
//#define D_SCORE_LINE 40
//
//#define D_CAM_Z_FIXED 695.0f
//
//#define D_PHOTOSHOP_Y(value) (D_PHONE_HEIGHT - value)
//
//
////#define D_SCENE_CHANGE_EFFECT_DOWN(scene) CCScene *pScene = CCTransitionSlideInL::transitionWithDuration(1.0f,scene);
//
////#define D_SCENE_CHANGE_EFFECT_DOWN(scene) CCScene *pScene = CCTransitionSlideInR::transitionWithDuration(1.0f,scene);
//
////#define D_SCENE_CHANGE_EFFECT_DOWN(scene) CCScene *pScene = CCTransitionSlideInL::transitionWithDuration(1.0f,scene);
//
////#define D_SCENE_CHANGE_EFFECT_DOWN(scene) CCScene *pScene = CCTransitionSlideInR::transitionWithDuration(1.0f,scene);
//
////m_pLoading->setVisible(true); \
//	
//
//
//#define D_SCENE_CHANGE_EFFECT_UP(scene) CCScene *pScene = CCTransitionFadeUp::transitionWithDuration(1.0f,scene); //m_pLoading->setVisible(true);
//
//#define D_SCENE_CHANGE_EFFECT_DOWN(scene) CCScene *pScene = CCTransitionFadeDown::transitionWithDuration(1.0f,scene); //m_pLoading->setVisible(true);
//
//#define D_SCENE_CHANGE_EFFECT_FADE(scene) CCScene *pScene = CCTransitionFade::transitionWithDuration(1.0f,scene); //m_pLoading->setVisible(true);
//
//
//
#define D_BASIC_PHONE_WIDTH 800
#define D_BASIC_PHONE_HEIGHT 480
//
#define D_SCALE_WIDTH 1.0f
#define D_SCALE_HEIGHT 1.0f
//
//#define D_POPTIME_MAX 1.0f
//
//
//#define D_STAGEMENU_START_X - 150.0f
//#define D_STAGEMENU_START_Y   300.0f
//
//#define D_STAGEMENU_DISTANCE 150.0f
//#define D_STAGEMENU_WIDTH_NUMBER 3
//
//#define D_STAGEMENU_WIDTH 140
//#define D_STAGEMENU_HEGIHT 140
//
//#define D_STAGE_MAX 33
//
//#define D_BUTTON_SOUND "StageStart.mp3"