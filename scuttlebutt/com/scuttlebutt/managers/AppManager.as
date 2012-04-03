/*
    This class contains a totally new kind of logic/code,
    If you use it in your project, I would love to know!
    Copyright Rohit Yadav <rohityadav89@gmail.com>, 2009-10
    
    The usual bla bla and DON'T SUE US FOR ANYTHING :-)
    Report bugs, send patches and for other queries contact: rohityadav89@gmail.com
    
    THIS SOURCE CODE IS PROVIDED "AS IS" AND "WITH ALL FAULTS", WITHOUT 
    ANY TECHNICAL SUPPORT OR ANY EXPRESSED OR IMPLIED WARRANTIES, INCLUDING,
    BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
    FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  ALSO, THERE IS NO WARRANTY OF 
    NON-INFRINGEMENT, TITLE OR QUIET ENJOYMENT.  IN NO EVENT SHALL ADOBE 
    OR ITS SUPPLIERS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
    PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
    OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
    WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
    OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOURCE CODE, EVEN IF
    ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
package com.scuttlebutt.managers
{
    import com.adobe.air.notification.Purr;
    import com.scuttlebutt.model.Settings;
    import com.scuttlebutt.model.User;
    import com.scuttlebutt.utils.AvatarUtil;
    import com.scuttlebutt.utils.ResourceUtil;
    import com.scuttlebutt.view.StatusBar;
    import com.scuttlebutt.view.UpdaterWindow;
    import com.scuttlebutt.view.VoiceChatWindow;
    
    import flash.desktop.DockIcon;
    import flash.desktop.NativeApplication;
    import flash.desktop.NotificationType;
    import flash.desktop.Updater;
    import flash.display.Bitmap;
    import flash.display.NativeWindowSystemChrome;
    import flash.events.Event;
    import flash.events.EventDispatcher;
    import flash.events.IOErrorEvent;
    import flash.events.ProgressEvent;
    import flash.filesystem.File;
    import flash.filesystem.FileMode;
    import flash.filesystem.FileStream;
    import flash.net.*;
    import flash.utils.ByteArray;
    
    import mx.controls.Alert;
    import mx.events.FlexEvent;
    
    public class AppManager extends EventDispatcher
    {
        public static const SETTINGS_CHANGE : String = "settingsChange";
        
        private static var _instance : AppManager;
        
        private static var _sid : String = "ScB::";
        private var hasSID : Boolean = false;
        
        private var _settingsFileLocation : String;
        private var _settings : Settings;
        public  var _statusBar : StatusBar;
        
        private var _voiceChatWindow:VoiceChatWindow = null;
		private var _voiceChatPeer:User;
        
        private var _updaterWindow:UpdaterWindow = null;

        private var status : int  = 0;
        
        private var purr : Purr;
        
        private var versionXMLURL:String = "http://scuttlebutt.yorg.in/version.xml";
        
        private var urlString:String; 
        private var urlReq:URLRequest; 
        private var urlStream:URLStream; 
        private var fileData:ByteArray;
        
		private var updateInfo:String;
        private var updateOption:String;
        private var serverVersion:String;
        private var updateURL:String;
        private var size:Number;
		
		public var isUserProvoked:Boolean = true;
        
        private var version:String="";
        
        public function AppManager() 
        {
            _settings = new Settings();
            _settings.user.sid = getSID();
            
            //This sound is irritating, if you need this, remove comments
            //var sound : Sound = new Sound();
            //sound.load(new URLRequest("assets/chop.mp3"));
            
            purr = new Purr(120);
            //purr.notificationSound = sound;
            
            var appXML:XML = NativeApplication.nativeApplication.applicationDescriptor;
            var ns:Namespace = appXML.namespace();
            version = appXML.ns::version;
        }
        
        public static function getInstance() : AppManager 
        {
            if(_instance == null) 
            {
                _instance = new AppManager();
            }
            return _instance;
        }
        
        public function showNotification( title : String, msg : String, sid: String = null ) : void
        {
            if(!settings._notification)
                return;
             
            trace("[Notification]");
            var avatar : String;
            var peer : User = UsersManager.getInstance().getUserBySID(sid)
            
            if(!peer)
                avatar = ResourceUtil.avatar;
            else
                avatar = peer.avatar;
            
            var bmp : Bitmap = new Bitmap(null, "auto", true);
            bmp.bitmapData = AvatarUtil.convertStringtoAvatar(avatar);
             
            if( NativeApplication.supportsDockIcon )
            {
                //Works cool on Mac OSX
                var dock : DockIcon = NativeApplication.nativeApplication.icon as DockIcon;
                dock.bounce(NotificationType.CRITICAL);
            }
            
            //Let Notificaiton System decide where to display it according to O.S.
            purr.addTextNotificationByParams(title, msg, null, 4, bmp);
        }
        
        public function toggleUserPresence( isIdle : Boolean ) : void
        {
            if(_settings.user.status == 0 || _settings.user.status == 3 )
            {
                //Idle only when user is available
                if(isIdle)
                {
                    status = _settings.user.status;
                    _settings.user.status = 3;
                }
                else
                {
                    _settings.user.status = status;
                }
                refreshUserList();
            }
        }
         
        public function update() : void
        {
        }
        
        public function playError( errStr : String ) : void
        {
            trace("[ERROR] " + errStr);
        }
        
        public function set settings( val : Settings ) : void
        {
            _settings = val;
            
            //Adding new settings wipes out the SID
            if(hasSID)
                _settings._user.sid = getSID();
            
            //Update status value
            status = _settings.user.status;

            dispatchEvent( new Event( AppManager.SETTINGS_CHANGE ) );
        }
        
        public function get settings() : Settings
        {
            return _settings;
        }
        
        public function get settingFileLocation() : String
        {
            return _settingsFileLocation;
        }
        
        public function set settingFileLocation( val : String ) : void
        {
            _settingsFileLocation = val;
        }

        public function refreshUserList() : void
        {
            //[ROBUSTNESS] Session Initiation Protocol
            //Checks SID: ScuttleButt (Instance) Identifier
            if(hasSID)
            {
                trace("\n[Refresh Command]");
                _settings._user.respond = true;
                NetworkManager.getInstance().checkInterfaces();
                NetworkManager.getInstance().broadcast();
            }
            else
                _settings._user.sid = getSID();
        }
        /** Create SID: ScuttleButt Instance Idenifier **/
        public function getSID() : String
        {
            /*Set One time only*/
            if(_sid == "ScB::")
            {
                var networkInterfaces:Vector.<NetworkInterface> = NetworkInfo.networkInfo.findInterfaces();
                
                for(var i:int = 0; i < networkInterfaces.length; i++)
                {   
                    if((networkInterfaces[i].hardwareAddress != "") && networkInterfaces[i].active )
                    {
                        _sid += networkInterfaces[i].hardwareAddress;               
                    }
                }
                if(_sid == "ScB::")
                    Alert.show("Unable to initialise SID (ScuttleButt Identifier), may not be connected to a network.\n" +
                        "Check network connection and hit the refresh button.", "Network Manager");
                else
                    hasSID = true;

                trace("[SID] " + _sid);
            }
            return _sid;
        }
        
		private function onVoiceChatWindowComplete(e:FlexEvent):void
		{
			this._voiceChatWindow.visible = true;
			this._voiceChatWindow.setVisibility(true);
			if(_voiceChatPeer)
				this._voiceChatWindow.peer = this._voiceChatPeer;
			
			_voiceChatWindow.removeEventListener(FlexEvent.CREATION_COMPLETE, onVoiceChatWindowComplete);
		}
		
		private function createVoiceChatWindow():void
		{
			_voiceChatWindow = new VoiceChatWindow;
			_voiceChatWindow.systemChrome = NativeWindowSystemChrome.NONE;
			_voiceChatWindow.transparent = true;
			_voiceChatWindow.resizable = true;
			_voiceChatWindow.open(true);
			_voiceChatWindow.addEventListener(FlexEvent.CREATION_COMPLETE, onVoiceChatWindowComplete);	
		}
		
        public function showVoiceChatWindow(val:User=null) : void
        {
			this._voiceChatPeer = val;
			trace("[SHOW VOICE CHAT WINDOW]");
			if(!_voiceChatWindow)
			{
				trace("[CREATE VOICE CHAT WINDOW]");
				createVoiceChatWindow();
				return;
			}
			else
			{
				if(_voiceChatWindow.closed)
				{
					trace("[RECREATE VOICE CHAT WINDOW] Chat window was closed");
					createVoiceChatWindow();
					return;
				}
	            this._voiceChatWindow.setVisibility(true);
	            if(val)
	                this._voiceChatWindow.peer = this._voiceChatPeer;
        	}
		}
        
        // Pre-read the server-side XML file to look for <force>yes</force>
        public function preCheckForUpdate(event:Event = null):void{
            
            var loader:URLLoader = new URLLoader();
            loader.addEventListener(Event.COMPLETE, checkForUpdate);
            loader.addEventListener(IOErrorEvent.IO_ERROR, onIOError); // Just in case we can't read the update.xml						
            
            loader.load(new URLRequest(versionXMLURL));
        }
        
        private function onIOError(event:IOErrorEvent):void 
		{
			if(isUserProvoked)
			{
				isUserProvoked = true;
            	Alert.show(event.toString(), "Error checking for updates!");
        	}
		}
		
		
		private function onUpdaterWindowComplete(e:FlexEvent):void
		{
			_updaterWindow.newUpdate(updateInfo, serverVersion);
		}
		
		private function createUpdaterWindow():void
		{
			_updaterWindow = new UpdaterWindow;
			_updaterWindow.systemChrome = NativeWindowSystemChrome.NONE;
			_updaterWindow.transparent = true;
			_updaterWindow.resizable = true;
			_updaterWindow.open(true);
			_updaterWindow.addEventListener(FlexEvent.CREATION_COMPLETE, onUpdaterWindowComplete);
			_updaterWindow.visible = true;
		}
		
		private function showUpdater():void
		{
			if(!_updaterWindow)
			{
				createUpdaterWindow();
			}
			else
			{
				if(this._updaterWindow.closed)
				{
					createUpdaterWindow();
				}
				_updaterWindow.visible = true;
			}

		}
		
        private function checkForUpdate(event:Event):void 
        {
            var versionXML:XML = new XML(event.target.data);
            namespace items = "http://ns.adobe.com/air/framework/update/description/1.0";
            use namespace items;
            
            updateOption = versionXML.option;
            serverVersion = versionXML.version;
            updateURL = versionXML.url;
            size = versionXML.size; //in bytes
			updateInfo = versionXML.description;
            
            trace("[SERVER VERSION] " + serverVersion );
            trace("[UPDATE OPTION] " + updateOption);
            trace("[UPDATE URL] " + updateURL);
            trace("[UPDATE SIZE] " + size);
            
            if( Number(serverVersion) > Number(version) )
            {
				showUpdater();
            }
            else
            {
                if(updateOption == "force")
                {
					showUpdater();
                }
                else
                {
					if(isUserProvoked)
					{
						trace("[NO UPDATES FOUND]");
						isUserProvoked = true;
                    	Alert.show("No Updates found.", "Server Message");
					}
                }
            }
        }

        public function startUpdate():void
        {
            if(_updaterWindow.userChoice)
            {
                urlReq = new URLRequest(updateURL); 
                urlStream = new URLStream(); 
                fileData = new ByteArray(); 
                urlStream.addEventListener(Event.COMPLETE, onDownloadComplete);
                urlStream.addEventListener(IOErrorEvent.IO_ERROR, onIOError);
                urlStream.addEventListener(ProgressEvent.PROGRESS, onProgress);
                urlStream.load(urlReq); 
            }
            
            _updaterWindow.userChoice = false;
        }
        
        private function onProgress(e:ProgressEvent):void
        {
            _updaterWindow.progressValue(e.bytesLoaded * 100 / size);
        }
        
        public function cancelUpdate():void
        {
            trace("[Update CANCELLED]");
			
			if(urlStream)
			{
	            urlStream.removeEventListener(Event.COMPLETE, onDownloadComplete);
	            urlStream.removeEventListener(ProgressEvent.PROGRESS, onProgress);
	            //urlStream.close();
			}
        }
        
        private function onDownloadComplete(event:Event):void 
        {  
            urlStream.readBytes(fileData, 0, urlStream.bytesAvailable); 
            writeAirFile(); 
        } 
        
        private function writeAirFile():void 
        { 
            var file:File = File.desktopDirectory.resolvePath("ScuttleButt.air"); 
            var fileStream:FileStream = new FileStream(); 
            fileStream.open(file, FileMode.WRITE); 
            fileStream.writeBytes(fileData, 0, fileData.length); 
            fileStream.close(); 
            trace("[Update INFO] The AIR file is written."); 
            updateFromAIRFile();
        }
        
        private function updateFromAIRFile():void
        {
            var updater:Updater = new Updater(); 
            var airFile:File = File.desktopDirectory.resolvePath("ScuttleButt.air"); 
            try{
                updater.update(airFile, serverVersion);
            }
            catch(e:Error)
            {
                Alert.show(e.toString());
            }
        }
        
    }
}