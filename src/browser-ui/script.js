let socket;
let waveform = [];

function setup() {
    createCanvas(windowWidth, windowHeight);
    background(220);

    const socket = new WebSocket('ws://localhost:8000', 'ws');
    socket.binaryType = 'arraybuffer';

    socket.onmessage = function(event) {
        waveform = Array.from(new Float32Array(event.data));
    };
}

function draw() {
    background(220);

    stroke(50); // Color of waveform
    noFill();
    beginShape();
    for (let i = 0; i < waveform.length; i++) {
        let x = map(i, 0, waveform.length, 0, width);
        let y = map(waveform[i], -1, 1, height, 0); // Assuming values range from -1 to 1
        vertex(x, y);
    }
    endShape();
}

function windowResized() {
    resizeCanvas(windowWidth, windowHeight);
}