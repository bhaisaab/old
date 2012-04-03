package com.scuttlebutt.view
{
    import flash.display.Graphics;
    import flash.events.Event;
    import flash.media.SoundMixer;
    import flash.utils.ByteArray;
    
    import mx.core.UIComponent;
    
    public class AudioVisualizer extends UIComponent
    {
        private const PLOT_HEIGHT:int = 40;
        private const CHANNEL_LENGTH:int = 120;	
        
        private const GRAPH_WIDTH:int = 8;
        private const GRAPH_HEIGHT:int = 30;
        
        private var bar:UIComponent = new UIComponent();
        
        public function AudioVisualizer()
        {
            bar.x = 0;
            bar.y = 15;
            
            this.addChild( bar );
        }
        
        public function start():void
        {
            this.addEventListener(Event.ENTER_FRAME, onEnterFrame);
        }
        
        public function stop():void
        {
            bar.graphics.clear();
            graphics.clear();
            this.removeEventListener(Event.ENTER_FRAME, onEnterFrame);
        }		
        
        private function onEnterFrame(event:Event):void 
        {
            var bytes:ByteArray = new ByteArray();
            
            SoundMixer.computeSpectrum( bytes, false, 0 );
            
            var graphics:Graphics = this.graphics;
            
            graphics.clear();
            
            graphics.lineStyle(0, 0xE44972);
            graphics.beginFill(0xE44972);
            graphics.moveTo(0, PLOT_HEIGHT);
            
            var n:Number = 0;
            
            for (var i:int = 0; i < CHANNEL_LENGTH; i++) 
            {
                n = (bytes.readFloat() * PLOT_HEIGHT);
                graphics.lineTo(i * 2, PLOT_HEIGHT - n);
            }
            
            graphics.lineTo(CHANNEL_LENGTH * 2, PLOT_HEIGHT);
            graphics.endFill();
            
            graphics.lineStyle(0, 0xE44972);
            graphics.beginFill(0xE44972, 0.5);
            graphics.moveTo(CHANNEL_LENGTH * 2, PLOT_HEIGHT);
            
            for (i = CHANNEL_LENGTH; i > 0; i--) 
            {
                n = (bytes.readFloat() * PLOT_HEIGHT);
                graphics.lineTo(i * 2, PLOT_HEIGHT - n);
            }
            
            graphics.lineTo(0, PLOT_HEIGHT);
            graphics.endFill();
        }
        
        public function drawMicBar(rate:Number, color:uint):void 
        {
            var i:int;
            rate /= 50;
            
            bar.graphics.clear();
            
            bar.graphics.lineStyle(1, color);
            bar.graphics.beginFill(color, 0.6);
            bar.graphics.moveTo(0, GRAPH_HEIGHT);
            
            for (i = 0; i <= GRAPH_WIDTH; i++) 
            {
                bar.graphics.lineTo(i * 2, GRAPH_HEIGHT - ((rate * GRAPH_HEIGHT)) * 0.75);
            }
            
            bar.graphics.lineTo(GRAPH_WIDTH*2, GRAPH_HEIGHT);
            bar.graphics.endFill();
        }
    }
}