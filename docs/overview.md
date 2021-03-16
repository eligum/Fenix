# Overview
Box2D is a 2D rigid body simulation library for games. Programmers can
use it in their games to make objects move in realistic ways and make
the game world more interactive. From the game engine's point of view,
a physics engine is just a system for procedural animation.

Box2D is written in portable C++. Most of the types defined in the
engine begin with the b2 prefix. Hopefully this is sufficient to avoid
name clashing with your game engine.

> **Caution**:
> Box2D should not be your first C++ project. Please learn C++
> programming, compiling, linking, and debugging before working with
> Box2D. There are many resources for this on the net.

## Feedback and Bugs
Please file bugs and feature requests here:
[Box2D Issues](https://github.com/erincatto/box2d/issues)

You can help to ensure your issue gets fixed if you provide sufficient
detail. A testbed example that reproduces the problem is ideal. You can
read about the testbed later in this document.

## Factories and Definitions
Fast memory management plays a central role in the design of the Box2D
API. So when you create a b2Body or a b2Joint, you need to call the
factory functions on b2World. You should never try to allocate these
types in another manner.

There are creation functions:

```cpp
b2Body* b2World::CreateBody(const b2BodyDef* def)
b2Joint* b2World::CreateJoint(const b2JointDef* def)
```

And there are corresponding destruction functions:

```cpp
void b2World::DestroyBody(b2Body* body)
void b2World::DestroyJoint(b2Joint* joint)
```
