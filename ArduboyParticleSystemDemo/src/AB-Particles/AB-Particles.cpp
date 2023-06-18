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

#include "User-Setup.h"

#include "AB-Particles.h"

void Particles::reset(int x, int y)
{
	for(uint8_t i = 0; i < UserSetup::particleAmount; ++i)
	{
		particleArray[i].counter = random(UserSetup::lifetimeMin, UserSetup::lifetimeMax);

		particleArray[i].size = random(UserSetup::sizeMin, UserSetup::sizeMax);

		particleArray[i].x = x;
		particleArray[i].y = y;

		particleArray[i].xVelocity = 0;
		particleArray[i].yVelocity = 0;

		particleArray[i].xForce = random(UserSetup::xForceMin, UserSetup::xForceMax) / 100.0;
        particleArray[i].yForce = random(UserSetup::yForceMin, UserSetup::yForceMax) / 100.0;
	}
}

void Particles::update()
{
	for(uint8_t i = 0; i < UserSetup::particleAmount; ++i)
	{
		particleArray[i].yVelocity += UserSetup::gravity * particleArray[i].size;

		particleArray[i].xVelocity += particleArray[i].xForce;
		particleArray[i].yVelocity -= particleArray[i].yForce;

		particleArray[i].x += particleArray[i].xVelocity;
		particleArray[i].y += particleArray[i].yVelocity;

		if(particleArray[i].isActive())
			--particleArray[i].counter;
	}
}

void Particles::render()
{
	if(!UserSetup::roundParticles && !UserSetup::filledParticles)
	{
		for(uint8_t i = 0; i < UserSetup::particleAmount; ++i)
		{
			if(particleArray[i].isActive())
			{
				arduboy.drawRect(particleArray[i].x, particleArray[i].y, particleArray[i].size, particleArray[i].size, WHITE);
			}
		}
	}

	if(!UserSetup::roundParticles && UserSetup::filledParticles)
	{
		for(uint8_t i = 0; i < UserSetup::particleAmount; ++i)
		{
			if(particleArray[i].isActive())
			{
				arduboy.fillRect(particleArray[i].x, particleArray[i].y, particleArray[i].size, particleArray[i].size, WHITE);
			}
		}
	}

	if(UserSetup::roundParticles && !UserSetup::filledParticles)
	{
		for(uint8_t i = 0; i < UserSetup::particleAmount; ++i)
		{
			if(particleArray[i].isActive())
			{
				arduboy.drawCircle(particleArray[i].x, particleArray[i].y, (particleArray[i].size / 2), WHITE);
			}
		}
	}

	if(UserSetup::roundParticles && UserSetup::filledParticles)
	{
		for(uint8_t i = 0; i < UserSetup::particleAmount; ++i)
		{
			if(particleArray[i].isActive())
			{
				arduboy.fillCircle(particleArray[i].x, particleArray[i].y, (particleArray[i].size / 2), WHITE);
			}
		}
	}
}