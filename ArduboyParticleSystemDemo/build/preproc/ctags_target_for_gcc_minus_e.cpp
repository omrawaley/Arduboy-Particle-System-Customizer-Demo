# 1 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
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

# 18 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 2

# 20 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 2

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
 if(arduboy.pressed(
# 66 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                   (1 << (
# 66 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                   6
# 66 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                   )) 
# 66 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                   /**< The Right button value for functions requiring a bitmask */))
 {
  UserSetup::gravity += 0.001;
 }

 if(arduboy.pressed(
# 71 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                   (1 << (
# 71 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                   5
# 71 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                   )) 
# 71 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                   /**< The Left button value for functions requiring a bitmask */) && UserSetup::gravity > 0.0001)
 {
  UserSetup::gravity -= 0.001;
 }
}

void adjustRoundParticles()
{
 if(arduboy.pressed(
# 79 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                   (1 << (
# 79 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                   6
# 79 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                   )) 
# 79 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                   /**< The Right button value for functions requiring a bitmask */))
 {
  UserSetup::roundParticles = true;
 }

 if(arduboy.pressed(
# 84 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                   (1 << (
# 84 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                   5
# 84 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                   )) 
# 84 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                   /**< The Left button value for functions requiring a bitmask */))
 {
  UserSetup::roundParticles = false;;
 }
}

void adjustFilledParticles()
{
 if(arduboy.pressed(
# 92 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                   (1 << (
# 92 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                   6
# 92 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                   )) 
# 92 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                   /**< The Right button value for functions requiring a bitmask */))
 {
  UserSetup::filledParticles = true;
 }

 if(arduboy.pressed(
# 97 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                   (1 << (
# 97 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                   5
# 97 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                   )) 
# 97 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                   /**< The Left button value for functions requiring a bitmask */))
 {
  UserSetup::filledParticles = false;
 }
}

void adjustParticleAmount()
{
 if(arduboy.justPressed(
# 105 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       (1 << (
# 105 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       6
# 105 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       )) 
# 105 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       /**< The Right button value for functions requiring a bitmask */) && UserSetup::particleAmount < 40)
 {
  ++UserSetup::particleAmount;
 }

 if(arduboy.justPressed(
# 110 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       (1 << (
# 110 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       5
# 110 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       )) 
# 110 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       /**< The Left button value for functions requiring a bitmask */) && UserSetup::particleAmount > 1)
 {
  --UserSetup::particleAmount;
 }
}

void adjustMinParticleSize()
{
 if(arduboy.justPressed(
# 118 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       (1 << (
# 118 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       6
# 118 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       )) 
# 118 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       /**< The Right button value for functions requiring a bitmask */) && UserSetup::sizeMin < UserSetup::sizeMax)
 {
  ++UserSetup::sizeMin;
 }

 if(arduboy.justPressed(
# 123 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       (1 << (
# 123 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       5
# 123 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       )) 
# 123 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       /**< The Left button value for functions requiring a bitmask */) && UserSetup::sizeMin > 1)
 {
  --UserSetup::sizeMin;
 }
}

void adjustMaxParticleSize()
{
 if(arduboy.justPressed(
# 131 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       (1 << (
# 131 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       6
# 131 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       )) 
# 131 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       /**< The Right button value for functions requiring a bitmask */))
 {
  ++UserSetup::sizeMax;
 }

 if(arduboy.justPressed(
# 136 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       (1 << (
# 136 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       5
# 136 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       )) 
# 136 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       /**< The Left button value for functions requiring a bitmask */) && UserSetup::sizeMax > UserSetup::sizeMin)
 {
  --UserSetup::sizeMax;
 }
}

void adjustMinParticleLifetime()
{
 if(arduboy.justPressed(
# 144 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       (1 << (
# 144 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       6
# 144 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       )) 
# 144 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       /**< The Right button value for functions requiring a bitmask */) && UserSetup::lifetimeMin < UserSetup::lifetimeMax)
 {
  ++UserSetup::lifetimeMin;
 }

 if(arduboy.justPressed(
# 149 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       (1 << (
# 149 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       5
# 149 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       )) 
# 149 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       /**< The Left button value for functions requiring a bitmask */) && UserSetup::lifetimeMin > 1)
 {
  --UserSetup::lifetimeMin;
 }
}

void adjustMaxParticleLifetime()
{
 if(arduboy.justPressed(
# 157 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       (1 << (
# 157 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       6
# 157 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       )) 
# 157 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       /**< The Right button value for functions requiring a bitmask */))
 {
  ++UserSetup::lifetimeMax;
 }

 if(arduboy.justPressed(
# 162 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       (1 << (
# 162 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       5
# 162 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       )) 
# 162 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       /**< The Left button value for functions requiring a bitmask */) && UserSetup::lifetimeMax > UserSetup::lifetimeMin)
 {
  --UserSetup::lifetimeMax;
 }
}

void adjustMinParticleXForce()
{
 if(arduboy.justPressed(
# 170 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       (1 << (
# 170 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       6
# 170 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       )) 
# 170 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       /**< The Right button value for functions requiring a bitmask */) && UserSetup::xForceMin < 0)
 {
  ++UserSetup::xForceMin;
 }

 if(arduboy.justPressed(
# 175 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       (1 << (
# 175 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       5
# 175 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       )) 
# 175 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       /**< The Left button value for functions requiring a bitmask */))
 {
  --UserSetup::xForceMin;
 }
}

void adjustMaxParticleXForce()
{
 if(arduboy.justPressed(
# 183 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       (1 << (
# 183 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       6
# 183 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       )) 
# 183 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       /**< The Right button value for functions requiring a bitmask */))
 {
  ++UserSetup::xForceMax;
 }

 if(arduboy.justPressed(
# 188 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       (1 << (
# 188 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       5
# 188 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       )) 
# 188 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       /**< The Left button value for functions requiring a bitmask */) && UserSetup::xForceMax > 0)
 {
  --UserSetup::xForceMax;
 }
}

void adjustMinParticleYForce()
{
 if(arduboy.justPressed(
# 196 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       (1 << (
# 196 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       6
# 196 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       )) 
# 196 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       /**< The Right button value for functions requiring a bitmask */) && UserSetup::yForceMin < UserSetup::yForceMax)
 {
  ++UserSetup::yForceMin;
 }

 if(arduboy.justPressed(
# 201 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       (1 << (
# 201 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       5
# 201 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       )) 
# 201 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       /**< The Left button value for functions requiring a bitmask */) && UserSetup::yForceMax > 0)
 {
  --UserSetup::yForceMin;
 }
}

void adjustMaxParticleYForce()
{
 if(arduboy.justPressed(
# 209 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       (1 << (
# 209 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       6
# 209 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       )) 
# 209 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       /**< The Right button value for functions requiring a bitmask */))
 {
  ++UserSetup::yForceMax;
 }

 if(arduboy.justPressed(
# 214 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       (1 << (
# 214 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       5
# 214 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       )) 
# 214 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       /**< The Left button value for functions requiring a bitmask */) && UserSetup::yForceMax > UserSetup::yForceMin)
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

 if(arduboy.justPressed(
# 240 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       (1 << (
# 240 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       4
# 240 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       )) 
# 240 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       /**< The Down button value for functions requiring a bitmask */) && menu.menuCursorIndex < (Menu::totalMenuOptions - 1))
 {
  menu.menuCameraY -= 8;
  ++menu.menuCursorIndex;
 }

 if(arduboy.justPressed(
# 246 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       (1 << (
# 246 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       7
# 246 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       )) 
# 246 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       /**< The Up button value for functions requiring a bitmask */) && menu.menuCursorIndex > 0)
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

 if(arduboy.justPressed(
# 303 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       (1 << (
# 303 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       3
# 303 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       )) 
# 303 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       /**< The A button value for functions requiring a bitmask */) || arduboy.justPressed(
# 303 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                                                        (1 << (
# 303 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                                                        2
# 303 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                                                        )) 
# 303 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                                                        /**< The B button value for functions requiring a bitmask */))
 {
  goToSimulation();

  particles.reset(particlePosX, particlePosY);
 }
}

void updateSimulation()
{
 particles.update();

 if(arduboy.justPressed(
# 315 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       (1 << (
# 315 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       3
# 315 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                       )) 
# 315 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                       /**< The A button value for functions requiring a bitmask */) || arduboy.justPressed(
# 315 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                                                        (1 << (
# 315 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                                                        2
# 315 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
                                                        )) 
# 315 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
                                                        /**< The B button value for functions requiring a bitmask */))
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
 font4x6.print((reinterpret_cast<const __FlashStringHelper *>(
# 329 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 329 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
              "Gravity "
# 329 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
              ); &__c[0];}))
# 329 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
              )));
 font4x6.println(UserSetup::gravity, 3);
 font4x6.print((reinterpret_cast<const __FlashStringHelper *>(
# 331 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 331 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
              "Round Particles "
# 331 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
              ); &__c[0];}))
# 331 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
              )));
 font4x6.println(menu.roundParticlesStatus);
 font4x6.print((reinterpret_cast<const __FlashStringHelper *>(
# 333 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 333 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
              "Filled Particles "
# 333 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
              ); &__c[0];}))
# 333 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
              )));
 font4x6.println(menu.filledParticlesStatus);
 font4x6.print((reinterpret_cast<const __FlashStringHelper *>(
# 335 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 335 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
              "Particle Amount "
# 335 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
              ); &__c[0];}))
# 335 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
              )));
 font4x6.println(UserSetup::particleAmount);
 font4x6.print((reinterpret_cast<const __FlashStringHelper *>(
# 337 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 337 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
              "Min Particle Size "
# 337 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
              ); &__c[0];}))
# 337 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
              )));
 font4x6.println(UserSetup::sizeMin);
 font4x6.print((reinterpret_cast<const __FlashStringHelper *>(
# 339 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 339 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
              "Max Particle Size "
# 339 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
              ); &__c[0];}))
# 339 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
              )));
 font4x6.println(UserSetup::sizeMax);
 font4x6.print((reinterpret_cast<const __FlashStringHelper *>(
# 341 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 341 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
              "Min Particle Lifetime "
# 341 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
              ); &__c[0];}))
# 341 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
              )));
 font4x6.println(UserSetup::lifetimeMin);
 font4x6.print((reinterpret_cast<const __FlashStringHelper *>(
# 343 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 343 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
              "Max Particle Lifetime "
# 343 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
              ); &__c[0];}))
# 343 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
              )));
 font4x6.println(UserSetup::lifetimeMax);
 font4x6.print((reinterpret_cast<const __FlashStringHelper *>(
# 345 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 345 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
              "Min Particle XForce "
# 345 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
              ); &__c[0];}))
# 345 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
              )));
 font4x6.println(UserSetup::xForceMin);
 font4x6.print((reinterpret_cast<const __FlashStringHelper *>(
# 347 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 347 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
              "Max Particle XForce "
# 347 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
              ); &__c[0];}))
# 347 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
              )));
 font4x6.println(UserSetup::xForceMax);
 font4x6.print((reinterpret_cast<const __FlashStringHelper *>(
# 349 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 349 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
              "Min Particle YForce "
# 349 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
              ); &__c[0];}))
# 349 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
              )));
 font4x6.println(UserSetup::yForceMin);
 font4x6.print((reinterpret_cast<const __FlashStringHelper *>(
# 351 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 351 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
              "Max Particle YForce "
# 351 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino" 3
              ); &__c[0];}))
# 351 "/Users/om/Downloads/ARDUBOY/ArduboyParticleSystemDemo/ArduboyParticleSystemDemo.ino"
              )));
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
