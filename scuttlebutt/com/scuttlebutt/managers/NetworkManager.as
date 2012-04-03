/*
    This class contains a totally new kind of logic/code
    (As UDP APIs were introduced at the time of development around Dec 2009),
    so if you use it in your project, I would love to know!
    And you cannot use my name or reference in your code 
    without permission.
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
    import com.scuttlebutt.model.ChatMessage;
    import com.scuttlebutt.model.User;
    import com.scuttlebutt.utils.XMLParserUtil;
    
    import flash.events.DatagramSocketDataEvent;
    import flash.events.EventDispatcher;
    import flash.net.*;
    import flash.utils.ByteArray;
    
    import mx.controls.Alert;
    
    public class NetworkManager extends EventDispatcher
    {
        private static var _instance : NetworkManager;
        
        //Broadcast to this address array
        public var broadcastAddressArray : Array;
        
        //TODO: Add Port changing option in Settings (Title Window)
        
        //Sockets for UDP transactions
        private var broadcastSocket : DatagramSocket;
        private var chatSocket : DatagramSocket;
        private var voiceChatSocket : DatagramSocket;
        
        //Socket Ports: Change port just in case
        private static var broadcastPort : int = 7875;
        private static var chatPort : int = 7876;
        private static var voiceChatPort : int = 7878;
        
        //Socket Binding state booleans
        private var broadcastSocketBinded : Boolean = false;
        private var chatSocketBinded : Boolean = false;
        
        //Your IPv4 address
        private var myAddress : String;
        
        //Voice Call state
        private var voiceCallState:String = "WAITING";
        private var isVoiceCallInUse:Boolean = false;
        private var sidOnCall:String = "";
        
        public static function getInstance() : NetworkManager
        {
            if(_instance == null) 
            {
                _instance = new NetworkManager();
            }
            return _instance;
        }
        
        public function NetworkManager() 
        {
            //debugNetwork();
            
            //Broadcast socket is only used for peer discovery and management
            broadcastSocket = new DatagramSocket();
            
            //Intialise broadcast address list
            broadcastAddressArray = new Array;
            
            //Binds and checks UDP broadcast socket
            checkInterfaces();
            
            //UDP socket's used as data loss within the local network is tending to zero.
            //Chat socket for sending/receiving p2p chats
            chatSocket = new DatagramSocket();
            bindChatSocket();
            
            voiceChatSocket = new DatagramSocket();
            
            try
            {
                voiceChatSocket.bind(voiceChatPort);
                voiceChatSocket.addEventListener( DatagramSocketDataEvent.DATA, onVoiceCallReceive);
                voiceChatSocket.receive();
            }
            catch(error:Error)
            {
                Alert.show("Error Binding Voice Chat Socket to port, port in use or not free. Restart application","Network Manager");
            }
        }
        
        //-- UDP Discovery routines start here --
        private function bindBroadcastSocket() : void
        {
            if(!broadcastSocketBinded)
            {
                try
                {
                    broadcastSocket.bind(broadcastPort);
                    broadcastSocket.addEventListener( DatagramSocketDataEvent.DATA, onUserInfoDatagramReceive );
                    broadcastSocket.receive();
                }
                catch(error:Error)
                {
                    broadcastSocketBinded = false;
                    Alert.show("Error Binding Socket to port, port in use or not free. Restart application","Network Manager");
                    return;
                }
                broadcastSocketBinded = true;
            }
        }
        
        public function checkInterfaces() : void
        {
            var networkInterfaces:Vector.<NetworkInterface> = NetworkInfo.networkInfo.findInterfaces();
            var address : String;
            
            //Check if Socket is UDP broadcast binded
            bindBroadcastSocket();
            
            //Start Fresh: Updates IP in case user or DHCP changes IP 
            //while(broadcastAddressArray.length)
            //    broadcastAddressArray.pop();
            
            for(var i : int = 0; i < networkInterfaces.length; i++)
            {
                //Is this interface connected to LAN?
                if(networkInterfaces[i].active)
                {
                    //Check all addresses in the vector
                    var interfaceAddressLength : int = networkInterfaces[i].addresses.length;
                    
                    for(var j : int = 0; j < interfaceAddressLength; j++)
                    {
                        if(networkInterfaces[i].addresses[j].broadcast != "")
                        {
                            address = networkInterfaces[i].addresses[j].address;
                            //Update IP
                            AppManager.getInstance().settings._user.ip = address;
                            
                            var redundancy : Boolean = false;
                            var r : int;
                            
                            //[ROBUSTNESS] Redundancy Check!
                            //User's own IP address not localhost
                            if(address != "127.0.0.1")
                            {   
                                for( r = 0; r < broadcastAddressArray.length; r++)
                                {
                                    if(broadcastAddressArray[r] == address)
                                    {    
                                        redundancy = true; break;    
                                    }
                                }
                                
                                if(!redundancy)
                                    broadcastAddressArray.push(address);
                                
                                myAddress = address;
                                    
                            }
                            
                            redundancy = false;
                            address = networkInterfaces[i].addresses[j].broadcast;
                       
                            //Broadcast address string
                            for( r = 0; r < broadcastAddressArray.length; r++)
                            {
                                if(broadcastAddressArray[r] == address)
                                {    
                                    redundancy = true; break;    
                                }
                            }
                            
                            if(!redundancy)
                                broadcastAddressArray.push(address);   
                            }
                        }
                    }
                }
            
            //If no active interface found, fallback to loopback
            if(!broadcastAddressArray.length)
            {
                Alert.show("No network connection detected, may not be connected to a network.", "Network Manager");
                AppManager.getInstance().playError("No network found, using loopback!");
                broadcastAddressArray.push("127.0.0.1");
            }
            
        }
        
		public function closeNetworkSockets():void
		{
			broadcastSocket.close();
			chatSocket.close();
			voiceChatSocket.close();
		}
		
        //[Rohit Yadav] My BulletProof Broadcast Routine :-)
        public function broadcast() : void 
        {   
            var udpString : String = XMLParserUtil.buildInfoDataGramXML().toXMLString();

            var byteArray : ByteArray = new ByteArray;         
            byteArray.writeUTFBytes( udpString );
            
            //Try to broadcast over user defined IPs and User List peers
            try
            {
                var j : int;
                var userDefinedIPArray : Array = AppManager.getInstance().settings._ipList;
                
                for(j = 0; j < UsersManager.getInstance().userList.length ; j++)
                {
                    if(UsersManager.getInstance().userList.getItemAt(j).ip == myAddress)
                        continue;
                    
                    trace("[List Peer Discovery] Attempting ["+j +"] at: " + UsersManager.getInstance().userList.getItemAt(j).ip);
                    broadcastSocket.send( byteArray, 0, udpString.length, UsersManager.getInstance().userList.getItemAt(j).ip, broadcastPort );        
                }
                
                for(j = 0; j < userDefinedIPArray.length; j++)
                {
                    if(userDefinedIPArray[j] == myAddress)
                        continue;
                    
                    trace("[ScB IP Table Peer Discovery] Attempting at: " + userDefinedIPArray[j]);
                    broadcastSocket.send( byteArray, 0, udpString.length, userDefinedIPArray[j], broadcastPort );
                }
            }
            catch (error : Error)
            {
                AppManager.getInstance().playError("Some Invalid ScB/UserList IPs"); //User Defined IPs or User List IPs
                //Alert.show("User defined IP Broadcast error: " + error.message + "\n Please remove parameters from ScuttleButt IP Table.", "Network Manager");
            }
               
            //Try to broadcast over all active interfaces...
            try
            {
                for(var i : int = 0; i < broadcastAddressArray.length; i++)
                {
                    //Alert.show("[Broadcast] Attempting at: " + broadcastAddressArray[i]);
                    trace("[Broadcast] Attempting at: " + broadcastAddressArray[i]);
                    broadcastSocket.send( byteArray, 0, udpString.length, broadcastAddressArray[i], broadcastPort );
                }
            }
            catch (error : Error)
            {
                //Error may arise when not connected to a router based network as 
                //Broadcasting address corresponds to the router or network is between only 2+ computers or
                //Network wire is unplugged!
                //In either case, tell user: unable to broadcasting thru network router
                
                AppManager.getInstance().playError("No working broadcasting interface found!");
            }
            
            //Reintialize list to remove any dead user which have have not sent a self-destruct packet 
            UsersManager.getInstance().userList.removeAll();
        }
        
        private function sendUserInfoDataGram( senderIP : String, respond : Boolean = false ) : void
        {
            if(respond)
            {
                AppManager.getInstance().settings._user.respond = true;
            }
            
            var udpString : String = XMLParserUtil.buildInfoDataGramXML().toXMLString();
            
            var byteArray : ByteArray = new ByteArray;         
            byteArray.writeUTFBytes( udpString );

            try
            {
                broadcastSocket.send( byteArray, 0, udpString.length, senderIP, broadcastPort );
            }
            catch( err: Error )
            {
                trace("[ACK] Error sending ack packet");
            }
        }

        private function onUserInfoDatagramReceive( event : DatagramSocketDataEvent ) : void
        {      
            var user : User = XMLParserUtil.parseInfoDatagramXML(new XML(event.data.toString()));

            //Update user's IP address
            user.ip = event.srcAddress;
            trace("[UDP] SID:  " + user.sid + " IP: "+user.ip);
            
            //[ROBUSTNESS] If user packet is asking for an update, send an update!
            if(user.respond)
                sendUserInfoDataGram(user.ip, false);

            //Tell UserManager to do stuff
            UsersManager.getInstance().addNewUser(user);
        }

        public function debugNetwork() : void
        {
            var networkInterfaces:Vector.<NetworkInterface> = NetworkInfo.networkInfo.findInterfaces();
            
            trace("[Total Inteface Addresses] " + networkInterfaces.length);
            for(var i:int = 0; i < networkInterfaces.length; i++)
            {
                //if(networkInterfaces[i].active) 
                {
                    trace("[Address length for " + i + " interface: "+networkInterfaces[i].addresses.length);
                    for(var j:int=0; j<networkInterfaces[i].addresses.length; j++)
                    {
                        trace("[Address=] "+networkInterfaces[i].addresses[j].address);
                        trace("[BrdCast=] "+networkInterfaces[i].addresses[j].broadcast);
                    }
                    trace("[NETWORK] Name: "+networkInterfaces[i].name);
                    trace("[NETWORK] IsActive: "+networkInterfaces[i].active);
                    trace("[NETWORK] DisplayName: "+networkInterfaces[i].displayName);
                    trace("[NETWORK] MAC: "+networkInterfaces[i].hardwareAddress);
                    trace("[NETWORK] MTU: "+networkInterfaces[i].mtu);
                    trace(" ");
                }
            }
        }
        //-- UDP Discovery Routines ends here! --
        
        //-- UDP Chat related routines start here --
        private function bindChatSocket() : void
        {
            if(!chatSocketBinded)
            {
                try
                {
                    chatSocket.bind(chatPort);
                    chatSocket.addEventListener( DatagramSocketDataEvent.DATA, chatDatagramReceive );
                    chatSocket.receive();
                }
                catch(error:Error)
                {
                    chatSocketBinded = false;
                    Alert.show("Error Binding ChatSocket, port in use or not free. Close any application using port 7876 and restart application","Network Manager");
                    return;
                }
                chatSocketBinded = true;
            }
        }
        
        public function chatDatagramSend( targetIP : String, message : String ) : void
        {
            //[Robustness] Bind check!
            bindChatSocket();
            
            var byteArray : ByteArray = new ByteArray;         
            byteArray.writeUTFBytes( message );
            
            try
            {
                broadcastSocket.send( byteArray, 0, message.length, targetIP, chatPort );
            }
            catch( err: Error )
            {
                trace("[ChatSocket] Error sending chatDatagram");
            }
        }
        
        private function chatDatagramReceive( event : DatagramSocketDataEvent ) : void
        {
            
            var cMsg : ChatMessage = XMLParserUtil.parseChatDatagramXML( new XML(event.data.toString()) );
            cMsg.ip = event.srcAddress;

            var peer : User;
            peer = UsersManager.getInstance().getUserBySID(cMsg.sid);
            
            //If user not in list, tell 'em to send an info packet
            if(!peer)
            {
                sendUserInfoDataGram(event.srcAddress, true);
                peer = new User;
                peer.sid = cMsg.sid;
                peer.name = cMsg.name;
            }
            
            trace("[Chat Peer] SID: " + peer.sid);
            
            //Forward to Window manager to send to appropriate window!
            WindowManager.getInstance().postReceivedChatMessage(peer, cMsg);
        }
        
        public function makeVoiceCall(destination:User):Boolean
        {
            if(isVoiceCallInUse)
                return false;
            
            sidOnCall = destination.sid;
            
            var message:String  = XMLParserUtil.buildChatDatagramXML("ACCEPT");
            var byteArray : ByteArray = new ByteArray;         
            byteArray.writeUTFBytes(message);
            
            try
            {
                voiceChatSocket.send(byteArray, 0, message.length, destination.ip, voiceChatPort);
            }
            catch(e:Error)
            {
                trace("[MAKE CALL ERROR]");
            }   
            voiceCallState = "HANDSHAKE";
            return true;
        }
        
        private function onVoiceCallReceive( event : DatagramSocketDataEvent ) : void
        {   
            var cMsg : ChatMessage = XMLParserUtil.parseChatDatagramXML( new XML(event.data.toString()) );
            cMsg.ip = event.srcAddress;
            
            var peer : User;
            peer = UsersManager.getInstance().getUserBySID(cMsg.sid);
            
            //If user not in list, tell 'em to send an info packet
            if(!peer)
            {
                sendUserInfoDataGram(event.srcAddress, true);
                peer = new User;
                peer.sid = cMsg.sid;
                peer.name = cMsg.name;
            }
            
            trace("[Voice Chat Peer] SID: " + peer.sid);
            
            if(voiceCallState == "WAITING")
            {
                if(cMsg.message == "ACCEPT")
                {
                    //call func here, ok by default
                    var message:String = XMLParserUtil.buildChatDatagramXML("OK");
                    var byteArray : ByteArray = new ByteArray;         
                    byteArray.writeUTFBytes(message);
                    try
                    {
                        voiceChatSocket.send(byteArray, 0, message.length, event.srcAddress, event.srcPort );
                    }
                    catch(e:Error)
                    {
                        trace("[VChat Protocol ERROR]");
                    }
                    voiceCallState = "ONAIR";
                    this.isVoiceCallInUse = true; 
                }
            }  
            
            if(voiceCallState == "HANDSHAKE")    
            {
                if(!this.isVoiceCallInUse)
                {
                    if(cMsg.message == "OK")
                    {                       
                        this.isVoiceCallInUse = true; 
                        voiceCallState = "ONAIR";
                    }
                }
            } 
            
            if(voiceCallState == "ONAIR")
                //Forward to Window manager to send to appropriate window!
                WindowManager.getInstance().postReceivedChatMessage(peer, cMsg);   
           
        }
    }
}