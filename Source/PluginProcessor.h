/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class MicroFreakEditorAudioProcessor  : public AudioProcessor
{
private:
    
    double startTime;
    double sampleRate = 44100.0;
    int previousSampleNumber = 0;

public:
    //==============================================================================
    MicroFreakEditorAudioProcessor();
    ~MicroFreakEditorAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    struct SliderListener
    {
        virtual ~SliderListener() {}
        virtual void handleNewSliderValue (int, double) = 0;
    };
    void addSliderListener    (SliderListener& listener) { sliderListeners.add    (&listener); }
    void removeSliderListener (SliderListener& listener) { sliderListeners.remove (&listener); }

    void guiUpdate(double value);
    void addMessageToBuffer (const MidiMessage& message);

private:
    ListenerList<SliderListener> sliderListeners;
    MidiBuffer midiOutputMessages;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MicroFreakEditorAudioProcessor)
};
