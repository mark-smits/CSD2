/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SineTable.h"
#include "Phasor.h"
#include "AdditiveSynth.h"

//==============================================================================
/**
*/
class MyFirstProjectAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    MyFirstProjectAudioProcessor();
    ~MyFirstProjectAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    // my own setters and getters
    void setAmp(double amp_in);

    void setAttack(float attack);
    void setDecay(float decay);
    void setSustain(float sustain);
    void setRelease(float release);

    void setEvenAmp(double amp_in);
    void setEvenPartials(int num_in);
    void setOddAmp(double amp_in);
    void setOddPartials(int num_in);

    void setCluster1Amp(double amp_in);
    void setCluster1Partials(int num_in);
    void setCluster1Ratio(float rat_in);
    void setCluster1FreqMult(float freq_in);

    void setCluster2Amp(double amp_in);
    void setCluster2Partials(int num_in);
    void setCluster2Ratio(float rat_in);
    void setCluster2FreqMult(float freq_in);

    void setCluster3Amp(double amp_in);
    void setCluster3Partials(int num_in);
    void setCluster3Ratio(float rat_in);
    void setCluster3FreqMult(float freq_in);

private:
    //==============================================================================
    AdditiveSynth synth;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MyFirstProjectAudioProcessor)

};
