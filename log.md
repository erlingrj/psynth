# Nov 21
- Fix some nasty C bugs. The MIDI parsing FSM is a little messy due to this fallthrough optimization that my MIDI keyboard is doing
- Next up: Add a compressor and parse velocity

# Nov 5
- TODO: Add some printing of the buffer alloc/dealloc there seems to be some 
leak? I suddenly get leakage.... why how what?
- Fix FSM for parsing the MIDI

# Nov 4
- Some wierd errors now. Why isnt anything printed? And wierd time issues. Seems like mem faults?