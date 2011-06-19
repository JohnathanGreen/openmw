#ifndef MWGUI_MESSAGE_BOX_H
#define MWGUI_MESSAGE_BOX_H

#include <openengine/gui/layout.hpp>
#include <MyGUI.h>

#include "window_base.hpp"
#include "window_manager.hpp"


namespace MWGui
{
    
    class InteractiveMessageBox;
    class MessageBoxManager;
    class MessageBox;

    struct MessageBoxManagerTimer {
        float current;
        float max;
        MessageBox *messageBox;
    };

    class MessageBoxManager
    {
        public:
            MessageBoxManager (WindowManager* windowManager, MyGUI::Gui *_gui);
            void onFrame (float frameDuration);
            void createMessageBox (const std::string& message);
            bool createInteractiveMessageBox (const std::string& message, const std::vector<std::string>& buttons);
            bool isInteractiveMessageBox ();
            
            void removeMessageBox (float time, MessageBox *msgbox);
            bool removeMessageBox (MessageBox *msgbox);
            void setMessageBoxSpeed (int speed);
            
            WindowManager *mWindowManager;
            
        private:
            std::vector<MessageBox*> mMessageBoxes;
            InteractiveMessageBox* mInterMessageBoxe;
            std::vector<MessageBoxManagerTimer> mTimers;
            MyGUI::Gui *gui;
            float mMessageBoxSpeed;
    };
    
    class MessageBox : public OEngine::GUI::Layout
    {
        public:
            MessageBox (MessageBoxManager& parMessageBoxManager, const std::string& message);
            void setMessage (const std::string& message);
            int getHeight ();
            void update (int height);
            
            bool mMarkedToDelete;
            
        protected:
            MessageBoxManager& mMessageBoxManager;
            int mHeight;
            const std::string& cMessage;
            MyGUI::EditPtr mMessageWidget;
            int mFixedWidth;
            int mBottomPadding;
            int mNextBoxPadding;
    };
    
    class InteractiveMessageBox : public OEngine::GUI::Layout
    {
        public:
            InteractiveMessageBox (MessageBoxManager& parMessageBoxManager, MyGUI::Gui *_gui, const std::string& message, const std::vector<std::string>& buttons);
            
        protected:
            MessageBoxManager& mMessageBoxManager;
            MyGUI::EditPtr mMessageWidget;
            MyGUI::WidgetPtr mButtonsWidget;
            MyGUI::Gui *mGUI;
            //std::vector<MyGUI::Button> mButtons;
    };

}

#endif
