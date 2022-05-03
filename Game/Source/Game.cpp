#include <Durna.h>
#include <Runtime/Core/Application.h>
#include "GameApplication.h"

Durna::Application* CreateApplication()
{
	return new GameApplication;
}