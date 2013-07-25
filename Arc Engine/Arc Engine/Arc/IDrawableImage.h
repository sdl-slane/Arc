#pragma once

#ifndef __ARC_IDRAWABLE_IMAGE_H__
#define __ARC_IDRAWABLE_IMAGE_H__

#include "Common.h"
#include "IDrawable.h"

#include "Animation.h"

namespace Arc
{
    class IDrawableImage :
        public IDrawable
    {
    protected:

        Animation
            *_pAnimation;

        double
            _animationTimeout;

        bool
            _animationComplete;

        virtual void calcOriginLocation( void )
        {
            if (_originLocation == ORIGIN_LOCATION_MANUAL)
                return;

            if (_pAnimation == nullptr)
            {
                _origin = Vector2::ZERO;
                return;
            }

            Size size = _pAnimation->frameSize(0);

            switch (_originLocation)
            {
            case ORIGIN_LOCATION_TOP_LEFT:

                _origin = Vector2::ZERO;

                break;
            case ORIGIN_LOCATION_TOP_RIGHT:

                _origin = Vector2(size.width(), 0);

                break;
            case ORIGIN_LOCATION_BOTTOM_LEFT:

                _origin = Vector2(0, size.height());

                break;
            case ORIGIN_LOCATION_BOTTOM_RIGHT:

                _origin = Vector2(size.width(), size.height());

                break;
            case ORIGIN_LOCATION_CENTER:

                _origin = Vector2(size.halfWidth(), size.halfHeight());

                break;
            case ORIGIN_LOCATION_TOP_CENTER:

                _origin = Vector2(size.halfWidth(), 0);

                break;
            case ORIGIN_LOCATION_BOTTOM_CENTER:

                _origin = Vector2(size.halfWidth(), size.height());

                break;
            case ORIGIN_LOCATION_LEFT_CENTER:

                _origin = Vector2(0, size.halfHeight());

                break;
            case ORIGIN_LOCATION_RIGHT_CENTER:

                _origin = Vector2(size.width(), size.halfHeight());

                break;
            default:
                break;
            }

        }

    public:

        int
            Frame;

        bool
            Looping;

        IDrawableImage( void )
        {
            _pAnimation        = nullptr;
            _animationTimeout  = 0.0;
            _animationComplete = false;

            Frame   = 0;
            Looping = false;
        }

        virtual ~IDrawableImage( void ) { }

        virtual void init( Animation* pAnimation = nullptr, bool looping = false, Color blendColor = Color::WHITE, float rot = 0.0f, float alpha = 0.0f )
        {
            Frame = 0;
            Looping = looping;
            setAnimation(pAnimation);
            IDrawable::init(blendColor, rot, alpha);
        }

        virtual void update( const double elapsedMillis )
        {
            if (_pAnimation == nullptr)
                return;

            _animationTimeout -= elapsedMillis;
            if (_animationTimeout <= 0)
            {
                if (!Looping && Frame == _pAnimation->length() - 1)
                {
                    animationComplete();
                    return;
                }
                Frame = (Frame + 1) % _pAnimation->length();
                _animationTimeout = _pAnimation->Speed;
                calcOriginLocation();
            }
        }

        virtual void render( const RenderTarget* renderTarget, const Vector2 pos )
        {
            if (_pAnimation == nullptr)
                return;

            if (!_pAnimation->hasFrame(Frame))
            {
                ERROR("IDrawableImage", "Frame Index out of range");
                return;
            }

            Sprite* sprite = _pAnimation->frameAt(Frame);

            renderTarget->draw(pos, sprite->pTexture, sprite->SourceRect, BlendColor, Rot, Vector2::ZERO);
        }

        virtual void setAnimation( Animation *pAnimation )
        {
            _pAnimation = pAnimation;

            if (_pAnimation == nullptr)
                return;

            Frame = 0;
            _animationComplete = false;

            if (_pAnimation->hasFrame(Frame))
            {
                _animationTimeout = _pAnimation->Speed;
            }
        }

        virtual void animationComplete( void ) { };

    }; // class IDrawableImage

} // namespace Arc

#endif // __ARC_IDRAWABLE_IMAGE_H__