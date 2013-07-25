#pragma once

#ifndef __ARC_RECT_COLLIDER_H__
#define __ARC_RECT_COLLIDER_H__

#include "Common.h"
#include "Collider.h"

namespace Arc
{
    class CircleCollider;

    class RectCollider
        : public Collider
    {
    public:

        Rect
            RectMask;

        RectCollider( Rect mask ) { RectMask = mask; }
        RectCollider( Vector2 pos, Size size) { RectMask = Rect(pos, size); }
        RectCollider( float x, float y, float width, float height) { RectMask = Rect(x, y, width, height); }
        virtual ~RectCollider( void ) { }

        virtual bool check( Point pos, Collider* pOther, Point otherPos );

        virtual string toString( void ) const { return "Rect Collider"; }

        virtual void render( const RenderTarget* renderTarget, Point pos );

    }; // class RectCollider

} // namespace Arc

#endif // __ARC_RECT_COLLIDER_H__
