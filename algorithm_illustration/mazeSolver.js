/*
This script uses right hand rule (follow right wall)
y is horizontal axis and x is vertical axis. (I fucked up)
Origin is top right.
Change the maze for test cases.
*/

/*
6/27/2017: update
- Added a UI to customize the maze
*/


var container = document.getElementById("container");
var	maze = [
	[1, 0, 1, 0, 0, 0, 0, 1, 1, 1],
	[1, 0, 1, 0, 0, 0, 0, 1, 0, 0],
	[1, 0, 1, 0, 0, 0, 0, 1, 0, 1],
	[1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
	[1, 0, 1, 0, 0, 0, 0, 0, 1, 0],
	[1, 0, 1, 0, 0, 0, 0, 0, 1, 0],
	[0, 0, 1, 0, 0, 0, 0, 0, 1, 0],
	[0, 0, 1, 0, 0, 0, 1, 1, 1, 1],
	[1, 1, 1, 0, 0, 0, 0, 0, 1, 0],
	[0, 0, 1, 0, 0, 0, 0, 0, 1, 1],
	];
var square = [];

// interface to customize the maze
for (let i = 0; i < 10; i++) {
	square.push([]);
	for (let j = 0; j < 10; j++) {
		// draw interface
		square[i].push(document.createElement("div"));
		square[i][j].className = "row-10";
		if (maze[i][j]==0) {
			square[i][j].style.background = "white";
		}
		else {
			square[i][j].style.background  = "black";
		}
		// interact - mouse click
		square[i][j].addEventListener(
		"click",
		function() {
			if (maze[i][j]==0) {
				maze[i][j] = 1;
				square[i][j].style.background = "black";
			}
			else {
				maze[i][j] = 0;
				square[i][j].style.background  = "white";
			}
		}
		)
		container.appendChild(square[i][j]);
	}
}

window.onload = function() {
	canvas = document.getElementById("canvas");
	context = canvas.getContext("2d");
	x = 0, y = 0;
	vx = 1; vy = 0; // velocity
	path = ''; // ignore this for now
	// short_path = ''; // comment out for future use
	setInterval(draw_context, 1000/2); // animate
}

function draw_context() {
	context.fillStyle = "white"; // white background
	context.fillRect(0, 0, 500, 500);
	drawPath(); // black path
	drawRobot(); // red robot
}

function drawPath() {
	context.fillStyle = "black";
	for (var i = 0; i < maze.length; i++) {
		for (var j = 0; j < maze[i].length; j++) {
			if (maze[i][j]==1) {
				context.fillRect(j*50, i*50, 50, 50);
			}
		}		
	}
}

function drawRobot() {
	context.fillStyle = "red";
	context.fillRect(50*y, 50*x, 50, 50);
	velocity = nextFrame(vx, vy); // get next frame velocity
	vx = velocity[0];
	vy = velocity[1];
	x+=vx;
	y+=vy;
}

function nextFrame(vx, vy) {
	if (vy>0) {
		if (maze[x+1]&&maze[x+1][y]) {
			vx = 1;
			vy = 0;
			path+="R";
		}
		else if (maze[x][y+1]) {
			vx = 0;
			vy = 1;
			if (maze[x-1]&&maze[x-1][y] || maze[x+1]&&maze[x+1][y]) {
				path+="S";
			}
		}
		else if (maze[x-1]&&maze[x-1][y]) {
			vx = -1;
			vy = 0;
			path+="L";
		}
		else if (maze[x][y-1]) {
			vx = 0;
			vy = -1;
			path+="U";
		}
	}
	else if (vy<0) {
		if (maze[x-1]&&maze[x-1][y]) {
			vx = -1;
			vy = 0;
			path+="R";
		}
		else if (maze[x][y-1]) {
			vx = 0;
			vy = -1;
			if (maze[x-1]&&maze[x-1][y] || maze[x+1]&&maze[x+1][y]) {
				path+="S";
			}
		}
		else if (maze[x+1]&&maze[x+1][y]) {
			vx = 1;
			vy = 0;
			path+="L";
		}
		else if (maze[x][y+1]) {
			vx = 0;
			vy = 1;
			path+="U";
		}
	}
	else if (vx>0) {
		if (maze[x][y-1]) {
			vx = 0;
			vy = -1;
			path+="R";
		}
		else if (maze[x+1]&&maze[x+1][y]) {
			vx = 1;
			vy = 0;
			if (maze[x][y-1] || maze[x][y+1]) {
				path+="S";
			}
		}
		else if (maze[x][y+1]) {
			vx = 0;
			vy = 1;
			path+="L";
		}
		else if (maze[x-1]&&maze[x-1][y]) {
			vx = -1;
			vy = 0;
			path+="U";
		}
	}
	else if (vx<0) {
		if (maze[x][y+1]) {
			vx = 0;
			vy = 1;
			path+="R";
		}
		else if (maze[x-1]&&maze[x-1][y]) {
			vx = -1;
			vy = 0;
			if (maze[x][y-1] || maze[x][y+1]) {
				path+="S";
			}
		}
		else if (maze[x][y-1]) {
			vx = 0;
			vy = -1;
			path+="L";
		}
		else if (maze[x+1]&&maze[x+1][y]) {
			vx = 1;
			vy = 0;
			path+="U";
		}
	}
	path = ''; // ignore
	return [vx, vy];
}


/*
Left hand rule cases:
LUR = U
LUS = R
RUL = U
SUL = R
SUS = U
LUL = S
*/