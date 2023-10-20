# Vector2

Vector2 exports sfex::Vector2<float> API to Lua. It represents 2D mathematical vectors. 

### Fields
`x`: X component of the Vector2.  
`y`: Y component of the Vector2.  

### Operators
`+`: Adds two vectors.  
`-`: Subtracts two vectors.  
`- (Unary minus)`: Negates the vector.  
`*`: Scales the vector by a scaling factor.  
`/`: Shrinks the vector by a shrinking factor.  
`//`: Shrinks the vector by a shrinking factor. Does an integer division.  
`==`: Compares two vectors.  

### Methods
`Vector2.new()`: Creates a new zero Vector2.  
`Vector2.new(other: Vector2)`: Creates a new Vector2 that has the same components with the other Vector2.  
`Vector2.new(x, y)`: Creates a new Vector2 that has the given x and y values.  
`vec:magnitude()`: Returns the magnitude of `vec`.  
`vec:magnitude2()`: Returns the magnitude of `vec` squared.  
`vec:setMagnitude(newMag)`: Sets the magnitude of the `vec` to newMag.  
`vec:normalize()`: Normalizes the `vec`.  
`vec:normalized()`: Returns the normalized version of `vec`.  
`vec:dot(other: Vector2)`: Computes the dot product between `vec` and `other` vector.  
`vec:cross(other: Vector2)`: Treats the `vec` and `other` as 3D vectors with z component being zero. Then computes the cross product between them and returns the z component of the resulting vector.  
`vec:cwiseMul(other: Vector2)`: Component-wise multiplies `vec` and `other`.  
`vec:cwiseDiv(other: Vector2)`: Component-wise divides `vec` and `other`.  
`vec:scale(scaleFactor)`: Scales the vector by given scale factor.  
`vec:scaled(scaleFactor)`: Returns the scaled version of this vector by given scale factor.  
`vec:rotate(angle)`: Rotates `vec` around the zero vector by given angle (in radians).  
`vec:rotate(angle, other: Vector2)`: Rotates `vec` around the `other` vector by given angle (in radians).  
`vec:rotated(angle)`: Returns the rotated version of `vec` around the zero vector by given angle (in radians).  
`vec:rotated(angle, other: Vector2)`: Returns the rotated version of `vec` around the `other` vector by given angle (in radians).  
`vec:angle()`: Returns the angle between `vec` and `<1, 0>` vector in radians.  
`vec:angle(other: Vector2)`: Returns the angle between `vec` and `other` vector in radians.  
`vec:projectOnto(other: Vector2)`: Projects `vec` onto `other`.  
`vec:projectedOnto(other: Vector2)`: Returns projected version of the `vec` onto `other`.  
