# **Game Vision, Storyline, Design Foundations**

### Goals

* Define the world, tone, characters, and "debugging as gameplay" mechanic.
* Create concept art, world maps, and quest structures.
* Define game engine's scope.

### Learn \& Research

* Native design basic (hero's journey, pacing, player agency).
* Game design documents (GDD) -- structure and clarity.
* Level design theory (flow, exploration, reward cycles).

### Tools \& Languages

* Writing tools: Notion, Obsidian, or Google Docs.
* Pixel art: Aseprite, Piksel, or Pixilart.
* Optional map editor (for prototyping): Tiled.

### Steps

1. Write a 1-paragraph concept summary ("elevator pitch").
2. Develop main storyline (start, middle, climax, resolution).
3. Define debugging-learning gameplay loop:

   * Example: In-game devices malfunction -> player "fixes" them by spotting logic errors in fictional code snippets.
4. Create world regions and a main hub.
5. Sketch a map layout.
6. Design 3-5 NPCs with personalities and dialogue.
7. Write at least 2 side quests
8. Create Game Design Document (GDD) with:

   * Story overview
   * Core mechanics
   * Quest and item system
   * Art and UI style references

# **Engine Foundations (Rendering \& Input)**

### Goals

Building the foundation of the game -- handle rendering, input, and basic game loop.

### Learn

* Game loop structure (update -> draw -> input -> repeat).
* 2D rendering using libs:

  * C#: SDL2-CS or MonoGame-like approach(no editor)
  * C++: SDL2 or RayLib
  * Rust: ggez or macroquad
* Basic linear algebra for 2D (vectors, transformations)

# **Engine Systems (Physics, Entities, Map)**

### Goals

Implement movement, collision, map loading, and game objects.

### Learn

* Entity Component System (ECS) basics
* Collision detection (AABB, tile-based)
* Map parsing from .tmx (Tiled) or own JSON format

### Steps

1. Create an EnrityManager (store entities \& components)
2. Implement a collision system (wall, objects)
3. Design a simple physics loop
4. Implement camera system (follow player)
5. Add map loading from files

# **Storyline \& Quest System**

### Goals

Implement story and quest management systems.

### Learn

* Finite State Machines (FSM) for dialogue/quest states
* Scripting Integration -- e.g. embed Lua for event logic
* JSON/YAML for storing quests and dialogues

### Steps

1. Create Dialogue system (text boxes, branching)
2. Build QuestManager with states: active, inactive, completed
3. Implement trigger zones (when player interacts, event fires)
4. Create a simple in-game scripting language (start learning Lua or own DSL)

### Optional Tech

* Lua scripting integration (C#, C++, Rust)
* Or JavaScript (via V8 engine or Duktape) for easier integration

# **Debugging-Learning Mechanics (Unique Gameplay)**

### Goals

Make the educational mechanic the heart of the game

### Learn

* In-game editors/UI systems (to simulate “debugging”).
* Script evaluation (sandboxed code execution).
* Player feedback loops (reward for fixing “bugs”).

### Steps

1. Create a fictional device/terminal where you “debug code.”
2. Show sample pseudocode with intentional bugs.
3. Let player fix code → engine validates logic.
4. Each fix progresses story or unlocks area.
5. Store player progress.

### Implement Ideas

* Use Lua for “fake programs” the player debugs.
* Example:

  * NPC: “My robot won’t water the plants!”
  * Player opens “code” → sees if water == false then plant:dry() instead of if water == true.
  * Fix → plant grows → quest complete.

# **Art, Audio, UI Polish**

### Goals

Add aesthetic elements to reinforce coziness and immersion.

### Learn

* Pixel art animation (Aseprite, sprite sheets).
* UI layout systems (custom or retained mode GUI).
* Audio management (music, SFX).

### Steps

1. Design cozy tilesets (grass, wood, water, etc.).
2. Add ambient music (lofi, calm village themes).
3. Implement menus (inventory, settings, quests).
4. Add basic lighting and shaders (optional).

### Tools

* Audio: Bfxr, Audacity, Bosca Ceoil.
* Art: Aseprite.

# **Save System, Optimizations, Packing**

### Goals

Prepare the game for release or early access

### Learn

* Serialization (save/load system).
* File I/O (JSON or binary).
* Memory \& performance profiling.

### Steps

1. Implement saving/loading.
2. Optimize draw calls and memory usage.
3. Package for distribution (Windows/macOS/Linux).

# **ADVANCED TOPICS**

| Topic                                      | What to Learn                     | Benefit                     |

| ------------------------------------------ | --------------------------------- | --------------------------- |

| \*\*C++ Engine Development\*\*                 | Build from scratch in SDL2/OpenGL | Learn low-level systems     |

| \*\*Rust Game Dev (ggez, Bevy)\*\*             | Safe and modern engine design     | Modern engine architecture  |

| \*\*Scripting Languages (Lua, AngelScript)\*\* | Embedding scripts                 | Flexible quests and modding |

| \*\*WebAssembly + JS (Rust or C++)\*\*         | Port engine to browser            | Publish easily              |

| \*\*Shader programming (GLSL)\*\*              | Cozy lighting, glow, fog          | Visual depth                |
