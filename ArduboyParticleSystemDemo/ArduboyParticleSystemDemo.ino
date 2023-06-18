/*
Copyright 2023 Om Rawaley (@omrawaley)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "src/AB-Particles/AB-Particles.h"
#include "src/AB-Particles/User-Setup.h"
#include "src/fonts/Font4x6.h"

enum class DemoState : uint8_t
{
	Preview,
	Simulation,
};

struct Menu
{
	int8_t menuCameraY;

	uint8_t menuCursorIndex;

	static constexpr uint8_t totalMenuOptions = 12;

	char *roundParticlesStatus;
	char *filledParticlesStatus;
};

struct CursorIndexState
{
	static constexpr uint8_t Gravity = 0;
	static constexpr uint8_t RoundParticles = 1;
	static constexpr uint8_t FilledParticles = 2;
	static constexpr uint8_t ParticleAmount = 3;
	static constexpr uint8_t MinParticleSize = 4;
	static constexpr uint8_t MaxParticleSize = 5;
	static constexpr uint8_t MinParticleLifetime = 6;
	static constexpr uint8_t MaxParticleLifetime = 7;
	static constexpr uint8_t MinParticleXForce = 8;
	static constexpr uint8_t MaxParticleXForce = 9;
	static constexpr uint8_t MinParticleYForce = 10;
	static constexpr uint8_t MaxParticleYForce = 11;
};

Particles particles;
Arduboy2 arduboy;
Font4x6 font4x6 = Font4x6();
DemoState demoState = DemoState::Preview;
Menu menu;

constexpr uint8_t particlePosX = 64;
constexpr uint8_t particlePosY = 32;

void adjustGravity()
{
	if(arduboy.pressed(RIGHT_BUTTON))
	{
		UserSetup::gravity += 0.001;
	}

	if(arduboy.pressed(LEFT_BUTTON) && UserSetup::gravity > 0.0001)
	{
		UserSetup::gravity -= 0.001;
	}
}

void adjustRoundParticles()
{
	if(arduboy.pressed(RIGHT_BUTTON))
	{
		UserSetup::roundParticles = true;
	}

	if(arduboy.pressed(LEFT_BUTTON))
	{
		UserSetup::roundParticles = false;;
	}
}

void adjustFilledParticles()
{
	if(arduboy.pressed(RIGHT_BUTTON))
	{
		UserSetup::filledParticles = true;
	}

	if(arduboy.pressed(LEFT_BUTTON))
	{
		UserSetup::filledParticles = false;
	}
}

void adjustParticleAmount()
{
	if(arduboy.justPressed(RIGHT_BUTTON) && UserSetup::particleAmount < 40)
	{
		++UserSetup::particleAmount;
	}

	if(arduboy.justPressed(LEFT_BUTTON) && UserSetup::particleAmount > 1)
	{
		--UserSetup::particleAmount;
	}
}

void adjustMinParticleSize()
{
	if(arduboy.justPressed(RIGHT_BUTTON) && UserSetup::sizeMin < UserSetup::sizeMax)
	{
		++UserSetup::sizeMin;
	}

	if(arduboy.justPressed(LEFT_BUTTON) && UserSetup::sizeMin > 1)
	{
		--UserSetup::sizeMin;
	}
}

void adjustMaxParticleSize()
{
	if(arduboy.justPressed(RIGHT_BUTTON))
	{
		++UserSetup::sizeMax;
	}

	if(arduboy.justPressed(LEFT_BUTTON) && UserSetup::sizeMax > UserSetup::sizeMin)
	{
		--UserSetup::sizeMax;
	}
}

void adjustMinParticleLifetime()
{
	if(arduboy.justPressed(RIGHT_BUTTON) && UserSetup::lifetimeMin < UserSetup::lifetimeMax)
	{
		++UserSetup::lifetimeMin;
	}

	if(arduboy.justPressed(LEFT_BUTTON) && UserSetup::lifetimeMin > 1)
	{
		--UserSetup::lifetimeMin;
	}
}

void adjustMaxParticleLifetime()
{
	if(arduboy.justPressed(RIGHT_BUTTON))
	{
		++UserSetup::lifetimeMax;
	}

	if(arduboy.justPressed(LEFT_BUTTON) && UserSetup::lifetimeMax > UserSetup::lifetimeMin)
	{
		--UserSetup::lifetimeMax;
	}
}

void adjustMinParticleXForce()
{
	if(arduboy.justPressed(RIGHT_BUTTON) && UserSetup::xForceMin < 0)
	{
		++UserSetup::xForceMin;
	}

	if(arduboy.justPressed(LEFT_BUTTON))
	{
		--UserSetup::xForceMin;
	}
}

void adjustMaxParticleXForce()
{
	if(arduboy.justPressed(RIGHT_BUTTON))
	{
		++UserSetup::xForceMax;
	}

	if(arduboy.justPressed(LEFT_BUTTON) && UserSetup::xForceMax > 0)
	{
		--UserSetup::xForceMax;
	}
}

void adjustMinParticleYForce()
{
	if(arduboy.justPressed(RIGHT_BUTTON) && UserSetup::yForceMin < UserSetup::yForceMax)
	{
		++UserSetup::yForceMin;
	}

	if(arduboy.justPressed(LEFT_BUTTON) && UserSetup::yForceMax > 0)
	{
		--UserSetup::yForceMin;
	}
}

void adjustMaxParticleYForce()
{
	if(arduboy.justPressed(RIGHT_BUTTON))
	{
		++UserSetup::yForceMax;
	}

	if(arduboy.justPressed(LEFT_BUTTON) && UserSetup::yForceMax > UserSetup::yForceMin)
	{
		--UserSetup::yForceMax;
	}
}

void updatePreview()
{
	if(UserSetup::roundParticles)
	{
		menu.roundParticlesStatus = "Yes";
	}
	else
	{
		menu.roundParticlesStatus = "No";
	}

	if(UserSetup::filledParticles)
	{
		menu.filledParticlesStatus = "Yes";
	}
	else
	{
		menu.filledParticlesStatus = "No";
	}

	if(arduboy.justPressed(DOWN_BUTTON) && menu.menuCursorIndex < (Menu::totalMenuOptions - 1))
	{
		menu.menuCameraY -= 8;
		++menu.menuCursorIndex;
	}

	if(arduboy.justPressed(UP_BUTTON) && menu.menuCursorIndex > 0)
	{
		menu.menuCameraY += 8;
		--menu.menuCursorIndex;
	}

	switch (menu.menuCursorIndex)
	{
		case CursorIndexState::Gravity:
			adjustGravity();
			break;
		
		case CursorIndexState::RoundParticles:
			adjustRoundParticles();
			break;

		case CursorIndexState::FilledParticles:
			adjustFilledParticles();
			break;

		case CursorIndexState::ParticleAmount:
			adjustParticleAmount();
			break;

		case CursorIndexState::MinParticleSize:
			adjustMinParticleSize();
			break;

		case CursorIndexState::MaxParticleSize:
			adjustMaxParticleSize();
			break;

		case CursorIndexState::MinParticleLifetime:
			adjustMinParticleLifetime();
			break;

		case CursorIndexState::MaxParticleLifetime:
			adjustMaxParticleLifetime();
			break;

		case CursorIndexState::MinParticleXForce:
			adjustMinParticleXForce();
			break;

		case CursorIndexState::MaxParticleXForce:
			adjustMaxParticleXForce();
			break;

		case CursorIndexState::MinParticleYForce:
			adjustMinParticleYForce();
			break;

		case CursorIndexState::MaxParticleYForce:
			adjustMaxParticleYForce();
			break;
	}

	if(arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON))
	{
		goToSimulation();

		particles.reset(particlePosX, particlePosY);
	}
}

void updateSimulation()
{
	particles.update();

	if(arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON))
	{
		goToPreview();
	}
}

void renderSimulation()
{
	particles.render();
}

void renderPreview()
{
	font4x6.setCursor(0, menu.menuCameraY);
	font4x6.print(F("Gravity "));
	font4x6.println(UserSetup::gravity, 3);
	font4x6.print(F("Round Particles "));
	font4x6.println(menu.roundParticlesStatus);
	font4x6.print(F("Filled Particles "));
	font4x6.println(menu.filledParticlesStatus);
	font4x6.print(F("Particle Amount "));
	font4x6.println(UserSetup::particleAmount);
	font4x6.print(F("Min Particle Size "));
	font4x6.println(UserSetup::sizeMin);
	font4x6.print(F("Max Particle Size "));
	font4x6.println(UserSetup::sizeMax);
	font4x6.print(F("Min Particle Lifetime "));
	font4x6.println(UserSetup::lifetimeMin);
	font4x6.print(F("Max Particle Lifetime "));
	font4x6.println(UserSetup::lifetimeMax);
	font4x6.print(F("Min Particle XForce "));
	font4x6.println(UserSetup::xForceMin);
	font4x6.print(F("Max Particle XForce "));
	font4x6.println(UserSetup::xForceMax);
	font4x6.print(F("Min Particle YForce "));
	font4x6.println(UserSetup::yForceMin);
	font4x6.print(F("Max Particle YForce "));
	font4x6.println(UserSetup::yForceMax);
}

void goToSimulation()
{
	demoState = DemoState::Simulation;
}

void goToPreview()
{
	demoState = DemoState::Preview;
}

void setup()
{
	arduboy.begin();
	arduboy.initRandomSeed();
	arduboy.clear();
}

void loop()
{
	if(!arduboy.nextFrame())
		return;

	arduboy.pollButtons();

	arduboy.clear();

	switch (demoState)
	{
		case DemoState::Preview:
			updatePreview();
		    renderPreview();
			break;

		case DemoState::Simulation:
		    updateSimulation();
			renderSimulation();
			break;
	}

	arduboy.display();
}