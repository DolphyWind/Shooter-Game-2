# IntRect
Exports `sf::IntRect` API to Lua. IntRect allows you to manuplate axis aligned rectangles.  

### Operators
`==`: Checks whether two IntRects are equal or not.  

### Methods
`IntRect.new()`: Creates an empty IntRect object.  
`IntRect.new(other: IntRect)`: Creates a copy of given IntRect object.  
`IntRect.new(position: Vector2, size: Vector2)`: Creates a new IntRect with given position and size.  
`IntRect.new(left: integer, top: integer, width: integer, height: integer)`: Creates a new IntRect with given position and size.  
`irect:contains(point: Vector2)`: Returns true if `irect` contains the given point. Returns false otherwise.  
`irect:contains(x: integer, y: integer)`: Returns true if `irect` contains the given point. Returns false otherwise.  
`irect:intersects(other: IntRect)`: Returns true if `irect` and `other` intersects. Returns false otherwise.  
`irect:intersects(other: IntRect, intersection: IntRect)`: Returns true if `irect` and `other` intersects. Returns false otherwise. Also returns the overlapped rectangle in the `intersection` parameter.  
`irect:getPosition()`: Returns the position of `irect`.  
`irect:getSize()`: Returns the size of `irect`.  

### Fields
`left`: Left coordinate of the rectangle.  
`top`: Top coordinate of the rectangle.  
`width`: Width of the rectangle.  
`height`: Height of the rectangle.  