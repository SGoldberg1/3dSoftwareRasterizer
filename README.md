# 3dSoftwareRasterizer

A software 3d rasterizer. The program explores:<br/>
-3d projection of 3d models, 3d transformations, and other linear algebra techniques. <br/>
-rasterization techniques such as line rasterization, triangle and rectangular filling. <br/>
-Bitmap rendering<br/>
-2D Bitmap Shader implementation such as linear blending, rotation, and scaling, and texture mapping. <br/>

There are two compilation units. Linux_Main.cpp compiles into the executable 'main.' <br/>
Engine.cpp is a unity build that compiles into a dynamic library engine.so(would be .dll on windows) <br/>

Source Description:<br/>
Linux_Main: The platform dependent entry point of the program. The intermediary between the OS and the engine. <br/>
Linux_Main.h: Data used in Linux_Main.cpp <br/>
Engine_Platform.h: This is used in both Engine.cpp and Linux_Main.cpp. <br/>
                    It provides a type definition for the entrypoint and other data that will be passed from Linux_Main.cpp to Engine.cpp. <br/>
Engine.cpp: The platform independent entrypoint.<br/>
Engine.h: Data for Engine.cpp<br/>
Engine_Memory.cpp: Routines for engine memory management. (Flat memory model partitioned into blocks or aka arenas)<br/>
Engine_Memory.h: Memory data<br/>
Engine_Math.cpp: Math routines for the engine<br/>
Engine_Math.h: Data for math <br/>
Engine_Types: Custom type definitions. <br/>
Engine_Rendering.cpp: Logic for queueing objects to be rendered. <br/>
Engine_Rendering.h: Data used to render various objects. <br/>
Engine_SoftwareRendering.cpp: Rendering routines and process for rendering queued objects. <br/>
Engine_Algorithms.cpp: Generic data structures and algorithms for debug use only. Currently only has a Queue. <br/>
Engine_Algorithms.cpp: Generic Sorting and searching for debug use only. <br/>
Engine_TextProcessing.cpp: Basic textual transformations such as int to string and vice versa. <br/>

Control Flow: <br/>
main() -> EngineUpdate() -> SDL_SoftwareRender() <br/>
The program enters main() in Linux_Main.cpp. It creates a window, allocates memory for offscreen buffer and memory  <br/>
to live throughout the duration of the program, and then enters a standard program loop: <br/>
input -> update -> present <br/>

There is however an additional step before input events are processed. When the engine.so is loaded, there is a copy made called temp.so.
The copy is what actually gets loaded so that we can recompile the engine.so while the program is running(hot loading). Linux_Main.cpp then
queries the modification date of the Engine.so, and if changed the temp.so is unloaded, engine.so copies over temp.so and then we reload temp.so.
This provides a way to tweak the program while it is running so that the current state of the program persists throughout changes.

Memory Management: <br/>
When the Engine.cpp runs for the first time(hot loading does not change this) memory is initialized. Memory in the engine is flat.
We take a chunk of memory and partition it into 'n' blocks as needed. Each block could represent a subsystem. Currently, the only
memory management is a push buffer. Consider memory layout: <br/>
persistent memory: | block1 | block2 | etc... | <br/>
block1: | data1 | data2 | etc... | <br/>

This memory is owned by the 'main' executable. So, and changes engine.so makes will modify that memory - insuring hotloading keeps current program state. <br/>

Rendering Process: <br/>
The renderer uses a push buffer as well. This push buffer is composed of discriminated unions. We have the data for the object to be rendered, and
The data(render_header) to identify the type of the object we need to render. This is tracked via the render_group aggregate type. 
Consider the following memory layout: <br/>

render_group: | render_header | object1 | render_header | object2 | etc... | <br/>

We then loop over all the data until 'n' bytes used has been met - pulling the render_header which determines the case to execute.  <br/>

Additional Comments:
Clipping is not handled properly... So, the whole triangle gets clipped if any of the vertices is outside of NDC.
The visibility problem has not been solved. Triangles that should be behind another triangle may get rendered ontop...
This is a software rasterizer without optimizations, SIMD, or MIMD, so framerates may be bad.
Hot keys: 
W -> Move forward
D -> Right Stride
A -> Left Stride
S -> Move Back
Q -> Move Up
E -> Move Down
Directional Left: Look Left
Directional Right: Look Right
Directional Up: Look Up
Directional Down: Look Down
1 -> Toggle WireFrame
2 -> Toggle Solid Fill
3 -> Toggle Shaded Fill
4 -> Toggle Triangle Normals
5 -> Toggle Line from light source to object origin
