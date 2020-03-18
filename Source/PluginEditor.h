/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MicroFreakEditorAudioProcessorEditor  :   public AudioProcessorEditor,
                                                private MicroFreakEditorAudioProcessor::SliderListener,
                                                public Timer
{
public:
    MicroFreakEditorAudioProcessorEditor (MicroFreakEditorAudioProcessor&);
    ~MicroFreakEditorAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    double cutoffValue;
    bool isUpdating;
    Slider cutoffFrequency;
    Label cutoffFrequencyLabel;
    void initializeCutoffSlider();
    void handleNewSliderValue (int, double) override;



    void timerCallback() override;


    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MicroFreakEditorAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MicroFreakEditorAudioProcessorEditor)
};
