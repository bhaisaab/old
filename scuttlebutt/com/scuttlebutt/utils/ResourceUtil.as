package com.scuttlebutt.utils
{
    public class ResourceUtil
    {
        //The default logo/icon BitmapData as Base64 XML
        public static const avatar : String = 
"eNrFWglUVEcWVUdFlM0FlBiDG4IGEAFpFzZZhGZRR2VklFXcEQEBg8tRZzQYZ4gaHcFk3IcTjRk1M+hEjcp4UERlVNBIBAWhQVtwwxXc3tR7/9f3N2087Klz/unu/+u/uvXqLfdVNUAj2uvXr+HNmzfS7xdPn0HJ9UK4nJ0D509lQd65XKgouQVvWD/eXr16pfHOb9UQB295F3IhIWoBWFpagq6uLrRp00a69PX1wd7eHtauWAllxSUac/+tsT+urobEufMlrMOMTGFmX3tYZukCKwe7wWILZwj+xAY+6WxIz/X09GDD51/A27dvtXTQ2thLim7AqKH2hMvduB/sHTkFrnpHQ7lfPKh9E+CuXyLcYZ8q33i46DkXUu0DoF+XrtR/inIcPHr4sNXnwMe6VVwMFmb9CctyK3co9FkAD/w/I8wVyngoVy4EFbvws4Lhr/RbBPfZ81yPORDa147e83N1h+fPn7eaLfExal7UgNvwkYThSztfwoxXqU8clCnjCHfdq4w9w+f3/BdBiU8sxFk60/sLwiMl+WhT6NcvX76U7Euut6asE5eNbc2S5TT2oiHOZB+3mX4RW7mo7w9dt1g/XIuisQsgwNSC5Bz650GSW1tbqzHm+2IU6rDu3Bqi+7IbxdClSxewN/oIfh47n7AI2OPrhZ/PAW3thGs44XdwcIC3bwRMaE95eXla4549exYuX76soc/G4E9LWUdjbnEYx2zhM7KL+uLmF/eLO/4JENXfkeRdyDpD8idPnky/Q0JC4OnTp3Rv//79dK99+/awbdu2BuOX9/X09CRZOR6zoYrpHu29ofjxwjVDf94zIpDkbVizluR37dpVisUTJ06kexs3btTIJwcOHGhQ3OJ2+Kz6MZiZmYF3z4FQ5BNDtl/WCOzloj9XMV/Odp9FmCZMmCDpunPnzlpYIyIipHvW1tYS9vrkcW47d8vKwcjICELNbKHMdyH5raqx+JXox4mQz3zIUr8HODk5SRwjNTVVwhoTEyPhsLW1pXvdu3eHwsLCeq8Bx19+s4S4wPS+w0Dl13T8dwl/FFgb9gRHR0fJTqOjoyX8S5YsoXuZmZmSbZmamoJara533uB97t1WQ48ePWBy7yFQooxtmv2I+s9j+AfqdQMXFxcaIykpScPWCwoKID8/X8OmZs+eXW/bkfd7VVMLVlZWYGVgQuuO+muK/WMuO+M+kzAFBQVBbU0NGBgY0O+27EpOTqZxV69eLWHHeT558qRB+HFd+drOnx5Jcn5wmkbxo9SnafFn38g/kLyVSYKdpKSkgJ2dHRxkfsxbVVUVhIWGkt459obyDe4nJzIO03gRzAc4t1E1Iv7jhesXN1DgIT9lHJLGKrxWAOs+XwPx82Pg+/Q9v2rPDWl8rXAdvEa70JjfMt09DEgiXaoagB37P2LvHRfz74ABA+DJo2qSfz4nh2Kc3AdmhUU0C9/m7547k01yO7fvACddI+BBPeeAPov+gnPOGhMJNizuoJx9u9MFXsjs38VRQfc2OQTAMZcwGCdypN3fbG0Wrs3XbmfaFpL7sa4BZLpFEJ/5UC5Gf8V4hTZ/yCkY+oj1DNYyvO3dsYvuRQ1SUGx+MX4ZHHYOoXvhU4ObhWfLfTnty/Uku1tHXTjqHCrwoffMAdcFucZN7xhYZ6uU7OKb9ZveyWX8DXMA3s9ka4qxVe2XAOmKSXRv1dJlzVbryOPWFnEORh07QZZrpBYnQntBLJnO4aDsaU59TUxM4Kjor8j1sV3KPkfPsNYs9RV8u3BsNCh7Ce/k5+Y2a62Gc+DrsJXpEcfwZWPd8F4g1IyyHJvnMRc+ZTkD+WNsWCSUl5ZKtsDxL4tLIBk7HSdSXkBevlshcNGo0Olaa9+c9Ri2OVMEO/2HIlC0o3cx/qQYZzzsHKX+z589k2rHilIVGBoaEo/I85pH71xn9aiXyQCa8y/5V1usTub6uyiufzjjdioxL6D+b7O1KPaOhUmMc+DzxbOioPr+Aw0Z8ZECB90wTKhFcf57Rwh5bXZweKNrlob4Au5bWVhYgK1RL7gi4xac55wfMxM8TPpL8T6V+c2RHzJgoYjdzbgvFHjNp76lvnEwrY+NRl3D9dRS+LF5eXmBQQcdOO8p1jYitxB8eBHhW2nlrpGb8FJ0+xjOMN/HPRfshzmF5uTm1qK6r4vf19cXdH/XAc55aOLnuUtNMTERTrO1SBsWAOtsvOFbVn9d9YyiWMn9PdFC2Js4IHKHltK9Bq9g8VuhUIAFq0WQ01eS/cS9N//isyqKMYkUazBe4fPqgMXwL8YLEbudtQ3x0YbwzKbEoHt31GBsbEz5vlgZJ8XQurkMMaON0BzY511xTXDP7oDzVOipo0f4T/54tFX25rj808eO07i474l4VLJ9Bv6JnODfI/8Im2394DsWXzDG7Bj+e1hj5QlT+1hL/rB1U6pWjmlp/ScvFfa09o0MovhdNwejb/7iJdS6df0XLx0dHXAdNRpO/OdIi/tsXfn4iXtQvTrpQa7nHC3bx+9oK9ms1sL4NNrWAXZuToOv138Fe7fvZGt3AkoKrkvyWkPvctv5+X8XoW3bthBhNkzMWZo1DeFnfnrafQbpOjAwsF5nCi3d+H7likSh5kZbvv8eDspzGO6h4/65ubk51D6vkfYL0QbrnuO0dKsRY1tp0U3iLoP1jSGfcZe774mbnE/gvvqc/sMFH03ZoMVBWqPJOWOVWg0eDkL9utnOn2J52QdqL/SBLNfpks/+ZekKSVZLn4mhP8lt8+LZc2BvIXCyRYOdCTe3e86dVWLskZ8J4ByOOoXCUMNewn6Iwwg6O2vJMzHUC9cN2utfl/8Z2rVrJ9RF1h6Ej+9l4YXfkUNinuJcXn6Wgb58xXMeJA0R9gFQ1t9ltVhz+rB8Tc+cPAUKm6E05hADY8o/yFsE7ML5Cvopnk3gs7VWXmRX2W4z6H65bG0o77L38MzMtJO+cBbDahteEzR3nZi8bPm7PckhrlKdgecWpeLZENbwWGtxri+/9jKehv1VEg8SzjzwnRz3WeD/kbDP4DPKBSorK5tsS/L8ET1D4OiOXXtDhlMw6Y5ylIi7QsSBe4FjjPtR38hJQZB9/CTs+GozdOzYUdgvGjGF+lWI5018LwhtrJCtWazlaOqH+0tYnzWFu/H1yxXrKqxtLzOdP/BPonFv+XB7Efgj2oGxThfqGz9znoasnzIOU37DZ18PH0/z5fyaz6FSPP+LthDiWfrW7U1aAx7Xvt+VTvLS7APgybglDHcsjaMW93IusZy0UNQb4WOcQJLB8ttrUQ+ZR47RuRn2mWPuCBdYjYDvc98p9o6hPbljrmECD4xPaBb95/z3lJDze38KBeIZL+rqJpvHLsVkGKTXXaiVWBy8dF47DsrjbhHjOOPdvaR9r60sXxcrY8l+cC6okz/ZCM+3/y21SfqX239I4BSS6W86CDYx7pti4yPtyyBvXLcqWcrHv8YD5PEkLWW9tBbjTS0hnfl21pgZsErEPth8EFQ/etTk2oW/+/jxY5gZHKr1n4y5odPh+tVr9Y7b8ufF14tgRlCwVpzC2v7qlSvNlsvkMq7l5UPGnu/gx/0HQVVS0qj/w2A/jf+tMJv7YvlKCJsWwnxnAzy4f7+x2P8P8VKLUA==";

    }
}