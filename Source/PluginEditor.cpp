/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MicroFreakEditorAudioProcessorEditor::MicroFreakEditorAudioProcessorEditor (MicroFreakEditorAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    startTimer(100);
    setSize (800, 300);
    initializeCutoffSlider();
    processor.addSliderListener(*this);
}

MicroFreakEditorAudioProcessorEditor::~MicroFreakEditorAudioProcessorEditor()
{
    processor.removeSliderListener(*this);
}

//==============================================================================
void MicroFreakEditorAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void MicroFreakEditorAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto area = getLocalBounds();
    cutoffFrequency.setBounds(area
                              .withWidth(30)
                              .withHeight(getHeight()-130)
                              .withX(50)
                              .withY(120)
                              );
}

void MicroFreakEditorAudioProcessorEditor::initializeCutoffSlider()
{
    cutoffFrequencyLabel.setText ("Cutoff", dontSendNotification);
    cutoffFrequencyLabel.attachToComponent (&cutoffFrequency, true );
    cutoffFrequency.setSliderStyle(Slider::LinearBarVertical);
    cutoffFrequency.setColour(Slider::backgroundColourId, Colours::yellow);
    cutoffFrequency.setRange(0.0, 127.0);
    cutoffFrequency.setTextBoxStyle(Slider::TextBoxRight, true, 50,50);
    cutoffFrequency.setTextBoxIsEditable(false);
    cutoffFrequency.setNumDecimalPlacesToDisplay(0);
    cutoffFrequency.setValue(1.0);
    addAndMakeVisible(&cutoffFrequency);
    cutoffFrequency.onValueChange = [this]
    {
        if(!isUpdating){
            processor.guiUpdate(cutoffFrequency.getValue());
        }
    };
    
}

void MicroFreakEditorAudioProcessorEditor::handleNewSliderValue(int controlNumber, double controllerValue)
{
    // Cutoff
    if(controlNumber == 23)
    {
        isUpdating = true;
        cutoffValue = controllerValue;
    }
}


void MicroFreakEditorAudioProcessorEditor::timerCallback(){
    if(cutoffFrequency.getValue() != cutoffValue){
        cutoffFrequency.setValue(cutoffValue);
        isUpdating = false;
    }
}


