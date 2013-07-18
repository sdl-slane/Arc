#include "Layer.h"
#include "ArcApp.h"
#include "Scene.h"

const EventType Layer::EVENT_LAYER_CHANGED = "layerChanged";

void Layer::init( void )
{
    _units = ArrayList<Unit*>();
    Visible = true;
    Enabled = true;

    addEventListener(EVENT_LAYER_CHANGED, this, &Layer::layerChanged);
}

void Layer::term( void )
{
    removeEventListener(EVENT_LAYER_CHANGED, this, &Layer::layerChanged);

    removeAllUnits();
}

void Layer::update( const Event& event )
{
    if (Enabled)
    {
        for (unsigned int i = 0; i < _units.size(); ++i)
        {
            _units[i]->update(event);
        }
    }
}

void Layer::render( const Event& event )
{
    if (Visible)
    {
        for (unsigned int i = 0; i < _units.size(); ++i)
        {
            _units[i]->render(event);
        }
    }
}

void Layer::layerChanged( const Event& event )
{
    sortByDepth();
}

bool Layer::addUnit( Unit* unit )
{
    if (!_units.contains(unit))
    {
        _units.add(unit);

        addEventListener(ArcApp::EVENT_UPDATE, unit, &Unit::update);
        addEventListener(ArcApp::EVENT_RENDER, unit, &Unit::render);

        dispatchEvent(Event(EVENT_LAYER_CHANGED));

        return true;
    }
    
    return false;
}

bool Layer::removeUnit( Unit* unit )
{
    return _units.remove(unit);
}

bool Layer::hasUnit( Unit* unit )
{
    return _units.contains(unit);
}

void Layer::sortByDepth( void )
{
    sort(_units.begin(), _units.end(), UnitDepthComp());
}

unsigned int Layer::removeAllUnits( void )
{
    unsigned int size = _units.size();

    for (unsigned int i = 0; i < size; ++i)
    {
        removeEventListener(ArcApp::EVENT_RENDER, _units[i], &Unit::render);
        removeEventListener(ArcApp::EVENT_UPDATE, _units[i], &Unit::update);

        delete _units[i];
    }
    _units.clear();

    return size;
}