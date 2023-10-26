# Image
Exports `sf::Image` API to Lua. Image allows you to load, manipulate and save images.

### Methods
`Image.new()`: Creates an empty Image object.  
`image:create(width: integer, height: integer)`: Creates the image and fills it with the color black.  
`image:create(width: integer, height: integer, color: Color)`: Creates the image and fills it with the given color.  
`image:loadFromFile(filename: string)`: Loads the image from given file. Returns true if the image gets successfully loaded. Returns false otherwise.  
`image:saveToFile(filename: string)`: Saves the file with the given filename. Returns true if the image gets successfully saved. Returns false otherwise.  
`image:getSize()`: Returns the size of the image as Vector2.  
`image:createMaskFromColor(color: Color)`: Sets the alpha values of every pixel that matches given color to zero.  
`image:createMaskFromColor(color: Color, alpha: integer)`: Sets the alpha values of every pixel that matches given color to zero.  
`image:copy(source: Image, destX: ingteger, destY: integer)`: Copies the pixels from the given image to this one. destX and destY is the coordinates of destinationPosition.  
`image:copy(source: Image, destX: ingteger, destY: integer, sourceRect: IntRect)`: Copies the pixels from the given image to this one. destX and destY is the coordinates of destinationPosition. Source rect is the sub-rectangle of the source image to copy. If it is empty, the whole image gets copied  
`image:copy(source: Image, destX: ingteger, destY: integer, sourceRect: IntRect, applyAlpha: bool)`: Copies the pixels from the given image to this one. destX and destY is the coordinates of destinationPosition. Source rect is the sub-rectangle of the source image to copy. If it is empty, the whole image gets copied. If applyAlpha is set to true, it applies alpha blending while copying.  
`image:setPixel(x: integer, y: integer, color: Color)`: Sets the color of the pixel with given coordinates to given color.  
`image:getPixel(x: integer, y: integer)`: Returns the color of the pixel with given coordinates.  
`image:flipHorizontally()`: Flips the image horizontally.  
`image:flipVertically()`: Flips the image vertically.  