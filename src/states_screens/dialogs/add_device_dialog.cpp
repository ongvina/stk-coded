//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2009 Marianne Gagnon
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 3
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.


#include "config/player.hpp"
#include "guiengine/engine.hpp"
#include "guiengine/widget.hpp"
#include "input/device_manager.hpp"
#include "input/input_manager.hpp"
#include "states_screens/dialogs/add_device_dialog.hpp"
#include "states_screens/options_screen_players.hpp"
#include "states_screens/options_screen_input.hpp"
#include "states_screens/state_manager.hpp"
#include "utils/string_utils.hpp"
#include "utils/translation.hpp"

using namespace GUIEngine;
using namespace irr::gui;
using namespace irr::core;

AddDeviceDialog::AddDeviceDialog() : ModalDialog(0.7f, 0.7f)
{    
    IGUIFont* font = GUIEngine::getFont();
    const int textHeight = font->getDimension(L"X").Height;
    const int buttonHeight = textHeight + 10;
    
    const int y_bottom = m_area.getHeight() - 2*(buttonHeight + 10) - 20;

    core::rect<s32> text_area( 15, 15, m_area.getWidth()-15, y_bottom-15 );
    
    IGUIStaticText* b = GUIEngine::getGUIEnv()->addStaticText( _("To add a new Gamepad/Joystick device, simply start SuperTuxKart with it connected and it will appear in the list.\n\nTo add a keyboard config, you can use the button below, HOWEVER please note that most keyboards only support a limited amount of simultaneous keypresses and are thus inappropriate for multiplayer gameplay."),
                                                              text_area, false , true , // border, word warp
                                                              m_irrlicht_window);
    b->setTabStop(false);
    
       
    {
        ButtonWidget* widget = new ButtonWidget();
        widget->m_properties[PROP_ID] = "addkeyboard";
        
        //I18N: In the 'add new input device' dialog
        widget->m_text = _("Add Keyboard Configuration");
        
        const int textWidth = font->getDimension( widget->m_text.c_str() ).Width + 40;
        
        widget->x = m_area.getWidth()/2 - textWidth/2;
        widget->y = y_bottom;
        widget->w = textWidth;
        widget->h = buttonHeight;
        widget->setParent(m_irrlicht_window);
        m_children.push_back(widget);
        widget->add();
    }
    {
        ButtonWidget* widget = new ButtonWidget();
        widget->m_properties[PROP_ID] = "cancel";
        widget->m_text = _("Cancel");
        
        const int textWidth = font->getDimension( widget->m_text.c_str() ).Width + 40;
        
        widget->x = m_area.getWidth()/2 - textWidth/2;
        widget->y = y_bottom + buttonHeight + 20;
        widget->w = textWidth;
        widget->h = buttonHeight;
        widget->setParent(m_irrlicht_window);
        m_children.push_back(widget);
        widget->add();
        
        widget->setFocusForPlayer( GUI_PLAYER_ID );    

    }
    
}
// ------------------------------------------------------------------------------------------------------
void AddDeviceDialog::onEnterPressedInternal()
{
}
// ------------------------------------------------------------------------------------------------------
GUIEngine::EventPropagation AddDeviceDialog::processEvent(std::string& eventSource)
{

    if (eventSource == "cancel")
    {   
        ModalDialog::dismiss();
        return GUIEngine::EVENT_BLOCK;
    }
    else if (eventSource == "addkeyboard")
    {
        input_manager->getDeviceList()->addEmptyKeyboard();
        input_manager->getDeviceList()->serialize();
        ModalDialog::dismiss();
        
        ((OptionsScreenInput*)GUIEngine::getCurrentScreen())->rebuildDeviceList();
        
        return GUIEngine::EVENT_BLOCK;
    }
    
    return GUIEngine::EVENT_LET;
}
