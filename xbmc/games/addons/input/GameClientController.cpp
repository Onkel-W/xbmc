/*
 *      Copyright (C) 2018 Team Kodi
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this Program; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "GameClientController.h"
#include "games/controllers/Controller.h"
#include "games/controllers/ControllerFeature.h"
#include "games/controllers/ControllerLayout.h"
#include "games/controllers/ControllerTopology.h"

#include <algorithm>
#include <vector>

using namespace KODI;
using namespace GAME;

CGameClientController::CGameClientController(ControllerPtr controller) :
  m_controller(std::move(controller))
{
}

game_controller_layout CGameClientController::TranslateController()
{
  game_controller_layout controllerStruct{};

  controllerStruct.controller_id = const_cast<char*>(m_controller->ID().c_str());
  controllerStruct.provides_input = m_controller->Layout().Topology().ProvidesInput();

  m_digitalButtons.clear();
  m_analogButtons.clear();
  m_analogSticks.clear();
  m_accelerometers.clear();
  m_keys.clear();
  m_relPointers.clear();
  m_absPointers.clear();
  m_motors.clear();

  for (const CControllerFeature &feature : m_controller->Features())
  {
    switch (feature.Type())
    {
      case FEATURE_TYPE::SCALAR:
      {
        switch (feature.InputType())
        {
          case JOYSTICK::INPUT_TYPE::DIGITAL:
            m_digitalButtons.emplace_back(const_cast<char*>(feature.Name().c_str()));
            break;
          case JOYSTICK::INPUT_TYPE::ANALOG:
            m_analogButtons.emplace_back(const_cast<char*>(feature.Name().c_str()));
            break;
          default:
            break;
        }
        break;
      }
      case FEATURE_TYPE::ANALOG_STICK:
        m_analogSticks.emplace_back(const_cast<char*>(feature.Name().c_str()));
        break;
      case FEATURE_TYPE::ACCELEROMETER:
        m_accelerometers.emplace_back(const_cast<char*>(feature.Name().c_str()));
        break;
      case FEATURE_TYPE::KEY:
        m_keys.emplace_back(const_cast<char*>(feature.Name().c_str()));
        break;
      case FEATURE_TYPE::RELPOINTER:
        m_relPointers.emplace_back(const_cast<char*>(feature.Name().c_str()));
        break;
      case FEATURE_TYPE::ABSPOINTER:
        m_absPointers.emplace_back(const_cast<char*>(feature.Name().c_str()));
        break;
      case FEATURE_TYPE::MOTOR:
        m_motors.emplace_back(const_cast<char*>(feature.Name().c_str()));
        break;
      default:
        break;
    }
  }

  //! @todo Sort vectors

  if (!m_digitalButtons.empty())
  {
    controllerStruct.digital_buttons = const_cast<char**>(m_digitalButtons.data());
    controllerStruct.digital_button_count = m_digitalButtons.size();
  }
  if (!m_analogButtons.empty())
  {
    controllerStruct.analog_buttons = const_cast<char**>(m_analogButtons.data());
    controllerStruct.analog_button_count = m_analogButtons.size();
  }
  if (!m_analogSticks.empty())
  {
    controllerStruct.analog_sticks = const_cast<char**>(m_analogSticks.data());
    controllerStruct.analog_stick_count = m_analogSticks.size();
  }
  if (!m_accelerometers.empty())
  {
    controllerStruct.accelerometers = const_cast<char**>(m_accelerometers.data());
    controllerStruct.accelerometer_count = m_accelerometers.size();
  }
  if (!m_keys.empty())
  {
    controllerStruct.keys = const_cast<char**>(m_keys.data());
    controllerStruct.key_count = m_keys.size();
  }
  if (!m_relPointers.empty())
  {
    controllerStruct.rel_pointers = const_cast<char**>(m_relPointers.data());
    controllerStruct.rel_pointer_count = m_relPointers.size();
  }
  if (!m_absPointers.empty())
  {
    controllerStruct.abs_pointers = const_cast<char**>(m_absPointers.data());
    controllerStruct.abs_pointer_count = m_absPointers.size();
  }
  if (!m_motors.empty())
  {
    controllerStruct.motors = const_cast<char**>(m_motors.data());
    controllerStruct.motor_count = m_motors.size();
  }

  return controllerStruct;
}
