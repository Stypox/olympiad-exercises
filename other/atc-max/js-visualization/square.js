class Square {
	constructor(x,y) {
		this.x = x;
		this.y = y;
		this.special = false;
		this.connected = false;
		this.pending = false;
	}

	show() {
		let connections = grid.getConnections(this.x,this.y).length;
		if(this.special)
			fill(255, 215, 0);
		else if(this.pending)
			fill(255,50,50);
		else if(connections==1)
			fill(50, 150, 150);
		else if(connections==2)
			fill(100, 255, 100);
		else
			fill(50, 50, 150);

		rect(this.x*squareSize, this.y*squareSize, squareSize, squareSize);
	}

	setSpecial() {
		this.special = true;
	}
	setPending(val) {
		this.pending = val;
	}

	log() {
		console.log("%o", this);
	}
}