#include "ImguiUtils.h"
#include "Imgui/imgui.h"

void ImguiUtils::DrawMatrix()
{
    const int COLUMNS_COUNT = 3;
    if (ImGui::BeginTable("##table1", COLUMNS_COUNT, ImGuiTableFlags_Borders | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable))
    {
        ImGui::TableSetupColumn("Apricot");
        ImGui::TableSetupColumn("Banana");
        ImGui::TableSetupColumn("Cherry");

        // Dummy entire-column selection storage
        // FIXME: It would be nice to actually demonstrate full-featured selection using those checkbox.
        static bool column_selected[3] = {};

        // Instead of calling TableHeadersRow() we'll submit custom headers ourselves
        ImGui::TableNextRow(ImGuiTableRowFlags_Headers);
        for (int column = 0; column < COLUMNS_COUNT; column++)
        {
            ImGui::TableSetColumnIndex(column);
            const char* column_name = ImGui::TableGetColumnName(column); // Retrieve name passed to TableSetupColumn()
            ImGui::PushID(column);
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
            ImGui::Checkbox("##checkall", &column_selected[column]);
            ImGui::PopStyleVar();
            ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
            ImGui::TableHeader(column_name);
            ImGui::PopID();
        }

        for (int row = 0; row < 5; row++)
        {
            ImGui::TableNextRow();
            for (int column = 0; column < 3; column++)
            {
                char buf[32];
                //sprintf(buf, "Cell %d,%d", column, row);
                ImGui::TableSetColumnIndex(column);
                ImGui::Selectable(buf, column_selected[column]);
            }
        }
        ImGui::EndTable();
    }
}
