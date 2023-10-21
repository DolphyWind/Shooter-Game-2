# ConvexShape
Exports AttachableObject\<sf::ConvexShape\> API to Lua. An attachable object is an object that can be attached to an entity. When an attachable object is attached to an entity, the origin of its coordinate system becomes that entity's global position.  

### Methods
`ConvexShape.new()`: Creates an empty convex shape.  
`CircleShape.new(pointCount: integer)`: Creates a convex shape that has given amount of points.  
`xshape:setPointCount(newPointCount: integer)`: Sets the number of points used to compose `xshape`.  
`xshape:getPointCount()`: Returns the number of points used to compose the `xshape`.  
`xshape:setPoint(index: integer, position: Vector2)`: Sets the position of the point of the shape that corresponds to given index.  
`xshape:getPoint(index: integer)`: Returns a point of the shape that corresponds to given index.  
`xshape:setTexture(texture: Texture)`: Sets the texture of `xshape`.  
`xshape:setTexture(texture: Texture, resetRect: bool)`: Set the texture of `xshape`.  
`xshape:setTextureRect(rect: IntRect)`: Sets the sub-rectangle of the texture that the `xshape` will display.  
`xshape:setFillColor(color: Color)`: Sets the fill color of the `xshape`.  
`xshape:setOutlineColor(color: Color)`: Sets the outline color of `xshape`.  
`xshape:setOutlineThickness(color: Color)`: Sets the outline thickness of `xshape`.  
`xshape:getTexture()`: Returns the texture of `xshape`.  
`xshape:getTextureRect()`: Returns the sub-rectangle of the texture displayed by the `xshape`.  
`xshape:getFillColor()`: Returns the fill color of `xshape`.  
`xshape:getOutlineColor()`: Returns the outline color of `xshape`.  
`xshape:getOutlineThickness()`: Returns the outline thickness of `xshape`.  
`xshape:getLocalBounds()`: Returns the local bounding rectangle of `xshape` as FloatRect.  
`xshape:getGlobalBounds()`: Returns the global bounding rectangle of `xshape` as FloatRect.  
`xshape:setPosition(x, y)`: Sets the position of the `xshape`.  
`xshape:setPosition(newPos: Vector2)`: Set the position of the `xshape`.  
`xshape:setRotation(angle)`: Sets the rotation of `xshape`.  
`xshape:setScale(x, y)`: Sets the scale of `xshape`.  
`xshape:setScale(newScale: Vector2)`: Set the scale of `xshape`.  
`xshape:setOrigin(x, y)`: Sets the origin of `xshape`.  
`xshape:setOrigin(newOrigin: Vector2)`: Sets the origin of `xshape`.  
`xshape:getLocalPosition()`: Returns the local position (Relative to attached entity) of `xshape` as Vector2.  
`xshape:getGlobalPosition()`: Returns the local position (Relative to world) of `xshape` as Vector2.  
`xshape:getRotation()`: Returns the rotation of `xshape`.  
`xshape:getScale()`: Returns the scale of `xshape` as Vector2.  
`xshape:getOrigin()`: Returns the origin point of `xshape` as Vector2.  
`xshape:move(offsetX, offsetY)`: Moves `xshape` by given offset.  
`xshape:move(offset: Vector2)`: Moves `xshape` by given offset.  
`xshape:rotate(angle)`: Rotates `xshape` by given angle.  
`xshape:scale(factorX, factorY)`: Scales `xshape` by given factor.  
`xshape:scale(factor: Vector2)`: Scales `xshape` by given factor.  
`xshape:getTransform()`: Get the combined transform of the `xshape`.  
`xshape:getInverseTransform()`: Get the inverse transform of the `xshape`.  
`xshape:attachTo(entity: Entity)`: Attaches `xshape` to given entity.  