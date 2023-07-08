#include "MenuObject.h"
#include <Objects/Components/CameraComponent.h>
#include <UI/MenuUI.h>

void MenuObject::Begin()
{
	CameraComponent* c = new CameraComponent();
	Attach(c);
	c->Use();
	c->RelativeTransform.Rotation.Y = -90;
	UICanvas::CreateNewCanvas<MenuUI>();
}
