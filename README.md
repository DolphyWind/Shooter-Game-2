# Shooter-Game-2
Shooter Game 2 is a multiplayer game where you can mod your game however you want.

# Completion Status
The modding system is 95% done. But the other menus will be implemented in the future. I am planning to make modding system a bit more "systematic". I am planning to finish it and add comments to code. After then I plan to finish to other parts of the game since the modding part is very important.

# Modding
To understand how to mod the game, please read [Modding Documentation](./docs/Modding%20Documentation.md).

# Compiling The Project
Since the project is a bit old, the compilation process has some minor inconveniences. You need SFML 2.5.1 installed on your system, I tried fetch content but SFEX, my own library,
do not compile properly and I am too lazy to address that at the moment.

On Linux, you also need `libFLAC.so.12`. If you have the modern versions of `libFLAC` like me, you can use `ln` tool to get around that. Optionally you can install a `1.3.x` version of
`flac`. I did not compile this project on Windows and macOS.
