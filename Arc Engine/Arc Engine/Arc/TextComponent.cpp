#include "TextComponent.h"
#include "Unit.h"

const Arc::UnitComponentType Arc::TextComponent::UNIT_CMP_TYPE_TEXT = "text";

Arc::TextComponent::~TextComponent(void)
{
	delete _pRenderedText;
}

void Arc::TextComponent::render( const RenderData* data )
{
	const Unit* parent = getUnit();

	if (parent == nullptr)
        return;

	data->getRenderTarget()->drawText(parent->getPos() + getOffset(), _pRenderedText, getBlendColor(), getRotation(), getScale(), getOrigin());
}