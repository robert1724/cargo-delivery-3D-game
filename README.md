# cargo-delivery-3D-game
A 3D train game built in C++ with OpenGL, where players navigate a train through intersections to collect resources and deliver them to the central station before time runs out.

Gameplay
  - A **central station** (sphere) issues orders of **5 random resources**
  - Resources must be collected **in order** from 3 different stations scattered across the map
  - The train moves **automatically** along rails and stops at **intersections** where the player chooses direction
  - After collecting all 5 resources, return to the central station to complete the delivery and receive a new order
  - **60-second timer** — the central station gradually turns from yellow to red. If time runs out, **Game Over**
    
Controls
  - W = Go north (up) at intersection 
  - A = Go west (left) at intersection 
  - S = Go south (down) at intersection
  - D = Go east (right) at intersection 
  - Right click + drag = Rotate camera
    
Map & Environment
  - The scene is a hand-crafted 3D world with:
  - **Grass** = Green quad (base terrain)
  - **Rivers/Lakes** = Blue rectangles and circles
  - **Mountains** = Brown 3D pyramids + brown 2D quads 
  - **Borders** = Dark walls enclosing the play area
   
Rail Types

  - **Normal** = Dark blue rectangles
  - **Bridge** = Alternating navy/white horizontal strips (over mountains) 
  - **Tunnel** = Alternating navy/white transversal strips (over water)

Stations
  - **Central** = Sphere, Yellow → Red (timer), Command issuer
  - **Station 1** = Cube, Pink, Cube resource 
  - **Station 2** = Pyramid, Red, Pyramid resource 
  - **Station 3** = Torus, Purple, Torus resource
  - Pending resources are displayed as miniature versions of the station shapes near the central station.
    
Train Design
  - **Locomotive**: Green parallelepiped (cabin) + blue cylinder (engine) + yellow base + red cylinder wheels
  - **Wagon**: Green parallelepiped + yellow base + red cylinder wheels + connector
  - Train orientation updates automatically based on the current rail direction
    
Technical Implementation
  - **Rail system** = Graph of "Rail" objects connecting "Intersection" nodes
  - **Train movement** = Linear interpolation along rail segments with constant speed 
  - **Direction selection** = Dot product between WASD input vector and available rail directions 
  - **Collision detection** = Distance-based proximity checks (radius 0.6) for resource collection 
  - **Timer** = 60s countdown; sphere mesh swaps through 12 color stages 
  - **Geometry** = All meshes hand-built from vertices (boxes, cylinders, spheres, pyramids, tori) 
  - **Game Over** = Black screen with red X after timeout, auto-closes after 3s 
  - The map contains **11 intersections** + **4 station nodes** + **6 pass-through nodes**, connected by **~25 rails** with 36+ segments.

Building & Running
  - This project is built within the [GFX Framework] used in the Computer Graphics course at Politehnica Bucharest.-
  - To run, follow the steps explained here https://ocw.cs.pub.ro/courses/egc/setup-framework
  - The project can run from Visual Studio Installer OpenGL or CMake (Linux)
