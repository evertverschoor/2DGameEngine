# 2DGameEngine

PLANNED WORK:

-> Support for more than one asset per entity (animations?)

-> Sound (XAudio probably)

-> Implement proper way of making entities move (not a certain distance every frame)

-> Convert to DLL

-> Support for actually being able to use this as a library

COULD HAVES:

-> OpenGL Renderer for Mac and Linux support (also xinput alternative?)

CHANGELOG:

Sept. 10, 2015

-> Added Sharpening and Motion Blur postprocessing effects, and a class to test motion blur through moving the mouse.

Sept. 11, 2015

-> Added Saturation effect and support for multiple postprocessing effects to work at the same time.

-> Bit of refactoring and renaming some classes to more proper names, stable build before majoring refactoring that might break stuff.

-> Fixed code convention for class variable names, added more documentation where needed and removed obsolete includes.

BENCHMARKS:

	Always 1080p, maxed out everything there is at the time.
	Running on weaker card without vsync(so the framerate isnt capped at 60)
	Specs: A10-5750M with Radeon HD 8650G, Windows 10

Sept. 10, 2015

-> avg 50-60fps during heavy motion blur

Sept. 11, 2015

-> avg 60+fps during heavy motion blur