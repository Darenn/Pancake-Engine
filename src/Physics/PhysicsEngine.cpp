//
// Created by kelle on 23/01/2017.
//

#include "Physics/PhysicsEngine.hpp"
#include "GameLogic/Components/Transform.hpp"
#include "Physics/PhysicsUserData.hpp"
#include <iostream>
#include <GameLogic/Components/CircleCollider.hpp>

using namespace PancakeEngine;

int PhysicsEngine::numberPixelsPerMeter = 72; // TODO to change with the scene

PhysicsEngine::PhysicsEngine() : world(b2Vec2(0, 10)), physicsListener() {
    world.SetContactListener(&physicsListener);
}

PhysicsEngine::~PhysicsEngine() {
}

void PhysicsEngine::update(float dt) {
    world.Step(dt, velocityIterations, positionIterations);
    for ( b2Body* b = world.GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetType() != b2_staticBody) {
            Rigidbody * rb = static_cast<Rigidbody*>(b->GetUserData());
            rb->gameObject->transform.setPosition((sf::Vector2f(b->GetPosition().x * numberPixelsPerMeter,
                                                                 b->GetPosition().y * numberPixelsPerMeter)));
            rb->gameObject->transform.setRotation(b->GetAngle());
        }
    }
}

void PhysicsEngine::addStaticBodyToPhysicsWorld(Collider& c) {
    // TODO Test if ti works with multiple triggers.

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;

    bodyDef.position.Set((c.gameObject->transform.getPosition().x)/numberPixelsPerMeter,
                         (c.gameObject->transform.getPosition().y)/numberPixelsPerMeter);
    bodyDef.userData = (void *) &c;
    //bodyDef.userData = new PhysicsUserData(PhysicsUserData::Type::Collider, nullptr, &c);
    b2Body* body = world.CreateBody(&bodyDef);
    createFixtures(*c.gameObject, *body);
}

void PhysicsEngine::addRigidBodyToPhysicsWorld(Rigidbody &rb) {
    b2BodyDef bodyDef;
    switch (rb.type) {
        case Rigidbody::bodyType::dynamicBody:
            bodyDef.type = b2_dynamicBody;
            break;
        case Rigidbody::bodyType::staticBody:
            bodyDef.type = b2_staticBody;
            break;
        case Rigidbody::bodyType::kinematicBody:
            bodyDef.type = b2_kinematicBody;
            break;
        default:
            assert(false);
    }

    bodyDef.position.Set((rb.gameObject->transform.getPosition().x)/numberPixelsPerMeter,
                         (rb.gameObject->transform.getPosition().y)/numberPixelsPerMeter);
    //bodyDef.userData = new PhysicsUserData(PhysicsUserData::Type::Rigidbody, &rb);
    bodyDef.userData = (void *) &rb;
    bodyDef.angularVelocity = rb.angularVelocity;
    bodyDef.angularDamping = rb.angularDrag;
    bodyDef.fixedRotation = rb.freezeRotation;
    bodyDef.bullet = rb.bullet;
    b2Body *body = world.CreateBody(&bodyDef);
    rb.physicsBody = body;

    createFixtures(*rb.gameObject, *body);
}


void PhysicsEngine::setPosition(const sf::Vector2f& pos, b2Body& body) {
    body.SetTransform(b2Vec2(pos.x / numberPixelsPerMeter, pos.y / numberPixelsPerMeter), body.GetAngle());
}

void PhysicsEngine::setRotation(const float angle, b2Body &body) {
    body.SetTransform(body.GetPosition(), angle);
}

void PhysicsEngine::removeBody(b2Body* body) {
    world.DestroyBody(body);
    body = nullptr;
}

// Helper functions

void PhysicsEngine::createFixtures(const GameObject& go, b2Body& body) {
    // Create a fixture for each collider
    std::vector<Collider *> v = go.getComponents<Collider>();
    for (unsigned i = 0; i < v.size(); ++i) {
        Collider & c = *v[i];
        b2FixtureDef fixtureDef;
        b2PolygonShape polygonShape;
        b2CircleShape circleShape;
        if (dynamic_cast<BoxCollider *>(&c) != NULL) {

            BoxCollider *bc = (BoxCollider *) &c;
            polygonShape.SetAsBox((bc->width/2)/PhysicsEngine::numberPixelsPerMeter, (bc->height/2)/PhysicsEngine::numberPixelsPerMeter,
                    (b2Vec2(c.offset.x/PhysicsEngine::numberPixelsPerMeter,c.offset.y/PhysicsEngine::numberPixelsPerMeter)),
                    c.gameObject->transform.getRotation());
            fixtureDef.shape = &polygonShape;
        }
        else if (dynamic_cast<CircleCollider *>(&c) != NULL) {
            CircleCollider* cc = (CircleCollider*) &c;
            circleShape.m_p.Set(cc->offset.x/PhysicsEngine::numberPixelsPerMeter, cc->offset.y/PhysicsEngine::numberPixelsPerMeter);
            circleShape.m_radius = cc->radius/PhysicsEngine::numberPixelsPerMeter;
            fixtureDef.shape = &circleShape;
        }
        else {
            assert(false); // Collider unknown
        }
        fixtureDef.density = c.density;
        fixtureDef.friction = c.friction;
        fixtureDef.restitution = c.bounciness;
        fixtureDef.isSensor = c.isTrigger;
        fixtureDef.userData = (void *) &c;
        c.fixture = body.CreateFixture(&fixtureDef);
    }
}



