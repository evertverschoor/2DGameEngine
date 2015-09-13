# 2DGameEngine

## Planned Work

-> Support for more than one asset per entity (animations?)

-> Implement proper way of making entities move (not a certain distance every frame)

-> Convert to DLL

-> Support for actually being able to use this as a library


## Could Haves

-> OpenGL Renderer for Mac and Linux support (also xinput alternative?)


## Changelog

### Sept. 10, 2015

-> Added Sharpening and Motion Blur postprocessing effects, and a class to test motion blur through moving the mouse.


### Sept. 11, 2015

-> Added Saturation effect and support for multiple postprocessing effects to work at the same time.

-> Bit of refactoring and renaming some classes to more proper names, stable build before majoring refactoring that might break stuff.

-> Fixed code convention for class variable names, added more documentation where needed and removed obsolete includes.


### Sept. 12, 2015

-> Added sound engine using XAudio2, can now load and unload sounds and play them.

-> Split VideoSettings and GraphicsSettings into two files, added Brighten effect, fixed Sharpen visual bug.


### Sept. 13, 2015

-> Added a camera with working mouse movement mode, hid the cursor

-> Fixed visual bug where rotated entities would display at a wrong location after moving the camera

-> Fixed visual bug where motion blur would keep going even after reaching the border of the scene


## Benchmarks

	Always 1080p, maxed out everything there is at the time.
	Running on weaker card without vsync(so the framerate isnt capped at 60)
	Specs: A10-5750M with Radeon HD 8650G, Windows 10

### Sept. 10, 2015

-> avg 50-60fps during heavy motion blur


### Sept. 11, 2015

-> avg 60+fps during heavy motion blur