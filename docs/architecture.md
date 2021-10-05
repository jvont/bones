# Engine Architecture

The engine is organized into several layers:

---

## Platform

This is the layer that allows us to interface with the current Platform - in other words, the Operating System and Hardware.

**Description:**

Window, audio, and input management; graphics contexts, timers, threading, networking, file management.

**Implementation:**

- Using native libraries (eg. windows.h, C++ libraries for things like hi-res counters).
- Realistically using a framework such as SDL2 or glfw3 which handles platform independence for us, along with GL wrappers (such as GLAD).

---

## Core

This layer contains all core utilities and data types for the engine.

**Utilities:**

- **Collections:** Memory pool/allocator, data collections
- **Debug:** Assertions, logging, profilers.
- **Events:** Event emitters, callback functions.
- **Files:** Async file I/O, resource loaders
- **Math:** STL wrappers, vectors, matrices, curves, planes, viewports, quaternions, easing/shaping functions, random numbers
- **Time:** Timers, coroutines, main update loop (fixed/variable).

**Implementation:**

Heavily using STL/STL wrappers along with (potentially) some platform APIs.

---

## Resources

The layer containing abstractions for resource objects. Primarily uses core utilities for file I/O and data types. Main goals of this layer are to provide the 'consumables' for subsequent layers.

**Resource types:**

Images, shaders, textures, meshes, fonts, audio/video streams.

**Implementation:**

Third-party libraries for convenience (eg. stb_image.h).

---

## Managers

Manages loading/unloading of resources.

**Managers:**

- **Window Manager:** Window/context creation/deletion, input handling.
- **Resource Manager:** Resource loading/unloading
- **Rendering Manager:** Graphics calls

**Implementation:**

Using server architecture and (maybe) flyweights.

---

<!-- ## Module

This layer contains the interfaces from the managers layer, providing an engine-like API for scripting.

**Modules:**

- **Graphics:** Render functions for primitives, lighting, text, cameras, etc.
- **Input:** Keyboard, mouse, gamepad, update server
- **Audio:** Audio management, 3D audio models

**Implementation:**

TODO

---

## Scene

Gameplay/application-specific systems.

**Modules:**

- **UI:** User interface framework for Debug, editor, and gameplay editors
- **Physics:** Colliders, spatial hashes, etc.
- **Entity-Component:** Game-specific objects, cameras, colliders, pathfinding, etc.

**Implementation:**

TODO

---

## Frontend

Engine UI/editors

**Modules:**

TODO

**Implementation:**

imgui -->