/*
Modified XMLParserUtil from:
Music Player chapter in the book Adobe AIR Create-Modify-Reuse(ISBN: 978-0-470-18207-9)
by:
Marc Leuchner, Todd Anderson, Matt Wright.
*/

package com.scuttlebutt.utils
{
    import com.scuttlebutt.managers.AppManager;
    import com.scuttlebutt.model.ChatMessage;
    import com.scuttlebutt.model.Settings;
    import com.scuttlebutt.model.User;
    
    public class XMLParserUtil
    {
        public static function parseSettingsXML( xml : XML ) : Settings
        {
            var settings : Settings = new Settings();
            settings._user.name = xml.name;
            settings._user.ip = xml.ip;
            settings._user.group = xml.group;
            settings._user.status = (int)(xml.status);
            settings._user.statusMessage = xml.statusMessage;
            settings._user.location = xml.location;
            settings._user.avatar = xml.avatar;
            
            if (xml.notification == "true")
                settings._notification = true;
            else
                settings._notification = false;
            
            if (xml.firstRun == "true")
                settings._firstRun = true;
            else
                settings._firstRun = false;

            var ipList : String = xml.iplist;
            var lastIndex : int = 0;
            
            for(var i:int = 0; i < ipList.length; i++)
            {
                if(ipList.charAt(i) == ":")
                {
                    trace("[XML Util] IPList: " + ipList.slice(lastIndex, i-1));
                    settings._ipList.push(ipList.slice(lastIndex, i));
                    lastIndex = i+1;
                }
            }
            return settings;
        }
        
        public static function buildSettingsXML() : XML
        {
            var xml : XML = new XML("<settings></settings>");
            var _user : User = AppManager.getInstance().settings._user;
            xml.name = _user.name;
            xml.ip = _user.ip;
            xml.group = _user.group;
            xml.status = _user.status;
            xml.statusMessage = _user.statusMessage;
            xml.location = _user.location;
            xml.avatar = _user.avatar;
            xml.notification = AppManager.getInstance().settings._notification;
            xml.firstRun = false;
            
            var ipList : String = "";
            for(var i : int = 0; i < AppManager.getInstance().settings._ipList.length; i++)
            {
                ipList += AppManager.getInstance().settings._ipList[i] + ":";
            }
            
            xml.iplist = ipList;
            
            //trace("[Built SettingsXML] :\n" + xml);
            return xml;
        }
        
        public static function parseInfoDatagramXML( xml : XML ) : User
        {
            var _user : User = new User();
            _user.sid = xml.sid;
            _user.name = xml.name;
            _user.ip = xml.ip;
            _user.group = xml.group;
            _user.status = (int)(xml.status);
            _user.statusMessage = xml.statusMessage;
            _user.location = xml.location;
            _user.avatar = xml.avatar;
            _user.alive = xml.alive=="true" ? true : false;
            _user.respond = xml.respond=="true" ? true : false;

            return _user;
        }
        
        public static function buildInfoDataGramXML() : XML
        {
            var xml : XML = new XML("<scuttlebutt></scuttlebutt>");
            var _user : User = AppManager.getInstance().settings._user;
            xml.sid = _user.sid;
            xml.name = _user.name;
            xml.ip = _user.ip;
            xml.group = _user.group;
            xml.status = _user.status;
            xml.statusMessage = _user.statusMessage;
            xml.location = _user.location;
            xml.avatar = _user.avatar;
            xml.alive = _user.alive;
            xml.respond = _user.respond;
            if(_user.respond == true)
                _user.respond = false;
            
            //trace("[Built DataGramXML] : \n" + xml);
            return xml;   
        }
        
        public static function parseChatDatagramXML( xml : XML ) : ChatMessage
        {
            var cMsg :ChatMessage = new ChatMessage();
            
            //IP will be handled by receiving/sending routines
            cMsg.sid = xml.sid;
            cMsg.name = xml.name;
            cMsg.message = xml.message;
            
            return cMsg;
        }
        
        public static function buildChatDatagramXML( message : String ) : XML
        {
            var xml : XML = new XML("<scuttlebutt></scuttlebutt>");

            xml.sid = AppManager.getInstance().settings._user.sid;
            xml.name = AppManager.getInstance().settings._user.name;
            xml.message = message;
            
            //trace("[Built ChatXML] : \n" + xml);
            return xml;   
        }
        
    }
}