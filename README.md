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
3. Compile libkissfft:
```
cd src/lib/kissfft
make KISSFFT_STATIC=1 KISSFFT_DATATYPE=double all
```
4. Compile and run
```
lfc src/Main.lf
bin/Main
```

## Todo
- [x] Add an amplitude envelope to avoid the ugly ticking audio
- [x] Add multiple waveform generators (currently we only have a sinusoidal oscillator)
- [x] Add multiple lanes so that we can do polysynths
- [x] Add a browser-based UI
- [x] Add FFT/inverse FFT reactor to enable simple filtering
- [x] There is something wrong with the sine oscillator. With poly0-synth it is all wierd. It is also veyr low in volume compared to tringale
- [x] Support program change MIDI commands
- [ ] Support control change MIDI commands for ADSR amplitude envelope
- [ ] Add a compressor, currently scaling down each lane if multiple lanes active
- [ ] Add a simple low-pass filter
- [ ] Interface an actual MIDI device
- [ ] Stereo audio. (Currently, we are just doing MONO)


## References:
- [Syndig](https://github.com/mmitch/syndig) an excellent software synthesizer 
written in C by Christian Garbs
