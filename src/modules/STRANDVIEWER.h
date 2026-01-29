// self-contained functions specifically devoted to the loading and manipulation of strand-meshes  
// in the imgui framework. Is this doable? Idk lol 

// each object/UI element pair has a SINGLE corresponding struct
// which contains all of the state needed to keep it running

// along with some method for modifying state (to be called within uiElements(const ImGuiIO& io))

// and another for drawing (to be called within rendering() of app thing)
