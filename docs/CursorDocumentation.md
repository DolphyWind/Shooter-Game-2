# Cursor
Exports `sf::Cursor` API to Lua. Cursor allows you to modify the appareance of system cursor.  

### Methods
`Cursor.new()`: Creates a new cursor object.  
`cursor:loadFromImage(image: Image, hospot: Vector2)`: Loads the `cursor` from an image.  
`cursor:loadFromSystem(type: integer)`: Loads the `cursor` from system.  

### Static Members
`Cursor.Type_Arrow`: Arrow cursor. Check SFML documentation for more info.  
`Cursor.Type_ArrowWait`: Busy Arrow cursor. Check SFML documentation for more info.  
`Cursor.Type_Wait`: Busy cursor. Check SFML documentation for more info.  
`Cursor.Type_Text`: I-beam cursor. Check SFML documentation for more info.  
`Cursor.Type_Hand`: Hand cursor. Check SFML documentation for more info.  
`Cursor.Type_SizeHorizontal`: Horizontal double arrow cursor. Check SFML documentation for more info.  
`Cursor.Type_SizeVertical`: Vertical double arrow cursor. Check SFML documentation for more info.  
`Cursor.Type_SizeTopLeftBottomRight`: Double arrow cursor going from top-left to bottom-right. Check SFML documentation for more info.  
`Cursor.Type_SizeBottomLeftTopRight`: Double arrow cursor going from bottom-left to top-right. Check SFML documentation for more info.  
`Cursor.Type_SizeAll`: Combination of SizeHorizontal and SizeVertical. Check SFML documentation for more info.  
`Cursor.Type_Cross`: Crosshair cursor. Check SFML documentation for more info.  
`Cursor.Type_Help`: Help cursor. Check SFML documentation for more info.  
`Cursor.Type_NotAllowed`: Action not allowed cursor. Check SFML documentation for more info.  