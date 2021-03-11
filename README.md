# 3dSoftwareRasterizer

A software 3d rasterizer. The program explores:
-3d projection of 3d models, 3d transformations, and other linear algebra techniques. 
-rasterization techniques such as line rasterization, triangle and rectangular filling.
-Bitmap rendering
-2D Bitmap Shader implementation such as linear blending, rotation, and scaling, and texture mapping

There are two compilation units. Linux_Main.cpp compiles into the executable 'main.' 
Engine.cpp is a unity build that compiles into a dynamic library engine.so(would be .dll on windows)

Source Description:
Linux_Main: The platform dependent entry point of the program. The intermediary between the OS and the engine. 
Linux_Main.h: Data used in Linux_Main.cpp
Engine_Platform.h: This is used in both Engine.cpp and Linux_Main.cpp. 
                    It provides a type definition for the entrypoint and other data that will be passed from Linux_Main.cpp to Engine.cpp.
Engine.cpp: The platform independent entrypoint.
Engine.h: Data for Engine.cpp
Engine_Memory.cpp: Routines for engine memory management. (Flat memory model partitioned into blocks or aka arenas)
Engine_Memory.h: Memory data
Engine_Math.cpp: Math routines for the engine
Engine_Math.h: Data for math
Engine_Types: Custom type definitions
Engine_Rendering.cpp: Logic for queueing objects to be rendered
Engine_Rendering.h: Data used to render various objects
Engine_SoftwareRendering.cpp: Rendering routines and process for rendering queued objects
Engine_Algorithms.cpp: Generic data structures and algorithms for debug use only. Currently only has a Queue
Engine_Algorithms.cpp: Generic Sorting and searching for debug use only.
Engine_TextProcessing.cpp: Basic textual transformations such as int to string and vice versa.

Control Flow:
main() -> EngineUpdate() -> SDL_SoftwareRender()
The program enters main() in Linux_Main.cpp. It creates a window, allocates memory for offscreen buffer and memory 
to live throughout the duration of the program, and then enters a standard program loop:
input -> update -> present

There is however an additional step before input events are processed. When the engine.so is loaded, there is a copy made called temp.so.
The copy is what actually gets loaded so that we can recompile the engine.so while the program is running(hot loading). Linux_Main.cpp then
queries the modification date of the Engine.so, and if changed the temp.so is unloaded, engine.so copies over temp.so and then we reload temp.so.
This provides a way to tweak the program while it is running so that the current state of the program persists throughout changes.

Memory Management:
When the Engine.cpp runs for the first time(hot loading does not change this) memory is initialized. Memory in the engine is flat.
We take a chunk of memory and partition it into 'n' blocks as needed. Each block could represent a subsystem. Currently, the only
memory management is a push buffer. Consider memory layout:
persistent memory: | block1 | block2 | etc... |
block1: | data1 | data2 | etc... |

This memory is owned by the 'main' executable. So, and changes engine.so makes will modify that memory - insuring hotloading keeps current program state.

Rendering Process:
The renderer uses a push buffer as well. This push buffer is composed of discriminated unions. We have the data for the object to be rendered, and
The data(render_header) to identify the type of the object we need to render. This is tracked via the render_group aggregate type. 
Consider the following memory layout:

render_group: | render_header | object1 | render_header | object2 | etc... |

We then loop over all the data until 'n' bytes used has been met - pulling the render_header which determines the case to execute. 
