package com.scuttlebutt.model
{   
    import flash.utils.ByteArray;

    [Bindable]
    public class ChatMessage
    {
        public var sid : String = "";
        public var ip : String = "";
        public var name : String = "";
        public var message : String = "";
        public var avatar : String = "";
        public var ba:ByteArray = new ByteArray;

        public function ChatMesages() : void
        {
        }
    }
}