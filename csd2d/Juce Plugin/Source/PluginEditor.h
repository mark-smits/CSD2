/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MyFirstProjectAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Slider::Listener
{
public:
    MyFirstProjectAudioProcessorEditor (MyFirstProjectAudioProcessor&);
    ~MyFirstProjectAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MyFirstProjectAudioProcessor& audioProcessor;

    // Dials

    juce::Slider ampDial;
    juce::Slider attackDial;
    juce::Slider decayDial;
    juce::Slider sustainDial;
    juce::Slider releaseDial;
    juce::Slider numEvenPartialsDial;
    juce::Slider evenPartialsAmpDial;
    juce::Slider numOddPartialsDial;
    juce::Slider oddPartialsAmpDial;
    juce::Slider numCluster1PartialsDial;
    juce::Slider cluster1PartialsAmpDial;
    juce::Slider cluster1FreqRatioDial;
    juce::Slider cluster1HarmRatioDial;
    juce::Slider numCluster2PartialsDial;
    juce::Slider cluster2PartialsAmpDial;
    juce::Slider cluster2FreqRatioDial;
    juce::Slider cluster2HarmRatioDial;
    juce::Slider numCluster3PartialsDial;
    juce::Slider cluster3PartialsAmpDial;
    juce::Slider cluster3FreqRatioDial;
    juce::Slider cluster3HarmRatioDial;
    
    // Labels

    juce::Label ampLabel;
    juce::Label attackLabel;
    juce::Label decayLabel;
    juce::Label sustainLabel;
    juce::Label releaseLabel;
    juce::Label numEvenPartialsLabel;
    juce::Label evenPartialsAmpLabel;
    juce::Label numOddPartialsLabel;
    juce::Label oddPartialsAmpLabel;
    juce::Label numCluster1PartialsLabel;
    juce::Label cluster1PartialsAmpLabel;
    juce::Label cluster1FreqRatioLabel;
    juce::Label cluster1HarmRatioLabel;
    juce::Label numCluster2PartialsLabel;
    juce::Label cluster2PartialsAmpLabel;
    juce::Label cluster2FreqRatioLabel;
    juce::Label cluster2HarmRatioLabel;
    juce::Label numCluster3PartialsLabel;
    juce::Label cluster3PartialsAmpLabel;
    juce::Label cluster3FreqRatioLabel;
    juce::Label cluster3HarmRatioLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyFirstProjectAudioProcessorEditor)
};
