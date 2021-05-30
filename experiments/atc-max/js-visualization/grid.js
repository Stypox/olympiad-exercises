class Grid {
	constructor(N) {
		this.N = N;

		this.squares = [];
		for (let c = 0; c < N; c++) {
			this.squares[c] = []
			for (let r = 0; r < N; r++) {
				this.squares[c][r] = new Square(c,r);
			}
		}

		this.squares[0][0].setSpecial();
		this.squares[N-1][N-1].setSpecial();

		this.connections = [];
		this.firstClick = true;
		this.xLast;
		this.yLast;
	}

	async show() {
		this.squares.forEach(subArr => {
			subArr.forEach(square => {
				square.show();
			});
		});
		this.connections.forEach(connection => {
			connection.show();
		});

		let corners = this.countCorners();
		fill(0,0,0);
		rect(this.N*squareSize, (this.N-2)/2*squareSize, (1.1 + Math.log10(corners+1)*0.6)*squareSize, 2*squareSize);
		fill(255,255,255);
		textSize(squareSize*5/6);
		text(corners, (this.N+0.3)*squareSize, (this.N/2+0.3)*squareSize);
	}

	getConnections(x,y) {
		let conns = [];
		this.connections.forEach(connection => {
			if (connection.contains(x,y))
				conns.push(connection);
		});
		return conns;
	}

	canConnect(x,y) {
		if(x<0 || x>=this.N || y<0 || y>=this.N)
			return false;
		
		if((x==0 && y==0) || (x==this.N-1 && y==this.N-1))
			return this.getConnections(x,y).length < 1;
		else
			return this.getConnections(x,y).length < 2;
	}

	connectionExists(xa,ya,xb,yb) {
		let exists = false;
		this.connections.forEach(connection => {
			if (connection.contains(xa,ya) && connection.contains(xb,yb))
				exists = true;
		});
		return exists;
	}

	hasCorner(x,y) {
		let conns = this.getConnections(x,y);
		if(conns.length < 2)
			return false;
		
		return conns[0].orientation() != conns[1].orientation();
	}

	countCorners() {
		let corners = 0;
		for (let x = 0; x < this.N; x++) {
			for (let y = 0; y < this.N; y++) {
				corners += this.hasCorner(x,y);
			}
		}
		return corners;
	}

	click(xm,ym) {
		let x = floor(xm/squareSize);
		let y = floor(ym/squareSize);

		if(this.firstClick) {
			if (this.canConnect(x,y)) {
				this.firstClick = false;
				this.xLast = x;
				this.yLast = y;
				this.squares[x][y].setPending(true);
			}
		}
		else {
			this.firstClick = true;
			this.squares[this.xLast][this.yLast].setPending(false);
			if (Math.abs(this.xLast - x) + Math.abs(this.yLast - y) == 1) {
				if (this.canConnect(x,y) && !this.connectionExists(x,y,this.xLast, this.yLast)) {
					this.connections.push(new Connection(this.xLast, this.yLast, x, y));

					// check again after connection
					if (this.canConnect(x,y)) {
						this.firstClick = false;
						this.xLast = x;
						this.yLast = y;
						this.squares[x][y].setPending(true);
					}
				}				
			}
			else {
				if (this.canConnect(x,y)) {
					this.firstClick = false;
					this.xLast = x;
					this.yLast = y;
					this.squares[x][y].setPending(true);
				}
			}
		}
	}
	undo() {
		if(this.connections.length) {
			this.connections.splice(this.connections.length-1, 1);
		}
	}

	log(x,y) {
		if (x>=0 && x<this.N && y>=0 && y<this.N) {
			this.squares[x][y].log();
		}
	}
}