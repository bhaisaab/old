/*
 * To get the FLA file of the Custom Loader, 
 * browse http://whatifi.undo.it or mail me at: rohityadav89@gmail.com
 */
package
{
    import flash.display.Sprite;
    import flash.events.Event;
    import flash.events.ProgressEvent;
    import flash.filters.DropShadowFilter;
    
    import mx.events.FlexEvent;
    import mx.preloaders.DownloadProgressBar;
    
    public class CustomLoader extends DownloadProgressBar
    {
        private var cp : CustomPreloader;
        
        public function CustomLoader()
        {
            cp = new CustomPreloader();
            cp.filters = [new DropShadowFilter(4, 45, 0, 0.5)];
            addEventListener(Event.ADDED_TO_STAGE, onAdded);
            addChild(cp);
        }
        
        public override function set preloader(preloader:Sprite):void
        {
            preloader.addEventListener(ProgressEvent.PROGRESS, onProgress);
            preloader.addEventListener(FlexEvent.INIT_COMPLETE, initComplete);
        }
        
        private function onProgress(e:ProgressEvent):void
        {
            cp.percent.text = Math.ceil(e.bytesLoaded/e.bytesTotal*100).toString() + "%";
            cp.gotoAndStop(Math.ceil(e.bytesLoaded/e.bytesTotal*100));
        }
        
        private function initComplete(e:Event):void
        {
            dispatchEvent(new Event(Event.COMPLETE));
        }
        
        private function onAdded(e:Event):void
        {
            cp.stop();

            cp.x = 180 - cp.width/2;
            cp.y = 200 - cp.height/2;
        }
        
    }
}