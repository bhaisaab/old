/*
    Modified Notification class from Adobe's Original AIR Notification Package
    Copyright Rohit Yadav, 2009-10
    
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
package com.scuttlebutt.utils
{           
    import flash.display.Bitmap;
    import flash.display.BitmapData;
    import flash.filters.DropShadowFilter;
    import flash.text.TextField;
    import flash.text.TextFieldAutoSize;
    import flash.text.TextFormat;
    import flash.text.TextFormatAlign;
    import flash.ui.ContextMenu;
    import flash.display.Screen;
    
    import com.adobe.air.notification.AbstractNotification;
    
	
    public class Notification
        extends AbstractNotification
    {        
        private var _message:String;        
        private var _title:String;
       	private var _bitmap: Bitmap;

        private var messageLabel:TextField;
       	private var titleLabel:TextField;
       	private var filters:Array;

        public function Notification(title:String, message:String, position:String = null, duration:uint = 4, bitmap: Bitmap = null)
        {
			if (bitmap != null)
			{
    	    	this.bitmap = bitmap;
   			}

			this.filters = [new DropShadowFilter(5, 45, 0x000000, .9)];

            super(position, duration);

        	this.title = title;
        	this.message = message;

            this.width = 320;
            this.height = 64;
            var mainScreen:Screen = Screen.mainScreen;
            
            this.x = mainScreen.bounds.width - this.width - 20;
            this.y = 30;
	    }

		private const Left_Pos: int = 45;

		override protected function createControls():void
		{
			super.createControls();
			var leftPos: int = (this.bitmap != null) ? 45 : 5;
			var cm:ContextMenu = new ContextMenu();
			cm.hideBuiltInItems();
			
			// title
            this.titleLabel = new TextField();
            this.titleLabel.autoSize = TextFieldAutoSize.LEFT;
            var titleFormat:TextFormat = this.titleLabel.defaultTextFormat;
            titleFormat.font = "Marker Felt Thin";
            titleFormat.bold = true;
            titleFormat.color = 0xFFFFFF;
            titleFormat.size = 14;
			titleFormat.align = TextFormatAlign.LEFT;
            this.titleLabel.defaultTextFormat = titleFormat;
            this.titleLabel.multiline = false;
            this.titleLabel.selectable = false;
            this.titleLabel.wordWrap = false;
            this.titleLabel.contextMenu = cm;
            this.titleLabel.x = leftPos;
            this.titleLabel.y = 5;
            this.titleLabel.filters = this.filters;
            this.getSprite().addChild(this.titleLabel);

			// message            
            this.messageLabel = new TextField();
           this.messageLabel.autoSize = TextFieldAutoSize.NONE;
            var messageFormat:TextFormat = this.messageLabel.defaultTextFormat;
            messageFormat.font = "Helvetica Neue Medium";
            messageFormat.color = 0xFFFFFF;
            messageFormat.size = 12;
			messageFormat.align = TextFormatAlign.LEFT;
            this.messageLabel.defaultTextFormat = messageFormat;
            this.messageLabel.multiline = true;
            this.messageLabel.selectable = false;
            this.messageLabel.wordWrap = true;
            this.messageLabel.contextMenu = cm;
            this.messageLabel.x = leftPos;
            this.messageLabel.y = 22;
            this.messageLabel.filters = this.filters;
            this.getSprite().addChild(this.messageLabel);

			if (this.bitmap != null)
			{
				var scaleX: Number = 1;
				var scaleY: Number = 1;
	            var bitmapData:BitmapData = this.bitmap.bitmapData;				
	            
                this.bitmap.smoothing = true;
                //32 x 32 pixel
	            this.bitmap.scaleX = 32/this.bitmap.width;
	            this.bitmap.scaleY = 32/this.bitmap.height;
	            this.bitmap.x = 5;
	            this.bitmap.y = 5;
	            this.bitmap.filters = this.filters;
	            this.getSprite().addChild(this.bitmap);
			}
		}

		public function set bitmap(bitmap:Bitmap):void
		{
			this._bitmap = new Bitmap(bitmap.bitmapData);
	    	this._bitmap.smoothing = true;
		}
		
		public function get bitmap():Bitmap
		{
			return this._bitmap;
		}

        public override function set title(title:String):void
        {
        	this._title = title;
        	this.titleLabel.text = title;
        }

        public override function get title():String
        {
            return this._title;
        }

        public function set message(message:String):void
        {
        	this._message = message;
           	this.messageLabel.text = message;
        }                                

		public function set htmlText(htmlText:String):void
		{
			this.messageLabel.htmlText = htmlText;			
		}		

		public function get htmlText():String
		{
			return this.messageLabel.htmlText; 
		}

        public function get message():String
        {
            return this._message;
        }

        public override function set width(width:Number):void
        {
			super.width = width;
			this.messageLabel.width = width - (this.messageLabel.x + 4);
			this.titleLabel.width = width - 8;
        }

        public override function set height(height:Number):void
        {
			super.height = height;
			this.messageLabel.height = height - (this.messageLabel.y + 4);
        }
                
    }
}