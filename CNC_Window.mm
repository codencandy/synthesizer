#include <AppKit/AppKit.h>

@interface MainWindowDelegate : NSObject< NSWindowDelegate >
{
    @public
        bool* m_running;
}

- (instancetype)initWithBool:(bool*)running;

@end

@implementation MainWindowDelegate

- (instancetype)initWithBool:(bool*)running
{
    self = [super init];

    m_running = running;

    return self;
}

- (BOOL)windowShouldClose:(NSWindow*)sender
{
    *m_running = false;
    return true;
}
@end

@interface MainWindow : NSWindow
@end

@implementation MainWindow

- (BOOL)canBecomeKeyWindow  { return true; }
- (BOOL)canBecomeMainWindow { return true; }

@end

MainWindow* CreateMainWindow( bool* running )
{
    MainWindowDelegate* delegate = [[MainWindowDelegate alloc] initWithBool:running];
    
    NSRect contentRect = NSMakeRect( 0, 0, 800, 500 );
    MainWindow* window = [[MainWindow alloc] initWithContentRect: contentRect 
                                                       styleMask: NSWindowStyleMaskClosable | NSWindowStyleMaskTitled
                                                         backing: NSBackingStoreBuffered defer: false];

    [window setTitle: @"synthesizer by cnc" ];
    [window setDelegate: delegate];
    [window makeKeyAndOrderFront: NULL];
    
    return window;
}

