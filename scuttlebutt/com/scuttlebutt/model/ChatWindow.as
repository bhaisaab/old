package com.scuttlebutt.model
{
    import com.scuttlebutt.view.ChatWindowUI;
    
    import flash.display.NativeWindowSystemChrome;

    public class ChatWindow
    {
        private var chatWindow : ChatWindowUI;
        private var _sid : String = "";
        private var _user : User;
        
        public function ChatWindow( val : User ) : void
        {
            createWindow(val);
            this.sid = val.sid;
            _user = val;
        }

        public function createWindow( val : User ) : void
        {
            chatWindow = new ChatWindowUI();

            chatWindow.updateUserInfo(val);
            chatWindow._peerName = val.name;
            chatWindow.systemChrome = NativeWindowSystemChrome.NONE;
            chatWindow.transparent = true;
            chatWindow.resizable = false;
            chatWindow.open(true);
            chatWindow.visible = true;
        }
        
        public function onChatMessageReceive( msg : ChatMessage ) : void
        {
            chatWindow.onChatMessageReceive(msg);
        }
        
        public function updateUserInfo(val:User) : void
        {
            _user = val;
            chatWindow.updateUserInfo(val);
        }
        
        public function closeWindow() : void
        {
            if(!chatWindow.closed)
                chatWindow.close();
            chatWindow = null;
        }
        
        public function showWindow() : void
        {
            if(!chatWindow.closed)
            {
                chatWindow.visible = true;
                chatWindow.setFocus();
                return;
            }
            else
            {
                trace("[Window was Closed] Recreating new window");
                createWindow(_user);
            }
        }
        
        public function set sid( val : String ) : void
        {
            _sid = val;   
        }
        
        public function get sid() : String
        {
            return _sid;
        }
    }
}