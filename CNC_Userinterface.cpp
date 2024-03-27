#include "CNC_Types.h"
#include "CNC_Application.h"
#include <imgui.h>
#include <imgui-knobs.h>

void CustomizeUi()
{
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.Fonts->AddFontFromFileTTF( "res/blender_book.ttf", 15 );

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    ImGuiStyle& myStyle = ImGui::GetStyle();
    
    // padding & spacing
    myStyle.WindowPadding     = ImVec2( 12.0f, 12.0f );
    myStyle.FramePadding      = ImVec2( 12.0f, 8.0f );
    myStyle.ItemSpacing       = ImVec2( 12.0f, 12.0f );
    myStyle.ItemInnerSpacing  = ImVec2( 4.0f, 4.0f );
    myStyle.IndentSpacing     = 21.0f;

    // borders
    myStyle.FrameBorderSize         = 0.0f;
    myStyle.WindowBorderSize        = 0.0f;
    myStyle.SeparatorTextBorderSize = 1.0f;

    // rounding
    myStyle.WindowRounding    = 6.0f;
    myStyle.FrameRounding     = 3.0f;
    myStyle.ScrollbarRounding = 9.0f;
    myStyle.GrabRounding      = 2.0f;

    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.13f, 0.13f, 0.13f, 0.70f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border]                 = ImVec4(0.35f, 0.79f, 0.81f, 0.50f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.09f, 0.10f, 0.11f, 0.54f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.17f, 0.18f, 0.20f, 0.40f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.45f, 0.45f, 0.45f, 0.67f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.09f, 0.10f, 0.11f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_CheckMark]              = ImVec4(0.23f, 0.82f, 0.72f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.88f, 0.77f, 0.24f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.88f, 0.77f, 0.24f, 1.00f);
    colors[ImGuiCol_Button]                 = ImVec4(0.08f, 0.09f, 0.08f, 0.40f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.27f, 0.28f, 0.30f, 1.00f);
    colors[ImGuiCol_Header]                 = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_Separator]              = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.23f, 0.28f, 0.35f, 0.86f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.41f, 0.44f, 0.47f, 0.80f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.39f, 0.45f, 0.52f, 1.00f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
    colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
    colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
    colors[ImGuiCol_TableBorderLight]       = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
    colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}

void ShowUserinterface( bool* showui, Application* app )
{
    Platform*    platform    = &app->m_platform;
    void*        audioEngine =  app->m_platform.m_audioService;
    Synthesizer* synth       = &app->m_synth;
    Env*         env         = &synth->m_env;

    ImGui::SetNextWindowSize(ImVec2(600,540), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos( ImVec2( 11, 11), ImGuiCond_FirstUseEver );
    
    ImGui::Begin( "SYNTHESIZER UI", showui );

    static f32 volume   =   2.0f;
    static f32 pitch    = 200.0f;
    ImGui::SeparatorText("SYNTH"); ImGui::Spacing();
    if( ImGuiKnobs::Knob( "VOLUME",   &volume, 0.0f,  100.0f,  1.0f, "%.1fdB", ImGuiKnobVariant_WiperDot ) )
    {
        changeVolume( synth, volume );
    } ImGui::SameLine();
    
    if( ImGuiKnobs::Knob( "PITCH", &pitch,  100.0f, 800.0f, 10.0f, "%.1fHz",   ImGuiKnobVariant_WiperDot ) )
    {
        changePitch( synth, &synth->m_osc, pitch );
    } ImGui::SameLine();
    
    ImGui::PlotLines("", synth->m_env.m_plotLevels, 200, 0, NULL, 3.4028235E38f, 3.4028235E38f, {300.0f, 130.0f}, 4);
    
    ImGui::SeparatorText( "ENVELOPE" );

    static f32 attack  = 0.2f; static f32 attackL  = env->m_attackLevel;
    static f32 decay   = 0.2f;  static f32 decayL   = env->m_decayLevel;
    static f32 sustain = 0.2f;
    static f32 release = 0.2f;
    if( ImGuiKnobs::Knob( "ATTACK", &attack,  0.0f, 1.0f, 0.05f, "%.2fs",   ImGuiKnobVariant_WiperDot, 0.0f, 0, 100) )
    {
        updateEnvelope( &synth->m_env, attack, decay, sustain, release, attackL, decayL );
    } 
    ImGui::SameLine();
    if( ImGuiKnobs::Knob( "DECAY", &decay,  0.0f, 1.0f, 0.05f, "%.2fs",   ImGuiKnobVariant_WiperDot, 0.0f, 0, 100 ) )
    {
        updateEnvelope( &synth->m_env, attack, decay, sustain, release, attackL, decayL );
    } 
    ImGui::SameLine();
    if( ImGuiKnobs::Knob( "SUSTAIN", &sustain,  0.0f, 1.0f, 0.05f, "%.2fs",   ImGuiKnobVariant_WiperDot, 0.0f, 0, 100 ) )
    {
        updateEnvelope( &synth->m_env, attack, decay, sustain, release, attackL, decayL );
    } 
    ImGui::SameLine();
    if( ImGuiKnobs::Knob( "RELEASE", &release,  0.0f, 1.0f, 0.05f, "%.2fs",   ImGuiKnobVariant_WiperDot, 0.0f, 0, 100 ) )
    {
        updateEnvelope( &synth->m_env, attack, decay, sustain, release, attackL, decayL );
    }
    ImGui::SameLine();
    if( ImGuiKnobs::Knob( "ATTACK L", &attackL,  0.0f, 1.0f, 0.05f, "%.2fdB",   ImGuiKnobVariant_WiperDot, 0.0f, 0, 100 ) )
    {
        updateEnvelope( &synth->m_env, attack, decay, sustain, release, attackL, decayL );
    }
    ImGui::SameLine();
    if( ImGuiKnobs::Knob( "DECAY L", &decayL,  0.0f, 1.0f, 0.05f, "%.2fdB",   ImGuiKnobVariant_WiperDot, 0.0f, 0, 100 ) )
    {
        updateEnvelope( &synth->m_env, attack, decay, sustain, release, attackL, decayL );
    }

    ImGui::SeparatorText( "PLAYER" );
    ImGui::Spacing();
    if( ImGui::Button( "PLAY" ) ) 
    {
        resetSynth( synth );
        platform->startPlayer( audioEngine ); 
    }
    ImGui::SameLine();
    
    if( ImGui::Button( "STOP" ) ) 
    {
        platform->stopPlayer( audioEngine );
    }

    ImGui::End();
}