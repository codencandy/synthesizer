#include <Metal/Metal.h>
#include <MetalKit/MetalKit.h>

#include "CNC_Types.h"
#include <imgui.h>
#include <imgui_impl_metal.h>
#include <imgui_impl_osx.h>

void CheckError( NSError* error )
{
    if( error != NULL )
    {
        NSLog( @"%@", [error localizedDescription] );
    }
}

@interface Renderer : NSObject< MTKViewDelegate >
{
    @public
        MTKView*              m_view;

        id< MTLDevice >              m_device;
        id< MTLCommandQueue >        m_queue;
        id< MTLRenderPipelineState > m_pipelineState;
}

- (void)LoadShaders;
- (void)Render;

@end

@implementation Renderer

- (void)LoadShaders;
{
    @autoreleasepool
    {
        NSError* error = NULL;
        NSString* shaderSource = [NSString stringWithContentsOfFile: @"CNC_Shader.metal"
                                                           encoding: NSUTF8StringEncoding 
                                                              error: &error];

        CheckError( error );                                                              

        MTLCompileOptions* options = [MTLCompileOptions new];
        id< MTLLibrary > library = [m_device newLibraryWithSource: shaderSource 
                                                          options: options 
                                                            error: &error];

        CheckError( error );

        id< MTLFunction > vertexShader   = [library newFunctionWithName: @"VertexShader" ];
        id< MTLFunction > fragmentShader = [library newFunctionWithName: @"FragmentShader" ];                                

        if( vertexShader == NULL ) NSLog( @"error compiling the vertex shader" );
        if( fragmentShader == NULL ) NSLog( @"error compiling the fragment shader" );

        MTLVertexDescriptor* vertexDesc = [MTLVertexDescriptor new];
        vertexDesc.attributes[0].bufferIndex = 0;
        vertexDesc.attributes[0].offset      = offsetof( struct VertexInput, m_position );
        vertexDesc.attributes[0].format      = MTLVertexFormatFloat3;
        vertexDesc.layouts[0].stepFunction   = MTLVertexStepFunctionPerVertex;
        vertexDesc.layouts[0].stride         = sizeof( struct VertexInput );

        MTLRenderPipelineDescriptor* renderDesc = [MTLRenderPipelineDescriptor new];
        renderDesc.vertexDescriptor = vertexDesc;
        renderDesc.vertexFunction   = vertexShader;
        renderDesc.fragmentFunction = fragmentShader;
        renderDesc.colorAttachments[0].pixelFormat = [m_view colorPixelFormat];

        m_pipelineState = [m_device newRenderPipelineStateWithDescriptor: renderDesc
                                                                   error: &error];

        CheckError( error );                                                                   
    }
}

- (void)Render
{
    [m_view draw];
}

- (void)drawInMTKView:(nonnull MTKView *)view
{
    @autoreleasepool
    {
        id< MTLCommandBuffer >        commandBuffer  = [m_queue commandBuffer];
        id< MTLRenderCommandEncoder > commandEncoder = [commandBuffer renderCommandEncoderWithDescriptor: [m_view currentRenderPassDescriptor]];

        [commandEncoder setRenderPipelineState: m_pipelineState];

        // render the ui on top of the scene
        ImGui::Render();
        ImGui_ImplMetal_RenderDrawData( ImGui::GetDrawData(), commandBuffer, commandEncoder);

        [commandEncoder endEncoding];
        [commandBuffer presentDrawable: [m_view currentDrawable]];
        [commandBuffer commit];
    }
}

- (void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size
{

}

@end

Renderer* CreateRenderer()
{
    Renderer* renderer = [Renderer new];

    CGRect contentRect = CGRectMake( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT );

    renderer->m_device = MTLCreateSystemDefaultDevice();
    renderer->m_view   = [[MTKView alloc] initWithFrame:contentRect device: renderer->m_device];
    renderer->m_queue  = [renderer->m_device newCommandQueue];
    
    [renderer->m_view setDelegate: renderer];
    [renderer->m_view setClearColor: MTLClearColorMake( 0.2f, 0.2f, 0.2f, 1.0f)];
    [renderer->m_view setNeedsDisplay: false];
    [renderer->m_view setPaused: true];

    [renderer LoadShaders];

    // IMGUI SETUP
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

        // Setup Renderer backend
    ImGui_ImplMetal_Init(renderer->m_device);
    ImGui_ImplOSX_Init(renderer->m_view);

    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize.x = renderer->m_view.bounds.size.width;
    io.DisplaySize.y = renderer->m_view.bounds.size.height;

    CGFloat framebufferScale = renderer->m_view.window.screen.backingScaleFactor ?: NSScreen.mainScreen.backingScaleFactor;
    io.DisplayFramebufferScale = ImVec2(framebufferScale, framebufferScale);

    return renderer;
}
