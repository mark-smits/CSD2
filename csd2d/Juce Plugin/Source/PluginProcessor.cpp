/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <JuceHeader.h>

//==============================================================================
MyFirstProjectAudioProcessor::MyFirstProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    synth.setSamplerate(48000);
}

MyFirstProjectAudioProcessor::~MyFirstProjectAudioProcessor()
{
}

//==============================================================================
const juce::String MyFirstProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MyFirstProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MyFirstProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MyFirstProjectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MyFirstProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MyFirstProjectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MyFirstProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MyFirstProjectAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MyFirstProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void MyFirstProjectAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MyFirstProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    synth.prepareToPlay(sampleRate);
}

void MyFirstProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MyFirstProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void MyFirstProjectAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
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

    // Plugin MIDI handling guts

    int time;
    juce::MidiMessage m;
    for (juce::MidiBuffer::Iterator i(midiMessages); i.getNextEvent(m, time);)
    {
        if (m.isNoteOn()) {
            synth.receiveNoteOn(m.getNoteNumber());
        }
        else if (m.isNoteOff()) {
            synth.receiveNoteOff(m.getNoteNumber());
        }
    }

    // Plugin audio processing guts

    auto* channel1Data = buffer.getWritePointer(0);
    auto* channel2Data = buffer.getWritePointer(1);

    for (int sample = 0; sample < buffer.getNumSamples(); sample++)
    {
        synth.tick();
        channel1Data[sample] = synth.getVal();
        channel2Data[sample] = synth.getVal();
    }
}

//==============================================================================
bool MyFirstProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MyFirstProjectAudioProcessor::createEditor()
{
    return new MyFirstProjectAudioProcessorEditor (*this);
}

//==============================================================================
void MyFirstProjectAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MyFirstProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MyFirstProjectAudioProcessor();
}

void MyFirstProjectAudioProcessor::setAmp(double amp_in)
{
    synth.setAmp(amp_in);
}

void MyFirstProjectAudioProcessor::setAttack(float attack) {
    synth.setAttack(attack);
}

void MyFirstProjectAudioProcessor::setDecay(float decay) {
    synth.setDecay(decay);
}

void MyFirstProjectAudioProcessor::setSustain(float sustain) {
    synth.setSustain(sustain);
}

void MyFirstProjectAudioProcessor::setRelease(float release) {
    synth.setRelease(release);
}


void MyFirstProjectAudioProcessor::setEvenAmp(double amp_in) {
    synth.setEvenAmp(amp_in);
}

void MyFirstProjectAudioProcessor::setEvenPartials(int num_in) {
    synth.setEvenPartials(num_in);
}

void MyFirstProjectAudioProcessor::setOddAmp(double amp_in) {
    synth.setOddAmp(amp_in);
}

void MyFirstProjectAudioProcessor::setOddPartials(int num_in) {
    synth.setOddPartials(num_in);
}


void MyFirstProjectAudioProcessor::setCluster1Amp(double amp_in) {
    synth.setCluster1Amp(amp_in);
}

void MyFirstProjectAudioProcessor::setCluster1Partials(int num_in) {
    synth.setCluster1Partials(num_in);
}

void MyFirstProjectAudioProcessor::setCluster1Ratio(float rat_in) {
    synth.setCluster1Ratio(rat_in);
}

void MyFirstProjectAudioProcessor::setCluster1FreqMult(float freq_in) {
    synth.setCluster1FreqMult(freq_in);
}


void MyFirstProjectAudioProcessor::setCluster2Amp(double amp_in) {
    synth.setCluster2Amp(amp_in);
}

void MyFirstProjectAudioProcessor::setCluster2Partials(int num_in) {
    synth.setCluster2Partials(num_in);
}

void MyFirstProjectAudioProcessor::setCluster2Ratio(float rat_in) {
    synth.setCluster2Ratio(rat_in);
}

void MyFirstProjectAudioProcessor::setCluster2FreqMult(float freq_in) {
    synth.setCluster2FreqMult(freq_in);
}


void MyFirstProjectAudioProcessor::setCluster3Amp(double amp_in) {
    synth.setCluster3Amp(amp_in);
}

void MyFirstProjectAudioProcessor::setCluster3Partials(int num_in) {
    synth.setCluster3Partials(num_in);
}

void MyFirstProjectAudioProcessor::setCluster3Ratio(float rat_in) {
    synth.setCluster3Ratio(rat_in);
}

void MyFirstProjectAudioProcessor::setCluster3FreqMult(float freq_in) {
    synth.setCluster3FreqMult(freq_in);
}
