#include <AppKit/AppKit.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_impl_metal.h>
#include <imgui_impl_osx.h>

#include "CNC_Types.h"
#include "CNC_Userinterface.cpp"
#include "CNC_Application.cpp"
#include "CNC_Synth.cpp"

#include "CNC_Window.mm"
#include "CNC_Render.mm"
#include "CNC_Audio.mm"

int main()
{
    NSApplication* app = [NSApplication sharedApplication];
    [app setPresentationOptions: NSApplicationPresentationDefault];
    [app setActivationPolicy: NSApplicationActivationPolicyRegular];
    [app activateIgnoringOtherApps: true];
    [app finishLaunching];

    bool running = true;
    bool showui  = true;

    struct Application synthApp = {};
    
    MainWindow*    window   = CreateMainWindow( &running );
    Renderer*      renderer = CreateRenderer();
    AudioRenderer* audio    = CreateAudio( &synthApp );

    CustomizeUi();
    ImGuiIO& io = ImGui::GetIO();

    [window setContentView: renderer->m_view];
    
    struct Platform platform = {};
    platform.m_audioService = audio;
    platform.startPlayer    = StartPlayer;
    platform.stopPlayer     = StopPlayer;
    synthApp.m_platform     = platform;
    
    Load( &synthApp );

    while( running )
    {
        @autoreleasepool
        {
            NSEvent* event = NULL;
            do
            {
                event = [app nextEventMatchingMask: NSEventMaskAny
                                         untilDate: NULL 
                                            inMode: NSDefaultRunLoopMode 
                                           dequeue: true];

                [app sendEvent: event];
                [app updateWindows];                                           
            }
            while( event != NULL );

            [window->m_displayLinkSignal wait];

            Update( &synthApp );
            Render( &synthApp );

            // Start the Dear ImGui frame
            ImGui_ImplMetal_NewFrame( [renderer->m_view currentRenderPassDescriptor] );
            ImGui_ImplOSX_NewFrame( renderer->m_view );
            ImGui::NewFrame();     

            if( showui )
            {
                ShowUserinterface( &showui, &synthApp );
            }
            else
            {
                if( io.KeysDown[ImGuiKey_F1] )
                {
                    showui = true;
                }
            }

            // shut down 
            if( io.KeysDown[ImGuiKey_Escape] )
            {
                running = false;
            }
            
            [renderer Render];
        }
    }

    Exit( &synthApp );

    return 0;
}