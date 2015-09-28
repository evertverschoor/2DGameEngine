#include "Gotham.h"


Gotham::Gotham()
{
	// Set name and size
	SetName("Gotham");
	SetSize(new Dimension(3000, 1080));

	// Set background image and type
	SetBackgroundAssetURI("Assets/Backgrounds/gotham_back.jpg");
	SetBackgroundType(SLOW_MOVE);

	SetGravityIntensity(10);
}


Gotham::~Gotham()
{
}
