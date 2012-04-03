package com.scuttlebutt.managers
{
    import com.scuttlebutt.model.User;
    
    import flash.events.EventDispatcher;
    
    import mx.collections.*;
    
    public class UsersManager extends EventDispatcher
    {
        private static var _instance : UsersManager;
        
        [Bindable]
        public var userList : ArrayList;
        
        public function UsersManager()
        {
            userList = new ArrayList();
        }
        
        public static function getInstance() : UsersManager
        {
            if(_instance == null) 
            {
                _instance = new UsersManager();
            }
            return _instance;
        }
        
        public function getUserBySID( sid : String ) : User
        {
            if(!sid)
                return null;
            
            var user : User;
            
            for( var i : int = 0; i < userList.length; i++ )
            {
                if( sid == User(userList.getItemAt(i)).sid )
                {
                    user = User(userList.getItemAt(i));
                    break;
                }
            }
            return user;
        }
        
        public function getUserIndexBySID( sid : String ) : int
        {
            for( var i : int = 0; i < userList.length; i++ )
            {
                if( sid == User(userList.getItemAt(i)).sid )
                    return i;
            }
            return -1;
        }
        
        //Assumes that getUserIndexBySID is true;
        public function getUserByIndex( index : int ) : User
        {
            return User(userList.getItemAt(index));
        }
        
        public function addNewUser( user : User ) : void
        {
            if( checkRedundancy(user) )
            {   
                //[ROBUSTNESS] Add only if user is alive
                trace("[Adding new USER to UserList ("+userList.length+")] SID: "+user.sid);
                if(user.alive)
                    userList.addItem(user); 
            }

            update();
        }
        
        public function update() : void
        {
            //StatusBar Total user count
            AppManager.getInstance()._statusBar._totalUsers = userList.length;
        }
        
        public function checkRedundancy( user : User) : Boolean
        {
            trace("[Redundancy check {"+userList.length+"} for SID] " + user.sid);
            
            for( var i : int = 0; i < userList.length; i++ )
            {
                //[ROBUSTNESS] SID will be constant no matter name, ip etc.
                if( User(userList.getItemAt(i)).sid == user.sid)
                {
                    if( user.alive )
                    {
                        trace("[User Update] " + user.sid);
                        //Fix data change event in future release
                        userList.setItemAt(user, i);
                        //User(userList.getItemAt(i)).update(user);
                    }
                    else
                    {
                        trace("[Removing Dead User] SID: " + user.sid);
                        //User is dead, remove it
                        userList.removeItemAt(i);
                    }
                    return false;
                }
            }
            return true;
        }
    }
}
