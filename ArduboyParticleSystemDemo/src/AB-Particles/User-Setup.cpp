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

namespace UserSetup
{
	uint8_t particleAmount = 30;

	bool roundParticles = false;
	bool filledParticles = false;

	int8_t xForceMin = -5;
	int8_t xForceMax = 6;

	int8_t yForceMin = 10;
	int8_t yForceMax = 15;

	uint8_t sizeMin = 2;
	uint8_t sizeMax = 5;

	uint8_t lifetimeMin = 80;
 	uint8_t lifetimeMax = 91;

	float gravity = 0.042;
}