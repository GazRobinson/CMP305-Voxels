CMP305-Voxels
## Procedural Methods
# LAB 6: DUNGEON GENERATION
**Gaz Robinson**
**School of Design and Informatics**
# Introduction
This week’s lab looks at some of the techniques involved in dungeon generation: Space Partitioning, Cellular Automata and Agent Based Generation!

If you have any problems, please ask in the lab, or contact me **(g.robinson@abertay.ac.uk)**.
#The code
New code again this week!
Download the Voxels starter code from MyLearningSpace and open it up.
When you run it, you should see a wave landscape, but now it’s being generated with 3D cubes; also known as **voxels** (3D pixels)!

In the code this week it’s the DirectX 11 Framework that you’re used to, but with a couple of new classes: **InstancedCubeMesh, InstanceShader** and **QuadMeshT**.

**InstancedCubeMesh** provides a system for drawing many (MANY) Cube meshes in an efficient manner. You don’t need to dig into this code to work the labs this week but do take a look if you want to see how to build instanced meshes!
**InstanceShader** is, exactly as the name implies, the shader system used for rendering our many cubes. Again, you don’t need to dig in; but do have a look if you’re curious!
**QuadMeshT** draws a horizontal Quad mesh (of a defined size) but has a parameter for providing a transform matrix, so you can easily draw it in different locations, scales and rotations.

You’ll likely be working in the **BuildCubeInstances** function of App1.cpp for most of the lab, but there are many different approaches to today’s tasks. Rather than using the voxels, you could use quad meshes to map out your dungeon for now.
 
To begin with, **BuildCubeInstances** loops through every possible voxel in a 64x64x64 cube and if the voxel is below the wave function, then the voxel is marked as solid and added to the list of instances to draw.
(Remember that the difference in voxel count between a 64 width cube and a 128 width cube is HUGE).
There’s currently no intelligent culling: If you tell it to draw a million cubes, then it’s going to draw a million cubes (or die trying…).

To draw voxels we build an array of **positions** and pass this array (along with the number of cubes) to the **InstancedCubeMesh** class. The class then facilitates drawing the same cube over and over at different positions!

# Why this approach?
The intention for this is to allow for a more accessible way of generating dungeons or caves in 3D, but you could also look at using it for a Minecraft-style voxel terrain.
If you’d rather build rooms using your own method, then you don’t have to use the voxels! You could use quad meshes, inverted cubes or whatever you want to try!
# Tasks
You can do this week’s tasks in any order, as they’re all pretty distinct. Try not to get hung up on the bonus tasks for now; but tackle them if you’re looking for more of a challenge!
## Task 1 - Space Partitioning
Using the lecture material provided, build a system of classes that can perform Binary/Quad Partitioning.
At this stage you don’t even need to render anything; you just need a system that can manage the creation and division of cells within a space.

It should start with a root cell that can be split into 2, 4 or more child cells. These cells should also be able to split into more cells.
The cells should have a position, a width and a height/depth.

Once you have this, try rendering the system with quad meshes or the voxel cubes.

## Task 1.2 - The Rogue Algorithm
Now that you’ve split your space into a collection of unique cells, it’s time to generate some rooms.
Following the ideas within the Rogue algorithm generate a room within each of your partition cells.
This room could be any shape as long as it fits within the confines of the cell.

### Bonus:
Next, decide which rooms are connected to each other, so that no room is left on its own.
Then using this information, create corridors (which are essentially narrow rooms) between the rooms themselves. (This can be trickier than it looks!)

## Task 2 - 3D Perlin Noise
Using the Perlin Noise class you’ve built in a previous week (if it doesn’t support 3D noise yet, you’ll need to add this functionality first!) and the voxel renderer, create a 3D voxel render of caves using 3D Perlin Noise!
Look at the lecture for an example input and expected output.
### Bonus:
Combine this with a height-based generation function to create a landscape terrain with caves below it (in a blocky style!).
For each voxel, you’ll need to look at the density function as before, but also compare it to your height function. Then you only create a block if it passes both functions (i.e. the density is above the threshold and it is below the height value).
 
## Task 3 - Cellular Automata
Build a system that allows you to manage a Cellular Automaton. Look back at last week’s L-System skeleton class for an example of how you might approach this!
It should have:
•	A 2D (or 3D) array of cells (these could be integer or boolean values)
•	A function for performing an iteration
•	Look at the lecture for some examples (Game of Life, Cave generation…)

Once this is built, or as part of the task, find a way to render the results. 
This could be written to a texture, use the voxel system, build a selection of quads… Anything that can draw “pixels”.

## Task 4 - Agent-based generation
Using the lecture notes and the reading links on MyLearningSpace, plan out and build an agent-based dungeon generator, starting with a simple blind-agent.
•	Move in the current direction and increase the chance of spawning a room by 2% & the chance of changing direction by 5%
•	Check to see if we’re changing direction, and if so, reduce the chance to 0%
•	Check to see if we’re placing a room, and if so, reduce the chance to 0%
•	Repeat
Once this is working, you can look at increasing the complexity with some intelligent pathing and building.
