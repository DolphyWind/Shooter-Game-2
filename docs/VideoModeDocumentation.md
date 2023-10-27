# VideoMode
Exports `sf::VideoMode` API to Lua. VideoMode defines a video mode.  

### Fields
`width`: Width of the video mode in pixels.  
`height`: Height of the video mode in pixel.  
`bitsPerPixel`: Pixel depth of video mode in bits per pixels.  

### Methods
`VideoMode.new()`:  Creates a new empty VideoMode object.  
`VideoMode.new(width: integer, height: integer)`:  Creates a new VideoMode object with given width and height.  
`VideoMode.new(width: integer, height: integer, bitsPerPixel: integer)`:  Creates a new VideoMode object with given width, height and bitsPerPixel.  
`VideoMode.getDesktopMode()`: Returns the current desktop video mode.  
`VideoMode.getFullscreenModes()`: Returns a list of all video modes supported in fullscreen mode.  
`videomode:isValid()`: Returns true if the `videomode` is valid for fullscreen mode. Returns false otherwise.  

### Operators
`==`: Checks whether the two VideoModes are equal or not.  
`<`: Compares two VideoModes.  
`<=`: Compares two VideoModes.  