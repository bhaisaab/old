package com.scuttlebutt.managers
{
    import flash.events.EventDispatcher;
    import flash.net.Socket;
    
    //File Transfer Manager
    public class FileManager extends EventDispatcher
    {
        private static var _instance : FileManager;
        
        private var commandSocket : Socket; 
        private var commandPort : int = 7877;
        
        public function FileManager()
        {
            commandSocket = new Socket();
            commandSocket.bind(commandPort);
            commandSocket.timeout = 120;
            socket.addEventListener(Event.CONNECT, connectHandler); 
            socket.addEventListener(Event.CLOSE, closeHandler); 
            socket.addEventListener(ErrorEvent.ERROR, errorHandler); 
            socket.addEventListener(IOErrorEvent.IO_ERROR, ioErrorHandler); 
            socket.addEventListener(ProgressEvent.SOCKET_DATA, dataHandler);
        }
        
        public static function getInstance() : FileManager
        {
            if(_instance == null) 
            {
                _instance = new FileManager();
            }
            return _instance;
        }
    }
}