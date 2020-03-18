/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MicroFreakEditorAudioProcessor::MicroFreakEditorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), startTime (Time::getMillisecondCounterHiRes() * 0.001)
#endif
{
}

MicroFreakEditorAudioProcessor::~MicroFreakEditorAudioProcessor()
{
}

//==============================================================================
const String MicroFreakEditorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MicroFreakEditorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MicroFreakEditorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MicroFreakEditorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MicroFreakEditorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MicroFreakEditorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MicroFreakEditorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MicroFreakEditorAudioProcessor::setCurrentProgram (int index)
{
}

const String MicroFreakEditorAudioProcessor::getProgramName (int index)
{
    return {};
}

void MicroFreakEditorAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MicroFreakEditorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void MicroFreakEditorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MicroFreakEditorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MicroFreakEditorAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    buffer.clear();
    int time;
    MidiMessage m;
    MidiBuffer processedMidi;
    
    // Handles new INCOMING midi messages.
    for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
    {
        std::cout<<"Receiving Midi"<<"\r\n";
        if(m.isController()){
            sliderListeners.call ([=] (SliderListener& l){
                l.handleNewSliderValue(m.getControllerNumber(), m.getControllerValue());
            });
        }
    }
    
    
     //Handles new OUTGOING midi messages.
     if(!midiOutputMessages.isEmpty())
     {
         std::cout<<"Sending Midi"<<"\r\n";
         midiMessages.swapWith(midiOutputMessages);
         midiOutputMessages.clear();
     }

}

//==============================================================================
bool MicroFreakEditorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MicroFreakEditorAudioProcessor::createEditor()
{
    return new MicroFreakEditorAudioProcessorEditor (*this);
}

//==============================================================================
void MicroFreakEditorAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MicroFreakEditorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MicroFreakEditorAudioProcessor();
}

void MicroFreakEditorAudioProcessor::guiUpdate(double value)
{
    auto message = MidiMessage::controllerEvent(6, 23, value);
    addMessageToBuffer(message);
}

void MicroFreakEditorAudioProcessor::addMessageToBuffer (const MidiMessage& message)
{
    auto timestamp = message.getTimeStamp();
    auto sampleNumber =  (int) (timestamp * sampleRate);
    midiOutputMessages.addEvent (message, sampleNumber);
}

