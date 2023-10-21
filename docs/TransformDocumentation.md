# Transform
Exports `sf::Transform` API to Lua. It represents translation, scale and rotation as a 3D matrix.

### Operators
`*`: Combines two transforms.  
`==`: Compares two transforms.  

### Methods
`Transform.new()`: Creates an empty transform.  
`Transform.new(a00, a01, a02, a10, a11, a12, a21, a22, a23)`: Constructs a transform object from a 3x3 matrix.  
`transform:getMatrix()`: Returns 16 elements, each one representing the fields of the 4x4 transform matrix of `transform`.  
`transform:getInverse()`: Returns the inverse of the `transform`.  
`transform:transformPoint(x, y)`: Applies the `transform` to given point and returns the result.  
`transform:transformPoint(vec: Vector2)`: Applies the `transform` to given vector and returns the result.  
`transform:transformRect(rect: FloatRect)`: Applies the `transform` to given float rect and returns the result.  
`transform:combine(other: Transform)`: Combines `transform` with other and returns `transform`, allowing you to chain your operations.  
`transform:translate(x, y)`: Combines `transform` with a translation and returns `transform`, allowing you to chain your operations.  
`transform:translate(vector: Vector2)`: Combines `transform` with a translation and returns `transform`, allowing you to chain your operations.  
`transform:rotate(angle)`: Combines `transform` with a rotation and returns `transform`, allowing you to chain your operations.  
`transform:rotate(angle, centerX, centerY)`: Combines `transform` with a rotation around a point and returns `transform`, allowing you to chain your operations.  
`transform:rotate(angle, center: Vector)`: Combines `transform` with a rotation around a point and returns `transform`, allowing you to chain your operations.  
`transform:scale(scaleX, scaleY)`: Combines `transform` with a scale and returns `transform`, allowing you to chain your operations.  
`transform:scale(scaleX, scaleY, centerX, centerY)`: Combines `transform` with a scale around a point and returns `transform`, allowing you to chain your operations.  
`transform:scale(factors: Vector2)`: Combines `transform` with a scale and returns `transform`, allowing you to chain your operations.  
`transform:scale(factors: Vector2, center: Vector2)`: Combines `transform` with a scale around a point and returns `transform`, allowing you to chain your operations.  