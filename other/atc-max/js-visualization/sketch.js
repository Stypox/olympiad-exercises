p5.disableFriendlyErrors = true;

var canvasWidth = 1200;
var canvasHeight = 800;
var N = 8;
var squareSize = Math.min(canvasWidth, canvasHeight)/N;

var grid;

function setup() {
	window.canvas = createCanvas(canvasWidth,canvasHeight)
	grid = new Grid(N);
}

function draw() {
	background(0,0,0,0);
	if(mouseIsPressed)
		grid.click(mouseX, mouseY);
	grid.show();
}

function keyHeld() {
	switch(key) {
		case 'z':
		case 'Z':
			if(keyIsDown(CONTROL)) {
				grid.undo();
			}
			break;
	}
}

function keyPressed() {
	switch(key) {
		case 'z':
		case 'Z':
			if(keyIsDown(CONTROL)) {
				grid.undo();
			}
			break;
	}
}