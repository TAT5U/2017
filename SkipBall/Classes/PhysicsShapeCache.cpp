/*PhysicsShapeCache.cpp*/

/*2017-06-01
	TAT5U
		�����G���W��������*/

/*���̃Q�[���̃{�[���ȊO�̕����G���W���̓v���p�e�B���X�g�̃f�[�^����ł��Ă��āA
  �v���p�e�B���X�g�́uPhysicsEditor�v�Ƃ����\�t�g�ō쐬���ꂽ���̂�s�v�ȕ�������菜���Ă���
  PhysicsShapeCache�̃R�[�h�́uPhysicsEditor�v��cocos2dx�̃R�[�h��
  �����ς��Ďg�p���Ă���
  URL��https://www.codeandweb.com/physicseditor/tutorials/creating-physics-shapes-for-cocos2d-x
  github(cpp)��https://github.com/CodeAndWeb/PhysicsEditor-Cocos2d-x/blob/master/Classes/PhysicsShapeCache.cpp
		(h)��https://github.com/CodeAndWeb/PhysicsEditor-Cocos2d-x/blob/master/Classes/PhysicsShapeCache.h�@�@�@�@*/


#include "PhysicsShapeCache.h"


PhysicsShapeCache::PhysicsShapeCache()
{
}


PhysicsShapeCache::~PhysicsShapeCache()
{
	removeAllShapes();
}


PhysicsShapeCache *PhysicsShapeCache::getInstance()
{
	static PhysicsShapeCache instance;
	return &instance;
}


bool PhysicsShapeCache::addShapesWithFile(const std::string &plist)
{
	float scaleFactor = Director::getInstance()->getContentScaleFactor();
	return addShapesWithFile(plist, scaleFactor);
}


bool PhysicsShapeCache::addShapesWithFile(const std::string &plist, float scaleFactor)
{
	//�����v���p�e�B���X�g��ǂݍ��ނƃG���[�ɂȂ邽�߃R�����g�A�E�g
	//CCASSERT(bodiesInFile.find(plist) == bodiesInFile.end(), "file already loaded");

	ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(plist);

	//�v���p�e�B���X�g���Ȃ��Ƃ��ɃG���[
	if (dict.empty())
	{
		return false;
	}

	ValueMap &metadata = dict["metadata"].asValueMap();
	int format = metadata["format"].asInt();
	if (format != 1)
	{
		CCASSERT(format == 1, "format not supported!");
		return false;
	}


	//�v���p�e�B���X�g�������ǂݎ��쐬
	ValueMap &bodydict = dict.at("bodies").asValueMap();
	std::vector<BodyDef*> bodies(bodydict.size());
	int num = 0;
	for (auto iter = bodydict.cbegin(); iter != bodydict.cend(); ++iter)
	{
		const ValueMap &bodyData = iter->second.asValueMap();
		std::string bodyName = iter->first;
		BodyDef *bodyDef = new BodyDef();
		bodies[num++] = bodyDef;
		bodyDefs.insert(std::make_pair(bodyName, bodyDef));
		bodyDef->anchorPoint = PointFromString(bodyData.at("anchorpoint").asString());
		bodyDef->isDynamic = bodyData.at("is_dynamic").asBool();
		bodyDef->affectedByGravity = bodyData.at("affected_by_gravity").asBool();
		bodyDef->allowsRotation = bodyData.at("allows_rotation").asBool();
		bodyDef->linearDamping = bodyData.at("linear_damping").asFloat();
		bodyDef->angularDamping = bodyData.at("angular_damping").asFloat();
		bodyDef->velocityLimit = bodyData.at("velocity_limit").asFloat();
		bodyDef->angularVelocityLimit = bodyData.at("angular_velocity_limit").asFloat();

		const ValueVector &fixtureList = bodyData.at("fixtures").asValueVector();
		for (auto &fixtureitem : fixtureList)
		{
			FixtureData *fd = new FixtureData();
			bodyDef->fixtures.push_back(fd);
			auto &fixturedata = fixtureitem.asValueMap();
			fd->density = fixturedata.at("density").asFloat();
			fd->restitution = fixturedata.at("restitution").asFloat();
			fd->friction = fixturedata.at("friction").asFloat();
			fd->tag = fixturedata.at("tag").asInt();
			fd->group = fixturedata.at("group").asInt();
			fd->contactTestMask = fixturedata.at("contact_test_mask").asInt();

			std::string fixtureType = fixturedata.at("fixture_type").asString();

			//��`�̏ꍇ
			if (fixtureType == "POLYGON")
			{
				fd->fixtureType = FIXTURE_POLYGON;
				const ValueVector &polygonsArray = fixturedata.at("polygons").asValueVector();
				for (auto &polygonitem : polygonsArray)
				{
					Polygon *poly = new Polygon();
					fd->polygons.push_back(poly);
					auto &polygonArray = polygonitem.asValueVector();
					poly->numVertices = (int)polygonArray.size();
					auto *vertices = poly->vertices = new cocos2d::Point[poly->numVertices];
					int vindex = 0;
					for (auto &pointString : polygonArray)
					{
						auto offset = PointFromString(pointString.asString());
						vertices[vindex].x = offset.x / scaleFactor;
						vertices[vindex].y = offset.y / scaleFactor;
						vindex++;
					}
				}
			}

			//�~�̏ꍇ
			else if (fixtureType == "CIRCLE")
			{
				fd->fixtureType = FIXTURE_CIRCLE;
				const ValueMap &circleData = fixturedata.at("circle").asValueMap();
				fd->radius = circleData.at("radius").asFloat() / scaleFactor;
				fd->center = PointFromString(circleData.at("position").asString()) / scaleFactor;
			}

			//��`���~�ȊO�͂Ȃ��̂ŃG���[
			else
			{
				return false;
			}

		}
	}

	bodiesInFile[plist] = bodies;

	return true;
}


PhysicsShapeCache::BodyDef *PhysicsShapeCache::getBodyDef(const std::string &name)
{
	try
	{
		return bodyDefs.at(name);
	}
	catch (std::out_of_range&)
	{
	}

	try
	{
		return bodyDefs.at(name.substr(0, name.rfind('.')));
	}
	catch (std::out_of_range&)
	{
	}

	return nullptr;
}

//�v���p�e�B���X�g����쐬���������G���W���ɏ����i�[
void PhysicsShapeCache::setBodyProperties(PhysicsBody *body, BodyDef *bd)
{
	body->setGravityEnable(bd->affectedByGravity);
	body->setDynamic(bd->isDynamic);
	body->setRotationEnable(bd->allowsRotation);
	body->setLinearDamping(bd->linearDamping);
	body->setAngularDamping(bd->angularDamping);
	body->setVelocityLimit(bd->velocityLimit);
	body->setAngularVelocityLimit(bd->angularVelocityLimit);
}

//Shape�̃^�O�Ȃǂ̏����i�[
void PhysicsShapeCache::setShapeProperties(PhysicsShape *shape, FixtureData *fd)
{
	shape->setGroup(fd->group);
	shape->setContactTestBitmask(fd->contactTestMask);
	shape->setTag(fd->tag);
}

//�����G���W���̊�{�ƂȂ�Body���쐬
PhysicsBody *PhysicsShapeCache::createBodyWithName(const std::string &name)
{
	BodyDef *bd = getBodyDef(name);

	//�w�肵�����O�̕����G���W�����Ȃ������Ƃ�
	if (!bd)
	{
		CCLOG("WARNING: PhysicsBody with name \"%s\", not found!", name.c_str());
		return nullptr;
	}
	PhysicsBody *body = PhysicsBody::create();
	setBodyProperties(body, bd);

	for (auto fd : bd->fixtures)
	{
		PhysicsMaterial material(fd->density, fd->restitution, fd->friction);
		if ((fixtureType=fd->fixtureType) == FIXTURE_CIRCLE)
		{
			auto shape = PhysicsShapeCircle::create(fd->radius, material, fd->center);
			setShapeProperties(shape, fd);
			body->addShape(shape);
		}
		else if ((fixtureType = fd->fixtureType) == FIXTURE_POLYGON)
		{
			for (auto polygon : fd->polygons)
			{
				auto shape = PhysicsShapePolygon::create(polygon->vertices, polygon->numVertices, material, fd->center);
				setShapeProperties(shape, fd);
				body->addShape(shape);
			}
		}
	}
	return body;
}

//�����G���W�����Z�b�g
//����ɂ��PlayScene�ł����̂悤��PhysicsBody�ŃZ�b�g�ł���悤�ɂȂ�
PhysicsBody *PhysicsShapeCache::setPhysics(const std::string &name, Sprite *sprite)
{
	PhysicsBody *body = createBodyWithName(name);
	return body;
}

//�v���p�e�B���X�g����ǂݎ���������폜
void PhysicsShapeCache::removeShapesWithFile(const std::string &plist)
{
	auto bodies = bodiesInFile.at(plist);

	for (auto iter = bodies.begin(); iter != bodies.end(); ++iter)
	{
		safeDeleteBodyDef(*iter);
	}

	bodiesInFile.erase(plist);

	return;
}

//Shape���폜
void PhysicsShapeCache::removeAllShapes()
{
	for (auto iter = bodyDefs.cbegin(); iter != bodyDefs.cend(); ++iter)
	{
		safeDeleteBodyDef(iter->second);
	}
	bodyDefs.clear();
	bodiesInFile.clear();
}

//�����G���W���̏����폜
void PhysicsShapeCache::safeDeleteBodyDef(BodyDef *bodyDef)
{
	for (auto fixturedata : bodyDef->fixtures)
	{
		for (auto polygon : fixturedata->polygons)
		{
			CC_SAFE_DELETE_ARRAY(polygon->vertices);
			CC_SAFE_DELETE(polygon);
		}
		fixturedata->polygons.clear();
		CC_SAFE_DELETE(fixturedata);
	}
	bodyDef->fixtures.clear();
	CC_SAFE_DELETE(bodyDef);
}