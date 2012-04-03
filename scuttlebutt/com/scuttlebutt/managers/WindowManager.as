package com.scuttlebutt.managers
{
    import com.scuttlebutt.model.ChatWindow;
    import com.scuttlebutt.model.User;
    import com.scuttlebutt.model.ChatMessage;
    
    import flash.events.EventDispatcher;
    
    import mx.collections.*;
    
    public class WindowManager extends EventDispatcher
    {
        private static var _instance : WindowManager;
        
        public var windows : ArrayList;
        
        public function WindowManager() 
        {
            windows = new ArrayList;           
        }
        
        public static function getInstance() : WindowManager
        {
            if(_instance == null) 
            {
                _instance = new WindowManager();
            }
            return _instance;
        }
        
        public function openChatWindow( val : User ) : int
        {
            for( var i : int = 0; i < windows.length; i++ )
            {
                if( ChatWindow(windows.getItemAt(i)).sid == val.sid )
                {   
                    trace("[Window Manager] Opening Window for SID " + val.sid);
                    ChatWindow(windows.getItemAt(i)).updateUserInfo(val);
                    ChatWindow(windows.getItemAt(i)).showWindow();
                    return i;
                }
            }
            return createChatWindow(val);
        }
        
        private function createChatWindow( val : User ) : int
        {
            windows.addItem( new ChatWindow(val) );
            return windows.length-1;
        }
              
        public function updateChatWindow( val : User ) : Boolean
        {
            if(!val)
                return false;
            
            for(var i : int = 0; i < windows.length; i++ )
            {
                if( ChatWindow(windows.getItemAt(i)).sid == val.sid )
                {
                    ChatWindow(windows.getItemAt(i)).updateUserInfo(val);
                    return true;
                }
            }
            return false;
        }
        
        public function postReceivedChatMessage( peer : User, msg : ChatMessage ) : void
        {
            //If no window initialised yet... find user from the list
            //TODO: Implement Dictionary or Hash Maps to faster search windows and users
            var index : int = openChatWindow(peer);
            trace("[window index]: " + index);
            
            //TODO: Make a Avatar Manager, so that avatars are updated only when required,
            //Not with every message!
            msg.avatar = peer.avatar;
            
            //If notifications enabled, notify user
            //TODO: show only when app minimised or on user presence idle/present
            if(AppManager.getInstance().settings._notification)
                AppManager.getInstance().showNotification(msg.name, msg.message, msg.sid);

            ChatWindow(windows.getItemAt(index)).onChatMessageReceive(msg);
        }
        
        public function closeAllWindows() : void
        {
            for(var i:int = 0; i < windows.length; i++)
            {
                ChatWindow(windows.getItemAt(i)).closeWindow();
            }
            windows.removeAll();
        }
    }
}