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

#pragma once

#include "User-Setup.h"

#include <Arduboy2.h>

class Particles
{
	private:

		struct Particle
		{
			float x;
			float y;

			float xVelocity;
			float yVelocity;

			float xForce;
			float yForce;

			uint8_t size;

			int counter;
			
			bool isActive() const
			{
				return(this->counter > 0);
			};
		};

	public:

		void reset(int x, int y);

		void update();
		void render();

		Particle particleArray[UserSetup::maximumAmountOfParticles];
		
};

extern Particles particles;
extern Arduboy2 arduboy;