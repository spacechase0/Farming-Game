#include "SceneChangeEvent.h"

SceneChangeEvent::SceneChangeEvent()
   : reason( Unspecified )
{
}

SceneChangeEvent::SceneChangeEvent( Reason theReason )
   : reason( theReason )
{
}
