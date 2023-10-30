# View
Exports `sf::View` API to Lua. View allows you to manuplate the camera in your game.  

### Methods
`View.new()`: Creates an empty view object.  
`View.new(frect: FloatRect)`: Creates a view object from given rectangle.  
`View.new(center: Vector2, size: Vector2)`: Creates a view object with given center and size.  
`view:setCenter(x, y)`: Sets the center of the `view`.  
`view:setCenter(center: Vector2)`: Sets the center of the `view`.  
`view:setSize(x, y)`: Sets the size of the `view`.  
`view:setSize(size: Vector2)`: Sets the size of the `view`.  
`view:setRotation(angle)`: Sets the rotation of `view`.  
`view:setViewport(frect: FloatRect)`: Sets the viewport of `view`. [Read](https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1View.php#a8eaec46b7d332fe834f016d0187d4b4a).  
`view:reset(rectangle: FloatRect)`: Resets the `view` to the given rectangle.  
`view:getCenter()`: Returns the center of `view` as Vector2.  
`view:getSize()`: Returns the size of `view` as Vector2.  
`view:getRotation()`: Returns the rotation of `view`.  
`view:getViewport()`: Returns the viewport of `view` as FloatRect.  
`view:move(x_offset, y_offset)`: Moves the `view`.  
`view:move(offset: Vector2)`: Moves the `view`.  
`view:rotate(angle)`: Rotates the `view`.  
`view:zoom(factor)`: Resizes the `view` with respect to its current size.  
`view:getTransform()`: Returns the transform of `view`.  
`view:getInverseTransform()`: Returns the inverse transform of `view`.  