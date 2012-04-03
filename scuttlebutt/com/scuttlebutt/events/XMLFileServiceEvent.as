/*
    Modified XMLParserUtil from:
    Music Player, chapter in the book Adobe AIR Create-Modify-Reuse(ISBN: 978-0-470-18207-9)
    by: Marc Leuchner, Todd Anderson, Matt Wright.
*/

package com.scuttlebutt.events
{
    import flash.events.Event;
    
    public class XMLFileServiceEvent extends Event
    {    	
        public static const XML_FILE_COPIED:String = "xmlFileCopied";
        public static const XML_FILE_NOT_FOUND:String = "xmlFileNotFound";
        public static const XML_FILE_WRITTEN:String = "xmlFileWritten";
        public static const XML_LOADED:String = "xmlLoaded";
        public static const XML_ERROR:String = "xmlError";
        
        private var _xmlResults:XML;
        private var _message:String;
        
        public function XMLFileServiceEvent( type:String, bubbles:Boolean=false, cancelable:Boolean=false )
        {
            super( type, bubbles, cancelable );
        }
        
        public function get xml():XML
        {
            return _xmlResults;
        }
        
        public function set xml( val:XML ):void
        {
            _xmlResults = val;
        }
        
        public function get message():String
        {
            return _message;
        }	
        
        public function set message( val:String ):void
        {
            _message = val;
        }
    }
}