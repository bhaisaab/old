package com.scuttlebutt.services
{
    import flash.display.Bitmap;
    import flash.display.BitmapData;
    import flash.display.Loader;
    import flash.events.ErrorEvent;
    import flash.events.Event;
    import flash.events.EventDispatcher;
    import flash.events.IOErrorEvent;
    import flash.filesystem.File;
    import flash.net.URLRequest;
    
    [Event(name="load", type="flash.events.Event")]
    [Event(name="invalid", type="flash.events.Event")]
    [Event(name="complete", type="flash.events.Event")]
    public class AvatarLoader  extends EventDispatcher
    {
        private var _loader : Loader;
        private var _file : File;
        
        private var _filter : RegExp = /^\S+\.(jpg|jpeg|png)$/i;
        
        public static const INVALID : String = "invalid";
        public static const COMPLETE : String = "complete";
        
        public function AvatarLoader()
        {
            _loader = new Loader();
            _loader.contentLoaderInfo.addEventListener( Event.COMPLETE,
                onLoadComplete );
            _loader.contentLoaderInfo.addEventListener( IOErrorEvent.IO_ERROR,
                onLoadError );
        }
        
        private function validateFile( file : File ) : Boolean
        {
            return _filter.exec( file.name ) != null;
        }
        
        private function onLoadError( evt : IOErrorEvent ) : void
        {
            dispatchEvent( new ErrorEvent(ErrorEvent.ERROR,
                false, false, evt.text) );
        }
        
        private function onLoadComplete( evt : Event ) : void
        {
            var data : BitmapData = ( _loader.content as Bitmap ).bitmapData;
        }
        
        private function loadFile( file:File ):void
        {
            _file = file;
            if( validateFile( _file ) )
            {
                _loader.load( new URLRequest( _file.url ) );
            }
        }
        
    }
}