# Psynth
The precise synthesizer or the parallel synthesizer is a project using the
polyglot coordination language Lingua Franca to build a software synthesizer in
C targeting Linux systems. I am currently using the PulseAudio libraries for
generating sound. This project is for my own educational purposes, I want to
learn more about audio synthesis, waveforms, sound engineering etc. The ultimate
goal of this project is to build a physical instrument.


## Getting started
1. Install the Lingua Franca compiler: 
`curl -Ls https://install.lf-lang.org | bash -s cli`
2. Install the pulsaudio libraries: 
`sudo apt install libpulse-dev`
3. Pull down KISSFFT submodule:
`git submodule update --init`
4. Compile libkissfft:
```
cd external/kissfft
make KISSFFT_STATIC=1 all
```
4. Compile and run
```
lfc src/Main.lf
bin/Main
```

## Input
The synth accepts MIDI commands and should work with a MIDI controller that is
connected to the computer showing up as `/dev/midi1` or `/dev/midi2`. There is
also a bad keyboard interface. Here you must press once to generate a NOTE_ON
command and press again to generate a NOTE_OFF command. It turns out that it 
is quite hard to detect key press and key release.

## Debug the waveform
There is a `Print` reactor that dumps the waveform to a CSV file and generates
a gnuplot script. Just instantiate a Print reactor and connect it to a stream 
of samples. After running the program do:
```
gnuplot *.gp
```
to run gnuplot which should generate a PDF with the waveform.


## Todo
- [x] Add an amplitude envelope to avoid the ugly ticking audio
- [x] Add multiple waveform generators (currently we only have a sinusoidal oscillator)
- [x] Add multiple lanes so that we can do polysynths
- [x] Add a browser-based UI
- [x] Add FFT/inverse FFT reactor to enable simple filtering
- [x] There is something wrong with the sine oscillator. With poly0-synth it is all weird. It is also very low in volume compared to a triangle
- [x] Support program change MIDI commands
- [ ] Support control change MIDI commands for ADSR amplitude envelope
- [ ] Add a compressor, currently scaling down each lane if multiple lanes active
- [ ] Add a simple low-pass filter
- [ ] Interface an actual MIDI device
- [ ] Stereo audio. (Currently, we are just doing MONO)

## The frequency domain
I am using KISSFFT to transform the audio signal into the frequency domain where
we can implement interesting filters. 

## References:
- [Syndig](https://github.com/mmitch/syndig) an excellent software synthesizer 
written in C by Christian Garbs
