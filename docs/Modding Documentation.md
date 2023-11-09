# Shooter Game 2's Entity System
In Shooter Game 2, everything is considered as an entity. Players, bullets even the walls are entity. There are two types of entities. First one is the player. It is entirely coded in C++ so to change its behavior, you have to change the C++ code and recompile the whole game. The second one is called LuaEntity. As the name suggests, Lua Entities are coded in lua programming language and they make up everything else in the Shooter Game 2. Entites has a name, a mod name (Even if it is not a part of a mod), a metadata (This field is completely left blank. It can be changed and can be used however a mod creator wants), a collider, a position in 2D coordinates and a health variable (defaults to 100). When the health of an entity reaches zero, it dies automatically and gets destroyed.  

## Mods In Shooter Game 2
Before we talk about how to create your own Lua Entities, we have to look at how mods are stored. Here's an example file structure of a mod
```bash
example_mod
├── assets
│   ├── image1.png
│   └── font.ttf
├── config.json
└── entities
    ├── entity1.lua
    └── entity2.lua
```

### "assets/" Folder
In assets folder, the asset of your mods will be stored. When loading an asset in a lua script, the load function loads the assets from this folder.

### "entities/" Folder
In entites folder, the code for LuaEntites are stored. The name of the entity can be different than the name of the file. The entites have some special functions. But they will be introduced in the entities section.

### "config.json" File
It contains information about the mod in the JSON format. The structure of the file given down below.  

**version**: The version of the mod. Eg. 1.2.3  
**authors**: The authors of the mod. Must be a list. Eg. ["DolphyWind", "Herobrine"]  
**modname**: The name of the mod. Should be the name of the parent folder.  
**title**: The title of the mod. Displayed in the mods menu or when selecting which mods to include on servers.  
**description**: The description of the mod. Displayed in the mods menu or when selecting which mods to include on servers.  
**dependencies**: A list of the mods that this mod depends on.  
**entities**: A list of objects, each object is a seperate entity. An entity holds 5 variables in them. Here's an example entity:  
```json
{
    "name": "bullet",
    "file": "bullet.lua",
    "hidden_in_mapmaker": false,
    "one_instance_only": false,
    "spawn_if_not_exists": false
}
```
Here, the **name** field contains the name used to refer this entity in scripts. The **file** field contains the lua file that this entity will run. **hidden_in_mapmaker** hides the entity from map maker menu. **one_instance_only** makes entity at most have one instance. **spawn_if_not_exists** spawns the entity if it doesn't exists in the map at the beginning of the game. The last three options are more targeted to a GameManager-like entities.

#### Future Of The Mods
I am also planning to add `settings.json` and export an API to Lua that will allow you to retrieve your settings.

## Special LuaEntity Functions
As I've mentioned before, the lua entities has some special functions. Here are a list of them with their descriptions:

**start()**: Start function is called at the beggining of the game and never runs again unless it is called by another function. The `start()` function of manually spawned entities are called at the end of the current frame.  

**handleEvent(e)**: Handle event function is used to interpret the events that it has given. Events will be explained in the [Modding API](#modding-api) section.

**update(dt)**: Update function is called each frame. The `dt` parameter is the amount of time passed between this frame and last frame in seconds.

**lateUpdate(dt)**: Similar to update function, the late update is called each frame. But it is called after `update` function. The `dt` parameter is the amount of time passed between this frame and last frame in seconds.  

**onDestroy()**: On Destroy function is called before an object gets destroyed.

**render()**: Render function is called each frame after `update` and `lateUpdate`. Used for rendering stuff on screen.

**onCollisionEnter(other)**: On Collision Enter is called when a collider of another object enters the collider of this object. The other object is passed as the `other` parameter.

**onCollisionStay(other)**: On Collision Stay is called when a collider of another object keeps colliding with the collider of this object. The other object is passed as the `other` parameter.

**onCollisionExit(other)**: On Collision Exit is called when a collider of another object exits the collider of this object. The other object is passed as the `other` parameter.

**onDeath()**: On Death function is called when the health of an entity is less than or equal to zero. Then the object gets destroyed. Keep in mind that the `onDestroy()` function is also getting called.

## Modding API 
The Shooter Game 2 exports some of its features to Lua. Here's a list of the classes that are exported with their documentations. In the documentations, please note that Lua has an `:` operator. `x:f()` passes x as the `f`'s first parameter. When you see this operator in the documentation, please interpret the variable on the left as an instance of that type. Also, I denoted the types of the some function arguments. If you see an argumat that isn't associated with a type, please assume that it is a number.  

+ [Vector2](./Vector2Documentation.md)
+ [Color](./ColorDocumentation.md)
+ [Stopwatch](./StopwatchDocumentation.md)
+ [Transform](./TransformDocumentation.md)
+ [RectangleShape](./RectangleShapeDocumentation.md)
+ [CircleShape](./CircleShapeDocumentation.md)
+ [ConvexShape](./ConvexShapeDocumentation.md)
+ [Entity]()
+ [Collider]()
+ [Keyboard](./KeyboardDocumentation.md)
+ [Mouse](./MouseDocumentation.md)
+ [Cursor](./CursorDocumentation.md)
+ [Joystick](./JoystickDocumentation.md)
+ [SoundBuffer](./SoundBufferDocumentation.md)
+ [Sound]()
+ [Music]()
+ [Image](./ImageDocumentation.md)
+ [Texture]()
+ [Sprite]()
+ [IntRect](./IntRectDocumentation.md)
+ [FloatRect](./FloatRectDocumentation.md)
+ [Glyph](./GlyphDocumentation.md)
+ [Font](./FontDocumentation.md)
+ [Text](./TextDocumentation.md)
+ [RenderWindow]()
+ [ContextSettings](./ContextSettingsDocumentation.md)
+ [VideoMode](./VideoModeDocumentation.md)
+ [Event]()
+ [View](./ViewDocumentation.md)
