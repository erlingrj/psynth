# Psynth
The precise synthesizer or the parallel synthesizer is a project using the
polyglot coordination language Lingua Franca to build a software synthesizer in
C targeting Linux systems. I am currently using the PulseAudio libraries for
generating sound. This project is for my own educational purposes, I want to
learn more about audio synthesis, waveforms, sound engineering etc. The ultimate
goal of this project is to build a physical instrument.


## Getting started
1. Install the Lingua Franca compiler: 
`curl -Ls https://install.lf-lang.org | sh -s cli`
2. Install the pulsaudio libraries: 
`sudo apt install libpulse-dev`
3. Compile and run
```
lfc src/Main.lf
bin/Main
```

## Todo
- [ ] Add an amplitude envelope to avoid the ugly ticking audio
- [ ] Add multiple lanes so that we can do polysynths
- [ ] Stereo audio. (Currently we are just doing MONO)
- [ ] Interface an actual MIDI device
- [ ] Add multiple waveforms (currently we only have a sinusoidal oscillator)



## References:
- [Syndig](https://github.com/mmitch/syndig) an excellent software synthesizer 
written in C by Christian Garbs