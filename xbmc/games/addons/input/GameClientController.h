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

#pragma once

#include "addons/kodi-addon-dev-kit/include/kodi/kodi_game_types.h"
#include "games/controllers/ControllerTypes.h"

#include <vector>

namespace KODI
{
namespace GAME
{
  class CController;

  /*!
   * \brief A container for the layout of a controller connected to a game
   *        client input port
   */
  class CGameClientController
  {
  public:
    /*!
     * \brief Construct a controller layout
     *
     * \brief controller The controller add-on
     */
    CGameClientController(ControllerPtr controller);

    /*!
     * \brief Translate a controller layout (Kodi to Game API)
     */
    game_controller_layout TranslateController();

  private:
    // Construction parameters
    const ControllerPtr m_controller;

    // Buffer parameters
    std::vector<char*> m_digitalButtons;
    std::vector<char*> m_analogButtons;
    std::vector<char*> m_analogSticks;
    std::vector<char*> m_accelerometers;
    std::vector<char*> m_keys;
    std::vector<char*> m_relPointers;
    std::vector<char*> m_absPointers;
    std::vector<char*> m_motors;
  };
} // namespace GAME
} // namespace KODI
