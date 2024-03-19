#include <AppKit/AppKit.h>

#include "CNC_Types.h"
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

    MainWindow* window = CreateMainWindow( &running );

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
        }
    }

    return 0;
}