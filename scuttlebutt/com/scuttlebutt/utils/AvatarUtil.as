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

    Algorithm for Bitmap to String: [Rohit Yadav]
     -> Extract BitmapData and extract pixels data (RGB) as ByteArray (of uints)
     -> Use ZLib to compress the data
     -> Convert it to a BASE64 string to be sent as XML data to peers

    For String to Bitmap, reverse the algorithm
*/

package com.scuttlebutt.utils
{
    import flash.display.BitmapData;
    import flash.geom.Matrix;
    import flash.geom.Rectangle;
    import flash.utils.ByteArray;
    
    import mx.utils.Base64Decoder;
    import mx.utils.Base64Encoder;

    public class AvatarUtil
    {
        public static function encodeBitmapData( bmp : BitmapData ) : ByteArray
        {
            return bmp.getPixels(bmp.rect);
        }
        
        public static function decodeBitmapData( data : ByteArray ) : BitmapData
        {
            var bmp : BitmapData = new BitmapData(48, 48, true);
            bmp.setPixels(new Rectangle(0,0,48,48), data);
            return bmp;
        }
        
        public static function convertAvatartoString( avatar : BitmapData ) : String
        {
            if(!avatar)
                return null;
            
            var avatarBA : ByteArray = new ByteArray;
            avatarBA.clear();
            
            //Extract ByteArray of RGB uints from BitmapData
            avatarBA = AvatarUtil.encodeBitmapData(avatar);
            
            //ZLib Compression
            avatarBA.compress();
            
            //Encode image as Base64 string to be sent along with the XML info data
            var encoder : Base64Encoder = new Base64Encoder;
            encoder.encodeBytes(avatarBA , 0 , avatarBA.length);

            return encoder.toString();
        }
        
        public static function convertStringtoAvatar( string : String ) : BitmapData
        {
            if(!string)
                return null;
            
            //Decode Base64 string
            var decoder : Base64Decoder = new Base64Decoder;
            decoder.decode(string);

            //Decode and decompress the image BitmapData
            var avatarBA : ByteArray = decoder.toByteArray();
            avatarBA.uncompress();
 
            return AvatarUtil.decodeBitmapData(avatarBA);
        }
        
        //Generates a size x size avatar
        //Not for large images (ie. large size > say 300-400 KB)
        public static function generateAvatar( data : BitmapData, size : Number ) : BitmapData
        {   
            var scale : Number = 1.0;
            
            if( data.width > size || data.height > size )
            {
                scale = Math.min( size / data.width, size / data.height );
            }
            
            //Scale the image, scale matrix
            var matrix : Matrix = new Matrix();
            matrix.scale( scale, scale );
            
            //Add cropping algo here in future, if app becomes popular :-)
            
            var avatar : BitmapData = new BitmapData( size, size, true );
            avatar.draw( data, matrix, null, null, null, true );
            
            return avatar;
        }

    }
}