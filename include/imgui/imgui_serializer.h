#ifndef IMGUI_SERIALIZER_H
#define IMGUI_SERIALIZER_H

namespace ImGui
{
    bool SaveStyle(const char* filename, const ImGuiStyle& style, int style_color);
    bool LoadStyle(const char* filename, ImGuiStyle& style, int& style_color);
}

#endif // IMGUI_SERIALIZER_H  