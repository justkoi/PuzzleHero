/****************************************************************************
 Copyright (c) 2013 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __CCPHYSICS_SHAPE_H__
#define __CCPHYSICS_SHAPE_H__

#include "ccConfig.h"
#if CC_USE_PHYSICS

#include "CCRef.h"
#include "CCGeometry.h"

NS_CC_BEGIN

class PhysicsShapeInfo;
class PhysicsBody;
class PhysicsBodyInfo;


typedef struct PhysicsMaterial
{
    float density;          ///< The density of the object.
    float restitution;      ///< The bounciness of the physics body.
    float friction;         ///< The roughness of the surface of a shape.
    
    PhysicsMaterial()
    : density(0.0f)
    , restitution(0.0f)
    , friction(0.0f)
    {}
    
    PhysicsMaterial(float aDensity, float aRestitution, float aFriction)
    : density(aDensity)
    , restitution(aRestitution)
    , friction(aFriction)
    {}
}PhysicsMaterial;

const PhysicsMaterial PHYSICSSHAPE_MATERIAL_DEFAULT(0.0f, 0.5f, 0.5f);

/**
 * @brief A shape for body. You do not create PhysicsWorld objects directly, instead, you can view PhysicsBody to see how to create it.
 */
class PhysicsShape : public Ref
{
public:
    enum class Type
    {
        UNKNOWN,
        CIRCLE,
        BOX,
        POLYGEN,
        EDGESEGMENT,
        EDGEBOX,
        EDGEPOLYGEN,
        EDGECHAIN,
    };
    
public:
    /** Get the body that this shape attaches */
    inline PhysicsBody* getBody() const { return _body; }
    /** Return the type of this shape */
    inline Type getType() const { return _type; }
    /** return the area of this shape */
    inline float getArea() const { return _area; }
    /** get moment */
    inline float getMoment() const { return _moment; }
    /** Set moment, it will change the body's moment this shape attaches */
    void setMoment(float moment);
    inline void setTag(int tag) { _tag = tag; }
    inline int getTag() const { return _tag; }
    
    /** get mass */
    inline float getMass() const { return _mass; }
    /** Set mass, it will change the body's mass this shape attaches */
    void setMass(float mass);
    inline float getDensity() const { return _material.density; }
    void setDensity(float density);
    inline float getRestitution() const { return _material.restitution; }
    void setRestitution(float restitution);
    inline float getFriction() const { return _material.friction; }
    void setFriction(float friction);
    const PhysicsMaterial& getMaterial() const { return _material; }
    void setMaterial(const PhysicsMaterial& material);
    
    /** Calculate the default moment value */
    virtual float calculateDefaultMoment() { return 0.0f; }
    /** Get offset */
    virtual Point getOffset() { return Point::ZERO; }
    /** Get center of this shape */
    virtual Point getCenter() { return getOffset(); }
    /** Test point is in shape or not */
    bool containsPoint(const Point& point) const;
    
    /** move the points to the center */
    static void recenterPoints(Point* points, int count, const Point& center = Point::ZERO);
    /** get center of the polyon points */
    static Point getPolyonCenter(const Point* points, int count);
    
    /**
     * A mask that defines which categories this physics body belongs to.
     * Every physics body in a scene can be assigned to up to 32 different categories, each corresponding to a bit in the bit mask. You define the mask values used in your game. In conjunction with the collisionBitMask and contactTestBitMask properties, you define which physics bodies interact with each other and when your game is notified of these interactions.
     * The default value is 0xFFFFFFFF (all bits set).
     */
    inline void setCategoryBitmask(int bitmask) { _categoryBitmask = bitmask; }
    inline int getCategoryBitmask() const { return _categoryBitmask; }
    /**
     * A mask that defines which categories of bodies cause intersection notifications with this physics body.
     * When two bodies share the same space, each body???s category mask is tested against the other body???s contact mask by performing a logical AND operation. If either comparison results in a non-zero value, an PhysicsContact object is created and passed to the physics world???s delegate. For best performance, only set bits in the contacts mask for interactions you are interested in.
     * The default value is 0x00000000 (all bits cleared).
     */
    inline void setContactTestBitmask(int bitmask) { _contactTestBitmask = bitmask; }
    inline int getContactTestBitmask() const { return _contactTestBitmask; }
    /**
     * A mask that defines which categories of physics bodies can collide with this physics body.
     * When two physics bodies contact each other, a collision may occur. This body???s collision mask is compared to the other body???s category mask by performing a logical AND operation. If the result is a non-zero value, then this body is affected by the collision. Each body independently chooses whether it wants to be affected by the other body. For example, you might use this to avoid collision calculations that would make negligible changes to a body???s velocity.
     * The default value is 0xFFFFFFFF (all bits set).
     */
    inline void setCollisionBitmask(int bitmask) { _collisionBitmask = bitmask; }
    inline int getCollisionBitmask() const { return _collisionBitmask; }
    
    void setGroup(int group);
    inline int getGroup() { return _group; }
    
protected:
    bool init(Type type);
    
    /**
     * @brief PhysicsShape is PhysicsBody's friend class, but all the subclasses isn't. so this method is use for subclasses to catch the bodyInfo from PhysicsBody.
     */
    PhysicsBodyInfo* bodyInfo() const;
    
    void setBody(PhysicsBody* body);
    
    /** calculate the area of this shape */
    virtual float calculateArea() { return 0.0f; }
    
protected:
    PhysicsShape();
    virtual ~PhysicsShape() = 0;
    
protected:
    PhysicsBody* _body;
    PhysicsShapeInfo* _info;
    Type _type;
    float _area;
    float _mass;
    float _moment;
    PhysicsMaterial _material;
    int _tag;
    int    _categoryBitmask;
    int    _collisionBitmask;
    int    _contactTestBitmask;
    int    _group;
    
    friend class PhysicsWorld;
    friend class PhysicsBody;
    friend class PhysicsJoint;
    friend class PhysicsDebugDraw;
};

/** A circle shape */
class PhysicsShapeCircle : public PhysicsShape
{
public:
    static PhysicsShapeCircle* create(float radius, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, const Point& offset = Point(0, 0));
    static float calculateArea(float radius);
    static float calculateMoment(float mass, float radius, const Point& offset = Point::ZERO);
    
    virtual float calculateDefaultMoment() override;
    
    float getRadius() const;
    virtual Point getOffset() override;
protected:
    bool init(float radius, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, const Point& offset = Point::ZERO);
    virtual float calculateArea() override;
    
protected:
    PhysicsShapeCircle();
    virtual ~PhysicsShapeCircle();
};

/** A box shape */
class PhysicsShapeBox : public PhysicsShape
{
public:
    static PhysicsShapeBox* create(const Size& size, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, const Point& offset = Point::ZERO);
    static float calculateArea(const Size& size);
    static float calculateMoment(float mass, const Size& size, const Point& offset = Point::ZERO);
    
    virtual float calculateDefaultMoment() override;
    
    void getPoints(Point* outPoints) const;
    int getPointsCount() const { return 4; }
    Size getSize() const;
    virtual Point getOffset() override { return _offset; }
    
protected:
    bool init(const Size& size, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, const Point& offset = Point::ZERO);
    virtual float calculateArea() override;
    
protected:
    PhysicsShapeBox();
    virtual ~PhysicsShapeBox();
    
protected:
    Point _offset;
};

/** A polygon shape */
class PhysicsShapePolygon : public PhysicsShape
{
public:
    static PhysicsShapePolygon* create(const Point* points, int count, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, const Point& offset = Point::ZERO);
    static float calculateArea(const Point* points, int count);
    static float calculateMoment(float mass, const Point* points, int count, const Point& offset = Point::ZERO);
    
    float calculateDefaultMoment() override;
    
    Point getPoint(int i) const;
    void getPoints(Point* outPoints) const;
    int getPointsCount() const;
    virtual Point getCenter() override;
protected:
    bool init(const Point* points, int count, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, const Point& offset = Point::ZERO);
    float calculateArea() override;
    
protected:
    PhysicsShapePolygon();
    virtual ~PhysicsShapePolygon();
    
protected:
    Point _center;
};

/** A segment shape */
class PhysicsShapeEdgeSegment : public PhysicsShape
{
public:
    static PhysicsShapeEdgeSegment* create(const Point& a, const Point& b, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    
    Point getPointA() const;
    Point getPointB() const;
    virtual Point getCenter() override;
    
protected:
    bool init(const Point& a, const Point& b, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    
protected:
    PhysicsShapeEdgeSegment();
    virtual ~PhysicsShapeEdgeSegment();
    
protected:
    Point _center;
    
    friend class PhysicsBody;
};

/** An edge box shape */
class PhysicsShapeEdgeBox : public PhysicsShape
{
public:
    static PhysicsShapeEdgeBox* create(const Size& size, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 0, const Point& offset = Point::ZERO);
    virtual Point getOffset() override { return _offset; }
    void getPoints(Point* outPoints) const;
    int getPointsCount() const { return 4; }
    
protected:
    bool init(const Size& size, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1, const Point& offset = Point::ZERO);
    
protected:
    PhysicsShapeEdgeBox();
    virtual ~PhysicsShapeEdgeBox();
    
protected:
    Point _offset;
    
    friend class PhysicsBody;
};

/** An edge polygon shape */
class PhysicsShapeEdgePolygon : public PhysicsShape
{
public:
    static PhysicsShapeEdgePolygon* create(const Point* points, int count, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    virtual Point getCenter() override;
    void getPoints(Point* outPoints) const;
    int getPointsCount() const;
    
protected:
    bool init(const Point* points, int count, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    
protected:
    PhysicsShapeEdgePolygon();
    virtual ~PhysicsShapeEdgePolygon();
    
    friend class PhysicsBody;
    
protected:
    Point _center;
};

/** a chain shape */
class PhysicsShapeEdgeChain : public PhysicsShape
{
public:
    static PhysicsShapeEdgeChain* create(const Point* points, int count, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    virtual Point getCenter() override;
    void getPoints(Point* outPoints) const;
    int getPointsCount() const;
    
protected:
    bool init(const Point* points, int count, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    
protected:
    PhysicsShapeEdgeChain();
    virtual ~PhysicsShapeEdgeChain();
    
protected:
    Point _center;
    
    friend class PhysicsBody;
};

NS_CC_END

#endif // CC_USE_PHYSICS
#endif // __CCPHYSICS_FIXTURE_H__
