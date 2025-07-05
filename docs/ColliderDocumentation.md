# Collider
Exports Shooter Game's `Collider` API to lua. It allows you to define a convex collider. A collider is simply a collection of points. When you set the points of the collider, consecutive points
are connected and stored as outer lines. Then, the median of those outer points are calculated and every point is connected with that median point and stored as inner lines.
When a collision ckeck is performed between two colliders, ShooterGame checks whether one's inner lines are colliding with the other's outer lines or not.
\#TODO: Rewrite the collider system and make it by the book. API should stay mostly the same.

### Methods
`Collider.new()`: Creates an empty collider.
`Collider.new(entity: Entity)`: Creates an empty collider and attaches it to the given entity.
`Collider.new(points: table, isStatic: boolean=false, entity: Entity=nil)`: Creates a new collider with given points and attaches it to given entity.
`collider:setPoints(points: table)`: Sets the points of the `collider` and calculates the inner and outer lines.
`collider:setStatic(isStatic: boolean)`: Set whether the `collider` is static or not. By default, colliders are in trigger mode meaning that they can only be used to detect collision. Two static colliders will push eachother out when they collide. Please note that a collider that is not attached to an entity cannot move by itself as it has no position attribute.  
`collider:setImmovable(isImmovable: boolean)`: Set whether the `collider` is immovable or not. If the `collider` is immovable, it can't be pushed away by other colliders. Does nothing if `collider` is not static. It is useful for walls etc.  
`collider:setEntity(entity: Entity)`: Sets the entity that `collider` belongs to.  
`collider:getColliderCenter()`: Get the center coordinate of `collider`'s points as Vector2.  
`collider:getPoints()`: Get the points of `collider` as a table.  
`collider:getInnerLines()`: Get inner lines of `collider` as a table.  
`collider:getOuterLines()`: Get outer lines of `collider` as a table.  
`collider:isStatic()`: Returns true if `collider` is static. Returns false otherwise.  
`collider:isImmovable()`: Returns true if `collider` is immovable. Returns false otherwise.
`collider:getEntity()`: Returns the entity that `collider` is attached to.  
`collider:checkCollisions(other: Collider)`: Checks the collisions between `collider` and `other`. Returns true if there are any collisions. Also moves the entities of the `collider` and `other` if they are static.  
