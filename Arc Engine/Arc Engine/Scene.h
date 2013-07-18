#pragma once

#ifndef __SCENE_H__
#define __SCENE_H__

#include "ArcCommon.h"
#include "EventDispatcher.h"
#include "IFrameListener.h"

#include "Layer.h"

class Scene :
    public EventDispatcher,
    public IFrameListener
{
protected:

    Map<unsigned int, Layer*>
        _layers;

public:

    bool
        Enabled,
        Visible;

    Scene( void ) { }
    virtual ~Scene( void ) { term(); }

    virtual void init( void );
    virtual void term( void );

    virtual void update( const Event& event );
    virtual void render( const Event& event );

    virtual bool   addLayer  ( int index );
    virtual Layer* getLayer  ( int index );
    virtual bool   hasLayer  ( int index );
    virtual void   swapLayers( int index, int newIndex );

    virtual unsigned int emptyLayer( int index );

    virtual void showLayer( int index );
    virtual void hideLayer( int index );
    virtual void setLayerVisible   ( int index, bool visible );
    virtual void toggleLayerVisible( int index );
    virtual bool isLayerVisible    ( int index );

    virtual void enableLayer ( int index );
    virtual void disableLayer( int index );
    virtual void setLayerEnabled   ( int index, bool enabled );
    virtual void toggleLayerEnabled( int index );
    virtual bool isLayerEnabled    ( int index );

    virtual bool addUnit     ( Unit* unit, int layer );
    virtual void moveUnit    ( Unit* unit, int newLayer );
    virtual bool removeUnit  ( Unit* unit );
    virtual bool hasUnit     ( Unit* unit );

    virtual Layer* getUnitLayer     ( Unit* unit );
    virtual int    getUnitLayerIndex( Unit* unit );

};

#endif