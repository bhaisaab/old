package com.scuttlebutt.model
{   
    [Bindable]
    public class User
    {    
        /** SID: ScuttleButt (Instance) Identifier **/
        public var sid : String = "";
        
        /** The name of the user. **/
        public var name : String = "";
        
        /** The group that this employee belongs too. **/
        public var group: String = "";
        
        /** The identifier of the user's IP **/
        public var ip : String = "";
        
        /** Status: Available, Busy, Idle, Away, Offline **/
        public var status : int = 0;
        
        /** Status Message **/
        public var statusMessage : String = "";
                
        /** The location(hostel, floor etc.) of the user. **/
        public var location : String = "";
        
        /** Avatar Image BitmapData Base64Encoded as string **/
        public var avatar : String = "";
        
        /** Is user alive? **/
        public var alive : Boolean = true;
        
        /** State of user, whether to tell peers to respond her or not! **/
        public var respond : Boolean = false;
        
        public function User()
        {
        }
        
        public function update( val : User ) : void
        {
            //All except SID, repond and alive
            this.name = val.name;
            this.ip = val.ip;
            this.group = val.group;
            this.status = val.status;
            this.statusMessage = val.statusMessage;
            this.location = val.location;
            this.avatar = val.avatar;
        }
        
        public function get id() : String
        {
            return this.sid;	
        }
        
        public function toString():String
        {
            return "User : " + name;
        }
    }
}