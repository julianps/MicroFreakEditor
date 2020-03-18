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
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
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
        processor.guiUpdate(cutoffValue);
    };
    
}

void MicroFreakEditorAudioProcessorEditor::handleNewSliderValue(int controlNumber, double controllerValue)
{
    std::cout<<"New incomming midi message"<<"\r\n";
    
    // Cutoff
    if(controlNumber == 23)
    {
        cutoffValue = controllerValue;
    }
}


void MicroFreakEditorAudioProcessorEditor::timerCallback(){
    if(cutoffFrequency.getValue() != cutoffValue){
        cutoffFrequency.setValue(cutoffValue);
    }
}


