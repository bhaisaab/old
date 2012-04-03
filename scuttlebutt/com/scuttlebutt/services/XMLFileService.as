/*
    Modified XMLParserUtil from:
    Music Player chapter in the book Adobe AIR Create-Modify-Reuse(ISBN: 978-0-470-18207-9)
    by: Marc Leuchner, Todd Anderson, Matt Wright.
*/

package com.scuttlebutt.services
{
    import com.scuttlebutt.events.XMLFileServiceEvent;
    
    import flash.events.Event;
    import flash.events.EventDispatcher;
    import flash.events.IOErrorEvent;
    import flash.filesystem.File;
    import flash.filesystem.FileMode;
    import flash.filesystem.FileStream;
    
    import mx.controls.Alert;
    
    public class XMLFileService extends EventDispatcher
    {
        private var _file : File;
        private var _fileStream : FileStream;
        private var _fileName : String;
        
        public function XMLFileService() : void
        {
        }
        
        public function loadXMLFileFromStorage( fileName : String ) : void
        {
            _file = File.applicationStorageDirectory.resolvePath( fileName );
            
            if( !_file.exists )
            {
                dispatchEvent( new XMLFileServiceEvent( XMLFileServiceEvent.XML_FILE_NOT_FOUND ) );
                return;
            }
            
            _fileStream = new FileStream();
            _fileStream.addEventListener( Event.COMPLETE, onXMLFileLoadComplete );
            _fileStream.addEventListener( IOErrorEvent.IO_ERROR, errorHandler );
            _fileStream.openAsync( _file, FileMode.READ );
        }
        
        public function saveXMLFileToStorage( fileName:String , data:XML ) : void
        {
            var xml_encoding : String = "<?xml version='1.0' encoding='utf-8'?>\n"; 
            var xml_toWrite : String = xml_encoding + data.toXMLString();
            
            _file = File.applicationStorageDirectory.resolvePath( fileName );
            
            _fileStream = new FileStream();
            _fileStream.addEventListener( Event.CLOSE, onXMLFileWriteComplete );
            _fileStream.openAsync( _file, FileMode.WRITE );
            _fileStream.writeUTFBytes( xml_toWrite );
            _fileStream.close();
        }
        
        public function copyXMLFileFromApplicationDirectoryToStorage( fileName : String ) : void
        {
            var sourceFile : File = File.applicationDirectory.resolvePath( fileName );
            
            if( !sourceFile.exists )
            {
                dispatchEvent( new XMLFileServiceEvent( XMLFileServiceEvent.XML_FILE_NOT_FOUND ) );
                return;
            }
            
            var resultsFile : File = File.applicationStorageDirectory.resolvePath( fileName );
            
            sourceFile.addEventListener( IOErrorEvent.IO_ERROR , errorHandler );
            sourceFile.addEventListener( Event.COMPLETE , onXMLFileCopyComplete );
            sourceFile.copyToAsync( resultsFile , true );
        }
        
        private function onXMLFileCopyComplete( event : Event ) : void
        {
            dispatchEvent( new XMLFileServiceEvent(XMLFileServiceEvent.XML_FILE_COPIED) );
        }
        
        private function onXMLFileLoadComplete( event : Event ) : void
        {
            var xml : XML = XML( _fileStream.readUTFBytes( _fileStream.bytesAvailable ) );
            _fileStream.removeEventListener( Event.COMPLETE, onXMLFileLoadComplete );
            _fileStream.removeEventListener( IOErrorEvent.IO_ERROR, errorHandler );
            _fileStream.close();
            
            var xmlEvent : XMLFileServiceEvent = new XMLFileServiceEvent( XMLFileServiceEvent.XML_LOADED );
            xmlEvent.xml = xml;
            dispatchEvent( xmlEvent ); 
        }
        
        private function onXMLFileWriteComplete( event : Event ) : void
        {
            dispatchEvent( new XMLFileServiceEvent(XMLFileServiceEvent.XML_FILE_WRITTEN) );
        }
        
        private function errorHandler( event : IOErrorEvent ) : void
        {
            var errorMessage : String = "Error Loading File "+event.text+" FILE ERROR";
            trace( errorMessage );
            var xmlEvent : XMLFileServiceEvent = new XMLFileServiceEvent( XMLFileServiceEvent.XML_ERROR );
            xmlEvent.message = errorMessage;
            dispatchEvent( xmlEvent );
            
            Alert.show( errorMessage );
        }
        
        public function get file() : File
        {
            return _file;
        }
        
        public function set file( val : File ) : void
        {
            _file = val;
        }
    }
}