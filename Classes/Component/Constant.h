#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#define SET_DATA(mapName,dataName,typeName)\
set##dataName(mapName[#dataName].as##typeName##())

#define WEAPON_JUDGE(string,weaponType)\
if(string==#weaponType)\
weapon=new(std::nothrow)##weaponType

//dataName需要双引号
#define VALUE_AT(mapName,dataName,typeName)\
mapName[dataName].as##typeName##()



#define HERO_BORN Vec2(80,80)

//Flag
#define FLAG_NOTHING  0
#define FLAG_MONSTER  1
#define FLAG_HERO     2
#define FLAG_NOHURT   3

//需要双引号
#define PATH_DATA             std::string("data/")
#define PATH_PICTURE_WEAPON   std::string("picture/weapon/")
#define PATH_PICTURE_BULLET   std::string("picture/bullet/")
#define PATH_PICTURE_HERO     std::string("picture/hero/")
#define PATH_MAP              std::string("map/")
#define PATH_PICTURE_PROP     std::string("picture/Prop/")


#define SAFE_MAP_NAME         std::string("SafeMap")
#define DEFAULT_HERO_NAME     std::string("Knight")
#define DEFAULT_WEAPON_NAME   std::string("Lightsaber")


//catagory&contact!=0 事件发送
//catagory&collision!=0 碰撞发生

#define BULLET_CATAGORY       0b0000000001
#define HERO_CATAGORY         0b0000000010
#define WALL_CATAGORY         0b0000000100
#define EXFLOOR_CATAGORY      0b0000001000
//#define CLOSE_DOOR_CATAGORY   0b0000010000
#define MONSTER_CATAGORY      0b0000100000
#define PROP_CATAGORY         0b0001000000		//所有道具，传送门，箱子，药瓶
#define WEAPON_CATAGORY       0b0010000000

#define BULLET_COLLISION      0b0000111110
#define HERO_COLLISION        0b0001111111
#define WALL_COLLISION        0b0000100011
#define EXFLOOR_COLLISION     0b0000100011
//#define CLOSE_DOOR_COLLISION  0b0000100101
#define MONSTER_COLLISION     0b0000111111
#define PROP_COLLISION        0b0000000000
#define WEAPON_COLLISION      0b0000000000

#define BULLET_CONTACT        0b0010111110
#define HERO_CONTACT          0b0011001001
#define WALL_CONTACT          0b0000000001
#define EXFLOOR_CONTACT       0b0000100011
//#define CLOSE_DOOR_CONTACT    0b0000000001
#define MONSTER_CONTACT       0b0010001001
#define PROP_CONTACT          0b0000000010
#define WEAPON_CONTACT        0b0000100011






#define HERO_LAYER  5
#define MAP_LAYER 0


#endif // !Constant_H