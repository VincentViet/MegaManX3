#define _CRT_SECURE_NO_WARNINGS

#include <imgui/imgui_impl_dx9.h>
#include <imgui/imgui_impl_win32.h>
#include <imgui/imgui_internal.h>
#include "debug.h"
#include "window.h"
#include "render.h"
#include <physics/draw.h>

#ifdef _WIN32
#define IM_NEWLINE "\r\n"
#else
#define IM_NEWLINE "\n"
#endif


static ImVec4 g_clear_color = ImVec4{ 0.45f, 0.55f, 0.60f, 1.0f };
static bool g_debug_open = true;

static Window* g_window = nullptr;
static Renderer* g_renderer = nullptr;
static ImGuiContext* g_context = nullptr;
static ImGuiIO g_io;

bool Debug::debug_mode = DEBUG_MODE;
float32 Debug::delta_time = 0.0f;
float32 Debug::total_time = 0.0f;
uint64 Debug::clear_color = COLOR_ARGB(
	static_cast<uint64>(g_clear_color.w * 255),
	static_cast<uint64>(g_clear_color.x * 255),
	static_cast<uint64>(g_clear_color.y * 255),
	static_cast<uint64>(g_clear_color.z * 255));

struct RectDraw
{
	ImVec2	tl;
	ImVec2	br;
	ImU32	color{};
};

static ImVector<RectDraw> g_rects;

//DebugWindow
static ImGuiTextFilter		g_filter;
static ImGuiTextBuffer		g_buffer;
static ImVector<int>		g_line_offsets;
static bool					g_scroll_to_bottom;

class MyDebugDraw : public b2Draw
{
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) override;
	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) override;
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;
	void DrawTransform(const b2Transform& xf) override;
	void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) override;
};

static MyDebugDraw* g_debug_draw = new MyDebugDraw;
void* Debug::debug_draw = g_debug_draw;

static void ClearLog()
{
	g_buffer.clear();
	g_line_offsets.clear();
}

static void ShowDebugWindow()
{
	if (g_debug_open)
	{
		if (ImGui::Begin("Debug", &g_debug_open))
		{
			ImGui::ColorEdit4("Clear Color", reinterpret_cast<float*>(&g_clear_color));
			ImGui::Checkbox("Debug Mode", &Debug::debug_mode);
			if (ImGui::Button("Clear")) ClearLog();
			ImGui::SameLine();
			const auto copy = ImGui::Button("Copy");
			ImGui::SameLine();
			g_filter.Draw("Filter", -100.0f);
			ImGui::Separator();
			ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
			if (copy) ImGui::LogToClipboard();

			if (g_filter.IsActive())
			{
				const auto buf_begin = g_buffer.begin();
				auto line = buf_begin;
				for (auto line_no = 0; line != nullptr; line_no++)
				{
					const auto line_end = (line_no < g_line_offsets.Size) ? buf_begin + g_line_offsets[line_no] : nullptr;
					if (g_filter.PassFilter(line, line_end))
						ImGui::TextUnformatted(line, line_end);
					line = line_end && line_end[1] ? line_end + 1 : nullptr;
				}
			}
			else
			{
				ImGui::TextUnformatted(g_buffer.begin());
			}

			if (g_scroll_to_bottom)
				ImGui::SetScrollHereY(1.0f);
			g_scroll_to_bottom = false;
			ImGui::EndChild();
		}
		ImGui::End();
	}
}

void MyDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	static Vec2 tl;
	static Vec2 br;

	for (auto i = 0; i < vertexCount; i += 4)
	{
		tl = vertices[0];
		br = vertices[2];
		g_rects.push_back(RectDraw{
			ImVec2{tl.x, tl.y},
			ImVec2{br.x, br.y},
			IM_COL32(color.r * 255, color.g * 255, color.b * 255, color.a * 255)
		});
	}
}

void MyDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	static Vec2 tl;
	static Vec2 br;

	for (auto i = 0; i < vertexCount; i += 4)
	{
		tl = vertices[0];
		br = vertices[2];
		g_rects.push_back(RectDraw{
			ImVec2{tl.x, tl.y},
			ImVec2{br.x, br.y},
			IM_COL32(color.r * 255, color.g * 255, color.b * 255, color.a * 255)
		});
	}
}

void MyDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{}

void MyDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{}

void MyDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{}

void MyDebugDraw::DrawTransform(const b2Transform& xf)
{}

void MyDebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{}

void Debug::Log(const char* fmt, ...)
{
	auto old_size = g_buffer.size();
	va_list args;
	va_start(args, fmt);
	g_buffer.appendfv(fmt, args);
	va_end(args);
	for (const auto new_size = g_buffer.size(); old_size < new_size; old_size++)
		if (g_buffer[old_size] == '\n')
			g_line_offsets.push_back(old_size);
	g_scroll_to_bottom = true;
}

void azorRenderDebug()
{
	static RectDraw* rect;

	if (g_context)
	{
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		for (auto i = 0; i < g_rects.Size; i++)
		{
			rect = &g_rects[i];
			g_context->OverlayDrawList.AddRect(
				rect->tl,
				rect->br,
				rect->color);
		}
		g_rects.clear();
		ShowDebugWindow();

		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		Debug::delta_time = g_io.DeltaTime;
		Debug::total_time += g_io.DeltaTime;
		Debug::clear_color = COLOR_ARGB(
			static_cast<uint64>(g_clear_color.w * 255),
			static_cast<uint64>(g_clear_color.x * 255),
			static_cast<uint64>(g_clear_color.y * 255),
			static_cast<uint64>(g_clear_color.z * 255));

	}
	else
	{
		IMGUI_CHECKVERSION();
		g_context = ImGui::CreateContext();
		g_io = ImGui::GetIO();
		(void)g_io;

		g_window = azorGetWindow();
		g_renderer = azorGetRenderer();
		const auto hwnd = static_cast<HWND>(g_window->handler);
		const auto device9 = static_cast<IDirect3DDevice9*>(g_renderer->device9);
		ImGui_ImplWin32_Init(hwnd);
		ImGui_ImplDX9_Init(device9);

		// g_debug_draw = new MyDebugDraw;
		// Debug::debug_draw = g_debug_draw;
	}
}

void azorDestroyDebug()
{
	free(Debug::debug_draw);

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext(g_context);
}
