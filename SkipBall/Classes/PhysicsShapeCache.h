/*PhysicsShapeCache.h*/

#ifndef __PhysicsShapeCache_h__
#define __PhysicsShapeCache_h__
#include "cocos2d.h"

USING_NS_CC;


class PhysicsShapeCache
{
public:

	//PhysicsShapeCache�̃V���O���g��
	static PhysicsShapeCache *getInstance();

	//�v���p�e�B���X�g�̒ǉ�
	bool addShapesWithFile(const std::string &plist);

	//�v���p�e�B���X�g����Shape��ǉ�
	bool addShapesWithFile(const std::string &plist, float scaleFactor);

	//Shape�t�@�C���̍폜
	void removeShapesWithFile(const std::string &plist);

	//Shape�̍폜
	void removeAllShapes();

	//�����G���W���̍쐬
	PhysicsBody *createBodyWithName(const std::string &name);

	//�����G���W���̃Z�b�g
	PhysicsBody *setPhysics(const std::string &name, Sprite *sprite);
private:

	//�~�̎��ʎq
	typedef enum
	{
		FIXTURE_POLYGON,
		FIXTURE_CIRCLE
	} FixtureType;

	//��`�̎��ʎq
	class Polygon
	{
	public:
		Point* vertices;
		int numVertices;
	};

	//�����G���W���̃f�[�^
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

		//�~
		Point center;
		float radius;


		std::vector<Polygon *> polygons;
	};

	//�����G���W����Body�̏��
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