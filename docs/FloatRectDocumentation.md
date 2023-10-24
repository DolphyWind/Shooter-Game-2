# FloatRect
Exports `sf::FloatRect` API to Lua. FloatRect allows you to manuplate axis aligned rectangles.  

### Operators
`==`: Checks whether two FloatRects are equal or not.  

### Methods
`FloatRect.new()`: Creates an empty FloatRect object.  
`FloatRect.new(other: FloatRect)`: Creates a copy of given FloatRect object.  
`FloatRect.new(position: Vector2, size: Vector2)`: Creates a new FloatRect with given position and size.  
`FloatRect.new(left, top, width, height)`: Creates a new FloatRect with given position and size.  
`frect:contains(point: Vector2)`: Returns true if `frect` contains the given point. Returns false otherwise.  
`frect:contains(x, y)`: Returns true if `frect` contains the given point. Returns false otherwise.  
`frect:intersects(other: FloatRect)`: Returns true if `frect` and `other` intersects. Returns false otherwise.  
`frect:intersects(other: FloatRect, intersection: FloatRect)`: Returns true if `frect` and `other` intersects. Returns false otherwise. Also returns the overlapped rectangle in the `intersection` parameter.  
`frect:getPosition()`: Returns the position of `frect`.  
`frect:getSize()`: Returns the size of `frect`.  

### Fields
`left`: Left coordinate of the rectangle.  
`top`: Top coordinate of the rectangle.  
`width`: Width of the rectangle.  
`height`: Height of the rectangle.  