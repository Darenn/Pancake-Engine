//
// Created by kelle on 23/01/2017.
//

#include "../include/PhysicsEngine.hpp"
#include <vector>
#include "../include/Rigidbody.hpp"
#include <iostream>


PhysicsEngine::PhysicsEngine() {
    world = new b2World(b2Vec2(0, 10));
}

PhysicsEngine::~PhysicsEngine() {
    delete world;
}

void PhysicsEngine::update(float dt) {
    //world->Step(1/30,10,10);
    world->Step(dt, velocityIterations, positionIterations);
    for ( b2Body* b = world->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetType() != b2_staticBody) {
            Rigidbody * rb = static_cast<Rigidbody*>(b->GetUserData());
            rb->gameObject->transform->setPosition(sf::Vector2f(b->GetPosition().x, b->GetPosition().y));
            rb->gameObject->transform->setRotation(b->GetAngle());
        }
    }
    //world->ClearForces();
}

void PhysicsEngine::addStaticBodyToPhysicsWorld(Collider& c) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(c.gameObject->transform->getPosition().x + c.offset.x,
                         c.gameObject->transform->getPosition().y + c.offset.y);
    bodyDef.userData = (void *) &c;
    b2Body* body = world->CreateBody(&bodyDef);
    b2PolygonShape shape;
    if(dynamic_cast<BoxCollider*>(&c) != NULL) {
        BoxCollider * bc = (BoxCollider *)&c;
        shape.SetAsBox(bc->width/2, bc->height/2, b2Vec2(c.offset.x,c.offset.y), c.gameObject->transform->getRotation());
    } else {
        assert(false);
    }
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density =1;
    fixtureDef.restitution = 0;
    /*fixtureDef.density = c.density;
    fixtureDef.friction = c.friction;
    fixtureDef.restitution = c.bounciness;*/
    body->CreateFixture(&fixtureDef);
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

    bodyDef.position.Set(rb.gameObject->transform->getPosition().x,
                         rb.gameObject->transform->getPosition().y);
    bodyDef.userData = (void *) &rb;
    /*bodyDef.angularVelocity = rb.angularVelocity;
    bodyDef.angularDamping = rb.angularDrag;
    bodyDef.fixedRotation = rb.freezeRotation;*/
    b2Body *body = world->CreateBody(&bodyDef);
    rb.physicsBody = body;

            // Create a fixture for each collider
    std::vector<Collider *> v = rb.gameObject->getComponents<Collider>();
        for (int i = 0; i < v.size(); ++i) {
            Collider & c = *v[i];
            b2PolygonShape shape;
            if (dynamic_cast<BoxCollider *>(&c) != NULL) {
                BoxCollider *bc = (BoxCollider *) &c;
                shape.SetAsBox(bc->width/2, bc->height/2, b2Vec2(c.offset.x,c.offset.y), c.gameObject->transform->getRotation());
            } else {
                assert(false);
            }
            b2FixtureDef fixtureDef;
            fixtureDef.shape = &shape;
            fixtureDef.density =1;
            fixtureDef.restitution = 0;
                    /*fixtureDef.density = c.density;
                    fixtureDef.friction = c.friction;
                    fixtureDef.restitution = c.bounciness;
                    fixtureDef.userData = (void *) &c;*/
            body->CreateFixture(&fixtureDef);
        }
}


