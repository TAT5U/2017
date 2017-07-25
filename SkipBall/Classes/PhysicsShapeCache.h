/*PhysicsShapeCache.h*/

#ifndef __PhysicsShapeCache_h__
#define __PhysicsShapeCache_h__
#include "cocos2d.h"

USING_NS_CC;


class PhysicsShapeCache
{
public:

	//PhysicsShapeCacheのシングルトン
	static PhysicsShapeCache *getInstance();

	//プロパティリストの追加
	bool addShapesWithFile(const std::string &plist);

	//プロパティリストからShapeを追加
	bool addShapesWithFile(const std::string &plist, float scaleFactor);

	//Shapeファイルの削除
	void removeShapesWithFile(const std::string &plist);

	//Shapeの削除
	void removeAllShapes();

	//物理エンジンの作成
	PhysicsBody *createBodyWithName(const std::string &name);

	//物理エンジンのセット
	PhysicsBody *setPhysics(const std::string &name, Sprite *sprite);
private:

	//円の識別子
	typedef enum
	{
		FIXTURE_POLYGON,
		FIXTURE_CIRCLE
	} FixtureType;

	//矩形の識別子
	class Polygon
	{
	public:
		Point* vertices;
		int numVertices;
	};

	//物理エンジンのデータ
	class FixtureData
	{
	public:
		FixtureType fixtureType;

		float density;
		float restitution;
		float friction;

		int tag;
		int group;
		int categoryMask;
		int collisionMask;
		int contactTestMask;

		//円
		Point center;
		float radius;


		std::vector<Polygon *> polygons;
	};

	//物理エンジンのBodyの情報
	class BodyDef
	{
	public:
		Point anchorPoint;
		std::vector<FixtureData *> fixtures;

		bool isDynamic;
		bool affectedByGravity;
		bool allowsRotation;

		float linearDamping;
		float angularDamping;
		float velocityLimit;
		float angularVelocityLimit;
		
		

	};
	FixtureType fixtureType;
	PhysicsShapeCache();
	~PhysicsShapeCache();
	void safeDeleteBodyDef(BodyDef *bodyDef);
	BodyDef *getBodyDef(const std::string &name);
	void setBodyProperties(PhysicsBody *body, BodyDef *bd);
	void setShapeProperties(PhysicsShape *shape, FixtureData *fd);


	std::map<std::string, BodyDef *> bodyDefs;
	std::map<std::string, std::vector<BodyDef *>> bodiesInFile;
};


#endif // __PhysicsShapeCache_h