#include <AVFoundation/AVFoundation.h>
#include "CNC_Types.h"

@interface AudioRenderer : NSObject
{
    @public
        AVAudioEngine*               m_audioEngine;
        AVAudioNode*                 m_output;
        AVAudioFormat*               m_audioFormat;
        AVAudioMixerNode*            m_mainMixerNode;
        AVAudioSourceNode*           m_srcNode;
        AVAudioSourceNodeRenderBlock m_callback;

        u32                          m_numberOfChannels;
        u32                          m_sampleRate;
        f32                          m_amplitude;

        void*                        m_applicationContext;
}

- (void)play;
- (void)stop;

@end

@implementation AudioRenderer

- (void)printSoundSettings: (AVAudioFormat*)format
{
    switch( format.commonFormat )
    {
        case AVAudioPCMFormatFloat32: NSLog( @"sample format: float" );  break;
        case AVAudioPCMFormatFloat64: NSLog( @"sample format: double" ); break;
        case AVAudioPCMFormatInt16:   NSLog( @"sample format: short" );  break;
        case AVAudioPCMFormatInt32:   NSLog( @"sample format: int" );    break;
        default: break;
    }   

    NSLog( @"number of channels: %d", format.channelCount );
    NSLog( @"interleaved: %@", format.interleaved ? @"YES" : @"NO" );
    NSLog( @"sampleRate: %d", m_sampleRate );
}

- (id)init
{
    if( self = [super init] )
    {
        m_callback = ^OSStatus( BOOL*                 isSilence, 
                                const AudioTimeStamp* timestamp, 
                                AVAudioFrameCount     framecount, 
                                AudioBufferList*      outputData )
        {
            
            struct SoundBuffer buffer = {0};
            buffer.m_numberOfSamples  = framecount;
            buffer.m_numberOfChannels = outputData->mNumberBuffers;
            buffer.m_bufferTime       = timestamp->mSampleTime / m_sampleRate;

            for( u32 i=0; i<buffer.m_numberOfChannels; ++i )
            {
                buffer.m_buffer[i] = outputData->mBuffers[i].mData;
            }

            RenderSound( &buffer, m_applicationContext );

            return noErr;
        };

        m_audioEngine   = [AVAudioEngine new];
        m_mainMixerNode = m_audioEngine.mainMixerNode;
        m_output        = m_audioEngine.outputNode;
        m_audioFormat   = [[AVAudioFormat alloc] initStandardFormatWithSampleRate: 44100.0 channels: 2];
        m_srcNode       = [[AVAudioSourceNode alloc] initWithRenderBlock: m_callback];                                          

        [m_audioEngine attachNode: m_srcNode];
        [m_audioEngine connect: m_srcNode       to: m_mainMixerNode format: m_audioFormat];
        [m_audioEngine connect: m_mainMixerNode to: m_output        format: m_audioFormat];

        m_numberOfChannels = m_audioFormat.channelCount;
        m_sampleRate       = m_audioFormat.sampleRate;
        m_amplitude        = 0.5f;

        m_mainMixerNode.outputVolume = m_amplitude;

        [self printSoundSettings: m_audioFormat];
    }

    return self;
}

- (void)play
{   
    NSError* error = NULL;

    if( [m_audioEngine startAndReturnError:&error] == NO )
    {
        // something went wrong while starting the engine
        NSLog( @"Couldn't start the audio" );
    }
}

- (void)stop
{
    [m_audioEngine stop];
}

@end

AudioRenderer* CreateAudio( void* app )
{
    AudioRenderer* audio = [AudioRenderer new];
    audio->m_applicationContext = app;

    return audio;
}

void StartPlayer( void* audio )
{
    AudioRenderer* audioEngine = (AudioRenderer*)audio;
    [audioEngine play];
}

void StopPlayer( void* audio )
{
    AudioRenderer* audioEngine = (AudioRenderer*)audio;
    [audioEngine stop];
}
