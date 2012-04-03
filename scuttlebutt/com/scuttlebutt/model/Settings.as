package com.scuttlebutt.model
{   
    [Bindable]
    public class Settings
    {
        public var _user : User;
        public var _firstRun : Boolean = false;
        public var _ipList : Array;
        public var _notification : Boolean = true;
        
        public function Settings()
        {
            _user = new User();
            _ipList = new Array;
        }
        
        public function get user() : User
        {
            return _user;
        }
        
        public function set user( val : User ) : void
        {
            _user = val;
        }
        
        //TODO: Make getters and setters for other vars
        
    }
}