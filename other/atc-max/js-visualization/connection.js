var Orientation = {
	vertical: 0,
	horizontal: 1,
}

class Connection {
	constructor(xa,ya,xb,yb) {
		this.xa = xa;
		this.ya = ya;
		this.xb = xb;
		this.yb = yb;
	}

	show() {
		line((this.xa+0.5)*squareSize, (this.ya+0.5)*squareSize, (this.xb+0.5)*squareSize, (this.yb+0.5)*squareSize);
	}

	contains(x,y) {
		return (this.xa==x && this.ya==y) || (this.xb==x && this.yb==y);
	}

	orientation() {
		if (this.xa == this.xb)
			return Orientation.horizontal;
		else if (this.ya == this.yb)
			return Orientation.vertical;
	}
}