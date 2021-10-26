# Mesh Orient - A library to fix triangle mesh orientation.

Library API:

```cpp
int TIGER::resetOrientation(std::vector<std::vector<double>> &point_list, std::vector<std::vector<int>> &facet_list, std::vector<int> &blockMark);
```

Input your points with ```point_list``` and triangles with ```facet_list```, all facets will be reset normal direction to fit right hand rule including non-manifold face. The normals of the triangular face mesh all point to the outside.

If you need to build an executable program, you can modify the CMakeLists.txt, turn on the option "BUILD_EXECUTABLE".

The usage of executable is

```
MeshOrient INPUT.vtk
```

