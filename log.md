# Dec 3
- I have fixed errors in: ADSR, Compressor and Oscillator and most of the long-standing problems are gone.
- One issue left. When I hit multple keys it still has glitching. I have tried the following:
1. Max thread priority for the threads
2. Buffer up lots of data in sound output and JUST outputting it directly
None had any impact. This leads me to believe that the error is in the samples that I have generated. I must closely
look at my oscillator implementation etc to see if I can spot the error

# Nov 26
- I found that increasing the priority of my threads does improve the functioning of this program.
- Found another race condition in the token-handling logic...
- It seems actually, that my problems with "clipping" and whatnot is not caused by the amplitude, but wierd jumps in the
outputted signal. This might actually be bugs in my ADSR envelope. Interesting. Will have to take a look at that soon.

# Nov 25
- Found the mem error. It was due to a data race in the runtime. 
- I am seeing occasionally a very hard-to-reproduce error where we have an event with tag NEVER being dequeued when we
are about to shutdown...
- I am still seeing some memory issues I think, because occasionally, we end up running out of buffers for my custom allocator...
- Also non-deterministically getting: `FATAL ERROR: midi_parser: buf_idx=3`at startup. Some faulty messages in the buffer somehow
- A first stab at a very simple filter. But it doesnt really work. I have to read more up on audio processing:
1. How should i interpret the FFT output. It is an array of complex numbers what is the real and imaginary part of each number? 
What is the interpretation of the index o each number. I think that is the frequency?
2. How should such filter 


# Nov 24
- Something is off. We get many many unfreed messages. They do not seem to be from my buffer code. But where else? It is either the buffers, or it is the physical action. But it only appears when we have multiple lanes (that is a big hint) also only appears when I am pressing multiple keys together. 
- These hints seems to point in different direction. Is it the physical action or my token stuff that is at fault?
- I think the way to debug this is to look at log messages and just trace out if there is a one-to-one mapping here. I am pretty sure it is the 

# Nov 23
- I was not able to get the Compressor properly working. And their are some isses:
- I get NET with -1234567 tag
- I get reaction returned with status 1
- Seems to happen when I blast the keyboard with stuff. Maybe race-condition in the Physical Action? Pull nightly to check.

# Nov 22
- There is some memory/token issues. I should add some better catching of these memory errors....

# Nov 21
- Fix some nasty C bugs. The MIDI parsing FSM is a little messy due to this fallthrough optimization that my MIDI keyboard is doing
- Next up: Add a compressor and parse velocity

# Nov 5
- TODO: Add some printing of the buffer alloc/dealloc there seems to be some 
leak? I suddenly get leakage.... why how what?
- Fix FSM for parsing the MIDI

# Nov 4
- Some wierd errors now. Why isnt anything printed? And wierd time issues. Seems like mem faults?