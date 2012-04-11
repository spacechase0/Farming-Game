#include "game/renderers/BaseRenderer.h"

BaseRenderer::BaseRenderer( std::shared_ptr< GameObject > theObject )
   : object( theObject )
{
}

BaseRenderer::~BaseRenderer()
{
}
